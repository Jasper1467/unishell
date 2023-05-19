#include "instrScanner.h"

TokenList InstreamScanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	tokens = reviewTokens(tokens);
	tokens = generateExpressions(tokens);

	return tokens;
}

TokenList InstreamScanner::generateExpressions(TokenList source) {
	TokenList res;

	size_t start = 0, end = 0;
	unsigned short aux = 0;

	for (size_t i = 0; i < source.size(); i++)
	{
		if (source[i].getType() == LPAREN) {
			aux++;

			start = i;

			while (aux) {
				checkIndex(source, i, aux);
				checkParen(source, i, aux);
			}

			end = i;

			res.push_back(Token(EXPRESSION, "", nullptr, TokenList(source.begin() + start + 1, source.begin() + end), res.size() - 1));
		}

		else res.push_back(source[i]);
	}

	return res;
}

void InstreamScanner::scanToken()
{
	char ch = advance();

	switch (ch)
	{
	case ' ':
	case '\r':
	case '\t':
		break;

	case '+': addToken(PLUS); break;
	case '-': addToken(MINUS); break;
	case '*': addToken(STAR); break;
	case '/': addToken(SLASH); break;

	case '=': addToken((match('=') ? EQUAL_EQUAL : EQUAL)); break;

	case '!': addToken((match('=') ? BANG_EQUAL : BANG)); break;
	case '<': addToken((match('=') ? LESS_EQUAL : LESS)); break;
	case '>': addToken((match('=') ? GREATER_EQUAL : GREATER)); break;

	// TODO: make the scanner interpret these as expressions
	case '(': addToken(LPAREN); break;
	case ')': addToken(RPAREN); break;

	case '\"': string(); break;
	case '$': word(INDENTIFIER); break;

	default:
		if (tokens.empty() && !ignoreCommand) word(COMMAND);

		else if (StringUtil::isDigit(ch)) {
			if (ch == '.' && StringUtil::isDigit(peek()) && peek() != '.') number();
			else if (ch != '.') number();
			else throw SystemException(InstreamScannerError, "Unexpected token", ExceptionRef(src, current - 1));
		}

		else if (!keyword() && !boolean()) word(LITERAL, true);
	}
}