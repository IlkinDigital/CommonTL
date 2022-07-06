#pragma once

#ifndef CTL_STRING_H
#define CTL_STRING_H

#include <ostream>
#include <cstring>

#include "ctl/Allocator.h"

namespace CTL
{
	// Dynamically allocated String
	class String : public Allocator<char>
	{
	public:
		static size_t s_MaxSize;
	public:
		String() {}
		String(const String& other);
		String(String&& other);

		String(size_t size);
		String(char* string); 
		String(const char* string);
		
		void Copy(char* string);
		void Copy(const char* string);

		void PushBack(const char& c) override;

		void PushString(const String& string);
		void PushString(const char* string);
		void PushString(char*& string);

		String Cut(const size_t& rLeft, const size_t& rRight);

		char* Cstr() const;

		void operator = (const char* string);
		void operator = (char* string);

		String operator + (const String& string) const;
		void operator += (const String& string);
		void operator += (const char* string);

		bool operator == (const String& string) const;
		bool operator != (const String& string) const;

		friend std::ostream& operator << (std::ostream& stream, const String& string);

	private:
		size_t ComputeSize(size_t size) const;
	};

	// Static string
	class StringView
	{
	public:
		StringView(char* str, size_t size)
		{
			m_ViewBuffer = str;
			m_Size = size;
		}

		StringView(const char* str)
		{
			m_ViewBuffer = str;
			m_Size = strlen(str);
		}

	private:
		const char* m_ViewBuffer;
		size_t m_Size;
	};
}

#endif