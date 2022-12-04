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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

dub_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
dub_void matchToken(dub_int tokenCode, dub_int tokenAttribute) {
	dub_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
dub_void syncErrorHandler(dub_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
dub_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
dub_void program() {
	while (lookahead.code != SEOF_T) {
	statements();
	}
	/*
	default:
		printError();
	}
	*/
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}



/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
dub_void optVarListDeclarations() {
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

	


// method paramaters handle
dub_void methodParam() {
	matchToken(LPR_T, NO_ATTR);
	while (lookahead.code != RPR_T) {
		switch (lookahead.code) {
		case STR_T: // string 
			matchToken(STR_T, NO_ATTR);
			break;
		case VAR_T: // variable
			matchToken(VAR_T, NO_ATTR);
			break;
		case INL_T: // int
			matchToken(INL_T, NO_ATTR);
			break;
		default:
			printError();
		}
		if (lookahead.code != COMM_T) { // check for multi param
			if (lookahead.code == RPR_T) { // check if only one param
				break;
			}
			else {
				printError(); // error otherwise
			}
		}
		else {
			matchToken(COMM_T, NO_ATTR); // comma tokens
		}
	}
	printf("%s%s\n", STR_LANGNAME, ": Method Parameter Handle parsed");
}


/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
dub_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
dub_void statementsPrime() {
	if (lookahead.code != SEOF_T) {
		statements();
	}
	/*
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
	*/
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
dub_void statement() {
	
	while (lookahead.code == LIN_T) {
		matchToken(LIN_T, NO_ATTR);
	}
	while (lookahead.code == TAB_T) {
		matchToken(TAB_T, NO_ATTR);
	}
	while (lookahead.code == SPA_T) {
		matchToken(SPA_T, NO_ATTR);
	}
	switch (lookahead.code) {
	case ARTH_T:
		matchToken(ARTH_T, NO_ATTR);
		break;
	case REL_T:
		matchToken(REL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case MNID_T:
		if (lookahead.code == MNID_T) {
			matchToken(MNID_T, NO_ATTR);
			while (lookahead.code == LIN_T) {
				matchToken(LIN_T, NO_ATTR);
			}
			function();
		}
		break;
	
	case KW_T:    
		if (lookahead.attribute.codeType == KW_return) {
			break;
		}
		else {
			parameter();
			break;
		}
		
	case VAR_T:
		if (lookahead.code == VAR_T) {
			matchToken(VAR_T, NO_ATTR);
			while (lookahead.code == SPA_T) {
				matchToken(SPA_T, NO_ATTR);
			}
			if (lookahead.code == ASS_T) {
				matchToken(ASS_T, NO_ATTR);
				assignment();
			}
			else {
				break;
			}
		}
		break;
	case SEOF_T:
		break;
	default:
		printError();
	}
}

dub_void assignment() {
	while (lookahead.code == SPA_T) {
		matchToken(SPA_T, NO_ATTR);
	}
	if (lookahead.code == VAR_T) {
		matchToken(VAR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Variable assignment parsed");
	}
	else if (lookahead.code == STR_T) {
		matchToken(STR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": String assignment parsed");
	}
	else if (lookahead.code == INL_T) {
		matchToken(INL_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Integer assignment parsed");
	}
	else {
		printf("%s%s\n", STR_LANGNAME, ": Error No assignment parsed");
	}
	while (lookahead.code == LIN_T) {
		matchToken(LIN_T, NO_ATTR);
	}
}
dub_void function() {
	while (lookahead.attribute.codeType != KW_return) {
		statement();
		if (lookahead.attribute.codeType == KW_return) {
			matchToken(KW_T, KW_return);
			break;
		}
	}
	printf("%s%s\n", STR_LANGNAME, ": Function statement parsed");

}

dub_void parameter() {
	
	if (lookahead.attribute.codeType == KW_print) {
		matchToken(KW_T, KW_print);
		matchToken(LPR_T, NO_ATTR);
		matchToken(STR_T, NO_ATTR);
		matchToken(RPR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Print statement parsed");
	}
	if (lookahead.attribute.codeType == KW_while) {
		matchToken(KW_T, KW_while);
		while (lookahead.code != LIN_T) {
			statement();
		}
		printf("%s%s\n", STR_LANGNAME, ": While statement parsed");
	}
	if (lookahead.attribute.codeType == KW_do) {
		matchToken(KW_T, KW_do);
		while (lookahead.code != LIN_T) {
			statement();
		}
		printf("%s%s\n", STR_LANGNAME, ": do statement parsed");
	}

}




dub_void arithmetic() {
	while (lookahead.code == SPA_T) {
		matchToken(SPA_T, NO_ATTR);
	}
	
	while (lookahead.attribute.codeType != KW_return) {
		statement();
		if (lookahead.attribute.codeType == KW_return) {
			matchToken(KW_T, KW_return);
			break;
		}
	}
	printf("%s%s\n", STR_LANGNAME, ": Function statement parsed");

}


/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
dub_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
dub_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
