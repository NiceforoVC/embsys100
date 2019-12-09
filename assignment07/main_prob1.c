/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Source code for assignment 07 problem 1
	      

Copyright   : Niceforo Villanueva
            : 2019
            : All Rights Reserved
*******************************************************************************/
#include "stm32f401xe.h"
//#include "system_stm32f4xx.h"
#include "delay.h"

#define SYS_CLOCK_HZ 16000000u

// We need to enable the clock for the ports area we want to use

// RCC Base address: 0x40023800
// RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
// Address offset: 0x30
// Write: 0x01

// GPIOA Base Address: 0x40020000
// GPIO port mode register (GPIOx_MODER) (x = A..E and H)
// Address offset: 0x00
// Write: 0x0400

// GPIOA Base address: 0x40020000
// GPIO port output data register (GPIOx_ODR) (x = A..E and H)
// Address offset: 0x14
// Set Bit[5] to 1 -> 0x20 // Turn LED ON
// Set Bit[5] to 0 -> 0x00 // Turn LED OFF

void main()
{
  // Enable clock to peripheral
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  // Set output mode
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
  
  SysTick->LOAD = SYS_CLOCK_HZ - 1;     // Counts from 0
  SysTick->VAL = 0x00;                  // Clears initial value
  SysTick->CTRL = 0x07;                 // Enable interrupt
  
  // Turn LED ON and OFF
  while (1)
  {
    //delay(1000000);    
  }
}
