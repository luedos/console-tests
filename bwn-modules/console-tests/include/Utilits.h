#pragma once

#if defined(_WIN32)
#include <Windows.h>
#endif
#include <string>


namespace bwn
{
class console_color
{
	//
	// Public structs.
	//
public:
#if defined(_WIN32)
	enum
	{
		BLACK		= 0x00,
		DARKBLUE	= 0x01,
		DARKGREEN	= 0x02,
		DARKCYAN	= 0x03,
		DARKRED		= 0x04,
		DARKPURPLE	= 0x05,
		DARKYELLOW	= 0x06,
		DARKWHIHT	= 0x07,
		GRAY		= 0x08,
		BLUE		= 0x09,
		GREEN		= 0x0A,
		CYAN		= 0x0B,
		RED			= 0x0C,
		PURPLE		= 0x0D,
		YELLOW		= 0x0E,
		WHIHT		= 0x0F
	};
#else
	enum
	{
		BLACK		= 30,
		DARKRED		= 31,
		DARKGREEN	= 32,
		DARKYELLOW	= 33,
		DARKBLUE	= 34,
		DARKPURPLE	= 35,
		DARKCYAN	= 36,
		DARKWHIHT	= 37,
		GRAY		= 90,
		RED			= 91,
		GREEN		= 92,
		YELLOW		= 93,
		BLUE		= 94,
		PURPLE		= 95,
		CYAN		= 96,
		WHIHT		= 97,
	};
#endif
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	console_color(char foreground_color);
	//! Constructor.
	console_color(char foreground_color, char background_color);

	//
	// Public interface.
	//
public:
	//! Returns text color.
	char get_foreground() const;
	//! Returns background color.
	char get_background() const;
	//! Resets colors to defaults.
	static std::ostream& reset(std::ostream& stream);
	//! Resets colors to defaults.
	static std::wostream& reset(std::wostream& stream);

	//
	// Private methods.
	//
private:
#if defined(_WIN32)
	//! Open those methods only if user explicitly wants it.
#if defined(BWN_COLORS_WIN_GET_CURRENT)
public:
#endif
	//! Returns current console color class.
	static console_color current_cout_color();
	//! Returns current err console color class.
	static console_color current_cerr_color();
#if defined(BWN_COLORS_WIN_GET_CURRENT)
private:
#endif
	//! Sets atributes to console handler.
	void SetAttributes(HANDLE handle) const;
#endif
	friend std::ostream& operator<<(std::ostream& stream, const console_color&color);
	friend std::wostream& operator<<(std::wostream& stream, const console_color&color);

	//
	// Private members.
	//
private:
	//! Text color.
	char foreground_color_;
	//! Background color.
	char background_color_;
#if defined(_WIN32)
	//! Used for reset method on windows.
	static const console_color& default_cout_color();
	//! Used for reset method on windows.
	static const console_color& default_cerr_color();
#endif
};

std::ostream& operator<<(std::ostream& stream, const console_color&color);
std::wostream& operator<<(std::wostream& stream, const console_color&color);

void ClearScreen();

void ErrorExit(const std::string& message = {});

}
