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

#pragma once  //With this this file it's only included once in the simulation

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
// Base class for all tasks
class Task
{
protected:
    const char* taskName;     // Name of the task.
    uint32_t stackSize;       // Stack size allocated for the task.
    UBaseType_t priority;     // Task priority.
    TaskHandle_t taskHandle;  // Handle to reference the task in FreeRTOS.

public:
    // Task it's going to be heredated to other files
    Task(const char* name, uint32_t stack, UBaseType_t prio) // Names of the instances of the task (name, stack, prio)
        : taskName(name), stackSize(stack), priority(prio), taskHandle(nullptr) {};

    //Class destructor (currently empty, but useful for cleanup if needed in derived classes)
    virtual ~Task() {}

    // Virtual function to define the task's behavior
    virtual void taskFunction() = 0;

    // Function to start the task
    void start()
    {
        printf("Before start\n");
        //Me -> taskFunction acccesing the pointer of an abstrac function
        // xTaskCreate creates a new task. Here it uses a lambda to call the taskFunction of the derived class.
        xTaskCreate([](void* obj) {static_cast<Task*>(obj)->taskFunction();}, taskName, stackSize, this, priority, &taskHandle);
        printf("After start\n");
    }

    // Stop the task
    void stop()
    {
        if (taskHandle != nullptr)
        {
            vTaskDelete(taskHandle);  // Deletes the task from FreeRTOS.
            taskHandle = nullptr;     // Resets the task handle to null.
        }
    }
};

/*
Esta clase Task es la base para todas las tareas que se crean en el proyecto.
Define cómo iniciar y detener las tareas. Cualquier clase que herede de Task debe implementar la función taskFunction,
que es donde se define el comportamiento específico de la tarea.
*/