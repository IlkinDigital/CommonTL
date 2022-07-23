#include <iostream>

#include "TimeLib.h"

#include "CTL/CTL.h"
#include "CTL/String.h"
#include "CTL/Vector.h"
#include "CTL/PriorityQueue.h"

#define LOG(message) std::cout << (message) << std::endl

using namespace CTL;

namespace Testbed {

	class Entity
	{
	public:
		Entity(const CTL::String& name)
			: m_Name(name) {}

		CTL::String m_Name;
	};

	void StringTest()
	{
		Time::TimeBomb tb;

		tb.Activate();

		for (int i = 0; i < 100'000; i++)
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
	}
}

void Log(const Object& object)
{
	LOG(object.ToString());
}

int main()
{
	CTL::Vector<int> vector;
	vector.PushBack(12);
	vector.PushBack(11);
	vector.PushBack(10);

	Log(vector);

	return 0;
}