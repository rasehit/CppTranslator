// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "lexical.h"
#include <iostream>

LexicalAnalyzer::SymType LexicalAnalyzer::WhatSymType(char ch)
{
	if (digits.FindSymbol(ch) >= 0)
		return T_DIGIT;
	if (sgndel.FindSymbol(ch) >= 0)
		return T_SGNDELIMITER;
	if (unsgndel.FindSymbol(ch) >= 0)
		return T_UNSGNDELIMITER;
	if (labels.FindSymbol(ch) >= 0)
		return T_LABELS;
	if (((ch >= 'a') && (ch <= 'z')) ||
		((ch >= 'A') && (ch <= 'Z')))
		return T_ALPHABETIC;
	if (ch == ':')
		return T_COLON;
	if (ch == '=')
		return T_ASSIGNSIGN;
	if (ch == '\"')
		return T_QUOTE;
	return T_OTHER;
}

LexemeType LexicalAnalyzer::WhatLexemeType(State state, char ch)
{
	if (state == S_NUMBER)
		return INTEGER;
	if (state == S_DELIMITER)
		return DELIMITER;
	if (state == S_ERROR)
		return ERROR;
	if (state == S_IDENTIFIER)
	{
		if (ch == '$')
			return VARIABLE;
		if (ch == '@')
			return LABEL;
		if (ch == '?')
			return FUNCTION;
	}
	if (state == S_KEY)
		return KEYWORD;
	if (state == S_ASSIGN)
		return ASSIGN;
	if (state == S_STRING)
		return STRING;
	return UNDEFINED;
}

void LexicalAnalyzer::MaintainHome(int ch)
{
	Lexeme temp;
	if (m_cstate == S_HOME)
	{
		if (WhatSymType(ch) == T_UNSGNDELIMITER)
			return;
		if ((WhatSymType(ch) == T_SGNDELIMITER) ||
			(WhatSymType(ch) == T_ASSIGNSIGN))
		{
			m_string += ch;
			m_cstate = S_DELIMITER;
		}
	}
	if (m_cstate == S_ASSIGN)
		m_string += '=';
	temp.Set(m_string, WhatLexemeType(m_cstate, m_string[0]),
		m_row, m_last_pos);
	m_list.PushBack(temp);
	m_string = "";
	if ((m_cstate == S_IDENTIFIER ||
		m_cstate == S_KEY ||
		m_cstate == S_NUMBER))
	{
		m_cstate = m_nstate;
		Step(ch);
	}
	m_cstate = m_nstate;
}

LexicalAnalyzer::State LexicalAnalyzer::GetNextState
	(State state, SymType type)
{
	switch (state)
	{
	case LexicalAnalyzer::S_HOME:
		return HomeState(type);
	case LexicalAnalyzer::S_ERROR:
		return ErrorState(type);
	case LexicalAnalyzer::S_NUMBER:
		return NumberState(type);
	case LexicalAnalyzer::S_IDENTIFIER:
		return IdentifierState(type);
	case LexicalAnalyzer::S_KEY:
		return KeyState(type);
	case LexicalAnalyzer::S_ASSIGN:
		return AssignState(type);
	case LexicalAnalyzer::S_STRING:
		return StringState(type);
	default:
		return S_ERROR;
	}
}

LexicalAnalyzer::State LexicalAnalyzer::HomeState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_SGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_UNSGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_DIGIT:
		return S_NUMBER;
	case LexicalAnalyzer::T_ALPHABETIC:
		return S_KEY;
	case LexicalAnalyzer::T_COLON:
		return S_ASSIGN;
	case LexicalAnalyzer::T_QUOTE:
		return S_STRING;
	case LexicalAnalyzer::T_LABELS:
		return S_IDENTIFIER;
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_HOME;
	default:
		return S_ERROR;
	}
}

LexicalAnalyzer::State LexicalAnalyzer::ErrorState(SymType type)
{
	return S_ERROR;
}

LexicalAnalyzer::State LexicalAnalyzer::NumberState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_SGNDELIMITER:
	case LexicalAnalyzer::T_UNSGNDELIMITER:
	case LexicalAnalyzer::T_COLON:
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_HOME;
	case LexicalAnalyzer::T_DIGIT:
		return S_NUMBER;
	default:
		return S_ERROR;
	}
}


LexicalAnalyzer::State LexicalAnalyzer::IdentifierState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_SGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_UNSGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_DIGIT:
		return S_IDENTIFIER;
	case LexicalAnalyzer::T_ALPHABETIC:
		return S_IDENTIFIER;
	case LexicalAnalyzer::T_COLON:
		return S_HOME;
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_HOME;
	default:
		return S_ERROR;
	}
}

LexicalAnalyzer::State LexicalAnalyzer::KeyState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_SGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_UNSGNDELIMITER:
		return S_HOME;
	case LexicalAnalyzer::T_ALPHABETIC:
		return S_KEY;
	case LexicalAnalyzer::T_COLON:
		return S_HOME;
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_HOME;
	default:
		return S_ERROR;
	}	
}

LexicalAnalyzer::State LexicalAnalyzer::AssignState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_HOME;
	default:
		return S_ERROR;
	}
}

LexicalAnalyzer::State LexicalAnalyzer::StringState(SymType type)
{
	switch (type)
	{
	case LexicalAnalyzer::T_SGNDELIMITER:
		return S_STRING;
	case LexicalAnalyzer::T_UNSGNDELIMITER:
		return S_STRING;
	case LexicalAnalyzer::T_DIGIT:
		return S_STRING;
	case LexicalAnalyzer::T_ALPHABETIC:
		return S_STRING;
	case LexicalAnalyzer::T_COLON:
		return S_STRING;
	case LexicalAnalyzer::T_QUOTE:
		return S_HOME;
	case LexicalAnalyzer::T_LABELS:
		return S_STRING;
	case LexicalAnalyzer::T_ASSIGNSIGN:
		return S_STRING;
	default:
		return S_ERROR;
	}
}

LexicalAnalyzer::LexicalAnalyzer() : m_is_error(false)
{
	m_row = 1;
	m_cur_pos = 0;
	m_last_pos = 0;
	m_cstate = S_HOME;
	m_nstate = S_HOME;
	digits = "0123456789";
	sgndel = "+-*\\,;<>[]&|^!(){}";
	unsgndel = " \n\t";
	labels = "?@$";
}

void LexicalAnalyzer::Step(int ch)
{
	m_cur_pos++;
	if (ch == '\n')
	{
		m_row++;
		m_cur_pos = 0;
	}
	m_nstate = GetNextState(m_cstate, WhatSymType(ch));
	if (m_nstate == S_HOME)
	{
		m_last_pos = m_cur_pos;
		MaintainHome(ch);
		return;
	}
	else if (m_nstate == S_ERROR)
	{
		if (!m_is_error)
		{
			Lexeme temp;
			m_is_error = true;
			temp.Set("ERROR", ERROR, m_row, m_last_pos);
			m_list.PushBack(temp);
			m_cstate = m_nstate;
		}
		return;
	}
	if (!((m_cstate == S_HOME) && (m_nstate == S_STRING)))
		m_string += ch;
	m_cstate = m_nstate;

}

void LexicalAnalyzer::Print()
{
	m_list.Print();
}

