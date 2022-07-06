#include <iostream>

#include "TimeLib.h"

#include "CTL/String.h"

class Entity
{
public:
	Entity(const std::string& name)
		: m_Name(name) {}

	std::string m_Name;
};

int main()
{
	Time::TimeBomb tb;

	tb.Activate();

	for (int i = 0; i < 200'000; i++)
	{
		CTL::String hi;
		hi.PushBack('i');
	}

	tb.Explode("CTL::String time: ");

	tb.Activate();

	for (int i = 0; i < 100'000; i++)
	{
		std::string hi;
		hi.push_back('i');
	}

	tb.Explode("std::string time: ");

	return 0;
}