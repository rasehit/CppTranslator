// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "lexeme.h"
#include <iostream>

const Lexeme & Lexeme::operator=(Lexeme & str)
{
	m_str = str.m_str;
	m_type = str.m_type;
	m_row = str.m_row;
	m_position = str.m_position;
	return *this;
}


void Lexeme::Print()
{
	//stl version
	std::cout << "Lexeme \"";
	m_str.Print();
	std::cout << "\" of type ";
	names.names[m_type].Print();
	std::cout << " at (" << m_row <<
		"," << m_position << ");\n";
}

void Lexeme::PushBack(char ch)
{
	m_str += ch;
}

void Lexeme::Set(String str, LexemeType type, int row, int position)
{
	m_str = str;
	m_type = type;
	m_row = row;
	m_position = position;
}

LexemeList::LexemeList(int num)
{
	if (num < 1)
	{
		begin = nullptr;
		length = 0;
	}
	else
	{
		begin = new ListNode;
		ListNode * prev = begin, *cur = nullptr;
		for (int i = 1; i < num; i++)
		{
			cur = new ListNode;
			prev->next = cur;
			prev = cur;
		}
		prev->next = nullptr;
		length = num;
	}
}

LexemeList::~LexemeList()
{
	ListNode * next, *cur = begin;
	while (cur != nullptr)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
}

void LexemeList::PushBack(Lexeme& item)
{
	ListNode * p = new ListNode, *next = begin;
	p->item = item;
	p->next = nullptr;
	length++;
	if (begin == nullptr)
	{
		begin = p;
		return;
	}
	while (next->next != nullptr)
		next = next->next;
	next->next = p;
}

Lexeme LexemeList::At(int num)
{
	ListNode * p = begin;
	if (begin == nullptr)
		throw;
	for (int i = 0; i < num; i++)
	{
		p = p->next;
		if (p == nullptr)
			throw;
	}
	return p->item;
}

int LexemeList::GetLength()
{
	return length;
}

void LexemeList::Print()
{
	ListNode * p = begin;
	while (p != nullptr)
	{
		p->item.Print();
		p = p->next;
	}
}
