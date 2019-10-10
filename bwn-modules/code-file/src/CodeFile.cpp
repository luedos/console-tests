#include "CodeFile.h"

#include <boost/filesystem.hpp>

#include "CodeFileStructs.h"

void CodeFile::LoadCodeFile(const boost::filesystem::path& file_path)
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

	LoadCodeFileData(data);
}

void CodeFile::LoadCodeFileData(const std::string& file_data)
{
	if (file_data.size() < sizeof(CODE_FILE_HEADER)) {
		throw std::runtime_error{ "Incorrect or old code file." };
	}

	CODE_FILE_HEADER header = *reinterpret_cast<const CODE_FILE_HEADER*>(&file_data[0]);

	if (std::strncmp(header.sig_, "CODE", 4)) {
		throw std::runtime_error{ "Incorrect or old code file." };
	}

	std::vector<CodeSection> temp_sections = CodeSection::ReadCodeData(file_data);

	if (header.ep_section_id_ >= temp_sections.size()) {
		throw std::runtime_error("Incorrect entry point id.");
	}

	ep_section_id_ = header.ep_section_id_;
	ep_offset_ = header.ep_offset_;

	imports_.clear();
	if (header.imports_offset_)
	{
		uint32_t import_offset = header.imports_offset_;

		while (true)
		{
			if (import_offset + sizeof(uint32_t) > file_data.size()) {
				throw std::runtime_error{ "Incorrect imports offset." };
			}

			uint32_t lib_offset = *reinterpret_cast<const uint32_t*>(&file_data[import_offset]);

			if (!lib_offset) {
				break;
			}

			if (lib_offset + sizeof(uint32_t) * 2 > file_data.size()) {
				throw std::runtime_error{ "Incorrect import library offset." };
			}
	
			ImportLibrary temp_import;
			{
				uint32_t lib_name_offset = *reinterpret_cast<const uint32_t*>(&file_data[lib_offset]);
				lib_offset += sizeof(uint32_t);

				if (!lib_name_offset || lib_name_offset + sizeof(uint32_t) > file_data.size()) {
					throw std::runtime_error{ "Incorrect import library name offset." };
				}

				temp_import.first = reinterpret_cast<const char*>(&file_data[lib_name_offset]);
			}

			while (true)
			{
				if (lib_offset + sizeof(uint32_t) > file_data.size()) {
					throw std::runtime_error{ "Incorrect import library offset." };
				}

				uint32_t func_name_offset = *reinterpret_cast<const uint32_t*>(&file_data[lib_offset]);

				if (!func_name_offset) {
					break;
				}

				if (func_name_offset + 1 > file_data.size()) {
					throw std::runtime_error{ "Incorrect import function name offset." };
				}

				temp_import.second.push_back(reinterpret_cast<const char*>(&file_data[func_name_offset]));

				lib_offset += sizeof(uint32_t);
			}

			imports_.push_back(std::move(temp_import));

			import_offset += sizeof(uint32_t);
		}
	}

	sections_ = std::move(temp_sections);
}

size_t CodeFile::GetEP() const
{
	return ep_offset_;
}

size_t CodeFile::GetEPSectionId() const
{
	return ep_section_id_;
}

const std::vector<CodeSection>& CodeFile::GetSections() const
{
	return sections_;
}

std::vector<CodeFile::ImportLibrary> CodeFile::GetImports() const
{
	return imports_;
}
