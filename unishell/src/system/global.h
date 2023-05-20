#pragma once

#include "../utilities/stringUtil.h"
#include "../outstream/colorStructure.h"

#include <map>

// global variables

const StringList __keywords = {
	"and",
	"or"
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

// --> global color variables
extern BaseColorStructure* __clr_quoted;
extern BaseColorStructure* __clr_identifier;
extern BaseColorStructure* __clr_command;
extern BaseColorStructure* __clr_numbers;
extern BaseColorStructure* __clr_operators;
extern BaseColorStructure* __clr_parens;
extern BaseColorStructure* __clr_cursor;
extern BaseColorStructure* __clr_keyword;
extern BaseColorStructure* __clr_boolean;
// <--