#pragma once

#include <boost/filesystem/path.hpp>

struct ExternalLink
{
	//
	// Public members.
	//
public:
	//! Offset of link start in section.
	size_t offset_;
	//! Id of destination external section.
	unsigned short section_id_;
	//! Id of entry from external section.
	unsigned short entry_id_;
};

struct ImportLib
{
	//! Offset of import library name.
	size_t name_offset_;
	//! Array of function names offsets.
	size_t functions[1];
};

struct ImportCall
{
	//! Offset of abs import call imm.
	size_t offset_;
	//! Id of import library.
	unsigned short lib_id_;
	//! Id of function in library.
	unsigned short func_id_;
};

class CodeSection
{
	//
	// Construction and destruction.
	//
private:
	//! Constructor.
	CodeSection(const std::string& data);
	//! Constructor.
	CodeSection(std::string&& data);

	//
	// Public interface.
	//
public:
	//! Reads code file and returns vector of sections.
	static std::vector<CodeSection> ReadCodeFile(const boost::filesystem::path& file_path);
	//! Reads string representation of code file and returns vector of sections.
	static std::vector<CodeSection> ReadCodeData(const std::string& file_data);

	//
	// Private methods.
	//
private:
	//! Returns code section created from code file data.
	static CodeSection SectionCodeFromCodeHeader(const std::string& data, size_t header_offset = 0);

	//
	// Public members.
	//
public:
	//! Section name.
	std::string name_;
	//! Section data.
	std::string data_;
	//! Section relocations.
	std::vector<ExternalLink> relocs_;
	//! Section exturnal calls.
	std::vector<ExternalLink> ext_calls_;
	//! Section import calls.
	std::vector<ImportCall> imp_calls_;
	//! Section entries.
	std::vector<uint32_t> entries_;
};