#include "../../Header Files/Tokenizer/Tokenizer.h"
#include "../../Header Files/Tokenizer/TokenConstants.h"
#include "../../Header Files/Globals/Constants.h"
#include "../../Header Files/Globals/Globals.h"

#ifdef _DEBUG
#include <unordered_map>
#endif

namespace Tokenizer
{
	Tokenizer::Tokenizer(const std::vector<Preprocessor::PreprocessedTokens>& preprocessedTokensFiles) : preprocessedTokensFiles(preprocessedTokensFiles) {}

	const Tokens& Tokenizer::tokenize()
	{
		for (const Preprocessor::PreprocessedTokens& preprocessedTokensFile : preprocessedTokensFiles)
		{
			for (tokenItBegin = tokenIt = preprocessedTokensFile.cbegin(), tokenItEnd = preprocessedTokensFile.cend(); tokenIt != tokenItEnd; ++tokenIt)
			{
				if (tokenIt->size() == 1)
					buildTokenUsingSingleChar();
				else
					buildToken();
			}
		}

#ifdef _DEBUG
		std::unordered_map<TokenType, std::string> tokenTypes
		{
			{ TokenType::PAREN_OPEN, "PAREN_OPEN" },
			{ TokenType::PAREN_CLOSE, "PAREN_CLOSE" },
			{ TokenType::ACCESS_MEMBER_SYMBOL, "ACCESS_MEMBER_SYMBOL" },
			{ TokenType::ACCESS_MODIFIER_DECL_END, "ACCESS_MODIFIER_DECL_END" },
			{ TokenType::STRING, "STRING" },
			{ TokenType::FOUR_CC, "FOUR_CC" },
			{ TokenType::CONSTANT, "CONSTANT" },
			{ TokenType::DESTRUCTOR_SYMBOL, "DESTRUCTOR_SYMBOL" },
			{ TokenType::IDENTIFIER, "IDENTIFIER" },
			{ TokenType::KEYWORD, "KEYWORD" },
			{ TokenType::OPERATOR, "OPERATOR" },
			{ TokenType::STATEMENT_END, "STATEMENT_END" },
		};
		for (const Token& token : tokens)
		{
			const Preprocessor::PreprocessedToken& pToken = token.getValue();
			userOutput.log(pToken.getFilePath() + " (" + std::to_string(pToken.getLine()) + "): " + pToken.getValue() + " " + tokenTypes[token.getTokenType()]);
		}
#endif

		return tokens;
	}
	
	void Tokenizer::buildToken()
	{
		using namespace TokenConstants;

		if (std::find(std::cbegin(keywords), std::cend(keywords), tokenIt->getValue()) != std::cend(keywords))
			emplaceTokenIt(TokenType::KEYWORD);

		else if (std::find(std::cbegin(literalTypes), std::cend(literalTypes), tokenIt->getValue()) != std::cend(literalTypes))
			emplaceTokenIt(TokenType::IDENTIFIER);

		else if (std::find(std::cbegin(literalConstants), std::cend(literalConstants), tokenIt->getValue()) != std::cend(literalConstants))
			emplaceTokenIt(TokenType::CONSTANT);

		else if (isTokenItRealValue())
			emplaceTokenIt(TokenType::CONSTANT);

		else if (std::find(std::cbegin(unusedReservedKeywords), std::cend(unusedReservedKeywords), tokenIt->getValue()) != std::cend(unusedReservedKeywords))
		{
			userOutput.error("In \"" + tokenIt->getFilePath() + "\" on line " + std::to_string(tokenIt->getLine()) + ": \"" + tokenIt->getValue() + "\" is a reserved keyword for vJass and can not be used.");
			Globals::transpiledSuccessfully = false;
		}

		else if (isTokenItAlNumWithLeadingAlphaOrUnderscore())
			emplaceTokenIt(TokenType::IDENTIFIER);

		else
			warnUnknownTokenIt();
	}

	void Tokenizer::buildTokenUsingSingleChar()
	{
		using namespace TokenConstants;

		const char& tokenValue = tokenIt->getValue()[0];
		
		if (tokenValue == STATEMENT_END)
			emplaceTokenIt(TokenType::STATEMENT_END);

		else if (tokenValue == SS_OP_LESS_THAN)
		{
			if (isTokenItTemplateOpen())
				emplaceTokenIt(TokenType::PAREN_OPEN);
			else
				emplaceTokenIt(TokenType::OPERATOR);
		}

		else if (tokenValue == SS_OP_GREATER_THAN)
		{
			if (isTokenItTemplateClose())
				emplaceTokenIt(TokenType::PAREN_CLOSE);
			else
				emplaceTokenIt(TokenType::OPERATOR);
		}

		else if (tokenValue == SYM_COMMA)
			emplaceTokenIt(TokenType::COMMA);

		else if (tokenValue == SYM_ACCESS_MEMBER)
			emplaceTokenIt(TokenType::ACCESS_MEMBER_SYMBOL);

		else if (tokenValue == SYM_STRING)
		{
			++tokenIt;
			emplaceTokenIt(TokenType::STRING);
			++tokenIt;
		}

		else if (tokenValue == SYM_FOUR_CC)
		{
			++tokenIt;
			emplaceTokenIt(TokenType::FOUR_CC);
			if (tokenIt->getValue().size() != Globals::Constants::FOUR_CC_SIZE)
				userOutput.warn("In \"" + tokenIt->getFilePath() + "\" on line " + std::to_string(tokenIt->getLine()) + ": FourCC must have exactly " + std::to_string(Globals::Constants::FOUR_CC_SIZE) + " characters. '" + tokenIt->getValue() + "'");
			++tokenIt;
		}

		else if (tokenValue == SYM_DESTRUCTOR)
			emplaceTokenIt(TokenType::DESTRUCTOR_SYMBOL);

		else if (tokenValue == SYM_ACCESS_MODIFIER_DECL_END)
			emplaceTokenIt(TokenType::ACCESS_MODIFIER_DECL_END);

		else if (std::find(std::cbegin(singleSymbolOperators), std::cend(singleSymbolOperators), tokenValue) != std::cend(singleSymbolOperators))
			emplaceTokenIt(TokenType::OPERATOR);

		else if (std::find(std::cbegin(parensOpen), std::cend(parensOpen), tokenValue) != std::cend(parensOpen))
			emplaceTokenIt(TokenType::PAREN_OPEN);

		else if (std::find(std::cbegin(parensClose), std::cend(parensClose), tokenValue) != std::cend(parensClose))
			emplaceTokenIt(TokenType::PAREN_CLOSE);

		else if (isdigit(tokenValue))
			emplaceTokenIt(TokenType::CONSTANT);

		else if (isAlNumOrUnderscore(tokenValue))
			emplaceTokenIt(TokenType::IDENTIFIER);

		else
			warnUnknownTokenIt();
	}

	void Tokenizer::emplaceTokenIt(const TokenType& tokenType)
	{
		tokens.emplace_back(*tokenIt, tokenType);
	}

	bool Tokenizer::isTokenItTemplateOpen() const
	{
		using namespace TokenConstants;

		for (Preprocessor::PreprocessedTokens::const_iterator forwardIt = tokenIt; forwardIt != tokenItEnd; ++forwardIt)
		{
			if (forwardIt->getValue()[0] == PAREN_ANGLE_CLOSE)
				return true;

			if (forwardIt->getValue()[0] != PAREN_ANGLE_OPEN && forwardIt->getValue()[0] != SYM_COMMA && !isTokenItNonKeywordAlNumWithLeadingAlphaOrUnderscore(forwardIt))
				return false;
		}

		return false;
	}
	
	bool Tokenizer::isTokenItTemplateClose() const
	{
		using namespace TokenConstants;

		for (Preprocessor::PreprocessedTokens::const_iterator backwardsIt = tokenIt; backwardsIt != tokenItBegin; --backwardsIt)
		{
			if (backwardsIt->getValue()[0] == PAREN_ANGLE_OPEN)
				return true;

			if (backwardsIt->getValue()[0] != PAREN_ANGLE_CLOSE && backwardsIt->getValue()[0] != SYM_COMMA && !isTokenItNonKeywordAlNumWithLeadingAlphaOrUnderscore(backwardsIt))
				return false;
		}

		return false;
	}

	bool Tokenizer::isTokenItAlNumWithLeadingAlphaOrUnderscore() const
	{
		return isTokenItAlNumWithLeadingAlphaOrUnderscore(tokenIt);
	}

	bool Tokenizer::isTokenItAlNumWithLeadingAlphaOrUnderscore(const Preprocessor::PreprocessedTokens::const_iterator& tokenIt) const
	{
		if (isdigit(tokenIt->getValue()[0]))
			return false;

		for (const char& c : tokenIt->getValue())
		{
			if (!isAlNumOrUnderscore(c))
				return false;
		}

		return true;
	}

	bool Tokenizer::isTokenItNonKeywordAlNumWithLeadingAlphaOrUnderscore(const Preprocessor::PreprocessedTokens::const_iterator& tokenIt) const
	{
		using namespace TokenConstants;

		return std::find(std::cbegin(keywords), std::cend(keywords), tokenIt->getValue()) == std::cend(keywords) && isTokenItAlNumWithLeadingAlphaOrUnderscore(tokenIt);
	}

	bool Tokenizer::isAlNumOrUnderscore(const char& c) const
	{
		return isalnum(c) || c == TokenConstants::SYM_UNDERSCORE;
	}

	bool Tokenizer::isTokenItRealValue() const
	{
		for (const char& c : tokenIt->getValue())
			if (!isdigit(c) && c != TokenConstants::DECIMAL_POINT)
				return false;

		return true;
	}

	void Tokenizer::warnUnknownTokenIt() const
	{
		userOutput.warn("Unknown token: \"" + tokenIt->getValue() + "\".");
	}
}
