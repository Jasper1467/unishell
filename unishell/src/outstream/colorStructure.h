#pragma once

#include "../utilities/stringUtil.h"

#define tostr std::to_string
#define endclr "\033[0m"

enum Color {
	null = 0,

	red = 31, green, yellow, blue,
	purple, cyan, white,

	// bright colors
	gray = 90, wred, wgreen, wyellow,
	wblue, wpurple, wcyan
};

inline Color stringToColor(const std::string& strMode) {
	if (strMode == "null") return null;

	if (strMode == "red") return red;
	if (strMode == "green") return green;
	if (strMode == "yellow") return yellow;
	if (strMode == "blue") return blue;
	if (strMode == "purple") return purple;
	if (strMode == "cyan") return cyan;
	if (strMode == "white") return white;

	if (strMode == "gray") return gray;
	if (strMode == "wred") return wred;
	if (strMode == "wgreen") return wgreen;
	if (strMode == "wyellow") return wyellow;
	if (strMode == "wblue") return wblue;
	if (strMode == "wpurple") return wpurple;
	if (strMode == "wcyan") return wcyan;

	return null;
}

enum ColorMode {
	normal = 0,
	dark = 2,
	italic = 3,
	underline = 4,
	crossed = 9
};

inline ColorMode stringToColorMode(const std::string& strMode) {
	if (strMode == "normal") return normal;
	if (strMode == "dark") return dark;
	if (strMode == "italic") return italic;
	if (strMode == "underline") return underline;
	if (strMode == "crossed") return crossed;

	return normal;
}



// returns the color assigned to the id (0 - 255)
inline std::string id(unsigned int i, ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;5;" + tostr(i) + 'm';
}

// returns rgb ANSI notation
inline std::string rgb(unsigned int red, unsigned int green, unsigned int blue, ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ";38;2;" + tostr(red) + ';' + tostr(green) + ';' + tostr(blue) + 'm';
}

inline std::string colorToString(Color color, ColorMode mode) noexcept {
	return "\033[" + tostr((int)mode) + ';' + tostr((int)color) + 'm';
}


class BaseColorStructure
{
public:
	BaseColorStructure(ColorMode mode = normal) : mode(mode) {}

	virtual inline std::string toString() = 0;

	ColorMode mode;
};

class IdColorStructure : public BaseColorStructure
{
public:
	IdColorStructure(unsigned int idc, ColorMode mode = normal) : BaseColorStructure(mode), idc(idc) {}

	inline std::string toString() override {
		return id(idc, mode);
	}

	unsigned int idc;

	static const size_t argSize = 1;
};

class RGBColorStructure : public BaseColorStructure
{
public:
	RGBColorStructure(unsigned int red, unsigned int green, unsigned int blue, ColorMode mode = normal) :
		BaseColorStructure(mode), red(red), green(green), blue(blue) {}

	inline std::string toString() override {
		return rgb(red, green, blue, mode);
	}

	unsigned int red;
	unsigned int green;
	unsigned int blue;

	static const size_t argSize = 3;
};

class ColorStructure : public BaseColorStructure
{
public:
	ColorStructure(Color color, ColorMode mode = normal) :
		BaseColorStructure(mode), color(color) {}

	inline std::string toString() override {
		return colorToString(color, mode);
	}

	Color color;

	static const size_t argSize = 1;
};
