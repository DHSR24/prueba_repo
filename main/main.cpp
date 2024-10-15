/*
 * Copyright (c) 2024 Tonix22
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
#include "taskWrapper.h"
#include "ledtask.h"
#include "freertos/FreeRTOS.h"
#include "delaytask.h"

using namespace std;


// Main function
extern "C" void app_main()
{
    // Create LED task instances. Each one controls a different LED with unique blinking intervals.
    LedTask ledTask1("LED Task 1", 4096, 3, GPIO_NUM_25, pdMS_TO_TICKS(2000)); // Task 1 blinks LED on GPIO 25 every 2 seconds.
    ledTask1.start();  // Star task 1 

    LedTask ledTask2("LED Task 2", 4096, 4, GPIO_NUM_26, pdMS_TO_TICKS(3000)); // Task 1 blinks LED on GPIO 26 every 3 seconds.
    ledTask2.start();  // Star task 2

    LedTask ledTask3("LED Task 3", 4096, 5, GPIO_NUM_27, pdMS_TO_TICKS(4000)); // Task 1 blinks LED on GPIO 25 every 4 seconds.
    ledTask3.start();  // Star task 3

    //DelayClass delay;
    // DelayTask instance manages periodic delays.
    DelayTask delay(1000);  // Delay task with a delay period of 1000ms (1 second).
    delay.start();  // Start the delay task

      // Infinite loop to keep the tasks alive.
      while (1) {
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay the loop to prevent blocking tasks (100ms delay).
        //delay.InMs(100);
    }
  
}
