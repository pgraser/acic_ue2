#include <string.h>
#include <assert.h>
#include "pch.h"

class String
{
public:
	explicit String(const char* str)
		: m_length(strlen(str))
		, m_string(new char[m_length + 1u])
	{
		assert("Given string may not be null" && (str != nullptr));

		// copies null terminator as well
		memcpy(m_string, str, m_length + 1u);
	}

	String(const String& other)
	{
		m_length = other.m_length;
		m_string = new char[m_length + 1u];
		memcpy(m_string, other.c_str, m_length + 1u);
	}

	String& operator=(const String& other)
	{
		if (this != &other)
		{
			delete[] m_string;
			m_length = other.m_length;
			m_string = new char[m_length + 1u];
			memcpy(m_string, other.c_str, m_length + 1u);
		}
		return *this;
	}

	~String(void)
	{
		delete[] m_string;
	}

	void Concatenate(const char* str)
	{
		Concatenate(str, strlen(str));
	}

	void Concatenate(const String& str)
	{
		Concatenate(str.m_string, str.m_length);
	}

	// returns length of string without null terminator
	size_t GetLength(void) const
	{
		return m_length;
	}

	const char* c_str(void) const
	{
		return m_string;
	}

private:
	void Concatenate(const char* str, size_t length)
	{
		const size_t neededBytes = m_length + length + 1u;
		char* newString = new char[neededBytes];
		memcpy(newString, m_string, m_length);

		// copies null terminator as well
		memcpy(newString + m_length, str, length + 1u);

		delete[] m_string;
		m_string = newString;
		m_length += length;
	}

	size_t m_length;
	char* m_string;
};
