#pragma once
#include <string>

namespace Tokenizer
{
	namespace TokenConstants
	{
		// Using standard string because they're easier to work with when searching, comparing and substringing.
		// No string is more then 15 chars and they will all be ompitmized with no heap allocation in release mode.
		using std::string;

		// Statement End
		inline constexpr char STATEMENT_END = ';';



		// Single Symbol Operators
		// Arithmetic Operators
		inline constexpr char SS_OP_ADD = '+';
		inline constexpr char SS_OP_SUBTRACT = '-';
		inline constexpr char SS_OP_MULTIPLY = '*';
		inline constexpr char SS_OP_DIVIDE = '/';
		// no pow, sqrt or mod

		// Assignment Operators
		inline constexpr char SS_OP_ASSIGN = '=';

		// Relational Operators
		inline constexpr char SS_OP_LESS_THAN = '<';
		inline constexpr char SS_OP_GREATER_THAN = '>';

		// Logical Operators
		inline constexpr char SS_OP_NOT = '!';

		// Bitwise Operators
		inline constexpr char SS_OP_BIN_AND = '&';
		inline constexpr char SS_OP_BIN_OR = '|';
		inline constexpr char SS_OP_BIN_XOR = '^';

		inline constexpr char const singleSymbolOperators[] =
		{
			SS_OP_ADD,
			SS_OP_SUBTRACT,
			SS_OP_MULTIPLY,
			SS_OP_DIVIDE,

			SS_OP_ASSIGN,

			SS_OP_LESS_THAN,
			SS_OP_GREATER_THAN,

			SS_OP_NOT,

			SS_OP_BIN_AND,
			SS_OP_BIN_OR,
			SS_OP_BIN_XOR,
		};



		// Special symbols
		inline constexpr char SYM_SPACE = ' ';
		inline constexpr char SYM_STRING = '"';
		inline constexpr char SYM_FOUR_CC = '\'';
		inline constexpr char SYM_ACCESS_MODIFIER_DECL_END = ':';
		inline constexpr char DECIMAL_POINT = '.';
		inline constexpr char SYM_ACCESS_MEMBER = DECIMAL_POINT;
		inline constexpr char SYM_COMMA = ',';
		inline constexpr char SYM_DESTRUCTOR = '~';
		inline constexpr char SYM_UNDERSCORE = '_';

		inline constexpr char const symbols[] =
		{
			SYM_SPACE,
			SYM_STRING,
			SYM_FOUR_CC,
			SYM_ACCESS_MODIFIER_DECL_END,
			DECIMAL_POINT,
			SYM_ACCESS_MEMBER,
			SYM_COMMA,
			SYM_DESTRUCTOR,
			SYM_UNDERSCORE,
		};



		// Parentheses Open
		inline constexpr char PAREN_OPEN = '(';
		inline constexpr char PAREN_BRACKET_OPEN = '[';
		inline constexpr char PAREN_CURLY_OPEN = '{';
		inline constexpr char PAREN_ANGLE_OPEN = SS_OP_LESS_THAN;

		inline constexpr char const parensOpen[] =
		{
			PAREN_OPEN,
			PAREN_BRACKET_OPEN,
			PAREN_CURLY_OPEN,
			PAREN_ANGLE_OPEN,
		};

		// Parentheses Close
		inline constexpr char PAREN_CLOSE = ')';
		inline constexpr char PAREN_BRACKET_CLOSE = ']';
		inline constexpr char PAREN_CURLY_CLOSE = '}';
		inline constexpr char PAREN_ANGLE_CLOSE = SS_OP_GREATER_THAN;

		inline constexpr char const parensClose[] =
		{
			PAREN_CLOSE,
			PAREN_BRACKET_CLOSE,
			PAREN_CURLY_CLOSE,
			PAREN_ANGLE_CLOSE,
		};



		// Preprocess Keywords
		inline const string KW_IMPORT = "#import";

		// Declaration Keywords
		inline const string KW_CONST = "const";
		inline const string KW_ARRAY = "array";
		inline const string KW_FUNCTION = "function";

		// OO Keywords
		inline const string KW_CLASS = "class";
		inline const string KW_THIS = "this";
		inline const string KW_SUPER = "super";
		inline const string KW_PUBLIC = "public";
		inline const string KW_PRIVATE = "private";
		inline const string KW_STATIC = "static";
		inline const string KW_EXTENDS = "extends";
		inline const string KW_INTERFACE = "interface";
		inline const string KW_VIRTUAL = "virtual";
		inline const string KW_OPERATOR = "operator";
		inline const string KW_PROPERTY = "property";

		// OO Memory Management Keywords
		inline const string KW_NEW = "new";
		inline const string KW_DELETE = "delete";
		inline const string KW_NULLPTR = "nullptr";

		// Flow Control Keywords
		inline const string KW_RETURN = "return";
		inline const string KW_IF = "if";
		inline const string KW_ELSEIF = "elseif";
		inline const string KW_ELSE = "else";
		inline const string KW_LOOP = "loop";
		inline const string KW_EXITWHEN = "exitwhen";
		inline const string KW_FOR = "for";
		inline const string KW_WHILE = "while";
		inline const string KW_BREAK = "break";

		inline const string keywords[] =
		{
			KW_IMPORT,

			KW_CONST,
			KW_ARRAY,
			KW_FUNCTION,

			KW_CLASS,
			KW_THIS,
			KW_SUPER,
			KW_PUBLIC,
			KW_PRIVATE,
			KW_STATIC,
			KW_EXTENDS,
			KW_INTERFACE,
			KW_VIRTUAL,
			KW_OPERATOR,
			KW_PROPERTY,

			KW_NEW,
			KW_DELETE,
			KW_NULLPTR,

			KW_RETURN,
			KW_IF,
			KW_ELSEIF,
			KW_ELSE,
			KW_LOOP,
			KW_FOR,
			KW_WHILE,
			KW_EXITWHEN,
			KW_BREAK,
		};



		// Literal Types
		inline const string LIT_T_VOID = "void";
		inline const string LIT_T_THISTYPE = "thistype";

		inline const string literalTypes[] =
		{
			LIT_T_VOID,
			LIT_T_THISTYPE,
		};



		// Literal Constants
		inline const string LIT_C_TRUE = "true";
		inline const string LIT_C_FALSE = "false";
		inline const string LIT_C_NULL = "null";

		inline const string literalConstants[] =
		{
			LIT_C_TRUE,
			LIT_C_FALSE,
			LIT_C_NULL,
		};



		// Double Symbol Operators
		// Increment & Decrement Operators
		inline const string DS_OP_INCREMENT = "++";
		inline const string DS_OP_DECREMENT = "--";

		// Assignment Operators
		inline const string DS_OP_ADD_ASSIGN = "+=";
		inline const string DS_OP_SUBTRACT_ASSIGN = "-=";
		inline const string DS_OP_MULTIPLY_ASSIGN = "*=";
		inline const string DS_OP_DIVIDE_ASSIGN = "/=";

		// Relational Operators
		inline const string DS_OP_EQUALS = "==";
		inline const string DS_OP_NOT_EQUALS = "!=";
		inline const string DS_OP_LESS_THAN_OR_EQUALS = "<=";
		inline const string DS_OP_GREATER_THAN_OR_EQUALS = ">=";

		// Logical Operators
		inline const string DS_OP_AND = "&&";
		inline const string DS_OP_OR = "||";

		// Bitwise Operators
		inline const string DS_OP_BIN_AND_ASSIGN = "&=";
		inline const string DS_OP_BIN_OR_ASSIGN = "|=";
		inline const string DS_OP_BIN_XOR_ASSIGN = "^=";

		inline const string doubleSymbolOperators[] =
		{
			DS_OP_INCREMENT,
			DS_OP_DECREMENT,

			DS_OP_ADD_ASSIGN,
			DS_OP_SUBTRACT_ASSIGN,
			DS_OP_MULTIPLY_ASSIGN,
			DS_OP_DIVIDE_ASSIGN,

			DS_OP_EQUALS,
			DS_OP_NOT_EQUALS,
			DS_OP_LESS_THAN_OR_EQUALS,
			DS_OP_GREATER_THAN_OR_EQUALS,

			DS_OP_AND,
			DS_OP_OR,

			DS_OP_BIN_AND_ASSIGN,
			DS_OP_BIN_OR_ASSIGN,
			DS_OP_BIN_XOR_ASSIGN,
		};



		// Comment Declarations
		inline const string ONE_LINE_COMMENT_DECL = "//";
		inline const string MULTI_LINE_COMMENT_DECL_BEGIN = "/*";
		inline const string MULTI_LINE_COMMENT_DECL_END = "*/";

		inline const string commentDeclarations[] =
		{
			ONE_LINE_COMMENT_DECL,
			MULTI_LINE_COMMENT_DECL_BEGIN,
			MULTI_LINE_COMMENT_DECL_END,
		};



		// Unused Reserved Keywords
		inline const string UR_KW_CALL = "call";
		inline const string UR_KW_SET = "set";
		inline const string UR_KW_NATIVE = "native";
		inline const string UR_KW_DEBUG = "debug"; // May allow debug keyword
		inline const string UR_KW_TYPE = "type"; // May allow type keyword
		inline const string UR_KW_INTEGER = "integer";
		inline const string UR_KW_BOOLEAN = "boolean";
		inline const string UR_KW_CONSTANT = "constant";
		inline const string UR_KW_TAKES = "takes";
		inline const string UR_KW_RETURNS = "returns";
		inline const string UR_KW_NOTHING = "nothing";
		inline const string UR_KW_GLOBALS = "globals";
		inline const string UR_KW_ENDGLOBALS = "endglobals";
		inline const string UR_KW_CREATE = "create";
		inline const string UR_KW_DESTROY = "destroy";
		inline const string UR_KW_ENDFUNCTION = "endfunction";
		inline const string UR_KW_STRUCT = "struct";
		inline const string UR_KW_METHOD = "method";
		inline const string UR_KW_ENDMETHOD = "endmethod";
		inline const string UR_KW_STUB = "stub";
		inline const string UR_KW_LOCAL = "local";
		inline const string UR_KW_THEN = "then";
		inline const string UR_KW_ENDIF = "endif";
		inline const string UR_KW_ENDLOOP = "endloop";
		inline const string UR_KW_ENDINTERFACE = "endinterface";
		inline const string UR_KW_LIBRARY = "library";
		inline const string UR_KW_ENDLIBRARY = "endlibrary";
		inline const string UR_KW_MODULE = "module";
		inline const string UR_KW_ENDMODULE = "endmodule";
		inline const string UR_KW_SCOPE = "scope";
		inline const string UR_KW_ENDSCOPE = "endscope";
		inline const string UR_KW_REQUIRES = "requires";
		inline const string UR_KW_INITIALIZER = "initializer";
		inline const string UR_KW_OPTIONAL = "optional";
		inline const string UR_KW_ALLOCATE = "allocate";
		inline const string UR_KW_ONDESTROY = "onDestroy";
		inline const string UR_KW_ONINIT = "onInit";
		inline const string UR_KW_DEFAULTS = "defaults";
		inline const string UR_KW_DELEGATE = "delegate";
		inline const string UR_KW_IMPLEMENT = "implement";
		inline const string UR_KW_EXECUTE = "execute";
		inline const string UR_KW_EVALUATE = "evaluate";
		inline const string UR_KW_HOOK = "hook"; // May allow hook keyword

		inline const string unusedReservedKeywords[] =
		{
			UR_KW_CALL,
			UR_KW_SET,
			UR_KW_NATIVE,
			UR_KW_DEBUG,
			UR_KW_TYPE,
			UR_KW_INTEGER,
			UR_KW_BOOLEAN,
			UR_KW_TAKES,
			UR_KW_RETURNS,
			UR_KW_NOTHING,
			UR_KW_GLOBALS,
			UR_KW_ENDGLOBALS,
			UR_KW_CREATE,
			UR_KW_DESTROY,
			UR_KW_ENDFUNCTION,
			UR_KW_STRUCT,
			UR_KW_METHOD,
			UR_KW_ENDMETHOD,
			UR_KW_STUB,
			UR_KW_LOCAL,
			UR_KW_THEN,
			UR_KW_ENDIF,
			UR_KW_ENDLOOP,
			UR_KW_ENDINTERFACE,
			UR_KW_LIBRARY,
			UR_KW_ENDLIBRARY,
			UR_KW_MODULE,
			UR_KW_ENDMODULE,
			UR_KW_SCOPE,
			UR_KW_ENDSCOPE,
			UR_KW_REQUIRES,
			UR_KW_INITIALIZER,
			UR_KW_OPTIONAL,
			UR_KW_ALLOCATE,
			UR_KW_ONDESTROY,
			UR_KW_ONINIT,
			UR_KW_DEFAULTS,
			UR_KW_DELEGATE,
			UR_KW_IMPLEMENT,
			UR_KW_EXECUTE,
			UR_KW_EVALUATE,
			UR_KW_HOOK
		};
	}
}
