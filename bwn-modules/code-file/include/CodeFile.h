#pragma once

#include <boost/filesystem/path.hpp>

#include "CodeSection.h"

class CodeFile
{
	//
	// Public aliases.
	//
public:
	//! List of functions names.
	using ImportFunctionsList = std::vector<std::string>;
	//! Name and functions of import library.
	using ImportLibrary = std::pair<std::string, ImportFunctionsList>;

	//
	// Public interface.
	//
public:
	//! Reads code file.
	void LoadCodeFile(const boost::filesystem::path& file_path);
	//! Reads code file data.
	void LoadCodeFileData(const std::string& file_data);
	//! Returns entry point offset.
	size_t GetEP() const;
	//! Returns section index of entry point.
	size_t GetEPSectionId() const;
	//! Returns begin and end of sections.
	const std::vector<CodeSection>& GetSections() const;
	//! Returns imports table.
	std::vector<ImportLibrary> GetImports() const;

	//
	// Private members.
	//
private:
	//! Code sections.
	std::vector<CodeSection> sections_;
	//! offset of entry point.
	size_t ep_offset_;
	//! Section index of entry point.
	size_t ep_section_id_;
	//! Imports of the file.
	std::vector<ImportLibrary> imports_;

};