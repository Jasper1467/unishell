#include "instream.h"



INSListBuffer INStream::globalInputList = INSListBuffer();

// user input
std::string INStream::getLine()
{
	INStreamBuffer lineInput;
	char charInput;

	bool end = false;

	sysprint(saveCursor());

	while (!end)
	{
		sysprint(loadCursor());

		charInput = _getch();

		controlKeyHandler(charInput, lineInput, end);
	}

	return lineInput;
}

// process control keys
void INStream::controlKeyHandler(char charInput, INStreamBuffer& lineInput, bool& end)
{
	// reset input list current index
	if ((int)charInput != SpecialChar)
		globalInputList.reset();

	switch ((int)charInput)
	{
	case CarriageReturn:
		updateConsoleInput(lineInput, false);
		globalInputList.add(lineInput);
		sysprintln(""); // new line
		end = true;
		break;

	case Backspace:
		lineInput.eraseAtIndex(lineInput.getCursorIndex() - 1); // erase the character before cursor
		updateConsoleInput(lineInput);
		
		break;

	// special characters have two codes, 
	// one to identify the character as special and another to be the code of the character itself
	case SpecialChar:
		charInput = _getch(); // each code is consumed individually, so you need to consume twice

		if (charInput == UpArrow) {
			globalInputList.up();
			lineInput.assign(globalInputList.get());
			lineInput.setCursorIndex((int) lineInput.size());
		}
		
		// don't allow DownArrow processing if ignoreCurrenIndexChange is true
		else if (charInput == DownArrow && !globalInputList.ignoreCurrentIndexChange) {
			globalInputList.down();
			lineInput.assign(globalInputList.get());
			lineInput.setCursorIndex((int) lineInput.size());
		}

		else if (charInput == LeftArrow)
			lineInput.cursorLeft();

		else if (charInput == RightArrow)
			lineInput.cursorRight();

		updateConsoleInput(lineInput);
		break;

	default:
		lineInput.insertStr(lineInput.getCursorIndex(), StringUtil::charToStr(charInput));
		updateConsoleInput(lineInput);
	}
}

// format string
std::string INStream::formatString(std::string text, int cursorPos)
{
	const std::string srcText = text;
	std::stringstream fText;
	size_t firstWordPos = INStreamRender::getWordEndPos(text);

	for (size_t i = 0; i < text.size(); i++)
	{
		if (i <= firstWordPos)
			INStreamRender::renderCommand(fText, text, cursorPos, i, firstWordPos);

		char current = text[i];

		switch (current)
		{
		case ' ':
		case '\t':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, StringUtil::charToStr(text[i]));
			break;

		case '\"':
			INStreamRender::renderQuoted(fText, text, i, cursorPos);
			break;

		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), __clr_encloses->toString()));
			break;

		case '!':
		case '<':
		case '>':
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
			INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), __clr_operators->toString()));
			break;

		case '$':
			INStreamRender::renderIdentifier(fText, text, i, cursorPos);
			break;

		default:
			if (StringUtil::isDigit(text[i]) && isValidForNum(text[i - 1]) && ((i + 1 < text.size() && isValidForNum(text[i + 1])) || i + 1 >= text.size()))
			{
				for (i; StringUtil::isDigit(text[i]); i++)
					INStreamRender::renderChar(i, cursorPos, text[i], fText, clr(StringUtil::charToStr(text[i]), __clr_numbers->toString()));

				i--;
			}

			else if (!INStreamRender::renderKeyword(fText, text, i, cursorPos) &&
				     !INStreamRender::renderBoolean(fText, text, i, cursorPos) &&
					 !INStreamRender::renderColor(fText, text, i, cursorPos))
			{
				INStreamRender::renderChar(i, cursorPos, text[i], fText, StringUtil::charToStr(text[i]));
			}
		}
	}

	// cursor is at end of the text
	if (cursorPos >= text.size() && cursorPos != -1)
		fText << INSCursor('_');
	
	return fText.str();
}