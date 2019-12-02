#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

//
// Asmjit "FU" includes.
//
//#include "asmjit/asmjit.h"

#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING

//
// STD includes.
//
#if defined(_WIN32)
//#include <Windows.h>
//#include <winnt.h>
//#include <WinUser.h>
#endif
//#include <ctime>
//#include <codecvt>
//#include <fstream>
#include <iostream>
//#include <iomanip>
//#include <random>
//#include <memory>
//#include <string>
//#include <array>
//#include <list>
//#include <forward_list>
//#include <vector>
//#include <assert.h>
//#include <experimental/filesystem>
//#include <regex>
//#include <thread>
#include <chrono>
//#include <functional>
//#include <string_view>
#include <experimental/string_view>

//
// Boost includes.
//
//#include <boost/optional.hpp>
//#include <boost/optional/optional_io.hpp>
//#include <boost/exception/all.hpp>
//#include <boost/smart_ptr.hpp>
//#include <boost/random.hpp>
//#include <boost/scoped_array.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>
//#include <boost/process.hpp>
//#include <boost/program_options.hpp>
//#include <boost/algorithm/algorithm.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/random.hpp>
//#include <boost/utility/string_view.hpp>

//
// Personal includes
//
//#include "Invoke.h"
//#include "TestOne/TestOne.h"
#include "Utilits.h"
//#include "Node.h"
//#include "Parser.h"
//#include "PRJG/PRJG.h"
//#include "imports-data/Structs.h"
//#include "PRNG.h"
//#include "../../pe-packer-furtherwork/pe-packer-lib/src/Unpacker/UnUnpacker-devalloc.h"
#include "units-declarations.h"
//#include "code-file/CodeFile.h"
//#include "distorm-wrapper/DistormWrapper.h"
//#include "dll-main.h"
//#include "IteratorWrapper.h"
//#include "NumeralSystem.h"
#include "TypeTreat.h"

//
// Additional libs includes.
//
//#include <xlnt/xlnt.hpp>
//#include "xlslib.h"

//#include <lzo/lzo1z.h>

//#include "distorm.h"
//#include "mnemonics.h"

//#include <pe_bliss.h>
//#include <pe_resource_manager.h>

//#include <json/json.h>

//#include <fmt/format.h>

//#include "lodepng.h"
//#include "libnsbitmap\libnsbmp.h"
//#include "eazybmp\EasyBMP.h"

//#include <atlimage.h>

//#include "asmpure/casmpure.h"

//#include "Timer\BwnTimer.h"
//#include "Timer\BwnWinTimer.h"
//#include "Timer\WinTimer.h"

//#include <magic_enum.hpp>

// Print as hex
#if false
void PrintAsHex(const std::string& data, size_t start_offset = 0)
{
	if (start_offset >= data.size())
	{
		std::cout << "Length : 0" << std::endl;
		return;
	}

	for (size_t i = 0; i < data.size() - start_offset; ++i)
	{
		const size_t offset = start_offset + i;

		if (i && !(i % 16)) {
			std::cout << "    ";
			for (auto it = data.begin() + (offset - 16); it != data.begin() + offset; ++it)
			{
				if (*it < 32 || *it > 126) {
					std::cout << bwn::console_color(bwn::console_color::DARKPURPLE) << '.' << bwn::console_color::reset;
				}
				else {
					std::cout << *it;
				}
			}
			std::cout << std::endl;
		}
	
		if (!(i % 16)) {
			std::cout << "0x" << std::setw(((data.size() > 0xFFFF) + 1) * 4) << std::setfill('0') << std::right << std::hex << i << "  " << std::dec;
		}
		
		//std::cout << std::setw((i % 4) != 3 ? 5 : 8) << std::left << static_cast<int>(static_cast<BYTE>(data[i]));

		if (data[offset]) {
			std::cout << std::hex << std::setw(2) << std::setfill('0')
					  << static_cast<int>(static_cast<unsigned char>(data[offset])) << std::dec << " ";
		}
		else {
			std::cout << bwn::console_color(bwn::console_color::DARKPURPLE) << "00 " << bwn::console_color::reset;
		}

		//if (data[i]) {
		//	std::cout << data[i];
		//}
		//else {
		//	ColorPrint(0x05, '0');
		//}
		//if ((i % 4) == 3) {
		//	std::cout << "    ";
		//}
	}

	size_t total = data.size() % 16;
	if (!total) {
		total = 16;
	}
	std::cout << std::string((16 - total) * 3 + 4, ' ');
	for (auto it = data.end() - total; it != data.end(); ++it)
	{
		if (*it < 32 || *it > 126)
		{
			std::cout << bwn::console_color(bwn::console_color::DARKPURPLE) << '.' << bwn::console_color::reset;
		}
		else
		{
			std::cout << *it;
		}
	}
	std::cout << std::endl;
	std::cout << "Length : " << data.size() << std::endl;
}
#endif // Print as hex

// Randomizer
#if false
namespace randomizer
{

size_t rnd()
{
	static std::mt19937 gen{ static_cast<size_t>(std::time(0)) };

	return gen();
}

}
#endif // Randomizer

// Directories statistics
#if false
#include "dirs-statistics/Structs.h"

const char* DirsArr[]
{
	"EXPORT",			// 0   // Export Directory
	"IMPORT",			// 1   // Import Directory
	"RESOURCE",			// 2   // Resource Directory
	"EXCEPTION",		// 3   // Exception Directory
	"SECURITY",			// 4   // Security Directory
	"BASERELOC",		// 5   // Base Relocation Table
	"DEBUG",			// 6   // Debug Directory
	"ARCHITECTURE",		// 7   // Architecture Specific Data
	"GLOBALPTR",		// 8   // RVA of GP
	"TLS",				// 9   // TLS Directory
	"LOAD_CONFIG",		//10   // Load Configuration Directory
	"BOUND_IMPORT",		//11   // Bound Import Directory in headers
	"IAT",				//12   // Import Address Table
	"DELAY_IMPORT",		//13   // Delay Load Import Descriptors
	"COM_DESCRIPTOR"	//14   // COM Runtime descriptor
};

void PrintDirs(const DirStat dirs[15], std::ostream* log)
{
	for (size_t i = 0; i < 15; ++i)
	{
		*log << DirsArr[i] << ":\n";

		auto stat = dirs[i].GetStatistic();

		for (size_t j = 0; j < stat.size(); ++j) {
			*log << "\t" << stat[j].second << "\t" << stat[j].first << "\n";
		}
	}

	std::cout << std::endl;
}

bool WriteExe(DirStat dirs[15], boost::filesystem::path path)
{
	std::unique_ptr<pe_bliss::pe_base> image;

	{
		std::ifstream file(path.string(), std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open " << path << std::endl;
			return false;
		}

		try
		{
			image.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
		}
		catch (const pe_bliss::pe_exception& e)
		{
			std::cout << "Error creating pe_base : " << e.what() << std::endl;
			return false;
		}

		if (!image)
		{
			std::cout << "Image value wasn't initialized" << std::endl;
			return false;
		}

		if (image->get_pe_type() != pe_bliss::pe_type::pe_type_32)
		{
			std::cout << "File with architecture other than x32 can't be packed " << std::endl;
			return false;
		}

		if (image->is_dotnet())
		{
			std::cout << ".NEt image cannot be packed!" << std::endl;
			return false;
		}
	}

//#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
//#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
//#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
//#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
//#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
//#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
//#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//	//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
//#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
//#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
//#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
//#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
//#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
//#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
//#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
//#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor

	for (size_t i = 0; i < 15; ++i)
	{
		try
		{
			if (image->get_directory_rva(i))
			{
				std::string name = image->section_from_directory(i).get_name();

				dirs[i].AddSection(name);
			}
		}
		catch (const std::exception& e) {}
	}


	return true;
}
#endif // Directories statistics

// Imports statistics
#if false
bool SortByCount(const ImportFunc& left, const ImportFunc& right)
{
	return left.count_ > right.count_;
}

bool SortByName(const ImportFunc& left, const ImportFunc& right)
{
	return std::strcmp(left.name_.data(), right.name_.data()) > 0;
}

void PrintFunctions(const std::vector<ImportLib>& libs, std::ofstream* log = nullptr)
{
	for (size_t i = 0; i < libs.size(); ++i)
	{
		std::cout << "===================<" << libs[i].name_ << ">===================" << std::endl;

		if (log) {
			*log << "===================<" << libs[i].name_ << ">===================" << std::endl;
		}

		size_t max_count = 0;

		for (size_t ii = 0; ii < libs[i].funcs_.size(); ++ii)
		{
			if (libs[i].funcs_[ii].count_ > max_count) {
				max_count = libs[i].funcs_[ii].count_;
			}
		}

		max_count *= 0.7;

		for (size_t ii = 0; ii < libs[i].funcs_.size(); ++ii)
		{
			if (libs[i].funcs_[ii].count_ > max_count) {
				std::cout << '\t' << libs[i].funcs_[ii].count_ << '\t' << libs[i].funcs_[ii].name_ << std::endl;
			}
			if (log) {
				*log << '\t' << libs[i].funcs_[ii].count_ << '\t' << libs[i].funcs_[ii].name_ << std::endl;
			}
		}
		std::cout << "===================</" << libs[i].name_ << ">===================" << std::endl;
		if (log) {
			*log << "===================</" << libs[i].name_ << ">===================" << std::endl;
		}
	}
}

bool WriteExe(std::vector<ImportLib>& importLibs, boost::filesystem::path path)
{
	std::unique_ptr<pe_bliss::pe_base> image;

	{
		std::ifstream file(path.string(), std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open " << path << std::endl;
			return false;
		}

		try
		{
			image.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
		}
		catch (const pe_bliss::pe_exception& e)
		{
			std::cout << "Error creating pe_base : " << e.what() << std::endl;
			return false;
		}

		if (!image)
		{
			std::cout << "Image value wasn't initialized" << std::endl;
			return false;
		}

		if (image->get_pe_type() != pe_bliss::pe_type::pe_type_32)
		{
			std::cout << "File with architecture other than x32 can't be packed " << std::endl;
			return false;
		}

		if (image->is_dotnet())
		{
			std::cout << ".NEt image cannot be packed!" << std::endl;
			return false;
		}
	}


	pe_bliss::imported_functions_list imports = pe_bliss::get_imported_functions(*image);

	for (size_t i = 0; i < imports.size(); ++i)
	{
		for (size_t o = 0; o < importLibs.size(); ++o)
		{
			if (boost::iequals(importLibs[o].name_, imports[i].get_name()))
			{
				for (size_t I_f = 0; I_f < imports[i].get_imported_functions().size(); ++I_f)
				{
					bool find = false;

					for (size_t L_f = 0; L_f < importLibs[o].funcs_.size(); ++L_f)
					{
						if (importLibs[o].funcs_[L_f].name_ == imports[i].get_imported_functions()[I_f].get_name())
						{
							++importLibs[o].funcs_[L_f].count_;
							find = true;
							break;
						}
					}

					if (!find)
					{
						importLibs[o].funcs_.push_back({ imports[i].get_imported_functions()[I_f].get_name() , 1 });
					}
				}
				break;
			}
		}
	}

	return true;
}
#endif // Imports statistics

// File raw statistics
#if false
const char* StandartSections[]
{
	".text",
	".idata",
	".rsrc",
	".data",
	".rdata",
	".reloc"
};

typedef struct Settings
{
	bool entropy_ = true;
	bool sections_ = true;
};

typedef struct SectionStats
{
	std::string name_;

	size_t vSize_;
	size_t rSize_;
};

typedef struct FileStats
{
	std::string name_;
	float entropy_ = 0;
	std::vector<SectionStats> sections_;

	size_t notStandartSections_ = 0;

};

bool WriteExe(FileStats& stats, boost::filesystem::path path)
{
	std::unique_ptr<pe_bliss::pe_base> image;

	{
		std::ifstream file(path.string(), std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open " << path << std::endl;
			return false;
		}

		try
		{
			image.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
		}
		catch (const pe_bliss::pe_exception& e)
		{
			std::cout << "Error creating pe_base : " << e.what() << std::endl;
			return false;
		}

		if (!image)
		{
			std::cout << "Image value wasn't initialized" << std::endl;
			return false;
		}

		if (image->get_pe_type() != pe_bliss::pe_type::pe_type_32)
		{
			std::cout << "File with architecture other than x32 can't be packed " << std::endl;
			return false;
		}

		if (image->is_dotnet())
		{
			std::cout << ".NEt image cannot be packed!" << std::endl;
			return false;
		}
	}

	stats.name_ = path.filename().string();

	stats.entropy_ = pe_bliss::entropy_calculator::calculate_entropy(*image);

	for (size_t i = 0; i < image->get_image_sections().size(); ++i)
	{
		stats.sections_.push_back({
			image->get_image_sections()[i].get_name(),
			image->get_image_sections()[i].get_virtual_size(),
			image->get_image_sections()[i].get_size_of_raw_data() });

		{
			bool find = false;

			for (size_t ii = 0; ii < sizeof(StandartSections) / sizeof(*StandartSections); ++ii)
			{
				if (stats.sections_.back().name_ == StandartSections[ii])
				{
					find = true;
					break;
				}
			}

			if (!find)
			{
				stats.notStandartSections_++;
			}
		}
	}

	return true;
}

void PrintExes(const std::vector<FileStats>& files, const Settings& settings, std::ostream& stream)
{
	stream << "Number of exe tested : " << files.size() << std::endl; 

	for (auto fp = files.begin(); fp < files.end(); ++fp)
	{
		stream << "File : " << fp->name_ << std::endl;

		if (settings.entropy_) {
			stream << "\tEntropy : " << fp->entropy_ << std::endl;
		}

		stream << "\tSections : " << std::endl;
		stream << "\tSections number : " << fp->sections_.size() << std::endl;
		stream << "\tNot standart sections number : " << fp->notStandartSections_ << std::endl;

		if (settings.sections_)
		{
			size_t totalVSize = 0;
			size_t totalRSize = 0;

			for (auto sp = fp->sections_.begin(); sp < fp->sections_.end(); ++sp)
			{
				totalVSize += sp->vSize_;
				totalRSize += sp->rSize_;
			}

			for (auto sp = fp->sections_.begin(); sp < fp->sections_.end(); ++sp)
			{
				stream << "\t\t" << sp->name_
					<< "\n\t\tVSize : 0x" << std::hex << sp->vSize_ << std::dec << " | " << sp->vSize_ << " | " << ((float)sp->vSize_ * 100) / totalVSize << "%"
					<< "\n\t\tRSize : 0x" << std::hex << sp->rSize_ << std::dec << " | " << sp->rSize_ << " | " << ((float)sp->rSize_ * 100) / totalRSize << "%"
					<< std::endl;
			}
		}
	}
}
#endif // File raw statistics

// Icon randomizing
#if false
struct BWN_ICON_HEADER
{
	WORD reserved;
	WORD type;
	WORD imageNum;
};

struct BWN_ICON_DIRECTORY
{
	BYTE width;
	BYTE height;
	BYTE colorCount;
	BYTE reserved;
	WORD colorPlanes;
	WORD bpp;
	DWORD bitmapSize;
	DWORD offset;
};


std::string RandomizeBMP(const std::string& data)
{	
	if (data.size() < sizeof(BITMAPINFOHEADER)) {
		throw std::exception{ "Icon is not bmp" };
	}

	BITMAPINFOHEADER image_info = *reinterpret_cast<const BITMAPINFOHEADER*>(&data[0]);

	if (sizeof(image_info) != image_info.biSize) {
		throw std::exception{ "Wrong (or old) \"BITMAPINFOHEADER\"" };
	}

	if (data.size() < image_info.biSizeImage + sizeof(BITMAPINFOHEADER)) {
		throw std::exception{ "Wrong icon size, or not enough data was given" };
	}

	if (image_info.biCompression) {
		throw std::exception{ "Compression can't be randomize yet" };
	}

	if (image_info.biBitCount != 32)
	{
		throw std::exception{ "Wrong colors number" };
	}

	std::string out = data;	

	std::time_t now = std::time(0);
	boost::random::mt19937 gen = boost::random::mt19937{ static_cast<std::uint32_t>(42) };
	
	DWORD* pixels_arr = reinterpret_cast<DWORD*>(&out[sizeof(BITMAPINFOHEADER)]);

	std::cout << "randomizing image..." << std::endl;

	for (size_t i = 0; i < (image_info.biSizeImage / 4); ++i)
	{
		if (pixels_arr[i] & 0xFF000000)
			pixels_arr[i] = (pixels_arr[i] & 0xFF000000) | (gen() & 0x00FFFFFF);
	}

	return out;
}



std::string RandomizePNG(const std::string& data)
{
	std::string out;
	size_t width, height;

	std::cout << "decoding image..." << std::endl;
	{
		lodepng::State state;

		unsigned error = lodepng::decode(out, width, height, state,data);


		if (error) {
			throw std::exception{ lodepng_error_text(error) };
		}
	}

	std::cout << "randomizing image..." << std::endl;
	{
		std::time_t now = std::time(0);
		boost::random::mt19937 gen = boost::random::mt19937{ static_cast<std::uint32_t>(now) };

		DWORD* pixels_arr = reinterpret_cast<DWORD*>(&out[0]);

		for (size_t i = 0; i < (out.size() / 4); ++i)
		{
			if (pixels_arr[i] & 0xFF000000)
				pixels_arr[i] = (pixels_arr[i] & 0xFF000000) | (gen() & 0x00FFFFFF);
		}
	}

	std::cout << "encoding image..." << std::endl;
	{
		unsigned error = lodepng::encode(out, out, width, height);

		if (error) {
			throw std::exception{ lodepng_error_text(error) };
		}
	}
	
	return out;
}
#endif // Icon randomizing

// asmjit
#if false
class PrintingErrorHandler : public asmjit::ErrorHandler
{
public:
	// Return `true` to set last error to `err`, return `false` to do nothing.
	void handleError(asmjit::Error, const char* message, asmjit::BaseEmitter*) override
	{
		std::cout << "Asmjit error : " << message << std::endl;
	}
};
#endif // asmjit

// Icon encryption
#if false
std::string IconEncrypt(const std::string& src, const std::string& key)
{
	size_t outSize = (src.size() * 2);

	outSize = outSize - outSize % sizeof(DWORD) + sizeof(DWORD);

	size_t width = std::ceil(std::sqrt(outSize / 4));
	if (width < 16) {
		width = 16;
	}
	size_t height = width;

	outSize = width * height * sizeof(DWORD);

	BITMAPINFOHEADER info;
	info.biWidth = width;
	info.biHeight = height;
	info.biSizeImage = width * height;
	info.biBitCount = 32;
	info.biPlanes = 1;
	info.biCompression = BI_RGB;
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biXPelsPerMeter = 100;
	info.biYPelsPerMeter = 100;
	info.biClrImportant = 0;
	info.biClrUsed = 0;

	std::string out;
	out.resize(sizeof(BITMAPINFOHEADER));

	*reinterpret_cast<BITMAPINFOHEADER*>(&out[0]) = info;

	out.reserve(out.size() + outSize);


	typedef struct {
		WORD x;			// x coordinate
		WORD y;			// y coordinate
		DWORD r_sq;		// radius squared
		DWORD clr;		// color
	} Circle;

	std::vector<Circle> circles;
	{
		boost::random::mt19937 gen{ static_cast<std::uint32_t>(std::time(0)) };

		size_t amount = gen() % 3 + 4;
		for (; amount > 0; --amount)
		{
			Circle temp;
			temp.x = gen() % width;
			temp.y = gen() % height;

			temp.r_sq = gen() % (width < height ? width : height);

			temp.clr = gen() & 0xFFFFFF00 + 0xFF;

			//for (size_t i = 0; i < 4; ++i) {
			//	temp.clr &= ~(0x0F << (i * 8));
			//}
			circles.push_back(temp);
		}
	}


	size_t i = 0;
	for (; i < src.size(); i += 2)
	{

		DWORD color = 0xFFFFFFFF;

		//{
		//	size_t x = (i / 2) % width;
		//	size_t y = (i / 2) / width;
		//
		//	for (auto it = circles.begin(); it < circles.end(); ++it)
		//	{
		//		int x_dif = static_cast<int>(x) - static_cast<int>(it->x);
		//		int y_dif = static_cast<int>(y) - static_cast<int>(it->y);
		//
		//		if (x_dif * x_dif + y_dif * y_dif < it->r_sq)
		//		{
		//			color = it->clr;
		//			break;
		//		}
		//	}
		//}

		if (i < src.size())
		{
			unsigned char encrypted = src[i] ^ key[i % key.size()];

			color = (color & 0xF0FFFFFF) | ((encrypted & 0xF0) << 20);
			color = (color & 0xFFF0FFFF) | ((encrypted & 0x0F) << 16);
		}

		if (i + 1 < src.size())
		{
			char encrypted = src[i + 1] ^ key[(i + 1) % key.size()];

			color = (color & 0xFFFFF0FF) | ((encrypted & 0xF0) << 4);
			color = (color & 0xFFFFFFF0) | ((encrypted & 0x0F));
		}

		{
			size_t offset = out.size();
			out.resize(offset + sizeof(DWORD));
			*reinterpret_cast<DWORD*>(&out[offset]) = color;
		}
	}

	if (i * 2 < outSize)
	{
		for (; i * 2 < outSize; i += 2)
		{
			DWORD color = 0;

			{
				size_t x = (i / 2) % width;
				size_t y = (i / 2) / width;

				for (auto it = circles.begin(); it < circles.end(); ++it)
				{
					int x_dif = static_cast<int>(x) - static_cast<int>(it->x);
					int y_dif = static_cast<int>(y) - static_cast<int>(it->y);

					if (x_dif * x_dif + y_dif * y_dif < it->r_sq)
					{
						color = it->clr;
						break;
					}
				}
			}

			{
				size_t offset = out.size();
				out.resize(offset + sizeof(DWORD));
				*reinterpret_cast<DWORD*>(&out[offset]) = color;
			}
		}
	}

	return out;
}


void IconDecrypt(const char* src, const size_t destLen, char* dest, const char* key)
{
	size_t keyLen = 0;
	for (; keyLen < 16 && key[keyLen]; ++keyLen) {}

	src += sizeof(BITMAPINFOHEADER);

	for (size_t dest_i = 0; dest_i < destLen; dest_i += 2)
	{
		DWORD pixel = *reinterpret_cast<const DWORD*>(&src[dest_i * 2]);

		{
			char encrypted = 0;
			encrypted += (0x0F000000 & pixel) >> 20;
			encrypted += (0x000F0000 & pixel) >> 16;
			dest[dest_i] = encrypted ^ key[dest_i % keyLen];
		}

		if (dest_i + 1 < destLen)
		{
			char encrypted = 0;
			encrypted += (0x00000F00 & pixel) >> 4;
			encrypted += (0x0000000F & pixel);
			dest[dest_i + 1] = encrypted ^ key[(dest_i + 1) % keyLen];
		}
	}
}

void PrintSome(const std::string& input, size_t max = 0)
{
	std::cout << std::hex;
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (max && i >= max) {
			break;
		}

		if ((i % 16) == 0) {
			std::cout << std::endl;
		}

		std::cout << "0x"
			<< std::setw(2) << std::setfill('0')
			<< static_cast<unsigned long>(static_cast<unsigned char>(input[i]));

		std::cout << " ";
	}
	std::cout << std::dec << std::endl;
}
#endif // Icon encryption

// Regex
#if false
void PrintRegex(std::sregex_iterator it)
{
	std::sregex_iterator end;

	for (; it != end; ++it)
	{
		std::cout << "Match : " << std::endl;

		std::string res_str = it->str();

		std::cout << std::hex << ">>";
		for (size_t ii = 0; ii < res_str.size(); ++ii) {
			std::cout
				<< " 0x" << std::setw(2) << std::setfill('0')
				<< static_cast<unsigned long>(static_cast<unsigned char>(res_str[ii]));
		}
		std::cout << std::dec << std::endl;

		std::cout << ">> \"" << res_str << '\"';

		std::cout << "\n>>\tReg pos : " << it->position()
			<< "\n>>\tReg size : " << it->length() << std::endl;
	}


}
#endif // Regex

// Encryptions
#if false
#define XOR_ENC_BLANK_PLUS 12
#define XOR_ENC_BLANKSIZE_PLUS 12

std::string XorEncrypt(const std::string& src, const std::string& key)
{
	std::string out;
	out.reserve(src.size());

	size_t blank = 0;
	size_t blankSize = 0;

	size_t keySize = key.size();

	for (size_t i = 0; i < src.size(); i++)
	{
		char encrypted = src[i] ^ key[i % keySize];

		out.push_back(encrypted);

		{
			size_t size_test = (encrypted >> 2) & 0xF;

			if (size_test < 4 && keySize > 5) {
				--keySize;
			}
			else if (size_test > 12 && keySize < key.size()) {
				++keySize;
			}
		}

		if (blank == 0)
		{
			blank = ((encrypted & 0x0E) >> 1) + XOR_ENC_BLANK_PLUS;
			blankSize = ((encrypted & 0x70) >> 4) + XOR_ENC_BLANKSIZE_PLUS;

			//size_t randomSize1 = static_cast<size_t>(std::ceil(0.05 * blankSize));
			//size_t randomSize2 =
			//	randomSize1 + randomizer::rnd() % randomSize1;
			//randomSize1 = randomSize1 + randomizer::rnd() % randomSize1;
			//
			//randomSize1 = 1;
			//randomSize2 = 1;

			for (size_t ii = 0; ii < blankSize; ++ii)
			{
				//if (ii < randomSize1 || ii >= blankSize - randomSize2) {
				//	out.push_back(randomizer::rnd() % 225 + 15);
				//}
				//else {
					out.push_back(0x00);
				//}
			}
		}
		else
		{
			--blank;
		}
	}

	return out;
}

static void XorDecrypt(const char* src, const size_t destLen, char* dest, const char* key)
{
	size_t keyLen = 0;
	for (; keyLen < 16 && key[keyLen]; ++keyLen) {}

	size_t keySize = keyLen;

	size_t blank = 0;

	for (size_t srci = 0, desti = 0; desti < destLen; ++desti, ++srci)
	{
		dest[desti] = src[srci] ^ key[desti % keySize];

		{
			size_t size_test = (src[srci] >> 2) & 0xF;

			if (size_test < 4 && keySize > 5) {
				--keySize;
			}
			else if (size_test > 12 && keySize < keyLen) {
				++keySize;
			}
		}

		if (blank == 0)
		{
			blank = ((src[srci] & 0x0E) >> 1) + XOR_ENC_BLANK_PLUS;
			srci += ((src[srci] & 0x70) >> 4) + XOR_ENC_BLANKSIZE_PLUS;
		}
		else
		{
			--blank;
		}
	}
}

std::string QwordSimpleEncrypt(const std::string& data, const std::string& key, DWORD delta)
{
	std::string out = data;

	DWORD k0;
	DWORD k1;
	DWORD k2;
	DWORD k3;

	{
		const DWORD* key_arr = reinterpret_cast<const DWORD*>(key.data());
		k0 = key_arr[0];
		k1 = key_arr[1];
		k2 = key_arr[2];
		k3 = key_arr[3];
	}

	DWORD qwordLength = (data.size() + 7) / 8;
	out.resize(qwordLength * 8, 0);

	DWORD* dataUint = reinterpret_cast<DWORD*>(&out[0]);

	for (size_t n = 0; n < qwordLength; dataUint += 2, n++)
	{
		DWORD v0 = dataUint[0];
		DWORD v1 = dataUint[1];
		DWORD sum = 0;

		for (DWORD i = 0; i < 32; i++)
		{
			sum += delta;
			v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
			v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		}

		dataUint[0] = v0;
		dataUint[1] = v1;

	}

	return out;
}

void QwordSimpleDecrypt(const char* source, char* dest, DWORD destLen, const char key[16], DWORD delta)
{
	DWORD k0;
	DWORD k1;
	DWORD k2;
	DWORD k3;

	{
		const DWORD* key_arr = reinterpret_cast<const DWORD*>(key);
		k0 = key_arr[0];
		k1 = key_arr[1];
		k2 = key_arr[2];
		k3 = key_arr[3];
	}

	const DWORD* srcUint = reinterpret_cast<const DWORD*>(source);
	DWORD* destUint = reinterpret_cast<DWORD*>(dest);

	DWORD qwordLength = (destLen + 7) / 8;

	for (size_t n = 0; n < qwordLength; srcUint += 2, destUint += 2, n++)
	{
		DWORD sum = delta * 32;

		DWORD v0 = srcUint[0];
		DWORD v1 = srcUint[1];

		for (int i = 0; i < 32; i++)
		{
			v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
			v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);

			sum -= delta;
		}

		destUint[0] = v0;
		destUint[1] = v1;
	}
}

std::string QwordEncrypt(const std::string& data, const std::string& key, DWORD delta)
{
	std::string encrypted = QwordSimpleEncrypt(data, key, delta);

	std::string out;
	out.reserve(encrypted.size() + (encrypted.size() / XOR_ENC_BLANK_PLUS) * XOR_ENC_BLANKSIZE_PLUS);

	size_t blank = 0;
	size_t blankSize = 0;

	for (size_t i = 0; i < encrypted.size(); i++)
	{
		char encryptedChar = encrypted[i] ^ key[i % 16];

		out.push_back(encrypted[i]);

		if (blank == 0)
		{
			blank = ((encryptedChar & 0x0E) >> 1) + XOR_ENC_BLANK_PLUS;
			blankSize = ((encryptedChar & 0x70) >> 4) + XOR_ENC_BLANKSIZE_PLUS;

			//size_t randomSize1 = static_cast<size_t>(std::ceil(0.1 * blankSize));
			//size_t randomSize2 = randomSize1 + randomizer::Randomizer::GetRandomizer()() % randomSize1;
			//randomSize1 = randomSize1 + randomizer::Randomizer::GetRandomizer()() % randomSize1;

			for (size_t ii = 0; ii < blankSize; ++ii)
			{
				//if (ii < randomSize1 || ii >= blankSize - randomSize2) {
				//	out.push_back(randomizer::Randomizer::GetRandomizer()() % 256);
				//}
				//else {
					out.push_back(0x00);
				//}
			}
		}
		else
		{
			--blank;
		}
	}

	return out;
}

void QwordDecrypt(const char* source, char* dest, DWORD destLen, const char key[16], DWORD delta)
{
	size_t blank = 0;
	size_t desti = 0;

	destLen = ((destLen + 7) / 8) * 8;

	for (size_t srci = 0; desti < destLen; ++desti, ++srci)
	{
		dest[desti] = source[srci];
		char encryptedChar = dest[desti] ^ key[desti % 16];

		if (blank == 0)
		{
			blank = ((encryptedChar & 0x0E) >> 1) + XOR_ENC_BLANK_PLUS;
			srci += ((encryptedChar & 0x70) >> 4) + XOR_ENC_BLANKSIZE_PLUS;
		}
		else
		{
			--blank;
		}
	}

	QwordSimpleDecrypt(dest, dest, destLen, key, delta);
}




void DecryptMaskAsStrings(const char* src, char* dest, size_t destLen, const char* key)
{
	size_t keyLen = 0;
	for (; keyLen < 16 && key[keyLen]; ++keyLen);

	encryption::PRNG gen;
	{
		size_t seed = 0;

		for (size_t i = 0; i < keyLen; ++i) {
			seed ^= key[i] << ((i % 4) * 8);
		}

		encryption::InitPRNG(gen, seed);
	}

	bool isPaths = encryption::PRNGGenerate(gen) % 100 < 30;

	size_t deviderChance = 2;
	size_t endingChance = 10;

	for (size_t halfi = 0, srci = 0; halfi < (destLen * 2); ++srci, ++halfi)
	{
		char dest_item = dest[halfi / 2] & (0x0f << ((!(halfi % 2)) * 4));
		dest_item |= (0x0f & src[srci]) << ((halfi % 2) * 4);

		dest[halfi / 2] = dest_item;


		size_t test = encryption::PRNGGenerate(gen);

		if ((test & 0x0000FFFF) % 100 < deviderChance) 
		{
			if ((test >> 16) % 100 < endingChance) 
			{
				if (!isPaths) {
					++srci;
				}
				srci += 4 - (srci + 1) % 4;
				endingChance = 10;
			}
			else 
			{
				++srci;
				endingChance += 8;
			}
			deviderChance = 2;
		}
		else
		{
			deviderChance += 2;
		}
	}
}


std::string EncryptMaskAsStrings(const std::string& code, const std::string& key)
{
	encryption::PRNG gen;
	{
		size_t seed = 0;

		for (size_t i = 0; i < key.size(); ++i) {
			seed ^= key[i] << ((i % 4) * 8);
		}

		encryption::InitPRNG(gen, seed);
	}

	std::string out;
	out.reserve(code.size() * 2 + 15);

	char head = 0x40;

	bool isPaths = encryption::PRNGGenerate(gen) % 100 < 30;

	size_t deviderChance = 2;
	size_t endingChance = 10;

	for (size_t i = 0; i < code.size() * 2; ++i)
	{
		char payload = ((code[i / 2] >> ((i % 2) * 4)) & 0x0F);

		if (!payload) {
			head |= 1 << 4;
		}

		out.push_back(head | payload);

		size_t test = encryption::PRNGGenerate(gen);

		if ((test & 0x0000FFFF) % 100 < deviderChance)
		{
			if ((test >> 16) % 100 < endingChance) 
			{
				if (!isPaths) {
					out.push_back('.');
				}

				out.resize(out.size() + 4 - out.size() % 4);
				endingChance = 10;
				head = 0x40;
			}
			else 
			{
				out.push_back(isPaths ? '/' : ' ');
				endingChance += 8;
				head = 0x60;
			}
			deviderChance = 2;
		}
		else 
		{
			head = 0x60;
			deviderChance += 2;
		}
	}

	if (out.size() && out.back()) {
		out.resize(out.size() + 4 - out.size() % 4);
	}

	return out;
}
#endif // Encryptions

// Random not random sequences
#if false
double GetNumberWithin(double max = 1, double min = 0, size_t pow = 8)
{
	if (min >= max) {
		max = min + 1;
	}

	if (pow < 1) {
		pow = 1;
	}
	else if (pow > 50) {
		pow = 50;
	}
	
	double ballancer = (0.000015 * std::pow(pow, 3) - 0.001671 * std::pow(pow, 2) + 0.063739 * pow - 0.03) * 1000;
	return (std::clamp<double>(std::pow((static_cast<double>(1000) / ((randomizer::rnd() % 1000) + ballancer)), pow) + 0.97, 0, 999.99) / 1000) * (max - min) + min;
}


template<typename T>
struct ChanceBlock
{
	//
	// Public members.
	//
public:
	T item_;
	int chance_;
};

size_t RandomizeChanceTable(
	std::vector<size_t>::const_iterator beg,
	std::vector<size_t>::const_iterator end)
{
	size_t total = 0;

	for (auto it = beg; it != end; ++it) {
		total += *it;
	}

	size_t chance;
	if (total == 0) {
		chance = 0;
	}
	else {
		chance = randomizer::rnd() % (static_cast<uint32_t>(std::ceil(total)));
	}

	total = 0;
	for (auto it = beg; it != end; ++it)
	{
		total += *it;

		if (total > chance) {
			return it - beg;
		}
	}

	return size_t(-1);
}

template<typename T>
size_t RandomizeChanceTable(
	const std::vector<ChanceBlock<T>>& chances)
{
	std::vector<size_t> table;
	table.reserve(chances.size());

	for (size_t i = 0; i < chances.size(); ++i) {
		table.push_back(std::abs(chances[i].chance_));
	}

	return RandomizeChanceTable(table.begin(), table.end());
}




class Sequence
{
	//
	// Construction and destruction.
	//
public:
	//! Destructor.
	virtual ~Sequence() = default;

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	virtual std::string GetSequence(size_t length) const = 0;
	//! Returns deep copy of object.
	virtual std::unique_ptr<Sequence> GetCopy() const = 0;
};

class AdderSequence : public Sequence
{
	//
	// Construction and destruction.
	//
public:
	AdderSequence(const std::vector<size_t>& adders = {});

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	std::string GetSequence(size_t length) const override;
	//! Returns deep copy of object.
	std::unique_ptr<Sequence> GetCopy() const;

	//
	// Private members.
	//
private:
	//! Adders.
	std::vector<size_t> adders_;
};

AdderSequence::AdderSequence(const std::vector<size_t>& adders)
	: adders_{ adders }
{
	if (adders_.size()) {
		return;
	}

	size_t count = static_cast<size_t>(GetNumberWithin(5, 1, 5));
	adders_.reserve(count);

	for (size_t i = 0; i < count; ++i) {
		adders_.push_back(static_cast<size_t>(GetNumberWithin(std::pow(0xFFFFFFFF, 0.65), 1, 4)));
	}
}

std::string AdderSequence::GetSequence(size_t length) const
{
	std::string out;
	out.reserve(length + 0x10);

	size_t item = 4 * static_cast<size_t>(GetNumberWithin(0xFFFFFFFE, 1, 2));

	for (size_t i = 0; out.size() < length; ++i)
	{
		out.resize(out.size() + sizeof(size_t));
		size_t* item_ptr = reinterpret_cast<size_t*>(&out[out.size() - sizeof(size_t)]);
		*item_ptr += item;

		item += adders_[i % adders_.size()];
	}

	return out;
}

std::unique_ptr<Sequence> AdderSequence::GetCopy() const
{
	return std::make_unique<AdderSequence>();
}


class MultiplyerSequence : public Sequence
{
	//
	// Construction and destruction.
	//
public:
	MultiplyerSequence(const std::vector<size_t>& multiplyers = {});

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	std::string GetSequence(size_t length) const override;
	//! Returns deep copy of object.
	std::unique_ptr<Sequence> GetCopy() const;

	//
	// Private members.
	//
private:
	//! Multiplyers.
	std::vector<size_t> multiplyers_;
};

MultiplyerSequence::MultiplyerSequence(const std::vector<size_t>& multiplyers)
	: multiplyers_{ multiplyers }
{
	if (multiplyers_.size()) {
		return;
	}

	size_t count = randomizer::rnd() % 3 + 2;
	multiplyers_.reserve(count);

	for (size_t i = 0; i < count; ++i) {
		multiplyers_.push_back(
			//static_cast<size_t>(GetNumberWithin(0x100, 11))
			(randomizer::rnd() % 0x100) | 1
		);
		//multiplyers_.back() = (multiplyers_.back() / 2) * 2 + 1;
	}
}

std::string MultiplyerSequence::GetSequence(size_t length) const
{
	std::string out;
	out.reserve(length + 0x10);
	size_t item = randomizer::rnd() & 0xFF << 16;
	size_t offset = 1;
	
	for (size_t i = 0; out.size() < length; ++i)
	{
		out.resize(out.size() + sizeof(size_t) - offset * (!!i));
		size_t* item_ptr = reinterpret_cast<size_t*>(&out[out.size() - sizeof(size_t)]);
		*item_ptr += item;

		item *= multiplyers_[i % multiplyers_.size()];
		if (!item) {
			item = 1;
		}
	}

	return out;
}

std::unique_ptr<Sequence> MultiplyerSequence::GetCopy() const
{
	return std::make_unique<MultiplyerSequence>();
}


class GridSequence : public Sequence
{
	//
	// Construction and destruction.
	//
public:
	GridSequence(size_t width = 0);

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	std::string GetSequence(size_t length) const override;
	//! Returns deep copy of object.
	std::unique_ptr<Sequence> GetCopy() const;

	//
	// Private members.
	//
private:
	//! Width of the grid.
	size_t width_;
};

GridSequence::GridSequence(size_t width)
	: width_{ width }
{
	if (width_) {
		return;
	}

	width_ = 8 << (randomizer::rnd() % 3);
}

std::string GridSequence::GetSequence(size_t length) const
{
	std::string out;
	out.reserve(length + 0x10);
	size_t item_size = randomizer::rnd() % 4 + 1;
	if (item_size == 3) {
		item_size = 2;
	}
	size_t left_item = static_cast<size_t>(GetNumberWithin(std::pow(0x100 << (item_size * 4), 0.7), 1));
	size_t beg_left_item = left_item;
	size_t right_item = static_cast<size_t>(GetNumberWithin(std::pow(0x100 << (item_size * 4), 0.7), 1));

	size_t left_adder = static_cast<size_t>(GetNumberWithin(std::pow(0x80 << (item_size * 4), 0.7), 1, 4));
	size_t right_adder = static_cast<size_t>(GetNumberWithin(std::pow(0x80 << (item_size * 4), 0.7), 1, 4));

	bool reverse = randomizer::rnd() % 100 < 30;

	size_t work_length = 0;

	for (size_t i = 0; work_length < length; ++i, work_length += item_size)
	{
		if (!(i % width_) && i)
		{
			right_item += right_adder;
			left_item = beg_left_item;
		}
		else {
			left_item += left_adder;
		}


		out.resize(work_length + sizeof(size_t));
		size_t* item_ptr = reinterpret_cast<size_t*>(&out[work_length]);
		*item_ptr = (((reverse ? right_item : left_item) << (item_size * 4)) 
			| ((reverse ? left_item : right_item) & ~((~0) << (item_size * 4))));
	}

	return out;
}

std::unique_ptr<Sequence> GridSequence::GetCopy() const
{
	return std::make_unique<GridSequence>();
}


static const std::vector<size_t> alphabet_chances
{
	816	 ,	// a 
	1270 ,	// e
	697	 ,	// i
	751	 ,	// o
	276	 ,	// u
	197	 ,	// y
	149	 ,	// b
	278	 ,	// c
	425	 ,	// d
	222	 ,	// f
	201	 ,	// g
	609	 ,	// h
	15	 ,	// j
	77	 ,	// k
	402	 ,	// l
	240	 ,	// m
	675	 ,	// n
	193	 ,	// p
	10	 ,	// q
	599	 ,	// r
	633	 ,	// s
	906	 ,	// t
	98	 ,	// v
	236	 ,	// w
	15	 ,	// x
	7	 	// z
};

static const char* letters_arr =
	"A"
	"E"
	"I"
	"O"
	"U"
	"Y"
	"B"
	"C"
	"D"
	"F"
	"G"
	"H"
	"J"
	"K"
	"L"
	"M"
	"N"
	"P"
	"Q"
	"R"
	"S"
	"T"
	"V"
	"W"
	"X"
	"Z"
	;


class StringSequence : public Sequence
{
	//
	// Construction and destruction.
	//
public:
	StringSequence(size_t alignment = 4);

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	std::string GetSequence(size_t length) const override;
	//! Returns deep copy of object.
	std::unique_ptr<Sequence> GetCopy() const;

	//
	// Private members.
	//
private:
	//! Text alignment.
	size_t alignment_;
};

StringSequence::StringSequence(size_t alignment)
	: alignment_{ alignment }
{
}

std::string StringSequence::GetSequence(size_t length) const
{
	std::string out;
	out.reserve(length);

	bool path = randomizer::rnd() % 100 < 25;
	bool lowercase = path;
	// a - 97
	// A - 65

	size_t deviderChance = 2;
	size_t endingChance = 10;

	size_t last_word = 0;
	int vowel = 0;

	for (; out.size() < length;)
	{
		size_t letter_index = 0;

		if (vowel > 1) {
			letter_index = 6 + RandomizeChanceTable(alphabet_chances.begin() + 6, alphabet_chances.end());
		}
		else if (vowel < -2) {
			letter_index = RandomizeChanceTable(alphabet_chances.begin(), alphabet_chances.begin() + 6);
		}
		else {
			letter_index = RandomizeChanceTable(alphabet_chances.begin(), alphabet_chances.end());
		}

		if (letter_index < 6) 
		{
			if (vowel > 0) {
				++vowel;
			}
			else {
				vowel = 1;
			}
		}
		else 
		{
			if (vowel < 0) {
				--vowel;
			}
			else {
				vowel = -1;
			}
		}

		out.push_back(letters_arr[letter_index] + 32 * lowercase);
		
		++last_word;

		if (randomizer::rnd() % 100 < deviderChance)
		{
			if (last_word == 1)
			{
				if (randomizer::rnd() % 100 < 30) {
					continue;
				}
				else {
					out.back() = 'A' + 32 * lowercase;
				}
			}

			if (randomizer::rnd() % 100 < endingChance)
			{
				if (!path) {
					out.push_back('.');
				}

				out.resize(out.size() + alignment_ - out.size() % alignment_);
				endingChance = 10;

				if (randomizer::rnd() % 100 < 10 + 15 * path) {
					path = !path;
				}

				lowercase = path;
			}
			else
			{
				if (path) 
				{
					if (last_word < 6 && randomizer::rnd() % 100 < 55) {
						out.push_back('_');
					}
					else {
						out.push_back('/');
					}
				}
				else {
					out.push_back(' ');
				}
				//out.push_back(path ? '/' : ' ');
				endingChance += 8;
				lowercase = true;
			}
			deviderChance = 2;

			last_word = 0;
			vowel = 0;
		}
		else
		{
			lowercase = true;
			deviderChance += 3;
		}

	}
	
	if (out.size() && out.back()) {
		out.resize(out.size() + alignment_ - out.size() % alignment_);
	}

	return out;
}

std::unique_ptr<Sequence> StringSequence::GetCopy() const
{
	return std::make_unique<StringSequence>();
}


class RandomBlanksSequence : public Sequence
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	RandomBlanksSequence(size_t stub = 3, size_t blank = 0x30);

	//
	// Public interface.
	//
public:
	//! Return generated sequence.
	std::string GetSequence(size_t length) const override;
	//! Returns deep copy of object.
	std::unique_ptr<Sequence> GetCopy() const;

	//
	// Private members.
	//
private:
	//! General stub size.
	size_t stub_;
	//! General blank size.
	size_t blank_;
};

RandomBlanksSequence::RandomBlanksSequence(size_t stub, size_t blank)
	: stub_{ stub }
	, blank_{ blank }
{
}

std::string RandomBlanksSequence::GetSequence(size_t length) const
{
	std::string out(length, '\0');
	for (size_t i = 0; i < out.size();)
	{
		size_t beg = i - i % 4;
		size_t rcount = randomizer::rnd() % stub_ + stub_ / 3;
		if (beg + rcount >= out.size()) {
			rcount = out.size() - beg - 1;
		}
		for (auto it = out.begin() + beg; it != out.begin() + beg + rcount; ++it) {
			*it = randomizer::rnd() % 225 + 15;
		}

		i += randomizer::rnd() % blank_ + blank_ / 3;
	}

	return out;
}

std::unique_ptr<Sequence> RandomBlanksSequence::GetCopy() const
{
	return std::make_unique<RandomBlanksSequence>();
}


class FalseSectionFactory
{
	//
	// Public enums.
	//
public:
	enum GenFlags
	{
		GEN_STRINGS			= 0x01,
		GEN_ADDERS			= 0x02,
		GEN_MULTIPLYERS		= 0x04,
		GEN_GRID			= 0x08,
		GEN_RANDOMBLANKS	= 0x10,
		GEN_ALL = GEN_STRINGS | GEN_ADDERS | GEN_MULTIPLYERS | GEN_GRID | GEN_RANDOMBLANKS
	};

	//
	// Public interface.
	//
public:
	//! Returns constructed section.
	std::string GenerateSection(size_t length) const;
	//! Sets alignment of data.
	void SetAlignment(size_t alignment);
	//! Sets general size of section.
	void SetSectionSize(size_t size);
	//! Sets general size of stubs between sections.
	void SetStubSize(size_t size);
	//! Sets generation flags (GenFlags).
	void SetFlags(size_t flags);

	//
	// Private members.
	//
private:
	//! Alignment of data.
	size_t alignment_ = 4;
	//! General stubs between sections.
	size_t stub_ = 0;
	//! General size of section.
	size_t sectionSize_ = 0x100;
	//! Genrating flags.
	GenFlags flags_ = GEN_ALL;
};

std::string FalseSectionFactory::GenerateSection(size_t length) const
{
	struct SequenceBlock
	{
		//! Sequence itself.
		std::shared_ptr<Sequence> sequence_;
		//! general size percentage delta of sequence.
		float size_;
	};

	std::vector<ChanceBlock<SequenceBlock>> sequences;

	if (flags_ & GEN_STRINGS) {
		sequences.push_back({ { std::make_shared<StringSequence>(), 0.7f }, 10 });
	}
	if (flags_ & GEN_ADDERS) {
		sequences.push_back({ { std::make_shared<AdderSequence>(), 1.f}, 20 });
	}
	if (flags_ & GEN_MULTIPLYERS) {
		sequences.push_back({ { std::make_shared<MultiplyerSequence>(), 1.f }, 20 });
	}
	if (flags_ & GEN_GRID) {
		sequences.push_back({ { std::make_shared<GridSequence>(), 0.7f }, 10 });
	}
	if (flags_ & GEN_RANDOMBLANKS) {
		sequences.push_back({ { std::make_shared<RandomBlanksSequence>(), 0.7f }, 10 });
	}

	if (sequences.empty()) {
		throw std::exception{ "(FalseSectionFactory) Generation sequences list is empty." };
	}

	std::string out;
	out.reserve(length + stub_ * 2);

	for (; out.size() < length;)
	{
		size_t sequence_index = RandomizeChanceTable(sequences);

		size_t section_size = static_cast<size_t>(sectionSize_
			* sequences[sequence_index].item_.size_
			* (0.8 + (static_cast<float>(randomizer::rnd() % 1000) / 1000) * 0.4));
		size_t stub_size = static_cast<size_t>(stub_ 
			* (0.9 + (static_cast<float>(randomizer::rnd() % 1000) / 1000) * 0.2));

		if (section_size + stub_size > length - out.size())
		{
			if (stub_size > length - out.size())
			{
				section_size = 0;
				stub_size = length - out.size();
			}
			else {
				section_size = length - out.size() - stub_size;
			}
		}

		if (section_size) {
			out += sequences[sequence_index].item_.sequence_->GetCopy()->GetSequence(section_size);
		}

		if (alignment_ > 1)
		{
			size_t needed_size = out.size() + stub_size;
			size_t alignment_rest = needed_size % alignment_;
			out.resize(needed_size + (alignment_rest ? (alignment_ - alignment_rest) : 0));
		}
	}

	return out;
}

void FalseSectionFactory::SetAlignment(size_t alignment)
{
	alignment_ = alignment;
}

void FalseSectionFactory::SetSectionSize(size_t size)
{
	sectionSize_ = size;
}

void FalseSectionFactory::SetStubSize(size_t size)
{
	stub_ = size;
}

void FalseSectionFactory::SetFlags(size_t flags)
{
	if (!(flags & GEN_ALL)) {
		throw std::exception{ "(FalseSectionFactory) Generation flags are empty." };
	}
	flags_ = static_cast<GenFlags>(flags);
}
#endif // Random not random sequences

// Calc parser tests
#if false
std::string TokenTypeToString(const bwn::calc_parser::Token& token)
{
	std::string out;

	if (token.GetType() & bwn::calc_parser::Token::LVALUE)
	{
		if (!out.empty()) {
			out += "|";
		}
		out += "LVALUE";
	}
	if (token.GetType() & bwn::calc_parser::Token::PRVALUE)
	{
		if (!out.empty()) {
			out += "|";
		}
		out += "PRVALUE";
	}
	if (token.GetType() & bwn::calc_parser::Token::OPERATOR)
	{
		if (!out.empty()) {
			out += "|";
		}
		out += "OPERATOR(";

		std::string operator_str;

		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_LVALUE)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_LVALUE";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_ITERATORS)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_ITERATORS";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_HIGH_RVALUE)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_HIGH_RVALUE";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_LOW_RVALUE)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_LOW_RVALUE";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_UNARY)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_UNARY";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_HIGH_LOGIC)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_HIGH_LOGIC";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_LOW_LOGIC)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_LOW_LOGIC";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::U_OP_TERNARY)
		{
			if (!operator_str.empty()) {
				operator_str += "|";
			}
			operator_str += "U_OP_TERNARY";
		}
		if (token.GetOperator() & bwn::calc_parser::Token::OP_COMA)
		{
			if (!operator_str.empty()) {
				out += "|";
			}
			operator_str += "OP_COMA";
		}

		out += operator_str + ")";
	}
	if (token.GetType() & bwn::calc_parser::Token::OPENING_BRACKET)
	{
		if (!out.empty()) {
			out += "|";
		}
		out += "OPENING_BRACKET";
	}
	if (token.GetType() & bwn::calc_parser::Token::CLOSING_BRACKET)
	{
		if (!out.empty()) {
			out += "|";
		}
		out += "CLOSING_BRACKET";
	}

	return out;
}

std::string ValueTypeToString(bwn::calc_parser::Value::Type type)
{
	switch (type)
	{
	case bwn::calc_parser::Value::T_NULL:
		return "T_NULL";
	case bwn::calc_parser::Value::T_BOOL:
		return "T_BOOL";
	case bwn::calc_parser::Value::T_INT:
		return "T_INT";
	case bwn::calc_parser::Value::T_UINT:
		return "T_UINT";
	case bwn::calc_parser::Value::T_DOUBLE:
		return "T_DOUBLE";
	case bwn::calc_parser::Value::T_STRING:
		return "T_STRING";
	default:
		return "(Unknown type)";
	}
}

std::string ValueToString(const bwn::calc_parser::Value& value, const std::string& value_name = {})
{
	return ValueTypeToString(value.GetType()) + " " + value_name + " = " + value.ToString();
}

std::string TokenInternToString(const bwn::calc_parser::Token& token)
{
	switch (token.GetType())
	{
	case bwn::calc_parser::Token::PRVALUE:
		return token.GetValue().ToString();
	case bwn::calc_parser::Token::LVALUE:
		return token.GetName();
	default:
		return TokenTypeToString(token);
	}
}

bwn::calc_parser::Variable SetVar(bwn::calc_parser::Repository& rep, const std::vector<bwn::calc_parser::Variable>& args)
{
	std::cout << "Test function invoked (by the way, HELLO WORLD)" << std::endl;
	std::cout << "Arguments are : " << std::endl;

	for (auto it = args.begin(); it != args.end(); ++it)
	{
		bwn::calc_parser::Value value;
		if (it->IsLvalue()) {
			value = rep.GetVariable(it->AsName());
		}
		else {
			value = it->AsValue();
		}

		std::cout << '\t' << ValueToString(value, it->IsLvalue() ? it->AsName() : "PRVALUE") << std::endl;
	}
	

	rep.SetVariable("New_var", "This is new variable");

	return bwn::calc_parser::Variable();
}
#endif // Calc parser tests

// Print optional
#if false
struct Unprintable
{
};

template<typename Char, typename CharTraits, typename T>
void PrintOptional(std::basic_ostream<Char, CharTraits>& stream, const boost::optional<T>& value, ...)
{
	if (!stream.good()) {
		return;
	}

	if (value)
	{
		stream << "<NotEmpty>";
	}
	else
	{
		stream << "<Empty>";
	}
}

template<typename Char, typename CharTraits, typename T>
auto PrintOptional(std::basic_ostream<Char, CharTraits>& stream, const boost::optional<T>& value, bool) ->
decltype((void)(stream << *value), std::declval<void>())
{
	if (!stream.good()) {
		return;
	}

	if (value)
	{
		stream << *value;
	}
	else
	{
		stream << "<Empty>";
	}
}

template<typename T>
std::wostream& operator<<(std::wostream& stream, const boost::optional<T>& value)
{
	PrintOptional(stream, value, false);

	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const boost::optional<T>& value)
{
	PrintOptional(stream, value, false);

	return stream;
}
#endif // Print optional

// Iterators
#if false
void ForwardIteratorPrint(bwn::ForwardIterator<int> beg, bwn::ForwardIterator<int> end)
{
	std::cout << "Forward iterators print..";
	for (auto it = beg; it != end; ++it)
	{
		std::cout << "\n\t" << *it;
	}
	std::cout << std::endl;
}


void BackwardIteratorPrint(bwn::BidirectionalIterator<int> beg, bwn::BidirectionalIterator<int> end)
{
	std::cout << "Bidirectional iterators print..";
	if (beg != end)
	{
		do
		{
			std::cout << "\n\t" << *(--end);
		} while (beg != end);
	}

	std::cout << std::endl;
}
#endif // Iterators

	// "C++ Templates. Second Edition"
#if false
template<typename F, typename...Args, typename = decltype((void)(std::declval<F>()(std::declval<Args&&>()...)))>
std::true_type IsValidImpl(void*);

template <typename F, typename...Args>
std::false_type IsValidImpl(...);

inline constexpr auto IsValid = [](auto f)
{
	return [](auto&& ... args)
	{
		return decltype(IsValidImpl<decltype(f), decltype(args)&&...>(nullptr)) {};
	};
};

constexpr auto isCallableWith = IsValid([](auto x, auto arg)->decltype((void)x(arg)){});


void TestFunction(int) {}
#endif // "C++ Templates. Second Edition"


int main(int argc, char* argv[])
{

	// Randomized chances
#if false
	std::vector<float> possibleBlocks_{10,20,30,40,50,70,100};

	while(true)
	{
		std::cout << "complexity : ";

		std::string input;
		std::getline(std::cin, input);


		float complexity;
		try
		{
			complexity = boost::lexical_cast<float, std::string>(input);
		}
		catch (const std::exception& e)
		{
			std::cout << "Error while processing input : " << e.what() << std::endl;
			continue;
		}

		if (complexity == 0)
		{
			break;
		}

		float total = 0;
		float middle;
		{
			// Preparing variables.
			float min = possibleBlocks_[0];
			float max = possibleBlocks_[0];
			for (size_t i = 0; i < possibleBlocks_.size(); ++i)
			{
				if (min > possibleBlocks_[i]) {
					min = possibleBlocks_[i];
				}

				if (max < possibleBlocks_[i]) {
					max = possibleBlocks_[i];
				}

				total += possibleBlocks_[i];
			}

			std::cout << "min : " << min << std::endl;
			std::cout << "max : " << max << std::endl;
			middle = (min + max) / 2;
			complexity *= middle / 50;
		}
		std::cout << "total : " << total << std::endl;
		std::cout << "middle : " << middle << std::endl;
		std::cout << "recalculated complexity : " << complexity << std::endl;


		std::vector<float> chances;
		chances.resize(possibleBlocks_.size());
		{
			total = 0;
			for (size_t i = 0; i < chances.size(); ++i)
			{

				float impact =
				(((possibleBlocks_[i] - middle) / middle))	// Block complexity inpact
				* ((complexity - middle) / middle);				// Desired complexity impact

				chances[i] = 30 + 30 * (impact > 0 ? 1 : -1) * std::powf(std::fabs(impact), 0.7);
				total += chances[i];
			}
		}

		std::cout << "Possible blocks : " << std::endl;
		for (size_t i = 0; i < possibleBlocks_.size(); ++i)
		{
			std::cout << '|' << possibleBlocks_[i];
		}
		std::cout << '|' << std::endl;


		std::cout << "Chances : " << std::endl;
		for (size_t i = 0; i < chances.size(); ++i)
		{
			std::cout << '|' << chances[i];
		}
		std::cout << '|' << std::endl;
	}
#endif // Randomized chances


	// Icon randomizing
#if false
	std::cout << "Icon randomising : " << std::endl;

	if (argc != 3) {
		std::cout << "Wrong arguments count" << std::endl;
		return -1;
	}


	try
	{
		std::string file_buff;

		{
			
			std::ifstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);

			if (!file) {
				throw std::exception{ "Can't open file" };
			}

			file_buff.resize(file.tellg());			

			file.seekg(std::ios::beg);

			file.read(&file_buff[0], file_buff.size());

			std::cout << "file size : " << file_buff.size() << std::endl;
		}

		{
			if (file_buff.size() < sizeof(BWN_ICON_DIRECTORY) + sizeof(BWN_ICON_HEADER)) {
				throw std::exception{ "Incorect file" };
			}

			BWN_ICON_HEADER icon_header = *reinterpret_cast<BWN_ICON_HEADER*>(&file_buff[0]);

			if (icon_header.type != 1) {
				throw std::exception{ "Incorect type" };
			}

			int dirs_offset = 0;

			for (size_t i = 0; i < icon_header.imageNum; ++i)
			{
				std::cout << "==========================" << std::endl;

				BWN_ICON_DIRECTORY icon_dir;
				{
					BWN_ICON_DIRECTORY* icon_dir_ptr = reinterpret_cast<BWN_ICON_DIRECTORY*>(&file_buff[sizeof(BWN_ICON_HEADER) + sizeof(BWN_ICON_DIRECTORY) * i]);
					
					std::cout << "old offset is : " << icon_dir_ptr->offset << std::endl;
					
					icon_dir_ptr->offset += dirs_offset;

					std::cout << "new offset is : " << icon_dir_ptr->offset << std::endl;

					icon_dir = *icon_dir_ptr;
				}

				std::string image_buff(file_buff, icon_dir.offset, icon_dir.bitmapSize);

				const char cmp_buff[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

				try
				{
					if (!std::memcmp(&image_buff[0], cmp_buff, 8))
					{
						std::cout << "trying as png..." << std::endl;

						image_buff = RandomizePNG(image_buff);
					}
					else
					{
						std::cout << "trying as bmp..." << std::endl;

						image_buff = RandomizeBMP(image_buff);
					}
				}
				catch (const std::exception& e)
				{
					std::cout << "failed to randomize image : " << e.what() << std::endl;
					continue;
				}

				std::cout << "image is randomized!" << std::endl;

				std::cout << "old image size is : " << icon_dir.bitmapSize << std::endl;
				std::cout << "new image size is : " << image_buff.size() << std::endl;				

				dirs_offset += image_buff.size() - icon_dir.bitmapSize;

				file_buff.replace(icon_dir.offset, icon_dir.bitmapSize, image_buff);

				reinterpret_cast<BWN_ICON_DIRECTORY*>(&file_buff[sizeof(BWN_ICON_HEADER) + sizeof(BWN_ICON_DIRECTORY) * i])->bitmapSize = image_buff.size();



				std::cout << "==========================" << std::endl;
			}
		}

		{
			std::ofstream file(argv[2], std::ios::out | std::ios::binary);

			file.write(file_buff.data(), file_buff.size());
		}

		std::cout << "Icon is randomized!";

	}
	catch (const std::exception& e)
	{
		std::cout << "Error : " << e.what() << std::endl;
		return 0;
	}
#endif // Icon randomizing


	// Some asm testing
#if false
	unsigned int first;

	unsigned int second;

	unsigned int third;

	__asm
	{
		// Moving
		INT 3;
		mov eax, 0x01010101;
		//mov ebx, 0x01010101;
		//mov ebx, eax;
		mov first, eax;
		mov second, eax;
		mov third, eax;


		mov [ebp - 4], eax;
		mov [ebp - 257], eax;
		

		mov ebp, eax;
		//mov first, ebx;
		//mov first, 0x20202020;

		//add eax, 0x01010101;
		//add ebx, 0x01010101;
		//add ebx, eax;
		//add first, eax;
		//add first, ebx;
		//add first, 0x20202020;

		//sub eax, 0x01010101;
		//sub ebx, 0x01010101;
		//sub ebx, eax;
		//sub first, eax;
		//sub first, ebx;
		//sub first, 0x20202020;

		//imul eax, 0x01010101;
		//imul ebx, 0x01010101;
		//imul ebx, eax;

		//cmp eax, 0x01010101;
		//cmp ebx, 0x01010101;
		//cmp ebx, eax;
		//cmp first, eax;
		//cmp first, ebx;
		//cmp first, 0x20202020;

		//or eax, 0x01010101;
		//or ebx, 0x01010101;
		//or ebx, eax;
		//or first, eax;
		//or first, ebx;
		//or first, 0x20202020;

		//dec eax;
		//dec ebx;
		//dec first;
		//dec second;
		//point:
		//jmp eax;
		//jmp ebx;
		//jmp first;
		//jmp second;
		//jmp point;

		//call eax;
		//call ebx;
		//call first;
		//call second;
		//call point;

		//not eax;
		//not ebx;
		//not first;
		//not second;
		
	}
#endif // Some asm testing


	// asmpure
#if false
	std::string input;
	{
		std::ifstream input_file("input.txt", std::ios::in | std::ios::binary | std::ios::ate);
	
		if (!input_file)
		{
			std::cout << "File can't be open" << std::endl;
			return -1;
		}

		input.resize(input_file.tellg());

		input_file.seekg(std::ios::beg);

		input_file.read(&input[0], input.size());
	}

	std::cout << "File size is : " << input.size() << std::endl;


	CAssembler *casm;
	int size, c;

	// create assembler
	casm = casm_create();

	// append assembly source
	casm_source(casm, input.data());

	// calculate size
	size = casm_compile(casm, NULL, 0);

	if (size < 0) {
		printf("compile error: %s\n", casm->error);
		casm_release(casm);
		return -1;
	}


	std::string opcodes;
	opcodes.resize(size);

	casm_compile(casm, reinterpret_cast<byte*>(&opcodes[0]), size);

	opcodes.erase(opcodes.find_last_not_of(static_cast<char>(0xCC)) + 1);


	std::ofstream out_file("asm.txt", std::ios::out | std::ios::binary);

	if (!out_file) {
		std::cout << "File can't be opened\n";
		casm_release(casm);
		return -1;
	}

	out_file << std::hex;

	for (size_t i = 0; i < opcodes.size(); ++i) 
	{
		if (i % 16) {
			out_file << ' ';
		}
		else if (i != 0)
		{
			out_file << '\n';
		}

		out_file << std::setw(2) << std::setfill('0')
			<< static_cast<unsigned long>(static_cast<unsigned char>(opcodes[i]));

	}

	out_file.close();



	//casm_dumpinst(casm, stdout);



	casm_release(casm);
#endif


	// asmjit
#if false
	namespace x86 = asmjit::x86;

	asmjit::CodeHolder codeHolder{};                        // Create a CodeHolder.
	codeHolder.init(asmjit::CodeInfo(asmjit::ArchInfo::kIdX86));// Initialize it for a 32-bit X86 target.
	PrintingErrorHandler eh{};
	codeHolder.setErrorHandler(&eh);

	// Generate a 32-bit function that sums 4 floats and looks like:
	//   void func(float* dst, const float* a, const float* b)
	asmjit::x86::Assembler ass(&codeHolder);                  // Create and attach X86Assembler to `code`.

	
	asmjit::x86::Gp reg1 = asmjit::x86::eax;
	asmjit::x86::Gp reg2 = asmjit::x86::cx;
	
	asmjit::x86::Mem var = asmjit::x86::byte_ptr(asmjit::x86::ebp, 10);
	
	
	ass.sub(asmjit::x86::eax, 0x1);
	ass.sub(asmjit::x86::eax, 0x2);
	ass.sub(asmjit::x86::eax, 0x3);

	ass.dd(0);
	ass.sub(asmjit::x86::eax, 0x4);
	ass.sub(asmjit::x86::eax, 0x5);

	ass.dd(0);
	ass.sub(asmjit::x86::eax, 0x6);
	ass.sub(asmjit::x86::eax, 0x7);

	ass.dd(0);
	ass.sub(asmjit::x86::eax, 0x8);
	ass.sub(asmjit::x86::eax, 0x9);

	//ass.shr(reg1, asmjit::x86::al);
	//ass.shr(reg1, asmjit::x86::bl);
	//ass.shr(reg1, asmjit::x86::dl);
	//ass.shr(asmjit::x86::al, reg2);
	//ass.shr(asmjit::x86::ah, reg2);
	//ass.shr(asmjit::x86::ax, reg2);
	//ass.shr(var, asmjit::x86::cl);




	//ass.shl(reg1, 0x10);
	//ass.shl(reg1, reg2);
	//ass.shl(var, reg2);

	//ass.and_(reg1, 0x10);
	//ass.and_(reg1, reg2);
	//ass.and_(var, reg2);
	//ass.and_(reg1, var);

	//ass.mov(reg, asmjit::x86::dword_ptr(asmjit::x86::ebp, 10));
	//ass.mov(reg, asmjit::x86::dword_ptr(asmjit::x86::ebp, -10));


	// Now we have two options if we want to do something with the code hold
	// by CodeHolder. In order to use it we must first sync X86Assembler with
	// the CodeHolder as it doesn't do it for every instruction it generates for
	// performance reasons. The options are:
	//
	//   1. Detach X86Assembler from CodeHolder (will automatically sync).
	//   2. Sync explicitly, allows to use X86Assembler again if needed.
	//
	// NOTE: AsmJit always syncs internally when CodeHolder needs to access these
	// buffers and knows that there is an Assembler attached, so you have to sync
	// explicitly only if you bypass CodeHolder and intend to do something on your
	// own.
	// codeHolder.sync();                            // So let's sync, it's easy.

	// We have no Runtime this time, it's on us what we do with the code.
	// CodeHolder stores code in SectionEntry, which embeds CodeSection
	// and CodeBuffer structures. We are interested in section's CodeBuffer only.
	//
	// NOTE: The first section is always '.text', so it's safe to just use 0 index.
	asmjit::CodeBuffer& buf = codeHolder.sectionById(0)->buffer();

	std::string opcodes(reinterpret_cast<const char*>(buf.data()), buf.size());

	std::cout << "Size of opcodes : " << opcodes.size() << std::endl;

	// Write into small-sample as code.
#if false
	{
		std::ifstream in_file(argv[0], std::ios::in | std::ios::binary);

		pe_bliss::pe_base image = pe_bliss::pe_factory::create_pe(in_file, false);

		pe_bliss::section local_section;

		local_section.readable(true).executable(true);

		local_section.get_raw_data() = opcodes;

		local_section.set_name(".ntext");

		image.prepare_section(local_section);

		pe_bliss::section& text_section = image.add_section(local_section);

		image.set_ep(image.rva_from_section_offset(text_section, 0));

		std::ofstream new_pe_file("asm-test.exe", std::ios::out | std::ios::binary | std::ios::trunc);

		pe_bliss::rebuild_pe(image, new_pe_file, false, false);
	}
#endif // Write into small-sample as code.

	// Writing code to a file
#if false
	{
		std::ofstream out_file("asm.txt", std::ios::out | std::ios::binary);

		if (!out_file) {
			std::cout << "File can't be opened\n";
			return -1;
		}

		out_file << std::hex;

		for (size_t i = 0; i < opcodes.size(); ++i)
		{
			if (i % 16) {
				out_file << ' ';
			}
			else if (i != 0)
			{
				out_file << '\n';
			}

			out_file << std::setw(2) << std::setfill('0')
				<< static_cast<unsigned long>(static_cast<unsigned char>(opcodes[i]));

		}

		out_file.close();
	}
#endif // Writing code to a file

	// Writing code to a console
#if false
	{
		std::cout << std::hex;

		for (size_t i = 0; i < opcodes.size(); ++i)
		{
			if (i % 16) {
				std::cout << ' ';
			}
			else if (i != 0)
			{
				std::cout << '\n';
			}

			std::cout << std::setw(2) << std::setfill('0')
				<< static_cast<unsigned long>(static_cast<unsigned char>(opcodes[i]));

		}
		std::cout << std::dec << std::endl;
	}
#endif // Writing code to a console

	PrintAsHex(opcodes);
#endif // asmjit


	// distorm
#if false
#define MAX_INSTRUCTIONS (1000)

	// Version of used compiled library.
	unsigned long dver = 0;
	// Holds the result of the decoding.
	_DecodeResult res;
	// Decoded instruction information.
	_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];

	_DInst dInstructions[MAX_INSTRUCTIONS];
	
	//	typedef struct {
	//		_OffsetType codeOffset, nextOffset; /* nextOffset is OUT only. */
	//		const uint8_t* code;
	//		int codeLen; /* Using signed integer makes it easier to detect an underflow. */
	//		_DecodeType dt;
	//		unsigned int features;
	//	} _CodeInfo;
	

	unsigned int relocs[] = {9, 19, 29, 39};

	_CodeInfo codeInfo;
	codeInfo.codeOffset = 0;
	codeInfo.nextOffset = 0;

	codeInfo.relocs = relocs;
	codeInfo.relocSize = sizeof(relocs) / sizeof(relocs[0]);

	codeInfo.code = reinterpret_cast<unsigned char*>(&opcodes[0]);
	codeInfo.codeLen = opcodes.size();
	codeInfo.dt = Decode32Bits;

	codeInfo.features = 0;

	// next is used for instruction's offset synchronization.
	// decodedInstructionsCount holds the count of filled instructions' array by the decoder.
	unsigned int decodedInstructionsCount = 0, i, next;

	// Default decoding mode is 32 bits, could be set by command line.
	_DecodeType dt = Decode32Bits;

	// Default offset for buffer is 0, could be set in command line.
	unsigned long long offset = 0;
	char* errch = NULL;

	// Index to file name in argv.
	//int param = 1;

	// Handling file.
	//HANDLE file;
	//DWORD filesize = sizeof(UnUnpacker_data);


#if false
	// Buffer to disassemble.
	unsigned char *buf, *buf2;

	// Disassembler version.
	dver = distorm_version();
	printf("diStorm version: %d.%d.%d\n", (dver >> 16), ((dver) >> 8) & 0xff, dver & 0xff);

	// Check params.
	if (argc < 2 || argc > 4) {
		printf("Usage: disasm.exe [-b16] [-b64] filename [memory offset]\r\nRaw disassembler output.\r\nMemory offset is origin of binary file in memory (address in hex).\r\nDefault decoding mode is -b32.\r\nexample:   disasm -b16 demo.com 789a\r\n");
		return -1;
	}

	if (strncmp(argv[param], "-b16", 4) == 0) {
		dt = Decode16Bits;
		param++;
	}
	else if (strncmp(argv[param], "-b64", 4) == 0) {
		dt = Decode64Bits;
		param++;
	}
	else if (*argv[param] == '-') {
		printf("Decoding mode size isn't specified!");
		return -1;
	}
	else if (argc == 4) {
		printf("Too many parameters are set.");
		return -1;
	}
	if (param >= argc) {
		printf("Filename is missing.");
		return -1;
	}
	if (param + 1 == argc - 1) { // extra param?
#ifdef SUPPORT_64BIT_OFFSET
		offset = _strtoui64(argv[param + 1], &errch, 16);
#else
		offset = strtoul(argv[param + 1], &errch, 16);
#endif
		if (*errch != '\0') {
			printf("Offset couldn't be converted.");
			return -1;
		}
	}
	wchar_t

	file = CreateFile(argv[param], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		printf("Could not open file %s (error %d)\n", argv[param], GetLastError());
		return -2;
	}

	if ((filesize = GetFileSize(file, NULL)) < 0) {
		printf("Error getting filesize (error %d)\n", GetLastError());
		CloseHandle(file);
		return -3;
	}

	// We read the whole file into memory in order to make life easier,
	// otherwise we would have to synchronize the code buffer as well (so instructions won't be split).
	buf2 = buf = (unsigned char*)malloc(filesize);
	if (!ReadFile(file, buf, filesize, &bytesread, NULL)) {
		printf("Error reading file (error %d)\n", GetLastError());
		CloseHandle(file);
		free(buf);
		return -3;
	}

	if (filesize != bytesread) {
		printf("Internal read-error in system\n");
		CloseHandle(file);
		free(buf);
		return -3;
	}

	CloseHandle(file);



	printf("bits: %d\nfilename: %s\norigin: ", dt == Decode16Bits ? 16 : dt == Decode32Bits ? 32 : 64, argv[param]);
#ifdef SUPPORT_64BIT_OFFSET
	if (dt != Decode64Bits) printf("%08I64x\n", offset);
	else printf("%016I64x\n", offset);
#else
	printf("%08x\n", offset);
#endif

#endif

	//const unsigned char* buf = UnUnpacker_data;

	// Decode the buffer at given offset (virtual address).
	while (1) {
		std::cout << "while cycle\n";
		// If you get an unresolved external symbol linker error for the following line,
		// change the SUPPORT_64BIT_OFFSET in distorm.h.
		//res = distorm_decode(offset, buf, filesize, dt, decodedInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		
		res = distorm_decompose(&codeInfo, dInstructions, MAX_INSTRUCTIONS, &decodedInstructionsCount);
		//_DecodeResult distorm_decompose64(_CodeInfo* ci, _DInst result[], unsigned int maxInstructions, unsigned int* usedInstructionsCount);
				
		if (res == DECRES_INPUTERR) {
			// Null buffer? Decode type not 16/32/64?
			printf("Input error, halting!");
			return -4;
		}

		for (i = 0; i < decodedInstructionsCount; i++) {

#if true
			std::string mnemonic(reinterpret_cast<char*>(GET_MNEMONIC_NAME(dInstructions[i].opcode)));

			std::cout << "0x" << std::hex << std::setw(12) << std::setfill(' ') << std::left << dInstructions[i].addr << std::dec << "Mnemonic : " << mnemonic << std::endl;
			
			for (size_t op = 0; op < 4 && dInstructions[i].ops[op].type != O_NONE; ++op)
			{
			/* Type of operand:
				O_NONE: operand is to be ignored.
				O_REG: index holds global register index.
				O_IMM: instruction.imm.
				O_IMM1: instruction.imm.ex.i1.
				O_IMM2: instruction.imm.ex.i2.
				O_DISP: memory dereference with displacement only, instruction.disp.
				O_SMEM: simple memory dereference with optional displacement (a single register memory dereference).
				O_MEM: complex memory dereference (optional fields: s/i/b/disp).
				O_PC: the relative address of a branch instruction (instruction.imm.addr).
				O_PTR: the absolute target address of a far branch instruction (instruction.imm.ptr.seg/off).
			*/

				if (dInstructions[i].ops[op].type == O_REG) 
				{
					std::cout << "Operand number " << op << " here is O_REG (" 
						<< GET_REGISTER_NAME(dInstructions[i].ops[op].index) << ")" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_IMM) {
					std::cout << "Operand number " << op << " here is O_IMM ("
						<< ((dInstructions[i].ops[op].size == 32) 
							? dInstructions[i].imm.dword 
							: ((dInstructions[i].ops[op].size == 16) 
							   ? dInstructions[i].imm.word 
							   : dInstructions[i].imm.byte)) << ")"
						<< std::endl;
				}
				if (dInstructions[i].ops[op].type == O_IMM1) {
					std::cout << "Operand number " << op << " here is O_IMM1" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_IMM2) {
					std::cout << "Operand number " << op << " here is O_IMM2" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_DISP) {
					std::cout << "Operand number " << op << " here is O_DISP" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_SMEM) {
					std::cout << "Operand number " << op << " here is O_SMEM ("
						<< GET_REGISTER_NAME(dInstructions[i].ops[op].index)
						<< "|" << static_cast<int>(dInstructions[i].disp) << ")" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_MEM) {
					std::cout << "Operand number " << op << " here is O_MEM" << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_PC) {
					std::cout << "Operand number " << op << " here is O_PC, size is " << dInstructions[i].ops[op].size << std::endl;
				}
				if (dInstructions[i].ops[op].type == O_PTR) {
					std::cout << "Operand number " << op << " here is O_PTR" << std::endl;
				}
			}


			if (dInstructions[i].ops[0].type == O_PC 
				&& mnemonic.size() > 0
				&& (mnemonic[0] == 'J' 
				|| mnemonic == "CALL"))
			{
				int offset = 0;

				if (decodedInstructions[i].size > 4)
				{
					offset = dInstructions[i].imm.sdword;
				}
				else
				{
					offset = dInstructions[i].imm.sbyte;
				}

				//std::cout << "branch offset is here : " << offset << std::endl;
				//std::cout << "instraction offset is here : " << dInstructions[i].addr << std::endl;
			}
#endif
			//std::cout << "imm : " << std::hex << dInstructions[i].imm.dword << std::dec << std::endl;

		}

		if (res == DECRES_SUCCESS) break; // All instructions were decoded.
		else if (decodedInstructionsCount == 0) break;

		unsigned long next = (unsigned long)(dInstructions[decodedInstructionsCount - 1].addr - codeInfo.codeOffset);
		next += dInstructions[decodedInstructionsCount - 1].size;
		// Advance ptr and recalc offset.
		codeInfo.code += next;
		codeInfo.codeLen -= next;
		codeInfo.codeOffset += next;
	}

	// Release buffer
#endif // distorm


	// Imports statistics
#if false
	namespace po = boost::program_options;

	typedef struct Settings
	{
		bool sortByName = false;

	};
	
	Settings settings_ = Settings{};

	po::options_description visible_options("DXPack Packer 1.0\nCommand Line Options");

	try
	{
		po::options_description cmdline;

		visible_options.add_options()
			("sort-name", po::value<bool>(&settings_.sortByName), "Sort functions by name")
			//("file-align,a", po::value<unsigned long>(&implementation_->settings_.fileAlignment_)->default_value(512), "Packed file alignment")
			//("strip-dos,s", po::value<bool>(&implementation_->settings_.stripDosHeader_)->default_value(true), "Strip DOS headers")
			//("repack-res,r", po::value<bool>(&implementation_->settings_.repackResources_)->default_value(true), "Repack resources")
			//("build-load-config,c", po::value<bool>(&implementation_->settings_.rebuildLoadConfig_)->default_value(true), "Rebuild Load Config directory")
			//("build-exports,e", po::value<bool>(&implementation_->settings_.rebuildExports_)->default_value(true), "Rebuild exports directory")
			//("random-iconbitsperbyte", po::value<size_t>(&implementation_->settings_.bitsPerByteIconRandom_)->default_value(3), "How many bits in each byte of icon will be randomize")
			//("force,f", "Force packing of possibly incorrect binaries")
			//("junk-complexity,j", po::value<float>(&implementation_->settings_.junkComplexity_)->default_value(10), "Complexity of junk code (from 0 to 100, 0 - do not generate junk)")
			;

		cmdline.add(visible_options);

		//cmdline.add_options()
		//	("image,i", po::value<Path>(&implementation_->settings_.inputFileName_), "PE image to pack")
		//	;


		//po::positional_options_description desc_pos;
		//desc_pos.add("image", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(cmdline).run(), vm);
		po::notify(vm);

		//if (vm.count("force"))
		//{
		//	implementation_->logs_ << "Force mode is active!" << endl;
		//	implementation_->settings_.force_ = true;
		//}
	}
	catch (const std::exception& e)
	{
		std::cout << "OPTIONS ARE SHIT" << std::endl;
		return -1;
	}





	std::vector<ImportLib> libs;
	libs.push_back(ImportLib());
	libs.back().name_ = "kernel32.dll";
	libs.push_back(ImportLib());
	libs.back().name_ = "user32.dll";
	libs.push_back(ImportLib());
	libs.back().name_ = "shell32.dll";

	boost::filesystem::path myPath(argv[0]);

	boost::filesystem::recursive_directory_iterator it(myPath.parent_path());
	boost::filesystem::recursive_directory_iterator endit;

	size_t exe_tested = 0;

	while (it != endit)
	{
		if (boost::filesystem::is_regular_file(*it) && it->path().extension() == ".exe"
			&& it->path().filename() != myPath.filename()) 
		{
			std::cout << "trying : " << it->path() << std::endl;
			if (WriteExe(libs, it->path())) {
				++exe_tested;
			}
		}

		++it;
	}

	if (settings_.sortByName)
	{
		for (size_t i = 0; i < libs.size(); ++i)
		{
			std::sort(libs[i].funcs_.begin(), libs[i].funcs_.end(), SortByName);
		}
	}
	else
	{
		for (size_t i = 0; i < libs.size(); ++i)
		{
			std::sort(libs[i].funcs_.begin(), libs[i].funcs_.end(), SortByCount);

			for (size_t ii = 0; ii < libs[i].funcs_.size();)
			{
				size_t present_count = libs[i].funcs_[ii].count_;

				size_t end = ii;
				for (; end < libs[i].funcs_.size() && present_count == libs[i].funcs_[end].count_; ++end);

				if (end < libs[i].funcs_.size()) {
					std::sort(libs[i].funcs_.begin() + ii, libs[i].funcs_.begin() + end, SortByName);
				}
				else {
					std::sort(libs[i].funcs_.begin() + ii, libs[i].funcs_.end(), SortByName);
				}
				ii = end;
			}
		}
	}
	


	//Json::Value root;
	//Json::Value json_libs;
	//for (size_t i = 0; i < libs.size(); ++i)
	//{
	//	Json::Value json_lib;
	//
	//	json_lib["name"] = libs[i].name_;
	//
	//	Json::Value json_funcs;
	//
	//	for (size_t ii = 0; ii < libs[i].funcs_.size(); ++ii)
	//	{
	//		Json::Value json_func;
	//		json_func["name"] = libs[i].funcs_[ii].name_;
	//		json_func["count"] = libs[i].funcs_[ii].count_;
	//
	//		json_funcs[ii] = json_func;
	//	}
	//
	//	json_lib["funcs"] = json_funcs;
	//
	//	json_libs[i] = json_lib;
	//}
	//root["libs"] = json_libs;
	//{
	//	std::ofstream file("imports.json", std::ios::out);
	//
	//	if (!file)
	//	{
	//		std::cout << "output json file can't be opened" << std::endl;
	//		system("Pause");
	//		return -1;
	//	}
	//
	//	file << root;
	//}


	{
		std::ofstream file("log.txt", std::ios::out);


		PrintFunctions(libs, &file);

		std::cout << std::endl << "exe tested : " << exe_tested << std::endl;
		file << std::endl << "exe tested : " << exe_tested << std::endl;
	}
#endif // Imports statistics


	// Directories statistics
#if false
	DirStat dirs[15]
	{
		{IMAGE_DIRECTORY_ENTRY_EXPORT},
		{IMAGE_DIRECTORY_ENTRY_IMPORT},
		{IMAGE_DIRECTORY_ENTRY_RESOURCE},
		{IMAGE_DIRECTORY_ENTRY_EXCEPTION},
		{IMAGE_DIRECTORY_ENTRY_SECURITY},
		{IMAGE_DIRECTORY_ENTRY_BASERELOC},
		{IMAGE_DIRECTORY_ENTRY_DEBUG},
		{IMAGE_DIRECTORY_ENTRY_ARCHITECTURE},
		{IMAGE_DIRECTORY_ENTRY_GLOBALPTR},
		{IMAGE_DIRECTORY_ENTRY_TLS},
		{IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG},
		{IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT},
		{IMAGE_DIRECTORY_ENTRY_IAT},
		{IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT},
		{IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR}
	};

	boost::filesystem::path myPath(argv[0]);

	boost::filesystem::recursive_directory_iterator it(myPath.parent_path());
	boost::filesystem::recursive_directory_iterator endit;

	size_t exe_tested = 0;

	while (it != endit)
	{
		if (boost::filesystem::is_regular_file(*it) && it->path().extension() == ".exe")
		{
			std::cout << "trying : " << it->path() << std::endl;
			if (WriteExe(dirs, it->path())) {
				++exe_tested;
			}
		}

		++it;
	}


	Json::Value root;
	Json::Value json_dirs;
	for (size_t i = 0; i < 15; ++i)
	{
		Json::Value json_dir;
	
		json_dir["name"] = std::string(DirsArr[i]);
	
		Json::Value json_sections;
	
		auto stat = dirs[i].GetStatistic();
	
		for (size_t ii = 0; ii < stat.size(); ++ii)
		{
			Json::Value json_section;
			json_section["section"] = stat[ii].first;
			json_section["count"] = stat[ii].second;
	
			json_sections[ii] = json_section;
		}
	
		json_dir["sections"] = json_sections;
	
		json_dirs[i] = json_dir;
	}
	root["dirs"] = json_dirs;
	{
		std::ofstream file("directories.json", std::ios::out);
	
		if (!file)
		{
			std::cout << "output json file can't be opened" << std::endl;
			system("Pause");
			return -1;
		}
	
		file << root;
	}


	{
		std::ofstream file("directory_statistics_log.txt", std::ios::out);


		PrintDirs(dirs, &file);

		std::cout << std::endl << "exe tested : " << exe_tested << std::endl;
		file << std::endl << "exe tested : " << exe_tested << std::endl;
	}

	PrintDirs(dirs, &std::cout);
#endif // Directories statistics


	// File raw statistics
#if false
	namespace po = boost::program_options;


	Settings settings_ = Settings{};

	po::options_description visible_options("DXPack Packer 1.0\nCommand Line Options");

	try
	{
		po::options_description cmdline;

		visible_options.add_options()
			("entropy", po::value<bool>(&settings_.entropy_), "Read entropy")
			("sections", po::value<bool>(&settings_.sections_), "Print datailed sections info")
			//("strip-dos,s", po::value<bool>(&implementation_->settings_.stripDosHeader_)->default_value(true), "Strip DOS headers")
			//("repack-res,r", po::value<bool>(&implementation_->settings_.repackResources_)->default_value(true), "Repack resources")
			//("build-load-config,c", po::value<bool>(&implementation_->settings_.rebuildLoadConfig_)->default_value(true), "Rebuild Load Config directory")
			//("build-exports,e", po::value<bool>(&implementation_->settings_.rebuildExports_)->default_value(true), "Rebuild exports directory")
			//("random-iconbitsperbyte", po::value<size_t>(&implementation_->settings_.bitsPerByteIconRandom_)->default_value(3), "How many bits in each byte of icon will be randomize")
			//("force,f", "Force packing of possibly incorrect binaries")
			//("junk-complexity,j", po::value<float>(&implementation_->settings_.junkComplexity_)->default_value(10), "Complexity of junk code (from 0 to 100, 0 - do not generate junk)")
			;

		cmdline.add(visible_options);

		//cmdline.add_options()
		//	("image,i", po::value<Path>(&implementation_->settings_.inputFileName_), "PE image to pack")
		//	;


		//po::positional_options_description desc_pos;
		//desc_pos.add("image", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(cmdline).run(), vm);
		po::notify(vm);

		//if (vm.count("force"))
		//{
		//	implementation_->logs_ << "Force mode is active!" << endl;
		//	implementation_->settings_.force_ = true;
		//}
	}
	catch (const std::exception& e)
	{
		std::cout << "OPTIONS ARE SHIT" << std::endl;
		return -1;
	}


	boost::filesystem::path myPath(argv[0]);

	boost::filesystem::recursive_directory_iterator it(myPath.parent_path());
	boost::filesystem::recursive_directory_iterator endit;

	std::vector<FileStats> files;

	while (it != endit)
	{
		if (boost::filesystem::is_regular_file(*it) && it->path().extension() == ".exe"
			&& it->path().filename() != myPath.filename())
		{
			std::cout << "Trying : " << it->path() << std::endl;

			FileStats temp;

			if (WriteExe(temp, it->path())) {
				files.push_back(temp);
			}

		}

		++it;
	}




	PrintExes(files, settings_, std::cout);

	{
		std::ofstream file("log.txt", std::ios::out);
		if (!file) {
			std::wcout << "Log file can't be opened" << std::endl;
			return -1;
		}

		PrintExes(files, settings_, file);
	}
#endif // File raw statistics


	// Regex
#if false
	//std::string input(
	//	"\xC7\x45\x55\x11\x12\x11\x11"
	//	"\xC7\x44\x77\x11\x11\x11\x11"
	//	"\xC7\x45\x55\x11\x11\x22"
	//	"\xC7\x45\x77\x77\x77\x77\x11\x11\x11\x11"
	//	"\xC7\x85\x77\x77\x77\x77\x11\x11\x11\x11"
	//	"\xC1\x45\x55\x11\x11\x11\x11");
	std::string input(
		"abcd1 //abc \n"
		"abcd2 //abc2 \n"
		"abcd3 /*abc3*/ abcd4 \n"
		"abcd5 // till end "
	);

	//const unsigned char local_arr[] = {
	//		0xcc, 0x90, 0xcc, 0x90, 0x90, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x90, 0x90, 0xcc, 0x90, 0xcc };
	//
	//input = std::string(reinterpret_cast<const char*>(local_arr), sizeof(local_arr));


	

	//const char searchedByte = '\x11';

	//std::string pattern(//"[\\xC7][\\x45][\\x00-\\xFF][\\x11][\\x11][\\x11][\\x11]"
	//	//"|"
	//	"[\\xCC][\\x90][\\xCC][\\x90][\\x90]([\\x00-\\xFF]+?(?=[\\x90][\\x90][\\xCC][\\x90][\\xCC]))[\\x90][\\x90][\\xCC][\\x90][\\xCC]"
	//	//"abc(.+?(?=(cba)))cba"
	//);
	// ((//)[\\x00-\\xFF]+?(?=(\\n)))|

	std::string pattern("((//).+?(?=($)|(\\n)))|((/\\*).+?(?=(\\*/))(\\*/))");
//

	//for (size_t i = 2; i < 6; ++i) {
	//	pattern[pattern.size() - i] = searchedByte;
	//}

	std::regex opcode;
	try
	{
		opcode = pattern;
	}
	catch (const std::regex_error& e)
	{
		std::cout << "Exception thrown : " << e.what() << std::endl;
		return -1;
	}

	std::sregex_iterator iter(input.begin(), input.end(), opcode);
	std::sregex_iterator end;

	PrintRegex(iter);

	//std::smatch reg_result;
	//std::regex_search(input, reg_result, opcode);
	
	//for (; iter != end; ++iter)
	//{
	//	std::cout << "Match :";
	//
	//	std::string res_str = iter->str();
	//
	//	std::cout << std::hex;
	//	for (size_t ii = 0; ii < res_str.size(); ++ii) {
	//		std::cout 
	//			<< " 0x" << std::setw(2) << std::setfill('0')
	//			<< static_cast<unsigned long>(static_cast<unsigned char>(res_str[ii]));
	//	}
	//	std::cout << std::dec;
	//
	//	std::cout << "\n\tReg pos : " << iter->position()
	//	<< "\n\tReg size : " << iter->length() << std::endl;
	//}
#endif // Regex


	// Finale name testing
#if false
	TestOne<int> some;

	// Simple vars
	TestOne<int>			some1;
	const TestOne<int>		some2;
	char					char1 = 1;
	const char				char2 = 1;
	unsigned char			char3 = 1;
	const unsigned char		char4 = 1;
	short					short1 = 1;
	const short				short2 = 1;
	unsigned short			short3 = 1;
	const unsigned short	short4 = 1;
	int						int1 = 1;
	const int				int2 = 1;
	unsigned int			int3 = 1;
	const unsigned int		int4 = 1;
	long					long1 = 1;
	const long				long2 = 1;
	unsigned long			long3 = 1;
	const unsigned long		long4 = 1;
	long long					longLong1 = 1;
	const long long				longLong2 = 1;
	unsigned long long			longLong3 = 1;
	const unsigned long long	longLong4 = 1;
	float					float1 = 1;
	const float				float2 = 1;
	double					double1 = 1;
	const double			double2 = 1;
	long double				longDouble1 = 1;
	const long double		longDouble2 = 1;
	bool					bool1 = 1;
	const bool				bool2 = 1;

	// Ptr
	char*						charPtr1 = &char1;
	const char*					charPtr2 = &char2;
	unsigned char*				charPtr3 = &char3;
	const unsigned char*		charPtr4 = &char4;
	char**						charPtrPtr1 = &charPtr1;
	const char**				charPtrPtr2 = &charPtr2;
	unsigned char**				charPtrPtr3 = &charPtr3;
	const unsigned char**		charPtrPtr4 = &charPtr4;
	char***						charPtrPtrPtr1 = &charPtrPtr1;
	const char***				charPtrPtrPtr2 = &charPtrPtr2;
	unsigned char***			charPtrPtrPtr3 = &charPtrPtr3;
	const unsigned char***		charPtrPtrPtr4 = &charPtrPtr4;
	// Const ptr
	char*					const	ConstCharPtr1 = &char1;
	const char*				const	ConstCharPtr2 = &char2;
	unsigned char*			const	ConstCharPtr3 = &char3;
	const unsigned char*	const	ConstCharPtr4 = &char4;
	char**					const	ConstCharPtrPtr1 = &charPtr1;
	const char**			const	ConstCharPtrPtr2 = &charPtr2;
	unsigned char**			const	ConstCharPtrPtr3 = &charPtr3;
	const unsigned char**	const	ConstCharPtrPtr4 = &charPtr4;
	char***					const	ConstCharPtrPtrPtr1 = &charPtrPtr1;
	const char***			const	ConstCharPtrPtrPtr2 = &charPtrPtr2;
	unsigned char***		const	ConstCharPtrPtrPtr3 = &charPtrPtr3;
	const unsigned char***	const	ConstCharPtrPtrPtr4 = &charPtrPtr4;

	// Lvalue ref
	char&						charLRef1 = char1;
	const char&					charLRef2 = char2;
	unsigned char&				charLRef3 = char3;
	const unsigned char&		charLRef4 = char4;

	// Lvalue ptr ref
	char*&						charPtrLRef1 = charPtr1;
	const char*&				charPtrLRef2 = charPtr2;
	unsigned char*&				charPtrLRef3 = charPtr3;
	const unsigned char*&		charPtrLRef4 = charPtr4;
	// Lvalue ptrptr ref
	char**&						charPtrPtrLRef1 = charPtrPtr1;
	const char**&				charPtrPtrLRef2 = charPtrPtr2;
	unsigned char**&			charPtrPtrLRef3 = charPtrPtr3;
	const unsigned char**&		charPtrPtrLRef4 = charPtrPtr4;

	// Lvalue const ptr ref
	char* const&					ConstCharPtrLRef1 = charPtr1;
	const char* const&				ConstCharPtrLRef2 = charPtr2;
	unsigned char* const&			ConstCharPtrLRef3 = charPtr3;
	const unsigned char* const&		ConstCharPtrLRef4 = charPtr4;
	// Lvalue const ptrptr ref
	char** const&					ConstCharPtrPtrLRef1 = charPtrPtr1;
	const char** const&				ConstCharPtrPtrLRef2 = charPtrPtr2;
	unsigned char** const&			ConstCharPtrPtrLRef3 = charPtrPtr3;
	const unsigned char** const&	ConstCharPtrPtrLRef4 = charPtrPtr4;

	// Rvalue ref
	char&&						charRRef1 = std::move(char1);
	const char&&				charRRef2 = std::move(char2);
	unsigned char&&				charRRef3 = std::move(char3);
	const unsigned char&&		charRRef4 = std::move(char4);

	// Rvalue ptr ref
	char*&&						charPtrRRef1 = std::move(charPtr1);
	const char*&&				charPtrRRef2 = std::move(charPtr2);
	unsigned char*&&			charPtrRRef3 = std::move(charPtr3);
	const unsigned char*&&		charPtrRRef4 = std::move(charPtr4);
	// Rvalue ptrptr ref
	char**&&					charPtrPtrRRef1 = std::move(charPtrPtr1);
	const char**&&				charPtrPtrRRef2 = std::move(charPtrPtr2);
	unsigned char**&&			charPtrPtrRRef3 = std::move(charPtrPtr3);
	const unsigned char**&&		charPtrPtrRRef4 = std::move(charPtrPtr4);

	// Rvalue const ptr ref
	char* const&&					ConstCharPtrRRef1 = std::move(charPtr1);
	const char* const&&				ConstCharPtrRRef2 = std::move(charPtr2);
	unsigned char* const&&			ConstCharPtrRRef3 = std::move(charPtr3);
	const unsigned char* const&&	ConstCharPtrRRef4 = std::move(charPtr4);
	// Rvalue const ptrptr ref
	char** const&&					ConstCharPtrPtrRRef1 = std::move(charPtrPtr1);
	const char** const&&			ConstCharPtrPtrRRef2 = std::move(charPtrPtr2);
	unsigned char** const&&			ConstCharPtrPtrRRef3 = std::move(charPtrPtr3);
	const unsigned char** const&&	ConstCharPtrPtrRRef4 = std::move(charPtrPtr4);

	// Sized arr
	char						charSArr1[] = { 0x1,0x2,0x3,0x4 };
	const char					charSArr2[] = { 0x1,0x2,0x3,0x4 };
	unsigned char				charSArr3[] = { 0x1,0x2,0x3,0x4 };
	const unsigned char			charSArr4[] = { 0x1,0x2,0x3,0x4 };
	char*						charPtrSArr1[] = { charPtr1,charPtr1,charPtr1,charPtr1 };
	const char*					charPtrSArr2[] = { charPtr2,charPtr2,charPtr2,charPtr2 };
	unsigned char*				charPtrSArr3[] = { charPtr3,charPtr3,charPtr3,charPtr3 };
	const unsigned char*		charPtrSArr4[] = { charPtr4,charPtr4,charPtr4,charPtr4 };
	char**						charPtrPtrSArr1[] = { charPtrPtr1,charPtrPtr1,charPtrPtr1,charPtrPtr1 };
	const char**				charPtrPtrSArr2[] = { charPtrPtr2,charPtrPtr2,charPtrPtr2,charPtrPtr2 };
	unsigned char**				charPtrPtrSArr3[] = { charPtrPtr3,charPtrPtr3,charPtrPtr3,charPtrPtr3 };
	const unsigned char**		charPtrPtrSArr4[] = { charPtrPtr4,charPtrPtr4,charPtrPtr4,charPtrPtr4 };
	// Sized arr ptr
	char(*charSArrPtr1)[4] = &charSArr1;
	const char(*charSArrPtr2)[4] = &charSArr2;
	unsigned char(*charSArrPtr3)[4] = &charSArr3;
	const unsigned char(*charSArrPtr4)[4] = &charSArr4;
	char*						(*charPtrSArrPtr1)[4] = &charPtrSArr1;
	const char*					(*charPtrSArrPtr2)[4] = &charPtrSArr2;
	unsigned char*				(*charPtrSArrPtr3)[4] = &charPtrSArr3;
	const unsigned char*		(*charPtrSArrPtr4)[4] = &charPtrSArr4;
	char**						(*charPtrPtrSArrPtr1)[4] = &charPtrPtrSArr1;
	const char**				(*charPtrPtrSArrPtr2)[4] = &charPtrPtrSArr2;
	unsigned char**				(*charPtrPtrSArrPtr3)[4] = &charPtrPtrSArr3;
	const unsigned char**		(*charPtrPtrSArrPtr4)[4] = &charPtrPtrSArr4;
	// Sized arr ptr
	char(**charSArrPtrPtr1)[4] = &charSArrPtr1;
	const char(**charSArrPtrPtr2)[4] = &charSArrPtr2;
	unsigned char(**charSArrPtrPtr3)[4] = &charSArrPtr3;
	const unsigned char(**charSArrPtrPtr4)[4] = &charSArrPtr4;
	char*						(**charPtrSArrPtrPtr1)[4] = &charPtrSArrPtr1;
	const char*					(**charPtrSArrPtrPtr2)[4] = &charPtrSArrPtr2;
	unsigned char*				(**charPtrSArrPtrPtr3)[4] = &charPtrSArrPtr3;
	const unsigned char*		(**charPtrSArrPtrPtr4)[4] = &charPtrSArrPtr4;
	char**						(**charPtrPtrSArrPtrPtr1)[4] = &charPtrPtrSArrPtr1;
	const char**				(**charPtrPtrSArrPtrPtr2)[4] = &charPtrPtrSArrPtr2;
	unsigned char**				(**charPtrPtrSArrPtrPtr3)[4] = &charPtrPtrSArrPtr3;
	const unsigned char**		(**charPtrPtrSArrPtrPtr4)[4] = &charPtrPtrSArrPtr4;

	// Sized arr ptr
	char(&charSArrLRef1)[4] = charSArr1;
	const char(&charSArrLRef2)[4] = charSArr2;
	unsigned char(&charSArrLRef3)[4] = charSArr3;
	const unsigned char(&charSArrLRef4)[4] = charSArr4;
	char*						(&charPtrSArrLRef1)[4] = charPtrSArr1;
	const char*					(&charPtrSArrLRef2)[4] = charPtrSArr2;
	unsigned char*				(&charPtrSArrLRef3)[4] = charPtrSArr3;
	const unsigned char*		(&charPtrSArrLRef4)[4] = charPtrSArr4;
	char**						(&charPtrPtrSArrLRef1)[4] = charPtrPtrSArr1;
	const char**				(&charPtrPtrSArrLRef2)[4] = charPtrPtrSArr2;
	unsigned char**				(&charPtrPtrSArrLRef3)[4] = charPtrPtrSArr3;
	const unsigned char**		(&charPtrPtrSArrLRef4)[4] = charPtrPtrSArr4;

	// Sized arr ptr
	char(&&charSArrRRef1)[4] = std::move(charSArr1);
	const char(&&charSArrRRef2)[4] = std::move(charSArr2);
	unsigned char(&&charSArrRRef3)[4] = std::move(charSArr3);
	const unsigned char(&&charSArrRRef4)[4] = std::move(charSArr4);
	char*						(&&charPtrSArrRRef1)[4] = std::move(charPtrSArr1);
	const char*					(&&charPtrSArrRRef2)[4] = std::move(charPtrSArr2);
	unsigned char*				(&&charPtrSArrRRef3)[4] = std::move(charPtrSArr3);
	const unsigned char*		(&&charPtrSArrRRef4)[4] = std::move(charPtrSArr4);
	char**						(&&charPtrPtrSArrRRef1)[4] = std::move(charPtrPtrSArr1);
	const char**				(&&charPtrPtrSArrRRef2)[4] = std::move(charPtrPtrSArr2);
	unsigned char**				(&&charPtrPtrSArrRRef3)[4] = std::move(charPtrPtrSArr3);
	const unsigned char**		(&&charPtrPtrSArrRRef4)[4] = std::move(charPtrPtrSArr4);

	ColorPrint(0x0C, "-----------// Simple variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(some1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(some2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(char1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(char2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(char3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(char4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(short1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(short2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(short3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(short4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(int1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(int2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(int3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(int4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longLong1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longLong2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longLong3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longLong4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(float1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(float2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(double1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(double2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longDouble1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(longDouble2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(bool1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(bool2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ReturnVoid())>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<const decltype(ReturnConstVoid())>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(nullptr)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<const decltype(nullptr)>::get_name());
	ColorPrint(0x0C, "-----------// Ptr variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrPtr4)>::get_name());
	ColorPrint(0x0C, "-----------// L value ref variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrLRef4)>::get_name());
	ColorPrint(0x0C, "-----------// R value ref variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(ConstCharPtrPtrRRef4)>::get_name());
	ColorPrint(0x0C, "-----------// Arrays variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArr4)>::get_name());
	ColorPrint(0x0C, "-----------// Ptr on Arrays variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrPtrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrPtrPtr4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtrPtr1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtrPtr2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtrPtr3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrPtrPtr4)>::get_name());
	ColorPrint(0x0C, "-----------// Ref on Arrays variables //-------------");
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrLRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrLRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrLRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrLRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charSArrRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrSArrRRef4)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrRRef1)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrRRef2)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrRRef3)>::get_name());
	ColorPrint(0x0B, "Variable type is : ", TypeTreat<decltype(charPtrPtrSArrRRef4)>::get_name());

	using SimpleArr = const int[10];
	using myType = const int***(*const)[10];
	using mySecondType = myType(**const*)[10];
	using FuncType = const SimpleArr*(**(***const)[10])(mySecondType*const*, myType**, mySecondType**(***)[]);
	std::cout << TypeTreat<const SimpleArr>::get_name() << std::endl;
#endif // Finale name testing


	// LZO fun
#if false
	std::ifstream file(argv[0], std::ios::in | std::ios::binary);
	if (!file)
	{
		std::cout << "Cannot open " << argv[0] << std::endl;
		return -1;
	}

	std::unique_ptr<pe_bliss::pe_base> image_;

	try
	{
		image_.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
	}
	catch (const pe_bliss::pe_exception& e)
	{
		std::cout << "Error creating pe_base : " << e.what() << std::endl;
		return -1;
	}

	if (!image_)
	{
		std::cout << "Image value wasn't initialized" << std::endl;
		return -1;
	}

	if (image_->get_pe_type() != pe_bliss::pe_type::pe_type_32)
	{
		std::cout << "File with architecture other than x32 can't be packed" << std::endl;
		return -1;
	}

	if (image_->is_dotnet())
	{
		std::cout << ".NEt image cannot be packed!" << std::endl;
		return -1;
	}


	std::string initial_data;
	
	for (size_t i = 0; i < image_->get_image_sections().size(); ++i) {
		initial_data += image_->get_image_sections()[i].get_raw_data();
	}

	std::cout << "Initial data size : " << initial_data.size() << std::endl;

	std::string out;

	{
		boost::scoped_array<lzo_align_t> work_memory(new lzo_align_t[LZO1Z_999_MEM_COMPRESS]);

		lzo_uint src_length = initial_data.size();

		lzo_uint out_length = 0;

		out.resize(src_length + src_length / 16 + 64 + 3);

		int res = lzo1z_999_compress(reinterpret_cast<const unsigned char*>(initial_data.data()),
			src_length,
			reinterpret_cast<unsigned char*>(&out[0]),
			&out_length,
			work_memory.get());

		if (res != LZO_E_OK)
		{
			std::cout << "Error, with index \"" << res << "\", while compressing data with LZO" << std::endl;
			return -1;
		}

		out.resize(out_length);
	}


	std::cout << "Encrypted data size : " << out.size() << std::endl;


	std::string unencryptedData;
	unencryptedData.resize(initial_data.size());


	lzo_uint out_length = 0;
	lzo1z_decompress(reinterpret_cast<const unsigned char*>(out.data()), out.size(), reinterpret_cast<unsigned char*>(&unencryptedData[0]), &out_length, 0);


	std::cout << "Result : " << ((unencryptedData == initial_data) ? "true" : "false") << std::endl;
#endif // LZO fun


	// Console colors
#if false
	const WORD colors[] =
	{
	0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 
	0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 
	0xC3, 0xD2, 0xE1, 0xF0 };

	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index = 0;

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	// Tell the user how to stop
	SetConsoleTextAttribute(hstdout, 0xEC);
	std::cout << "Press any key to quit.\n" << std::hex;

	// Draw pretty colors until the user presses any key
	for (; index < sizeof(colors) / sizeof(colors[0]); ++index)
	{
		SetConsoleTextAttribute(hstdout, colors[index]);
		std::cout << "\t\t\t\t Hello World (0x" << std::setw(2) << std::setfill('0') << colors[index] << ")\t\t\t\t" << std::endl;
		//if (++index > sizeof(colors) / sizeof(colors[0]))
		//	index = 0;
	}
	FlushConsoleInputBuffer(hstdin);
	std::cout << std::dec;
	// Keep users happy
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	//return 0;
#endif // Console colors


	// Encryptions
#if false
	std::string input = "This is simple string, because this is simple string, so this is simple string";

	for (size_t m_i = 0; m_i < 16; ++m_i)
	{
		std::string key;

		{
			std::mt19937 gen{ static_cast<size_t>(std::time(0)) };
			key.resize(gen() % 7 + 10);
			for (size_t i = 0; i < key.size(); ++i) {
				key[i] = gen() % 225 + 15;
			}
		}

		std::string encrypted = EncryptMaskAsStrings(input, key);

		std::string output;
		output.resize(input.size());

		key.push_back(0x00);
		DecryptMaskAsStrings(encrypted.data(), &output[0], output.size(), key.data());

		//std::cout << input << std::endl;
		std::cout << output << std::endl;
		//std::cout << encrypted << std::endl;
	}
#endif // Encryptions


	// Value types testing
#if false
	const int a = 5;

	decltype(auto) decl_lval1 = a;
	decltype(auto) decl_lval2 = (a);
	//decltype(auto) decl_rval1 = GetRVal();
	//decltype(auto) decl_rval2 = (GetRVal());
	decltype(auto) decl_rval3 = 5;
	decltype(auto) decl_rval4 = (5);
	decltype(auto) decl_rval5 = std::move(a);
	decltype(auto) decl_rval6 = (std::move(a));

	//std::cout << "Decltype : " << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_lval1)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_lval2)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval1)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval2)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval3)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval4)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval5)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(decl_rval6)>::get_name() << std::endl;

	auto auto_lval1 = a;
	auto auto_lval2 = (a);
	//auto auto_rval1 = GetRVal();
	//auto auto_rval2 = (GetRVal());
	auto auto_rval3 = 5;
	auto auto_rval4 = (5);
	auto auto_rval5 = std::move(a);
	auto auto_rval6 = (std::move(a));


	auto& lauto_lval1 = a;
	auto& lauto_lval2 = (a);


	auto&& fauto_lval1 = a;
	auto&& fauto_lval2 = (a);
	//auto&& fauto_rval1 = GetRVal();
	//auto&& fauto_rval2 = (GetRVal());
	auto&& fauto_rval3 = 5;
	auto&& fauto_rval4 = (5);
	auto&& fauto_rval5 = std::move(a);
	auto&& fauto_rval6 = (std::move(a));

	//std::cout << "Auto&& : " << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_lval1)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_lval2)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval1)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval2)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval3)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval4)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval5)>::get_name() << std::endl;
	//std::cout << bwn::TypeTreat<decltype(fauto_rval6)>::get_name() << std::endl;

	//ForwardTest(a);
	//ForwardTest((a));
	////ForwardTest(GetRVal());
	////ForwardTest((GetRVal()));
	//ForwardTest(5);
	//ForwardTest((5));
	//ForwardTest("here");
	//ForwardTest(("here"));


	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype(a)>(a))>::get_name() << std::endl;
	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype(a)>((a)))>::get_name() << std::endl;
	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype(5)>(5))>::get_name() << std::endl;
	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype((5))>((5)))>::get_name() << std::endl;
	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype("here")>("here"))>::get_name() << std::endl;
	std::cout << "Variable : " << bwn::TypeTreat<decltype(std::forward<decltype(("here"))>(("here")))>::get_name() << std::endl;

	std::vector<int> arr1{ 1 };
	int arr2[1];

	using arr_t = int[1];

	const arr_t& arr3 = arr2;

	//ArrayTest(arr1);
	//ArrayTest(arr2);

	//ArrayTest<int[1]>(arr2);
	//ArrayTest<int(&)[1]>(arr2);


#define MY_ARR arr3

//	std::cout << "auto : " << std::endl;
//	for (auto it : MY_ARR) {
//		std::cout << '\t' << bwn::TypeTreat<decltype(it)>::get_name() << std::endl;
//	}
//	std::cout << "auto& : " << std::endl;
//	for (const auto& it : MY_ARR) {
//		std::cout << '\t' << bwn::TypeTreat<decltype(it)>::get_name() << std::endl;
//	}
//	std::cout << "auto&& : " << std::endl;
//	for (auto&& it : MY_ARR) {
//		std::cout << '\t' << bwn::TypeTreat<decltype(it)>::get_name() << std::endl;
//	}
#endif // Value types testing


	// SRJUNK_HELPER
#if false
	std::string data;
	
	if (argc < 4)
	{
		std::ifstream file(argv[1], std::ios::in | std::ios::binary);
		
		if (!file) 
		{
			std::cout << "Can't open the file : " << argv[1] << std::endl;
			return -1;
		}

		file.seekg(0, std::ios::end);
		data.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		data.assign((std::istreambuf_iterator<char>(file)),
					std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "Incodrect number of parameters" << std::endl;
		return -1;
	}

	std::cout << "File size : " << data.size() << '\n';;

	size_t count = 4;

	if (argc > 2) 
	{
		try
		{
			count = boost::lexical_cast<size_t, std::string>(argv[2]);
		}
		catch (const std::exception&) 
		{
		}
	}

	std::regex reg;
	try
	{
		reg = "UintList<([\\x00-\\xFF]+?(?=>))>";
	}
	catch (const std::regex_error& e)
	{
		std::cout << "Exception at regex creation thrown : " << e.what() << std::endl;
		return -1;
	}

	std::sregex_iterator iter(data.begin(), data.end(), reg);
	std::sregex_iterator end;
	std::vector<std::string> results;

	for (; iter != end; ++iter) {
		results.push_back(iter->str());
	}

	std::mt19937 gen{ static_cast<size_t>(std::time(0)) };

	size_t pos = 0;
	for (auto it = results.begin(); it != results.end(); ++it) 
	{
		pos = data.find(*it, pos);

		if (pos > data.size()) {
			continue;
		}

		std::string stub = "UintList<";

		for (size_t i = 0; i < count; ++i)
		{
			stub += std::to_string(gen() % 0x100000);
			if (i < count - 1) {
				stub += ", ";
			}
		}
		stub += ">";

		data.replace(pos, it->size(), stub);
		pos += stub.size();
	}

	{
		std::ofstream file(argv[1], std::ios::out | std::ios::binary);
		if (!file) 
		{
			std::wcout << "Can't open file for writing" << std::endl;
			return -1;
		}

		file.write(data.data(), data.size());
	}

	std::cout << "New file size : " << data.size() << std::endl;
#endif // SRJUNK_HELPER


	// Multishot
#if false
	namespace po = boost::program_options;
	
	po::options_description visible_options("PE-PACKER multi fire");

	std::string file_path;
	std::string name_stub;
	std::string options_file;
	std::string packing_file;
	size_t start_index;
	size_t end_index;
	size_t step_index;
	bool console_output = false;

	try
	{
		po::options_description cmdline;

		visible_options.add_options()
			("name,n", po::value<std::string>(&name_stub)->default_value("test"), "General name of output files")
			("options,o", po::value<std::string>(&options_file)->default_value("options.txt"), "File with rest of options")
			("start,s", po::value<size_t>(&start_index)->default_value(1), "Start index in names")
			("end,e", po::value<size_t>(&end_index)->default_value(5), "Finale index in names")
			("step,t", po::value<size_t>(&step_index)->default_value(1), "Step of the indexsation")
			("console,c", po::value<bool>(&console_output)->default_value(0), "Print output also to the console")
			;

		cmdline.add(visible_options);

		cmdline.add_options()
			("pack,p", po::value<std::string>(&file_path), "Exe file to pack")
			;


		po::positional_options_description desc_pos;
		desc_pos.add("input", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(cmdline).positional(desc_pos).run(), vm);
		po::notify(vm);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << visible_options << std::endl;
		return -1;
	}

	if (file_path.empty() || !(boost::filesystem::exists(file_path))) 
	{
		std::cout << "File to pack isn't found, try to specify it with \"-i\" option" << std::endl;
		return -1;
	}

	std::cout << "Pack file path : " << file_path << std::endl;

	if (!step_index) {
		step_index = 1;
	}

	std::string rest_options;

	{
		std::ifstream file(options_file, std::ios::binary | std::ios::in);

		if (file) 
		{
			file.seekg(0, std::ios::end);
			rest_options.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			rest_options.assign(
				std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>());

			boost::trim(rest_options);
		}
	}

	if (start_index > end_index) {
		end_index = start_index;
	}

	boost::filesystem::path packer = boost::process::search_path("pe-packer.exe");

	if (packer.empty()) 
	{
		std::cout << "Packer wasn't found (try change name to pe-packer.exe)" << std::endl;
		return -1;
	}

	rest_options = " -i " + file_path + " " + rest_options;

	for (; start_index <= end_index; start_index += step_index)
	{
		std::cout << "==================// executing number : " << start_index << "//===================" << std::endl;

		std::ofstream log_file;
		{
			std::string log_name = "log" + std::to_string(start_index) + ".txt";
			log_file.open(log_name);
			if (!log_file) {
				std::cout << "Failed to open a log : \"" << log_name << "\"" << std::endl;
			}
			else {
				std::cout << "Output to : \"" << log_name << "\"" << std::endl;
			}
		}

		boost::process::ipstream is; //reading pipe-stream
		boost::process::child c(boost::filesystem::absolute(packer), rest_options, "-o " + name_stub + std::to_string(start_index) + ".exe", boost::process::std_out > is);

		std::string data;
		std::string line;

		while (c.running() && std::getline(is, line) && !line.empty())
		{
			if (log_file) {
				log_file << line;
			}
			if (console_output) {
				std::cout << line << std::endl;
			}
		}

		c.wait();

		if (log_file) {
			log_file.flush();
		}
		//if (console_output) {
		//	std::cout.flush();
		//}

		std::cout << "==============================//===============================" << std::endl;
	}
#endif // Multishot


	// IconChecker
#if false
	namespace po = boost::program_options;

	po::options_description visible_options("Exe icon power");

	std::string input_file;
	std::string output_file;
	size_t start_index;
	size_t end_index;
	int bits_shift;
	bool turn_alpha;

	try
	{
		po::options_description cmdline;

		visible_options.add_options()
			("help,h", "Prints available commands")
			("output,o", po::value<std::string>(&output_file), "Output file")
			("start,s", po::value<size_t>(&start_index)->default_value(0), "Start index icons")
			("end,e", po::value<size_t>(&end_index)->default_value(0), "Finale index in icons")
			("shift,t", po::value<int>(&bits_shift)->default_value(-5), "Shift of bits per byte of icons (negative for left shift)")
			("alpha,a", po::value<bool>(&turn_alpha)->default_value(false), "Turn alpha to max")
			;

		cmdline.add(visible_options);

		cmdline.add_options()
			("input,i", po::value<std::string>(&input_file), "Exe file to use icons from")
			;


		po::positional_options_description desc_pos;
		desc_pos.add("input", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(cmdline).positional(desc_pos).run(), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << visible_options;
			return 0;
		}

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << visible_options << std::endl;
		return -1;
	}

	if (input_file.empty() || !(boost::filesystem::exists(input_file)))
	{
		std::cout << "File isn't found, try to specify it with \"-i\" option" << std::endl;
		return -1;
	}

	std::string file_data;

	std::vector<std::pair<size_t, size_t>> icon_offsets;

	{
		std::ifstream file(input_file, std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open \"" << input_file << '\"' << std::endl;
			return -1;
		}
		file.seekg(0, std::ios::end);
		file_data.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		file_data.assign(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}

	std::cout << "File size : " << file_data.size() << std::endl;

	{
		std::ifstream file(input_file, std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open \"" << input_file << '\"' << std::endl;
			return -1;
		}

		std::unique_ptr<pe_bliss::pe_base> image;
		try
		{
			image.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
		}
		catch (const pe_bliss::pe_exception& e)
		{
			std::cout << "Error creating pe_base : " << e.what() << std::endl;
			return -1;
		}

		if (!image)
		{
			std::cout << "Image value wasn't initialized" << std::endl;
			return -1;
		}

		if (image->is_dotnet())
		{
			std::cout << ".NET image cannot be opened!" << std::endl;
			return -1;
		}


		if (image->has_resources())
		{

			pe_bliss::resource_directory root_dir = pe_bliss::get_resources(*image);
			pe_bliss::pe_resource_viewer res(root_dir);

			pe_bliss::pe_resource_viewer::resource_id_list icon_id_list(res.list_resource_ids(pe_bliss::pe_resource_viewer::resource_icon));
			pe_bliss::pe_resource_viewer::resource_name_list icon_name_list(res.list_resource_names(pe_bliss::pe_resource_viewer::resource_icon));
			
			try
			{

				for (auto it = icon_id_list.begin(); it != icon_id_list.end(); ++it)
				{
					std::string icon_data = res.get_resource_data_by_id(pe_bliss::pe_resource_viewer::resource_icon, *it).get_data();

					size_t offset = file_data.find(icon_data);

					if (offset < file_data.size()) {
						icon_offsets.push_back({offset, icon_data.size()});
					}
					else {
						icon_offsets.push_back({ 0, 0 });
					}
				}

				for (auto it = icon_name_list.begin(); it != icon_name_list.end(); ++it)
				{
					const std::string& icon_data = res.get_resource_data_by_name(pe_bliss::pe_resource_viewer::resource_icon, *it).get_data();

					size_t offset = file_data.find(icon_data);
					if (offset < icon_data.size()) {
						icon_offsets.push_back({ offset, icon_data.size() });
					}
					else {
						icon_offsets.push_back({ 0, 0 });
					}
				}
			}
			catch (const pe_bliss::pe_exception& e)
			{
				std::cout << "Resource error (icons) : " << e.what() << std::endl;
				return -1;
			}

		}
		else
		{
			std::cout << "Resources wasn't found" << std::endl;
			return -1;
		}
	}

	if (end_index < start_index) {
		end_index = start_index;
	}

	std::cout << "Number of icons : " << icon_offsets.size() << std::endl;

	for (size_t i = start_index; i <= end_index && i < icon_offsets.size(); ++i)
	{
		std::cout << "Trying (" << i << ")" << std::endl;

		if (!icon_offsets[i].first 
			|| !icon_offsets[i].second 
			|| icon_offsets[i].first + icon_offsets[i].second > file_data.size()) 
		{
			std::cout << "Incorect icon (0x" << std::hex
				<< std::setw(8) << std::setfill('0') << icon_offsets[i].first << " | 0x"
				<< std::setw(8) << std::setfill('0') << icon_offsets[i].second << ")" 
				<< std::dec << std::endl;
			continue;
		}

		std::cout << "Icon parameters : 0x" << std::hex
			<< std::setw(8) << std::setfill('0') << icon_offsets[i].first << " | 0x"
			<< std::setw(8) << std::setfill('0') << icon_offsets[i].second 
			<< std::dec << std::endl;

		std::string icon_data(file_data.begin() + icon_offsets[i].first, 
			file_data.begin() + icon_offsets[i].first + icon_offsets[i].second);

		if (icon_data.size() < sizeof(BITMAPINFOHEADER)) 
		{
			std::cout << "Not enough size was given for \"BITMAPINFOHEADER\" (" << i << ')' << std::endl;
			continue;
		}

		const BITMAPINFOHEADER image_info = *reinterpret_cast<const BITMAPINFOHEADER*>(&icon_data[0]);

		if (sizeof(image_info) != image_info.biSize) 
		{
			std::cout << "Wrong (or old) \"BITMAPINFOHEADER\" (" << i << ')' << std::endl;
			continue;
		}

		if (image_info.biCompression != BI_RGB) 
		{
			std::cout << "BMP compression can't be randomize yet (" << i << ')' << std::endl;
			continue;
		}

		for (size_t i = sizeof(BITMAPINFOHEADER); i + 4 < icon_data.size(); i += sizeof(DWORD))
		{
			DWORD color = *reinterpret_cast<DWORD*>(&icon_data[i]);

			for (size_t b = 0; b < 3; ++b)
			{
				size_t byte_mask = 0x000000FF << (b * 8);
				size_t byte_color = color & byte_mask;
				color = (color & ~byte_mask) 
					| (((bits_shift < 0) ? (byte_color << (-bits_shift)) : (byte_color >> bits_shift)) & byte_mask);
			}

			if (turn_alpha) {
				color |= 0xFF000000;
			}

			*reinterpret_cast<DWORD*>(&icon_data[i]) = color;
		}

		icon_data.resize(icon_offsets[i].second);
		file_data.replace(icon_offsets[i].first, icon_offsets[i].second, icon_data);

		std::cout << "Icon (" << i << ") changed" << std::endl;
	}


	{
		if (output_file.empty()) {
			output_file = input_file;
		}

		std::ofstream file(output_file, std::ios::out | std::ios::binary);

		if (!file) 
		{
			std::cout << "Can't open file \"" << output_file << "\" for writing" << std::endl;
			return -1;
		}

		file << file_data;
	}
#endif // IconChecker


	// EazyBMP++
#if false
	namespace po = boost::program_options;

	po::options_description visible_options("Exe icon power");

	std::experimental::filesystem::path input_file;
	std::experimental::filesystem::path output_file;
	size_t start_index;
	size_t end_index;
	int bits_shift;
	bool turn_alpha;

	try
	{
		po::options_description cmdline;

		visible_options.add_options()
			("output,o", po::value<std::experimental::filesystem::path>(&output_file), "Output file")
			("start,s", po::value<size_t>(&start_index)->default_value(0), "Start index icons")
			("end,e", po::value<size_t>(&end_index)->default_value(1), "Finale index in icons")
			("shift,t", po::value<int>(&bits_shift)->default_value(-5), "Shift of bits per byte of icons (negative for left shift)")
			("alpha,a", po::value<bool>(&turn_alpha)->default_value(false), "Turn alpha to max")
			;

		cmdline.add(visible_options);

		cmdline.add_options()
			("input,i", po::value<std::experimental::filesystem::path>(&input_file), "Exe file to use icons from")
			;


		po::positional_options_description desc_pos;
		desc_pos.add("input", 1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(cmdline).positional(desc_pos).run(), vm);
		po::notify(vm);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << visible_options << std::endl;
		return -1;
	}

	if (input_file.empty() || !(boost::filesystem::exists(input_file.string())))
	{
		std::cout << "File isn't found, try to specify it with \"-i\" option" << std::endl;
		return -1;
	}


	std::string file_data;

	std::vector<std::pair<size_t, size_t>> icon_offsets;

	{
		std::cout << "Reading file \"" << input_file << "\"" << std::endl;
		std::ifstream file(input_file, std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open \"" << input_file << '\"' << std::endl;
			return -1;
		}
		file.seekg(0, std::ios::end);
		file_data.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		file_data.assign(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}
	std::cout << "File size : " << file_data.size() << std::endl;

	{
		std::ifstream file(input_file, std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << "Cannot open \"" << input_file << '\"' << std::endl;
			return -1;
		}

		std::unique_ptr<pe_bliss::pe_base> image;
		try
		{
			image.reset(new pe_bliss::pe_base(pe_bliss::pe_factory::create_pe(file, false)));
		}
		catch (const pe_bliss::pe_exception& e)
		{
			std::cout << "Error creating pe_base : " << e.what() << std::endl;
			return -1;
		}

		if (!image)
		{
			std::cout << "Image value wasn't initialized" << std::endl;
			return -1;
		}

		if (image->is_dotnet())
		{
			std::cout << ".NET image cannot be packed!" << std::endl;
			return -1;
		}


		if (image->has_resources())
		{

			pe_bliss::resource_directory root_dir = pe_bliss::get_resources(*image);
			pe_bliss::pe_resource_viewer res(root_dir);

			pe_bliss::pe_resource_viewer::resource_id_list icon_id_list(res.list_resource_ids(pe_bliss::pe_resource_viewer::resource_icon));
			pe_bliss::pe_resource_viewer::resource_name_list icon_name_list(res.list_resource_names(pe_bliss::pe_resource_viewer::resource_icon));

			try
			{

				for (auto it = icon_id_list.begin(); it != icon_id_list.end(); ++it)
				{
					std::string icon_data = res.get_resource_data_by_id(pe_bliss::pe_resource_viewer::resource_icon, *it).get_data();

					size_t offset = file_data.find(icon_data);

					if (offset < file_data.size()) {
						icon_offsets.push_back({ offset, icon_data.size() });
					}
					else {
						icon_offsets.push_back({ 0, 0 });
					}
				}

				for (auto it = icon_name_list.begin(); it != icon_name_list.end(); ++it)
				{
					const std::string& icon_data = res.get_resource_data_by_name(pe_bliss::pe_resource_viewer::resource_icon, *it).get_data();

					size_t offset = file_data.find(icon_data);
					if (offset < icon_data.size()) {
						icon_offsets.push_back({ offset, icon_data.size() });
					}
					else {
						icon_offsets.push_back({ 0, 0 });
					}
				}
			}
			catch (const pe_bliss::pe_exception& e)
			{
				std::cout << "Resource error (icons) : " << e.what() << std::endl;
				return -1;
			}

		}
		else
		{
			std::cout << "Resources wasn't found" << std::endl;
			return -1;
		}
	}

	if (end_index < start_index) {
		end_index = start_index;
	}

	std::cout << "Number of icons : " << icon_offsets.size() << std::endl;

	for (size_t i = start_index; i <= end_index && i < icon_offsets.size(); ++i)
	{
		std::cout << "Trying (" << i << ")" << std::endl;

		if (!icon_offsets[i].first
			|| !icon_offsets[i].second
			|| icon_offsets[i].first + icon_offsets[i].second > file_data.size())
		{
			std::cout << "Incorect icon (0x" << std::hex
				<< std::setw(8) << std::setfill('0') << icon_offsets[i].first << " | 0x"
				<< std::setw(8) << std::setfill('0') << icon_offsets[i].second << ")"
				<< std::dec << std::endl;
			continue;
		}

		std::cout << "Icon parameters : 0x" << std::hex
			<< std::setw(8) << std::setfill('0') << icon_offsets[i].first << " | 0x"
			<< std::setw(8) << std::setfill('0') << icon_offsets[i].second
			<< std::dec << std::endl;

		std::string icon_data(file_data.begin() + icon_offsets[i].first,
			file_data.begin() + icon_offsets[i].first + icon_offsets[i].second);

		try
		{
			icon_data = ChangeBMPIcon(icon_data);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception while working with icon (" << i << ") : " << e.what() << std::endl;
			continue;
		}

		icon_data.resize(icon_offsets[i].second);
		file_data.replace(icon_offsets[i].first, icon_offsets[i].second, icon_data);

		std::cout << "Icon (" << i << ") changed" << std::endl;
	}


	{
		std::experimental::filesystem::path new_file_path;

		if (!output_file.empty())
		{
			new_file_path = output_file;
		}
		else
		{
			new_file_path = input_file;
			new_file_path.replace_extension("");

			new_file_path.replace_filename(new_file_path.filename().string() + "_packed");
			new_file_path.replace_extension(input_file.extension());

		}


		std::ofstream file(new_file_path, std::ios::out | std::ios::binary);
		
		if (!file)
		{
			std::cout << "Can't open file \"" << new_file_path << "\" for writing" << std::endl;
			return -1;
		}
		
		file << file_data;
		
		std::cout << "File writen to \"" << new_file_path << "\"" << std::endl;
	}
#endif // EAZYBMP++


	// Json fun
#if false
	Json::Value root;
	
	try
	{


		{
			boost::filesystem::ifstream file("TestJson.json", std::ios::in);

			if (!file) {
				ErrorExit("No file");
			}

			file >> root;
			//Json::CharReaderBuilder rbuilder;
			//std::string errs;
			//if (!Json::parseFromStream(rbuilder, file, &root, &errs)) {
			//	ErrorExit("Parse error : " + errs);
			//}
		}

		//for (size_t i = 0; i < root.size(); ++i) {
		//	std::cout << root.get(i, {}).asString() << std::endl;
		//}
		
		std::cout << root["one"].asUInt()	<< std::endl;
		std::cout << root["two"].asUInt()	<< std::endl;
		std::cout << root["three"].asUInt()	<< std::endl;
		std::cout << root["four"].asUInt()	<< std::endl;
		std::cout << root["five"].asUInt()	<< std::endl;

	}
	catch (const std::exception& e)
	{
		ErrorExit(std::string("Exception : ") + e.what());
	}
#endif // Json fun


	// CODE file dumper
#if false
	try {
		enum DUMP_OPTIONS
		{
			DUMP_DATA = 0x01,
			DUMP_OPS = 0x02,
			DUMP_RELOC = 0x04,
			DUMP_CALLS = 0x08,
			DUMP_ENTRY = 0x10,
			DUMP_IMP = 0x20
		};

		boost::filesystem::path file_path;
		size_t dump_options = 0;

		constexpr std::ostream& (*endl)(std::ostream&) = std::endl<char, std::char_traits<char>>;

		{
			namespace po = boost::program_options;

			po::options_description visible_options("Code file checker options");

			po::options_description cmdline;

			visible_options.add_options()
				("help", "Prints possible options.")
				("dump-data", "Do dump code symbols.")
				("dump-ops", "Do dump code operators.")
				("dump-reloc", "Do dump code relocations.")
				("dump-calls", "Do dump code exturnal calls.")
				("dump-entries", "Do dump code entries.")
				("dump-imports", "Do dump imports data.");

			cmdline.add(visible_options);

			cmdline.add_options()("input,i", po::value<boost::filesystem::path>(&file_path), "File to check");


			po::positional_options_description desc_pos;
			desc_pos.add("input", 1);

			po::variables_map vm;
			po::store(po::command_line_parser(argc, argv)
						  .options(cmdline)
						  .positional(desc_pos)
						  .run(),
				vm);
			po::notify(vm);

			if (vm.count("help")) {
				std::cout << visible_options;
				return 0;
			}

			if (vm.count("dump-data")) {
				dump_options |= DUMP_DATA;
			}
			if (vm.count("dump-ops")) {
				dump_options |= DUMP_OPS;
			}
			if (vm.count("dump-reloc")) {
				dump_options |= DUMP_RELOC;
			}
			if (vm.count("dump-calls")) {
				dump_options |= DUMP_CALLS;
			}
			if (vm.count("dump-entries")) {
				dump_options |= DUMP_ENTRY;
			}
			if (vm.count("dump-imports")) {
				dump_options |= DUMP_IMP;
			}
		}

		std::cout << "File : " << file_path << std::endl;

		CodeFile file_handler;
		file_handler.LoadCodeFile(file_path);

		std::cout << "\tSection id of entry point : " << file_handler.GetEPSectionId() << std::endl;
		std::cout << "\tEntry point offset : 0x"
				  << std::hex << std::setw((!!(file_handler.GetEP() >> 16) + 1) * 4) << std::setfill('0') << file_handler.GetEP()
				  << std::dec << " (" << file_handler.GetEP() << ")" << std::endl;

		{
			std::vector<CodeFile::ImportLibrary> imports = file_handler.GetImports();
			std::cout << "\tImports number : " << imports.size() << std::endl;

			if ((dump_options & DUMP_IMP) && imports.size())
			{
				for (auto lib = imports.begin(); lib != imports.end(); ++lib)
				{
					std::cout << "\t(" << (lib - imports.begin()) << ") " << lib->first << std::endl;

					for (auto func = lib->second.begin(); func != lib->second.end(); ++func) {
						std::cout << "\t\t(" << (func - lib->second.begin()) << ") " << *func << std::endl;
					}
				}
			}
		}

		for (auto it = file_handler.GetSections().begin(); it != file_handler.GetSections().end(); ++it) 
		{
			std::cout << "\nSection : \"" << std::setw(10) << std::setfill(' ') << std::left << (it->name_ + "\"") << "(" << (it - file_handler.GetSections().begin()) << ")" << std::endl;
			std::cout << "\tSize of data : 0x"
					  << std::hex << std::setw((!!(it->data_.size() >> 16) + 1) * 4) << std::setfill('0') << std::right << it->data_.size()
					  << std::dec << " (" << it->data_.size() << ')' << std::endl;

			if (dump_options & DUMP_DATA) {
				PrintAsHex(it->data_);
				std::cout << std::endl;
			}

			if (dump_options & DUMP_OPS) {
			}

			std::cout << "\n\tRelocations number : " << it->relocs_.size() << std::endl;

			if ((dump_options & DUMP_RELOC) && !it->relocs_.empty()) 
			{
				for (auto reloc = it->relocs_.begin(); reloc != it->relocs_.end(); ++reloc) {
					std::cout << "\t(" << std::setw(4) << std::setfill(' ') << std::left << (std::to_string(reloc - it->relocs_.begin()) + ")")
							  << "| offset : 0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << reloc->offset_ << std::dec
							  << " " << std::setw(13) << std::setfill(' ') << std::left << ("(" + std::to_string(reloc->offset_) + ")")
							  << "| section id : " << std::setw(4) << std::setfill(' ') << std::left << reloc->section_id_
							  << "| entry id : " << reloc->entry_id_ << std::endl;
				}
			}

			std::cout << "\n\tExturnal calls number : " << it->ext_calls_.size() << std::endl;

			if ((dump_options & DUMP_CALLS) && !it->ext_calls_.empty())
			{
				for (auto call = it->ext_calls_.begin(); call != it->ext_calls_.end(); ++call) {
					std::cout << "\t(" << std::setw(4) << std::setfill(' ') << std::left << (std::to_string(call - it->ext_calls_.begin()) + ")")
						<< "| offset : 0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << call->offset_ << std::dec
						<< " " << std::setw(13) << std::setfill(' ') << std::left << ("(" + std::to_string(call->offset_) + ")")
						<< "| section id : " << std::setw(4) << std::setfill(' ') << std::left << call->section_id_
						<< "| entry id : " << call->entry_id_ << std::endl;
				}
			}

			std::cout << "\n\tImport calls number : " << it->imp_calls_.size() << std::endl;

			if ((dump_options & DUMP_IMP) && !it->imp_calls_.empty())
			{
				for (auto call = it->imp_calls_.begin(); call != it->imp_calls_.end(); ++call) {
					std::cout << "\t(" << std::setw(4) << std::setfill(' ') << std::left << (std::to_string(call - it->imp_calls_.begin()) + ")")
						<< "| offset : 0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << call->offset_ << std::dec
						<< " " << std::setw(13) << std::setfill(' ') << std::left << ("(" + std::to_string(call->offset_) + ")")
						<< "| library id : " << std::setw(4) << std::setfill(' ') << std::left << call->lib_id_
						<< "| function id : " << call->func_id_<< std::endl;
				}
			}

			std::cout << "\n\tEntries number : " << it->entries_.size() << std::endl;

			if ((dump_options & DUMP_ENTRY) && !it->entries_.empty()) 
			{
				for (auto entry = it->entries_.begin(); entry != it->entries_.end(); ++entry) {
					std::cout << "\t(" << std::setw(4) << std::setfill(' ') << std::left << (std::to_string(entry - it->entries_.begin()) + ")")
							  << "| offset : 0x" << std::hex << std::setw(8) << std::setfill('0') << std::right << *entry << std::dec
							  << " " << std::setw(13) << std::setfill(' ') << std::left << ("(" + std::to_string(*entry) + ")") << std::endl;
				}
			}
		}

		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Exception : " << e.what() << std::endl;
		return -1;
	}
#endif // CODE file dumper


	// XLS fun
#if false
	// Get the workbook handler
	xlslib_core::workbook wb;
	xlslib_core::worksheet* sh = wb.sheet("sheet");

	sh->label(1,1,"Label 1|1");
	sh->label(5,1,"Label 5|1");
	sh->label(9,1,"Label 9|1");

	sh->label(1,5,"Label 1|5");
	sh->label(5,5,"Label 5|5");
	sh->label(9,5,"Label 9|5");

	sh->label(1,9,"Label 1|9");
	sh->label(5,9,"Label 5|9");
	sh->label(9,9,"Label 9|9");

	sh->colwidth(1, 3000);
	sh->colwidth(2, 300);
	sh->colwidth(3, 300);
	sh->colwidth(4, 300);
	sh->colwidth(5, 3000);
	sh->colwidth(6, 300);
	sh->colwidth(7, 300);
	sh->colwidth(8, 300);
	sh->colwidth(9, 3000);

	sh->rowheight(1, 3000);
	sh->rowheight(2, 300);
	sh->rowheight(3, 300);
	sh->rowheight(4, 300);
	sh->rowheight(5, 3000);
	sh->rowheight(6, 300);
	sh->rowheight(7, 300);
	sh->rowheight(8, 300);
	sh->rowheight(9, 3000);

#if false
	xlslib_core::worksheet* sh2 = wb.sheet("sheet2");


	// Title
	sh->label(1,1,"test1");
	sh->rowheight(1,100);
	sh->rowheight(2,150);

	// Title
	sh2->label(1,1,"test3");
	sh2->rowheight(1,100);
	sh2->rowheight(2,150);
	sh2->label(2,1,"test4");
	sh2->number(3,1,1.0);
	sh2->number(4,1,2.0);
	sh2->number(5,1,3.0);

	sh->label(2,1,"test2");
	sh->number(3,1,1.0);
	sh->number(4,1,2.0);
	sh->number(5,1,3.0);

#if 0
	printf("    # limit: "); // what the heck is this???
   char buf[100];
   gets(buf);
   unsigned32_t lim = atoi(buf);
#else
	unsigned32_t lim = 42;
#endif
	//printf("\n    # limit: %d\n", lim); // >= 14 --> error to load sheet #2; <= 13 = ok

	unsigned32_t j, k;
	for (j = 0 ; j <= 127; j++)
	{
		for (k = 0; k <= 128; k++)
		{
			//sh->number(j, k, (0.0 + j + k ) / 1000);
			if (k == 128 && j > lim)
				;
			else
				sh->blank(j, k);
		}
	}

	// WARNING: column and row numbers are zero based in xlslib, but Excel starts numbering the buggers at '1' instead!
	sh->number(20,2,1.0);
	sh->number(26,4,2.0);
	sh->number(30,6,3.0);
	std::string s("This tab should should show three numbers: two in row 131/133 + one in row 132 at columns 129(DY)/173(FQ) respectively");
	sh->label(1,1,s);
#endif

	int err = wb.Dump("testCPP.xls");

	if (err != NO_ERRORS) {
		std::cout << "Error occurred : " << err << std::endl;
	}
#endif // XLS fun


	// XLNT fun
#if false
	xlnt::workbook wb;
	xlnt::worksheet ws = wb.active_sheet();

	ws.cell(1,1).value("Lable 1|1");
	ws.cell(5,1).value("Lable 5|1");
	ws.cell(9,1).value("Lable 9|1");

	ws.cell(1,5).value("Lable 1|5");
	ws.cell(5,5).value("Lable 5|5");
	ws.cell(9,5).value("Lable 9|5");

	ws.cell(1,9).value("Lable 1|9");
	ws.cell(5,9).value("Lable 5|9");
	ws.cell(9,9).value("Lable 9|9");

	ws.column_properties(1).width = 25;
	ws.column_properties(2).width = 5;
	ws.column_properties(3).width = 5;
	ws.column_properties(4).width = 5;
	ws.column_properties(5).width = 50;
	ws.column_properties(6).width = 5;
	ws.column_properties(7).width = 5;
	ws.column_properties(8).width = 5;
	ws.column_properties(9).width = 75;

	ws.row_properties(1).height = 10;
	ws.row_properties(2).height = 5;
	ws.row_properties(3).height = 5;
	ws.row_properties(4).height = 5;
	ws.row_properties(5).height = 25;
	ws.row_properties(6).height = 5;
	ws.row_properties(7).height = 5;
	ws.row_properties(8).height = 5;
	ws.row_properties(9).height = 50;

	//ws.cell("A1").value(5);
	//ws.cell("B2").value("string data");
	//ws.cell("C3").formula("=RAND()");
	//ws.merge_cells("C3:C4");
	//ws.freeze_panes("B2");
	wb.save("test.xlsx");
#endif // XLNT fun


	// Iterators fun
#if false
	std::cout << std::boolalpha;

	using ValueT = int;
	using IterT = int*;

	std::vector<int> vector_ {1,2,3,4,5};
	std::list<int> list_{6,7,8,9,10};
	std::array<int, 5> array_{11,12,13,14,15};
	std::forward_list<int> flist_{12,13,14,15,16};
	int carray_[] = {16,17,18,19,20};
	int* ptr_ = carray_;

	bwn::BidirectionalIterator<int> b_iter{list_.begin()};

	ForwardIteratorPrint(vector_.begin(), vector_.end());
	ForwardIteratorPrint(list_.begin(), list_.end());
	ForwardIteratorPrint(array_.begin(), array_.end());
	ForwardIteratorPrint(carray_, carray_ + 5);

	BackwardIteratorPrint(vector_.begin(), vector_.end());
	BackwardIteratorPrint(list_.begin(), list_.end());
	BackwardIteratorPrint(array_.begin(), array_.end());
	BackwardIteratorPrint(carray_, carray_ + 5);
#endif // Iterators fun


	// Neargye libs fun
#if false
	enum Names{
		First,
		Second,
		Third
	};

	Names enum_name = First;
	std::cout << "name : " << magic_enum::enum_name(enum_name) << std::endl;

	enum_name = Second;
	std::cout << "name : " << magic_enum::enum_name(enum_name) << std::endl;
#endif // Neargye libs fun


	// "C++ Templates. Second Edition" fun
#if false
	std::cout << std::boolalpha;

	std::cout << isCallableWith(&TestFunction, 1) << std::endl;
	std::cout << isCallableWith(&TestFunction, 2) << std::endl;
	std::cout << isCallableWith(&TestFunction, "string") << std::endl;
	std::cout << isCallableWith(&TestFunction, std::string()) << std::endl;
#endif // "C++ Templates. Second Edition" fun


	// Numeral system fun
#if false
	bwn::NumeralSystem number(10, 1234);

	std::cout << number << std::endl;

	number.ChangeBase(6);

	std::cout << number << std::endl;

	number.ChangeBase(2);

	std::cout << number << std::endl;

	number.ChangeBase(10);

	std::cout << number << std::endl;
#endif // Numeral system fun


	// Testing poligon
#if false
	bool quit = false;
	std::string input;

	std::vector<int32_t> false_container{ 15923423, 985234, 9384536, 2652365, 37346458, 23474576, 4575364, 28735425, 1539345, 495834, 1 };
	bwn::NumeralSystem number{ 10 };

	while (!quit)
	{
		bwn::console_color special_color{bwn::console_color::GREEN};

		std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
		std::chrono::time_point<std::chrono::high_resolution_clock> t_end;

		std::chrono::time_point<std::chrono::high_resolution_clock> t_false_start{};
		std::chrono::time_point<std::chrono::high_resolution_clock> t_false_end{};


		constexpr uint32_t iterations = 10000;

		bwn::ClearScreen();
		try {
			std::cout << special_color << "----------Start----------" << bwn::console_color::reset << std::endl;
			t_start = std::chrono::high_resolution_clock::now();
			{	// OFICIAL START

				for (uint32_t i = 0; i < iterations; ++i)
				{
					number.container_ = false_container;
					number.Normalize();
				}


				// OFICIAL END
				//t_false_start = std::chrono::high_resolution_clock::now();
				//std::cout << special_color << "----------Before End----------" << bwn::console_color::reset << std::endl;
				//t_false_end = std::chrono::high_resolution_clock::now();
			}
			t_end = std::chrono::high_resolution_clock::now();
			std::cout << special_color << "----------After End----------" << bwn::console_color::reset << std::endl;
		}
		catch (const std::exception& e) {
			t_end = std::chrono::high_resolution_clock::now();
			std::cout << bwn::console_color(bwn::console_color::RED) << "\nDuring testing exception accrued :\n" << e.what() << bwn::console_color::reset << std::endl;
		}

		std::cout << "Testing time : " << std::chrono::duration<double, std::micro>(t_end - t_start - (t_false_end - t_false_start)).count() << "(us)" << std::endl;

		std::cout << "Quit? ((y|q)/any) : ";
		std::getline(std::cin, input);
		if (input == "y" || input == "q") {
			quit = true;
		}
	}
#endif // Testing poligon

	try
	{
		Throw();
	}
	catch(const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	// Cancellation point
#if false
	{
		std::cout << "Press any button..";
		std::getchar();
	}
#endif // Cancellation point

}
