#include "Header Files/Preprocessor/Preprocessor.h"
#include "Header Files/Tokenizer/Tokenizer.h"
#include "Header Files/CompilerOptions/CompilerOptionsInterpreter.h"
#include "Header Files/SourceBuilder/SourceBuilder.h"
#include "Header Files/Utilities/HighResolutionClock/HighResolutionClock.h"
#include "Header Files/Utilities/UserOutput/UserOutput.h"
#include "Header Files/Globals/Globals.h"
#include "Header Files/EntityFactory/EntityFactory.h"
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#include <algorithm>
#endif


#ifdef _DEBUG

void printTokensInCodeFormat(const Preprocessor::PreprocessedTokens& tokens)
{
	using std::cout;

	std::string indent = "";
	for (const Preprocessor::PreprocessedToken& token : tokens)
	{
		const std::string& tokenValue = token.getValue();
		if (tokenValue == "{" || tokenValue == "}")
		{
			if (tokenValue == "{")
			{
				cout << "\n" << indent << tokenValue << "\n";
				indent += "    ";
				cout << indent;
			}
			else
			{
				indent.resize(indent.size() - 4);
				cout << "\n" << indent << tokenValue << "\n" << indent;
			}
		}
		else if (tokenValue == ";" || tokenValue == ":")
			cout << tokenValue << "\n" << indent;
		else
			cout << tokenValue << " ";
	}
}

void printTokensInListFormat(const Preprocessor::PreprocessedTokens& tokens)
{
	using std::cout;

	cout << "[\n";
	
	for (Preprocessor::PreprocessedTokens::const_iterator it = tokens.cbegin(), last = tokens.cend() - 1; it != tokens.cend(); ++it)
	{
		cout << "   " << *it;
		if (it != last)
			cout << ",";
		cout << "\n";
	}

	cout << "]";
}

void printTypeEntities(const std::vector<const Entities::EType*>& types)
{
	std::vector<const Entities::EType*> typesCopy = types;

	std::sort
	(
		typesCopy.begin(),
		typesCopy.end(),
		[](const Entities::EType* eTypeA, const Entities::EType* eTypeB)
		{
			return !dynamic_cast<const Entities::EClass*>(eTypeA) && dynamic_cast<const Entities::EClass*>(eTypeB);
		}
	);

	for (const Entities::EType* const& eType : typesCopy)
	{
		assert(eType != nullptr);
		if (const Entities::EClass* eClass = dynamic_cast<const Entities::EClass*>(eType); eClass != nullptr)
		{
			std::cout << "  class " << eClass->getName();
			if (eClass->getIsTemplate())
			{
				std::cout << "<";
				for (const std::string& templateTypeName : eClass->getTemplateTypeNames())
					std::cout << templateTypeName << ",";
				std::cout << ">";
			}
			std::cout << " {\n";
			for (const Entities::EAttribute& attribute : eClass->getAttributes())
			{
				std::cout << "    " << (attribute.getIsPublic() ? "public " : "private ")
					<< (attribute.getIsStatic() ? "static " : "")
					<< (attribute.getIsConst() ? "const " : "")
					<< attribute.getName();
				if (attribute.doesHaveValue())
				{
					std::cout << "=";
					for (Tokenizer::Tokens::const_iterator it = attribute.getValueBegin(); it != attribute.getValueEnd(); ++it)
					{
						if (it->getTokenType() == Tokenizer::TokenType::KEYWORD || it->getTokenType() == Tokenizer::TokenType::IDENTIFIER)
							std::cout << " ";
						std::cout << it->getValue().getValue();
					}
				}
				std::cout << ";\n";
			}
			std::cout << "  }\n\n";
		}
		else
		{
			std::cout << "  type " << eType->getName() << "\n\n";
		}
	}
}

#endif



#ifdef _DEBUG

int numberOfHeapAllocations = 0;

// Count Heap Allocations
void* operator new(std::size_t size) throw(std::bad_alloc) {
	++numberOfHeapAllocations;
	return malloc(size);
}

#endif



void transpile
(
	CompilerOptions::ICompilerOptionsInterpreter& compilerOptionsInterpreter,
	SourceBuilder::ISourceBuilder& sourceBuilder,
	Preprocessor::IPreprocessor& preprocessor
)
{
	using Utilities::UserOutput;
	UserOutput& userOutput = UserOutput::getInstance();


	const CompilerOptions::CompilerOptions& compilerOptions = compilerOptionsInterpreter.read();

	if (compilerOptions.sourceFolderPath == compilerOptions.outFolderPath)
	{
		userOutput.warn("Source Folder and Out Folder are the same. Terminating program.");
		Globals::transpiledSuccessfully = false;
		return;
	}


	const std::vector<SourceBuilder::SourceFile>& sourceFiles = sourceBuilder.getSourceFiles(compilerOptions);
	
	const std::vector<Preprocessor::PreprocessedTokens>& preprocessedTokensFiles = preprocessor.tokenize(sourceFiles);
	

#ifdef _DEBUG
	for (const Preprocessor::PreprocessedTokens& preprocessedTokensFile : preprocessedTokensFiles)
	{
		// printTokensInCodeFormat(preprocessedTokensFile);
		// printTokensInListFormat(preprocessedTokensFile);
	}
#endif


	Tokenizer::Tokenizer tokenizer(preprocessedTokensFiles);
	const Tokenizer::Tokens& tokens = tokenizer.tokenize();

	EntityFactory::EntityFactory entityFactory(tokens);
	entityFactory.buildEntities();


#ifdef _DEBUG
	const std::vector<const Entities::EType*>& genereatedTypes = entityFactory.getTypes();
	printTypeEntities(genereatedTypes);
#endif
}



int main(const int commandLineCompilerOptionsCount, const char** commandLineCompilerOptions)
{
	// Initialize Clock
	using Utilities::HighResolutionClock;
	HighResolutionClock::getInstance();


	// Perform automatic leak checking at program exit
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	using Utilities::UserOutput;
	const UserOutput& userOutput = UserOutput::getInstance();


	CompilerOptions::CompilerOptionsInterpreter compilerOptionsInterpreter(commandLineCompilerOptions, commandLineCompilerOptionsCount);
	SourceBuilder::SourceBuilder sourceBuilder;
	Preprocessor::Preprocessor preprocessor;
	

	try
	{
		transpile
		(
			compilerOptionsInterpreter,
			sourceBuilder,
			preprocessor
		);
	}
	catch (const std::string& errorMessage)
	{
		userOutput.error(errorMessage);
		Globals::transpiledSuccessfully = false;
	}


#ifdef _DEBUG
	std::cout << "\nNumber of Heap Allocations: " << numberOfHeapAllocations << "\n";

	new char; // Intentional memory leak, 1 bytes long.
#endif


	if (Globals::transpiledSuccessfully)
	{
		userOutput.log("Transpiled successfully in ", "");
		userOutput.logTimePoint(".\n\n");
	}
	else
		userOutput.log("Transpilation failed!", "\n\n");

	userOutput.log("Number of warnings: " + std::to_string(userOutput.getWarnings()));

	return 0;
}
