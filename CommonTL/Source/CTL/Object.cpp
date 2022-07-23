#include "ctlpch.h"
#include "Object.h"

#include "CTL/String.h"

namespace CTL {

    String Object::ToString() const
    {
        return typeid(*this).name();
    }

    std::ostream& operator<<(std::ostream& stream, const Object& object)
    {
        return stream << object.ToString();
    }

}