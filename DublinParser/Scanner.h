/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer Literal token */
	SEOF_T,		/* 11: Source end-of-file token */
	SPA_T,      /* 12: Space Token*/
	TAB_T,		/* 13: Tab Token */
	VAR_T,      /* 14: Variable Sign */
	UND_T,		/* 15: Underscore */
	ARTH_T,     /* 16: Arithmetic Token */
	REL_T,      /* 17: Relational Token */
	LOG_T,		/* 18: Logical Token    */
	ASS_T,      /* 19: Assignment Token */
	LIN_T,		/* 20: Line break Token */
	COMM_T      /* 21: Comma Token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	dub_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	dub_int intValue;						/* integer literal attribute (value) */
	dub_int keywordIndex;					/* keyword index in the keyword table */
	dub_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	dub_float floatValue;					/* floating-point literal attribute (value) */
	dub_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	dub_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	dub_byte flags;			/* Flags information */
	union {
		dub_int intValue;				/* Integer value */
		dub_float floatValue;			/* Float value */
		dub_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	dub_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '$'
#define CHRCOL3 '"'
#define CHRCOL4 '_'
#define CHRCOL5 '\n'
#define CHRCOL6 ' '


/* These constants will be used on VID / MID function */
#define MNIDPREFIX '_'
#define VARPREFIX '$'


/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 8

/* TO_DO: Transition table - type of states defined in separate table */
static dub_int transitionTable[][TABLE_COLUMNS] = {
	/*   [A-z] , [0-9],    $,    ",    _, \n,       ,  other
		   L(0),  D(1), C(2), Q(3), U(4), N(5),  S(6),  O(7)   */
		{     1,  14,   6,     4,    8,   ESWR,  ESWR,     2},  // S0:  NOAS
		{     1,     1, ESWR, ESWR, ESWR, ESWR,     2,  ESWR},  // S1:  NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S2:  ASNR  (KEY)
		{  ESWR,  ESWR, ESWR, ESWR,  ESWR, ESWR,  ESWR,  ESWR}, // S3:  NOAS
		{     4,     4,    4,    5,    4,    4,     4,     4},  // S4:  NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S5:  ASNR  (SL)
		{     6,     6, ESWR, ESWR, ESWR,    7,     7,  ESWR},  // S6:  NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S7:  ASNR  (VAR)
		{  ESWR,  ESWR, ESWR, ESWR,    9, ESWR,  ESWR,  ESWR},  // S8:  NOAS
		{     9,     9, ESWR, ESWR,   10, ESWR,  ESWR,  ESWR},  // S9:  NOAS
		{  ESWR,  ESWR, ESWR, ESWR,   11,   11,  ESWR,  ESWR},  // S10: NOAS
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S11: ASWR  (MVID)
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S12: ASWR  (ES)
		{    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS},  // S13: ASWR  (ER)
		{  ESWR,    14, ESWR, ESWR, ESWR,   15,    15,    15},  // S14: NOAS  
        {    FS,    FS,   FS,   FS,   FS,   FS,    FS,    FS}   // S15: ASWR  (IL)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static dub_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY) - Keywords */
	NOFS, /* 03 */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) - String Literal */
	NOFS, /* 06 */
	FSWR, /* 07 (VAR) - Variables */
	NOFS, /* 08 */
	NOFS, /* 09 */
	NOFS, /* 10 */
	FSNR, /* 11 (MVID) - Methods */
	FSNR, /* 12 (Err1 - no retract) */
	FSWR, /* 13 (Err2 - retract) */
	NOFS, /* 14 */
	FSWR  /* 15 (IL) - Integer Literal */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
dub_int startScanner(ReaderPointer psc_buf);
static dub_int nextClass(dub_char c);			/* character class function */
static dub_int nextState(dub_int, dub_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(dub_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(dub_char lexeme[]);
Token funcVar	(dub_char lexeme[]);
Token funcKEY	(dub_char lexeme[]);
Token funcMID   (dub_char lexeme[]);
Token funcErr	(dub_char lexeme[]);
Token funcIL    (dub_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcKEY,	/* key	[02] */
	NULL,	    /* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,	    /* -    [06] */
	funcVar,	/* VAR  [07] */
	NULL,	    /* -    [08] */
	NULL,	    /* -    [09] */
	NULL,		/* -    [10] */
	funcMID,	/* MID  [11] */
	funcErr,	/* ERR1 [12] */
	funcErr,	/* ERR2 [13] */
	NULL,       /* -    [14] */
	funcIL      /* IL   [15] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 8

/* TO_DO: Define the list of keywords */
static dub_char* keywordTable[KWT_SIZE] = {
	"class",
	"else",
	"while",
	"do",
	"return",
	"print",
	"if",
	"void"
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	dub_char indentationCharType;
	dub_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
