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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */
 
/* Logical constants - adapt for your language */
#define DUB_TRUE  1
#define DUB_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			dub_char;
typedef int				dub_int;
typedef float			dub_float;
typedef void			dub_void;

typedef unsigned char	dub_boln;
typedef unsigned char	dub_byte;

typedef long			dub_long;
typedef double			dub_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
dub_int mainReader  (dub_int argc, dub_char** argv);

dub_int mainScanner (dub_int argc, dub_char** argv);
/*
boa_intg mainParser  (boa_intg argc, boa_char** argv);
*/
dub_void printLogo();

#endif
