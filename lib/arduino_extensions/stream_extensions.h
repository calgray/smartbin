/**
 * MIT License
 * 
 * Copyright (c) 2021 UWA-CITS5506-Gp01
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <Print.h>
#include <Printable.h>
#include <sstream>
#include <optional>


inline Print& operator<<(Print& obj, const char* arg)
{
    obj.print(arg);
    return obj;
}

template<typename T>
inline Print& operator<<(Print& obj, const T& arg)
{
    obj.print(arg);
    return obj;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt)
{
    return opt.has_value() ? os << opt.value() : os << "NULL";
}

template<typename T>
Print& operator<<(Print& obj, const std::optional<T>& opt)
{
    return opt.has_value() ? obj << opt.value() : obj << "NULL";
}
