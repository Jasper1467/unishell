#include "tokenProcessing.h"

TokenList TokenProcess::generateExpressions(TokenList source) {
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

TokenList TokenProcess::generateColorTokens(TokenList source) {
	TokenList res;

	size_t start = 0, end = 0;

	for (size_t i = 0; i < source.size(); i++) {
		if (i + 1 < source.size() && source[i + 1].getType() == COLON) {
			start = i;
			i++;

			if (i + 1 >= source.size())
				throw SystemException(TokenProcessingError, "Unterminated color structure", ExceptionRef(*System::input(), System::input()->size() - 1));;

			i++;
			consume(source, COLON, i, "Unterminated color structure");

			end = i;

			res.push_back(Token(COLOR, "", nullptr, TokenList(source.begin() + start, source.begin() + end + 1), res.size() - 1));
		}

		else res.push_back(source[i]);
	}

	return res;
}