/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

#include "test_memory.h"

// AVR does not implement many STL libraries, use
// #include <ArduinoSTL.h> to check if the class is available
#if defined (__AVR__) || (__avr__)
#undef CXXSTL
#else
#define CXXSTL 1
#endif

#include <memory>

#include <unity.h>

void test_memory_raw_ptr(void)
{
    auto* a = new int(1);
    auto* b = new int(2);
    TEST_ASSERT_EQUAL(2, *b);
    delete b;
    delete a;
}

void test_memory_auto_ptr(void)
{
    auto a = std::auto_ptr<int>(new int(1));
    auto b = std::auto_ptr<int>(new int(2));
    a = b;
    TEST_ASSERT_EQUAL(2, *a);
}

void test_memory_unique_ptr(void)
{
#if CXXSTL && __cplusplus >= 201103L
    auto a = std::unique_ptr<int>(new int(1));
    auto b = std::unique_ptr<int>(new int(2));
    a = std::move(b);
    TEST_ASSERT_EQUAL(2, *a);
    TEST_ASSERT_GREATER_OR_EQUAL(201103L, __cplusplus);
#endif
}

void test_memory_shared_ptr(void)
{
#if CXXSTL && __cplusplus >= 201103L
    auto a = std::shared_ptr<int>(new int(1));
    auto b = std::shared_ptr<int>(new int(2));
    a = std::move(b);
    TEST_ASSERT_EQUAL(2, *a);
    TEST_ASSERT_GREATER_OR_EQUAL(201103L, __cplusplus);
#endif
}

void test_memory_make_unique(void)
{
#if CXXSTL &&  __cplusplus >= 201403L
    auto a = std::make_unique<int>(1);
    auto b = std::make_unique<int>(2);
    a = std::move(b);
    TEST_ASSERT_EQUAL(2, *a);
    TEST_ASSERT_GREATER_OR_EQUAL(201403L, __cplusplus);
#endif
}