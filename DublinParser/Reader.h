/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 ________________________________________
|                                        |
| ........... DUBLIN LANGUAGE ...........|
|                                        |
| ________       ___.   .__  .__         |
| \______ \  __ _\_ |__ |  | |__| ____   |
|  |    |  \|  |  \ __ \|  | |  |/    \  |
|  |    |`  \  |  / \_\ \  |_|  |   |  \ |
| /_______  /____/|___  /____/__|___|  / |
| _____________________________________  |
|                                        |
|                                        |
| ... ALGONQUIN COLLEGE - 2022F ... .....|
|________________________________________|

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */ 
#define READER_SET_FUL   0x08 /* Binary 0000 1000 Bitwise OR |= */
#define READER_RESET_FUL 0xF7   /* Binary 1111 0111 Bitwise AND &= */
#define READER_CHECK_FUL READER_SET_FUL  /* uses AND */
/* TO_DO: BIT 2: EMP: Empty */
#define READER_SET_EMP 0x04   /* Binary 0000 0100 Bitwise OR |= */
#define READER_RESET_EMP 0xFB   /* Binary 1111 1011 Bitwise AND &= */
#define READER_CHECK_EMP READER_SET_EMP  
/* TO_DO: BIT 1: REL = Relocation */
#define READER_SET_REL 0x02   /* Binary 0000 0010 Bitwise OR |= */
#define READER_RESET_REL 0xFD   /* Binary 1111 1101 Bitwise AND &= */
#define READER_CHECK_REL READER_SET_REL  
/* TO_DO: BIT 0: END = EndOfBuffer */
#define READER_SET_END 0x01  /* 0000 0001 Bitwise OR |= */
#define READER_RESET_END 0xFE /* 1111 1110 Bitwise AND &= */
#define READER_CHECK_END READER_SET_END

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (DUBLIN) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	dub_int mark;			/* the offset to the mark position (in chars) */
	dub_int read;			/* the offset to the get a char position (in chars) */
	dub_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	dub_char*	content;			/* pointer to the beginning of character array (character buffer) */
	dub_int	    size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	dub_int	    increment;			/* character array increment factor */
	dub_int	    mode;				/* operational mode indicator */
	dub_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	dub_int	    histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(dub_int, dub_int, dub_int);
ReaderPointer	readerAddChar		(ReaderPointer const, dub_char);
dub_boln		readerClear		    (ReaderPointer const);
dub_boln		readerFree		    (ReaderPointer const);
dub_boln		readerIsFull		(ReaderPointer const);
dub_boln		readerIsEmpty		(ReaderPointer const);
dub_boln		readerSetMark		(ReaderPointer const, dub_int);
dub_int		    readerPrint		    (ReaderPointer const);
dub_int		    readerLoad			(ReaderPointer const, FILE* const);
dub_boln		readerRecover		(ReaderPointer const);
dub_boln		readerRetract		(ReaderPointer const);
dub_boln		readerRestore		(ReaderPointer const);
/* Getters */
dub_char		readerGetChar		(ReaderPointer const);
dub_char*		readerGetContent	(ReaderPointer const, dub_int);
dub_int		    readerGetPosRead	(ReaderPointer const);
dub_int		    readerGetPosWrte	(ReaderPointer const);
dub_int		    readerGetPosMark	(ReaderPointer const);
dub_int		    readerGetSize		(ReaderPointer const);
dub_int		    readerGetInc		(ReaderPointer const);
dub_int		    readerGetMode		(ReaderPointer const);
dub_byte		readerGetFlags		(ReaderPointer const);
dub_int		    readerShowStat		(ReaderPointer const);

#endif
