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

#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

// DelayTask is a derived class that introduces a delay in its task function.
class DelayTask : public Task     // Heredates Task from the taskWrapper.h file
{
    private:
    int delay_ms;  // Delay period on miliseconds

    public:
    // Constructor to initialize the delay task with a specific time.
    DelayTask(int time) : Task ("DelayTask",4096,4), delay_ms(time) {}

// Implementation of the task function that runs the delay task.
void taskFunction() override
{
    for(;;)
    {
        vTaskDelay(delay_ms);  // Waits for the specified delay period.
        printf("Delay task running \n");  //// Prints a message to indicate that the delay task is running.
    }
}
 
};

/*
Esta clase hereda de Task y define una tarea específica que introduce un retardo cíclico usando vTaskDelay. 
El constructor permite definir el tiempo de retardo, y la tarea imprimirá un mensaje cada vez que se ejecute después del retardo.
*/