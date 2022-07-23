#pragma once

#include <ostream>

namespace CTL {

	class String;

	class Object
	{
	public:
		virtual String ToString() const;

		friend std::ostream& operator << (std::ostream& stream, const Object& object);
	};

}
