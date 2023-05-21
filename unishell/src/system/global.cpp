#include "global.h"

const StringList __keywords = {
	"and",
	"or",
	"null"
};

const StringList __boolean = {
	"true",
	"false"
};

const StringList __colormode = {
	"normal",
	"dark",
	"italic",
	"underline",
	"crossed"
};

const StringList __color = {
	"null",
	"red",
	"green",
	"yellow",
	"blue",
	"purple",
	"cyan",
	"white",

	"gray",
	"wred",
	"wgreen",
	"wyellow",
	"wblue",
	"wpurple",
	"wcyan"
};

const StringList __color_formats = {
	"id",
	"rgb",
	"clr"
};

const std::string __word_separator = "=+-*/()[]{}<>?;:,|\\! ";

BaseColorStructure* __clr_quoted = new IdColorStructure(106);
BaseColorStructure* __clr_identifier = new IdColorStructure(115);
BaseColorStructure* __clr_command = new IdColorStructure(141);
BaseColorStructure* __clr_numbers = new IdColorStructure(192);
BaseColorStructure* __clr_operators = new IdColorStructure(222);
BaseColorStructure* __clr_encloses = new IdColorStructure(210);
BaseColorStructure* __clr_cursor = new IdColorStructure(75, underline);
BaseColorStructure* __clr_keyword = new IdColorStructure(170);
BaseColorStructure* __clr_boolean = new IdColorStructure(219);