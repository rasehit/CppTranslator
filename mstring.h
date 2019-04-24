#ifndef TOOLS_HEADER
#define TOOLS_HEADER
constexpr int SIZE = 64;

class String
{
private:
	char * contents;
	int length;
	int current;
public:
	String(String & str);
	String(const char * p_contents);
	String() : String ("") {};
	~String();

	const String& operator=(String& str);
	const String& operator=(const char * p_contents);
	const String& operator+=(const char * p_contents);
	const String& operator+=(char ch);
	const String& operator+=(String& str);
	char operator[](int i);
	bool operator==(String& str);
	bool operator==(const char * p_contents);

	int GetLength();
	int FindSymbol(char ch);
	void Append(char ch);
	void Append(String& str);
	void Append(String&& str);
	char PopBack();
	char At(int i);
	void Print();
};

template <class T1, class T2, class T3>
struct TripleTupleItem
{
	T1 key1;
	T2 key2;
	T3 value;		
};




#endif
