#ifndef LEXEME_HEADER
#define LEXEME_HEADER

#include "mstring.h"

enum LexemeType 
{
	DELIMITER = 0,
	INTEGER,
	STRING,
	VARIABLE,
	LABEL,
	FUNCTION,
	KEYWORD,
	ASSIGN,
	ERROR,
	UNDEFINED
};

class LexemeNames
{
public:
	String names [10];	
	LexemeNames()
	{
		names[0] = "DELIMITER";
		names[1] = "INTEGER";
		names[2] = "STRING";
		names[3] = "VARIABLE";
		names[4] = "LABEL";
		names[5] = "FUNCTION";
		names[6] = "KEYWORD";
		names[7] = "ASSIGN";
		names[8] = "ERROR";
		names[9] = "UNDEFINED";
	};
};

class Lexeme
{
private:
	int m_row, m_position;
	LexemeType m_type;
	LexemeNames names;
	String m_str;
public:
	Lexeme(	String str = "",
			LexemeType type = UNDEFINED,
			int row = 0,
			int position = 0) :
			m_str(str), m_type(type),
			m_row(row), m_position(position) {};
	Lexeme(Lexeme& lex) :
		m_str(lex.m_str),
		m_type(lex.m_type),
		m_row(lex.m_row),
		m_position(lex.m_position) {};
	~Lexeme() {};

	const Lexeme& operator=(Lexeme& str);

	void Print();
	void PushBack(char ch);
	void Set(String str, LexemeType type, int row,
		int position);
};

struct ListNode
{
	Lexeme item;
	ListNode * next;
};

class LexemeList
{
private:
	ListNode * begin;
	int length;
public:
	LexemeList(int i);
	LexemeList() : LexemeList(0) {};
	~LexemeList();

	void PushBack(Lexeme& item);
	Lexeme At(int num);
	int GetLength();
	void Print();
};

#endif // !LEXICAL_HEADER

#pragma once
