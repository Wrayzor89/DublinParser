/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern dub_int line;
extern Token tokenizer();
extern dub_char* keywordTable[];
dub_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"Dublin"
#define LANG_RETURN		"return"
#define LANG_READ		"input&"
#define LANG_MAIN		"__main__"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_class,
	KW_else,
	KW_while,
	KW_do,
	KW_return,
	KW_print,
	KW_if,
	KW_void
};

/* Function definitions */
dub_void startParser();
dub_void matchToken(dub_int, dub_int);
dub_void syncErrorHandler(dub_int);
dub_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
dub_void optVarListDeclarations();
dub_void outputStatement();
dub_void outputVariableList();
dub_void program();
dub_void statement();
dub_void statements();
dub_void statementsPrime();
dub_void methodParam();
dub_void function();
dub_void assignment();
dub_void arithmetic();
dub_void parameter();
#endif
