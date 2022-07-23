#pragma once

#include "CoreMinimal.h"
#include "CTL/String.h"

namespace CTL {

	class Formatter
	{
	public:
		static String ToString(int8 value);
		static String ToString(int16 value);
		static String ToString(int32 value);
		static String ToString(int64 value);

		static String ToString(uint8 value);
		static String ToString(uint16 value);
		static String ToString(uint32 value);
		static String ToString(uint64 value);

		static String ToString(float value);
		static String ToString(double value);
	};

}