// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mstring.h"
#include <iostream>

void String::Append(char ch)
{
	if (current == (length - 1))
	{
		length *= 2;
		char * new_str = new char[length]; 
		for (int i = 0; i < current; i++)
		{
			new_str[i] = contents[i];
		}
		delete [] contents;
		contents = new_str;		
	}
	contents[current] = ch;	
	current++;
	contents[current] = '\0';
	
}

String::String(String & str)
{
	int i = 0;
	contents = new char[SIZE];
	current = 0;
	length = SIZE;
	while (str[i] != -1)
	{
		Append(str[i]);
		i++;
	}
}

String::String(const char * p_contents)
{
	int i = 0;
	contents = new char[SIZE];
	current = 0;
	length = SIZE;
	while (p_contents[i] != '\0')
	{
		Append(p_contents[i]);
		i++;
	}
}

String::~String()
{
	delete[] contents;
}

const String & String::operator=(String & str)
{
	int i = 0;
	current = 0;
	while (str[i] != -1)
	{
		Append(str[i]);
		i++;
	}
	return *this;
}

const String & String::operator=(const char * p_contents)
{
	int i = 0;
	current = 0;
	while (p_contents[i] != '\0')
	{
		Append(p_contents[i]);
		i++;
	}
	return *this;
}

const String & String::operator+=(const char * p_contents)
{
	int i = 0;
	while (p_contents[i] != '\0')
	{
		Append(p_contents[i]);
		i++;
	}
	return *this;
}

const String & String::operator+=(char ch)
{
	Append(ch);
	return *this;
}

const String & String::operator+=(String & str)
{
	Append(str);
	return *this;
}

char String::operator[](int i)
{
	return At(i);
}

bool String::operator==(String & str)
{
	int i = 0;
	if (current != str.current)
		return false;
	for (int i = 0; i < current; i++)
	{
		if (contents[i] != str.contents[i])
			return false;
	}
	return true;
}

bool String::operator==(const char * p_contents)
{
	int i = 0;
	while (contents[i] != '\0')
	{
		if (p_contents[i] != contents[i])
			return false;
		i++;
	}
	if (p_contents[i] != contents[i])
		return false;
	return true;
}

int String::GetLength()
{
	return current;
}

int String::FindSymbol(char ch)
{
	int i = 0;
	for (int i = 0; i < current; i++)
	{
		if (contents[i] == ch)
			return i;
	}
	return -1;
}

char String::At(int i)
{
	if ((i < current) && (i >= 0))
		return contents[i];
	else 
		return -1;
}

void String::Print()
{
	std::cout << contents;
	//printf("%s", contents);
}

void String::Append(String& str)
{
	int i = 0;
	while (str[i] != -1)
	{
		Append(str[i]);
		i++;
	}
}

void String::Append(String && str)
{
	int i = 0;
	while (str[i] != -1)
	{
		Append(str[i]);
		i++;
	}
}

char String::PopBack()
{
	if (current == 0)
		return '\0';
	current--;
	char t = contents[current];
	contents[current] = '\0';
	return t;
}

