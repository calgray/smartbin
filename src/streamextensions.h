#pragma once

#include <Print.h>
#include <sstream>
#include <optional>


template<typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os << "NULL";
}

template<class T>
inline Print& operator <<(Print &obj, T arg)
{
    std::stringstream ss;
    ss << arg;
    obj.print(ss.str().c_str());
    return obj;
}