#pragma once

#pragma pack(push, 1)

struct CODE_FILE_HEADER
{
	char sig_[4];
	uint32_t ep_offset_;
	uint32_t ep_section_id_;
	uint32_t imports_offset_;
};

struct CODE_SECTION_HEADER
{
	char name_[8];
	uint32_t entries_offset_;
	uint32_t entries_size_;
	uint32_t relocs_offset_;
	uint32_t relocs_size_;
	uint32_t ext_calls_offset_;
	uint32_t ext_calls_size_;
	uint32_t imp_calls_offset_;
	uint32_t imp_calls_size_;
	uint32_t data_offset_;
	uint32_t data_size_;
};

#pragma pack(pop)
