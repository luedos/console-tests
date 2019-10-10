#include "CodeSection.h"
#include "CodeFileStructs.h"

#include <boost/filesystem.hpp>


CodeSection::CodeSection(const std::string& data)
	: data_{ data }
{}

CodeSection::CodeSection(std::string&& data)
	: data_{ std::move(data) }
{}

std::vector<CodeSection> CodeSection::ReadCodeFile(const boost::filesystem::path& file_path)
{
	boost::filesystem::ifstream file(file_path, std::ios::in | std::ios::binary);

	if (!file) {
		throw std::runtime_error{ ("Can't open file \"" + file_path.string() + "\".").data() };
	}

	std::string data;

	file.seekg(0, std::ios::end);
	data.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return ReadCodeData(data);
}

std::vector<CodeSection> CodeSection::ReadCodeData(const std::string& file_data)
{
	if (file_data.size() < sizeof(CODE_FILE_HEADER) + sizeof(uint32_t) /*at least one header ptr*/) {
		throw std::runtime_error{ "Incorect or old code file." };
	}

	CODE_FILE_HEADER header = *reinterpret_cast<const CODE_FILE_HEADER*>(&file_data[0]);

	if (std::strncmp(header.sig_, "CODE", 4)) {
		throw std::runtime_error{ "Incorect or old code file." };
	}

	std::vector<CodeSection> out;
	out.reserve(3);

	const size_t* headers_arr = reinterpret_cast<const size_t*>(&file_data[sizeof(CODE_FILE_HEADER)]);

	for (size_t i = 0; headers_arr[i]; ++i) 
	{
		out.push_back(SectionCodeFromCodeHeader(file_data, headers_arr[i]));

		if (sizeof(CODE_FILE_HEADER) + (i + 1) * sizeof(size_t) >= file_data.size()) {
			throw std::runtime_error{ "Incorect code file, not enough data." };
		}
	}

	return out;
}

CodeSection CodeSection::SectionCodeFromCodeHeader(const std::string& data, size_t header_offset)
{
	if (data.size() < header_offset + sizeof(CODE_SECTION_HEADER)) {
		throw std::runtime_error{ "Not enough data for code section header." };
	}

	CODE_SECTION_HEADER header = *reinterpret_cast<const CODE_SECTION_HEADER*>(&data[header_offset]);

	if (data.size() < header_offset + header.data_offset_ + header.data_size_) {
		throw std::runtime_error{ "Not enough data for code section data." };
	}

	CodeSection out{ std::string(
						 data.begin() + (header_offset + header.data_offset_),
						 data.begin() + (header_offset + header.data_offset_ + header.data_size_))};

	out.name_ = header.name_[sizeof(header.name_) / sizeof(header.name_[0]) - 1]
						   ? std::string(reinterpret_cast<const char*>(header.name_), sizeof(header.name_) / sizeof(header.name_[0]))
						   : std::string(reinterpret_cast<const char*>(header.name_));

	if (header.entries_offset_) {
		if (data.size() < header_offset + header.entries_offset_ + header.entries_size_ * sizeof(uint32_t)) {
			throw std::runtime_error{ "Not enough data for code section entries." };
		}

		out.entries_.reserve(header.entries_size_);

		const uint32_t* entries = reinterpret_cast<const uint32_t*>(&data[header_offset + header.entries_offset_]);
		for (size_t i = 0; i < header.entries_size_; ++i) {
			out.entries_.push_back(entries[i]);
		}
	}

	if (header.relocs_offset_) {
		if (data.size() < header_offset + header.relocs_offset_ + header.relocs_size_ * sizeof(ExternalLink)) {
			throw std::runtime_error{ "Not enough data for code section relocations." };
		}

		out.relocs_.reserve(header.relocs_size_);

		const ExternalLink* relocs = reinterpret_cast<const ExternalLink*>(&data[header_offset + header.relocs_offset_]);
		for (size_t i = 0; i < header.relocs_size_; ++i) {
			out.relocs_.push_back(relocs[i]);
		}
	}

	if (header.ext_calls_offset_) 
	{
		if (data.size() < header_offset + header.ext_calls_offset_ + header.ext_calls_size_ * sizeof(ExternalLink)) {
			throw std::runtime_error{ "Not enough data for code section exturnal calls." };
		}

		out.ext_calls_.reserve(header.ext_calls_size_);

		const ExternalLink* calls = reinterpret_cast<const ExternalLink*>(&data[header_offset + header.ext_calls_offset_]);
		for (size_t i = 0; i < header.ext_calls_size_; ++i) {
			out.ext_calls_.push_back(calls[i]);
		}
	}

	if (header.imp_calls_offset_)
	{
		if (data.size() < header_offset + header.imp_calls_offset_ + header.imp_calls_size_ * sizeof(ImportCall)) {
			throw std::runtime_error{ "Not enough data for code section import calls." };
		}

		out.imp_calls_.reserve(header.imp_calls_size_);

		const ImportCall* calls = reinterpret_cast<const ImportCall*>(&data[header_offset + header.imp_calls_offset_]);
		for (size_t i = 0; i < header.imp_calls_size_; ++i) {
			out.imp_calls_.push_back(calls[i]);
		}
	}

	return out;
}