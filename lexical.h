#ifndef LEXICAL_HEADER
#define LEXICAL_HEADER

#include "mstring.h"
#include "lexeme.h"

class LexicalAnalyzer
{
private:
	String m_string;
	LexemeList m_list;
	String	digits, sgndel,
			unsgndel, labels;
	enum State 
	{
		S_HOME,
		S_ERROR,
		S_DELIMITER,
		S_NUMBER,
		S_IDENTIFIER,
		S_KEY, 
		S_ASSIGN, 
		S_STRING
	} m_cstate, m_nstate;
	enum SymType
	{
		T_SGNDELIMITER,
		T_UNSGNDELIMITER,
		T_DIGIT, 
		T_ALPHABETIC, 
		T_COLON,
		T_ASSIGNSIGN,
		T_QUOTE,
		T_LABELS,
		T_OTHER
	};
	int m_row, m_cur_pos, m_last_pos;
	bool m_is_error;

	SymType WhatSymType(char ch);
	LexemeType WhatLexemeType(State state, char ch);
	void MaintainHome(int ch);
	State GetNextState(State state, SymType type);
	State HomeState(SymType type);
	State ErrorState(SymType type);
	State NumberState(SymType type);
	State IdentifierState(SymType type);
	State KeyState(SymType type);
	State AssignState(SymType type);
	State StringState(SymType type);
public:
	LexicalAnalyzer();
	~LexicalAnalyzer() {};
	void Step(int ch);
	void Print();

};

#endif // !LEXICAL_HEADER

