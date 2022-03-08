#include "../../Header Files/Preprocessor/LineTokenizer.h"
#include "../../Header Files/Tokenizer/TokenConstants.h"
#include <algorithm>

namespace Preprocessor
{
	LineTokenizer::LineTokenizer(const std::string& line, PreprocessedTokens& tokensDestination, const int& lineCount, const std::string& filePath, bool& mulitLineComment)
		: tokensDestination(tokensDestination), lineCount(lineCount), filePath(filePath), begin(line.cbegin()), end(line.cend()), lineIt(begin), mulitLineComment(mulitLineComment) {}

	void LineTokenizer::tokenize()
	{
		for (; lineIt != end && handleLineIt(); ++lineIt);

		if (buildingString)
			throwIncompleteString();

		pushAndClearCurrentToken();
	}

	bool LineTokenizer::handleLineIt()
	{
		static constexpr bool CONTINUE = true, BREAK = false;

		if (mulitLineComment)
		{
			if (isLineItMultiLineCommentEnd())
			{
				mulitLineComment = false;
				++lineIt;
			}
		}

		else if (!buildingString && isLineItMultiLineCommentDeclaration())
			mulitLineComment = true;

		else if (buildingString)
			buildString();

		else if (isLineItFourCCDeclaration())
		{
			pushAndClearCurrentToken();
			buildingFourCC = !buildingFourCC;
			pushLineItAsToken();
		}

		else if (buildingFourCC)
		{
			if (isLineItAlNum())
				currentToken += *lineIt;
			else
				throwIllegalFourCCChars(*lineIt);
		}

		else if (currentToken.empty() && isPrevTokenDeciamlPoint() && isLineItDigitOrDecimalPoint())
		{
			tokensDestination.pop_back();
			currentToken += Tokenizer::TokenConstants::DECIMAL_POINT;
			currentToken += *lineIt;
		}

		else if (isCurrentTokenRealValue() && isLineItAlphaOrUnderscore())
			throwIllegalIdentifier();

		else if (isLineItOneLineCommentDeclaration())
		{
			pushAndClearCurrentToken();
			return BREAK;
		}

		else if (isCurrentTokenRealValue() && isLineItDigitOrDecimalPoint())
		{
			if (isLineItDecimalPoint() && currentTokenContainsDecimalPoint())
				throwRealValueWithDoubleDecimalPoints();

			currentToken += *lineIt;
		}

		else if (isLineItAlNumOrUnderscore())
			currentToken += *lineIt;

		else
		{
			pushAndClearCurrentToken();
			if (!isLineItSpace())
				pushLineItAsToken();
		}

		return CONTINUE;
	}

	void LineTokenizer::pushLineItAsToken()
	{
		tokensDestination.emplace_back(std::string(1, *lineIt), lineCount, filePath);

		buildingString = isLineItStringDeclaration();
	}

	void LineTokenizer::buildString()
	{
		if (isLineItStringDeclaration())
			completeStringBuilding();
		else
			currentToken += *lineIt;
	}

	void LineTokenizer::completeStringBuilding()
	{
		pushAndClearCurrentToken();
		tokensDestination.emplace_back(std::string(1, Tokenizer::TokenConstants::SYM_STRING), lineCount, filePath);
		buildingString = false;
	}

	void LineTokenizer::pushAndClearCurrentToken()
	{
		if (currentToken.empty())
			return;

		tokensDestination.emplace_back(currentToken, lineCount, filePath);
		currentToken.clear();
	}

	bool LineTokenizer::isLineItMultiLineCommentDeclaration() const
	{
		using Tokenizer::TokenConstants::MULTI_LINE_COMMENT_DECL_BEGIN;

		if (end - lineIt < 2)
			return false;

		return std::equal(lineIt, lineIt + 2, MULTI_LINE_COMMENT_DECL_BEGIN.cbegin(), MULTI_LINE_COMMENT_DECL_BEGIN.cend());
	}

	bool LineTokenizer::isLineItMultiLineCommentEnd() const
	{
		using Tokenizer::TokenConstants::MULTI_LINE_COMMENT_DECL_END;

		if (end - lineIt < 2)
			return false;

		return std::equal(lineIt, lineIt + 2, MULTI_LINE_COMMENT_DECL_END.cbegin(), MULTI_LINE_COMMENT_DECL_END.cend());
	}

	bool LineTokenizer::isLineItStringDeclaration() const
	{
		return *lineIt == Tokenizer::TokenConstants::SYM_STRING;
	}

	bool LineTokenizer::isLineItFourCCDeclaration() const
	{
		return *lineIt == Tokenizer::TokenConstants::SYM_FOUR_CC;
	}

	bool LineTokenizer::isLineItSpace() const
	{
		return *lineIt == Tokenizer::TokenConstants::SYM_SPACE;
	}

	bool LineTokenizer::isLineItOneLineCommentDeclaration() const
	{
		using Tokenizer::TokenConstants::ONE_LINE_COMMENT_DECL;

		if (end - lineIt < 2)
			return false;

		return std::equal(lineIt, lineIt + 2, ONE_LINE_COMMENT_DECL.cbegin(), ONE_LINE_COMMENT_DECL.cend());
	}

	bool LineTokenizer::isLineItAlphaOrUnderscore() const
	{
		return isalpha(*lineIt) || isLineItUnderscore();
	}

	bool LineTokenizer::isLineItAlNum() const
	{
		return isalnum(*lineIt);
	}

	bool LineTokenizer::isLineItAlNumOrUnderscore() const
	{
		return isalnum(*lineIt) || isLineItUnderscore();
	}

	bool LineTokenizer::isLineItUnderscore() const
	{
		return *lineIt == Tokenizer::TokenConstants::SYM_UNDERSCORE;
	}

	bool LineTokenizer::isLineItDecimalPoint() const
	{
		return *lineIt == Tokenizer::TokenConstants::DECIMAL_POINT;
	}

	bool LineTokenizer::isPrevTokenDeciamlPoint() const
	{
		if (tokensDestination.empty())
			return false;

		const std::string& prevTokenValue = tokensDestination.back().getValue();
		return prevTokenValue.size() == 1 && prevTokenValue[0] == Tokenizer::TokenConstants::DECIMAL_POINT;
	}

	bool LineTokenizer::isCurrentTokenRealValue() const
	{
		if (currentToken.empty())
			return false;

		return std::all_of(
			currentToken.begin(),
			currentToken.end(),
			[](const unsigned char& c)
			{
				return isdigit(c) || c == Tokenizer::TokenConstants::DECIMAL_POINT;
			}
		);
	}

	bool LineTokenizer::isLineItDigitOrDecimalPoint() const
	{
		return isdigit(*lineIt) || isLineItDecimalPoint();
	}

	bool LineTokenizer::currentTokenContainsDecimalPoint() const
	{
		return std::find(currentToken.begin(), currentToken.end(), Tokenizer::TokenConstants::DECIMAL_POINT) != currentToken.end();
	}

	const std::string LineTokenizer::buildTokenOfCurrentSyntaxError() const
	{
		using Tokenizer::TokenConstants::SYM_SPACE;

		return std::string(lineIt - currentToken.size(), std::find(lineIt, end, SYM_SPACE) != end ? std::find(lineIt, end, SYM_SPACE) : end);
	}

	void LineTokenizer::throwIllegalIdentifier() const
	{
		throw "In " + filePath + " (" + std::to_string(lineCount) + "): Illegal identifier: \"" + buildTokenOfCurrentSyntaxError() + "\"\n" +
			"\tRules for naming identifiers:\n" +
			"\t\tIdentifiers can only contain letters, digits and underscores.\n" +
			"\t\tIdentifiers must begin with a letter or an underscore.\n" +
			"\t\tIdentifiers can not contain 2 or more adjacent underscores (i.e \"__\").\n" +
			"\t\tReserved words cannot be used as Identifier names.\n";
	}
	
	void LineTokenizer::throwRealValueWithDoubleDecimalPoints() const
	{
		throw "In " + filePath + " (" + std::to_string(lineCount) + "): Illegal real: \"" + buildTokenOfCurrentSyntaxError() + "\"\n" +
			"\tReal values can not have more than 1 decimal point.\n";
	}

	void LineTokenizer::throwIncompleteString() const
	{
		throw "In " + filePath + " (" + std::to_string(lineCount) + "): Incomplete string: \"" + buildTokenOfCurrentSyntaxError() + "\"\n" +
			"\tMissing end of string literal.\n";
	}

	void LineTokenizer::throwIllegalFourCCChars(const char& illegalChar) const
	{
		throw "In " + filePath + " (" + std::to_string(lineCount) + "): Illegal FourCC character: \"" + illegalChar + "\"\n";
	}
}
