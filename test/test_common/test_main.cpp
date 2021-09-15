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

#include "test_container.h"
#include "test_memory.h"

#include <unity.h>

void setUp(void) {
// set stuff up here
}

void tearDown(void) {
// clean stuff up here
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(test_container_vector);
    
    RUN_TEST(test_memory_raw_ptr);
    RUN_TEST(test_memory_unique_ptr);
    RUN_TEST(test_memory_shared_ptr);
    RUN_TEST(test_memory_make_unique);
    UNITY_END();
}


#ifdef ARDUINO

#include <Arduino.h>

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    process();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv)
{
    process();
    return 0;
}

#endif
