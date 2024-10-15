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
#ifndef LEDTASK  //Same purpose as #pragma once
#define LEDTASK

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

// Derived class for LED control
class LedTask : public Task
{
    private:
        gpio_num_t ledPin;      // GPIO pin where the LED is connected.
        TickType_t delayMs;     // Delay time for LED blinking in milliseconds.
        uint32_t current_level; // Current level of the LED (on/off).

    public:
        // Constructor initializes the task with name, stack size, priority, pin number, and blink delay.
        LedTask(const char* name, uint32_t stack, UBaseType_t prio, gpio_num_t pin, TickType_t delay) 
            : Task(name, stack, prio), ledPin(pin), delayMs(delay) 
            {
                printf("LED task create %s \n",name);  // Print task creation message.
                current_level = 0;                     // Initialize LED level to off.
            }

        // Override the task function to define LED blinking behavior
        void taskFunction() override
        {
            gpio_reset_pin(ledPin);   // Reset the GPIO pin to a known state.

            gpio_set_direction(ledPin, GPIO_MODE_OUTPUT);  // Set the GPIO pin as output for the LED.
            
            printf("GPIO has been set %d \n",(int)ledPin);  // Confirm that the GPIO pin has been configured.

            for (;;)
            {
                // Toggle the LED between on and off states (pseudo-code)
                toggleLed(ledPin);
            }
        }

        // Simple LED toggle function (pseudo-code)
        void toggleLed(gpio_num_t pin)
        {
            current_level ^=1; // 0 ^1 =1, 1  ^1 = 0  XOR operation to toggle between 0 and 1.
            printf("GPIO: %d , current_level %ld \n",(int)ledPin, current_level);  // Print current LED state.
            gpio_set_level(pin, current_level);  // Set the GPIO pin to the new level (on or off).
            vTaskDelay(delayMs / portTICK_PERIOD_MS);  // Delay for the specified blink period.
        }
};

#endif

/*
La clase LedTask hereda de Task y controla el parpadeo de un LED conectado a un pin GPIO específico. 
En el ciclo de la tarea, el LED cambia entre encendido y apagado, y el intervalo de parpadeo está determinado por el valor delayMs. 
La función toggleLed se encarga de alternar el estado del LED y de introducir el retardo correspondiente.
*/