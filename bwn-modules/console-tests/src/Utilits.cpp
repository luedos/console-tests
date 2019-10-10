#include "pch.h"

#include <iostream>
#include "Utilits.h"

using namespace bwn;

console_color::console_color(char foreground_color)
	: foreground_color_{ foreground_color }
	, background_color_{ -1 }
{
}

console_color::console_color(char foreground_color, char background_color)
	: foreground_color_{ foreground_color }
	, background_color_{ background_color }
{
}

char console_color::get_foreground() const
{
	return foreground_color_;
}

char console_color::get_background() const
{
	return background_color_;
}

#if defined(_WIN32)
std::ostream& bwn::operator<<(std::ostream& stream, const console_color& color)
{
	HANDLE hstdout = INVALID_HANDLE_VALUE;

	if (&stream == &std::cout)
	{
		console_color::default_cout_color();
		hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else if (&stream == &std::cerr)
	{
		console_color::default_cerr_color();
		hstdout = GetStdHandle(STD_ERROR_HANDLE);
	}

	color.SetAttributes(hstdout);

	return stream;
}
#elif defined(__unix__)
std::ostream& bwn::operator<<(std::ostream& stream, const console_color& color)
{
	if (&stream != &std::cout && &stream != &std::cerr) {
		return stream;
	}

	std::string code = "\033[";
	code.reserve(8);
	code += std::to_string(static_cast<unsigned int>(static_cast<unsigned char>(color.foreground_color_)));
	if (color.background_color_ != -1)
	{
		code.push_back(';');
		code += std::to_string(static_cast<unsigned int>(static_cast<unsigned char>(color.background_color_)) + 10);
	}
	code.push_back('m');

	stream << code;

	return stream;
}
#endif

#if defined(_WIN32)
std::wostream& bwn::operator<<(std::wostream& stream, const console_color& color)
{

	HANDLE hstdout = INVALID_HANDLE_VALUE;

	if (&stream == &std::wcout)
	{
		console_color::default_cout_color();
		hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else if (&stream == &std::wcerr)
	{
		console_color::default_cerr_color();
		hstdout = GetStdHandle(STD_ERROR_HANDLE);
	}

	color.SetAttributes(hstdout);

	return stream;
}
#elif defined(__unix__)
std::wostream& bwn::operator<<(std::wostream& stream, const console_color& color)
{
	if (&stream != &std::wcout && &stream != &std::wcerr) {
		return stream;
	}

	std::wstring code = L"\033[";
	code.reserve(8);
	code += std::to_wstring(static_cast<unsigned int>(static_cast<unsigned char>(color.foreground_color_)));
	if (color.background_color_ != -1)
	{
		code.push_back(L';');
		code += std::to_wstring(static_cast<unsigned int>(static_cast<unsigned char>(color.background_color_)) + 10);
	}
	code.push_back(L'm');

	stream << code;

	return stream;
}
#endif


#if defined(_WIN32)
std::ostream& console_color::reset(std::ostream& stream)
{
	if (&stream == &std::cout) {
		stream << default_cout_color();
	}
	else if (&stream == &std::cerr) {
		stream << default_cerr_color();
	}

	return stream;
}

std::wostream& console_color::reset(std::wostream& stream)
{
	if (&stream == &std::wcout) {
		stream << default_cout_color();
	}
	else if (&stream == &std::wcerr) {
		stream << default_cerr_color();
	}

	return stream;
}
#elif defined(__unix__)
std::ostream& console_color::reset(std::ostream& stream)
{
	if (&stream == &std::cout || &stream == &std::cerr) {
		stream << "\033[39;49m";
	}

	return stream;
}

std::wostream& console_color::reset(std::wostream& stream)
{
	if (&stream == &std::wcout || &stream == &std::wcerr) {
		stream << "\033[39;49m";
	}

	return stream;
}
#endif


#if defined(_WIN32)
console_color console_color::current_cout_color()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	return console_color(csbi.wAttributes & 0x0F, (csbi.wAttributes & 0xF0) >> 4);
}

console_color console_color::current_cerr_color()
{
	HANDLE hstdout = GetStdHandle(STD_ERROR_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	return console_color(csbi.wAttributes & 0x0F, (csbi.wAttributes & 0xF0) >> 4);
}

void console_color::SetAttributes(HANDLE handle) const
{
	if (handle == INVALID_HANDLE_VALUE) {
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);

	WORD out_attributes = (foreground_color_ & 0x0F) | (csbi.wAttributes & 0xFFF0);

	if (background_color_ != -1) {
		out_attributes = (out_attributes & 0xFF0F) | ((background_color_ & 0x0F) << 4);
	}

	SetConsoleTextAttribute(handle, out_attributes);
}

const console_color& console_color::default_cout_color()
{
	static console_color singelton = current_cout_color();

	return singelton;
}

const console_color& console_color::default_cerr_color()
{
	static console_color singelton = current_cerr_color();

	return singelton;
}
#endif

#if defined(_WIN32)
void bwn::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}
#elif defined(__unix)
void bwn::ClearScreen()
{
	printf("\033[H\033[J");
}
#endif

void ErrorExit(const std::string& message = {})
{
	if (!message.empty()) {
		std::cout << bwn::console_color(bwn::console_color::RED) << message << bwn::console_color::reset << std::endl;
	}

	system("Pause");
	exit(-1);
}