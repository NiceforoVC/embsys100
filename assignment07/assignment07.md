# EMBSYS100 - AU19, Assignment 07

## Goal

The goals for the assignment this week:

1. Practice setting up a user-defined vector table.
2. Practice dealing with interrupts and the use of the SysTick timer.

## Problems

### 1. Starting from the blinking LED code that you created using the GPIO registers:

*a. Define your own vector table.*

```C
// Startup code for Nucleo F401RE

extern int CSTACK$$Limit;
extern void __iar_program_start(void);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

int const __vector_table[] @ ".intvec" = {
  (int)&CSTACK$$Limit,  //0x800' 0000
  (int)&__iar_program_start,
  (int)&NMI_Handler,
  (int)&HardFault_Handler,
  (int)&MemManage_Handler,
  (int)&BusFault_Handler,
  (int)&UsageFault_Handler,
  0,    // Reserved
  0,    // Reserved
  0,    // Reserved
  0,    // Reserved
  (int)&SVC_Handler,
  (int)&DebugMon_Handler,
  0,    // Reserved 
  (int)&PendSV_Handler,
  (int)&SysTick_Handler
};

void NMI_Handler(void)
{
  while (1)
  {
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
  // user code
}

void DebugMon_Handler(void)
{
  // user code
}

void PendSV_Handler(void)
{
  // user code
}

void SysTick_Handler(void)
{
  // user code
}
```

*b. Enable use of CMSIS in project options settings.*

![Image of project options](https://github.com/NiceforoVC/embsys100/blob/master/assignment07/CMSIS_options.png)

*c. Add the files **“stm32f401xe.h”** & **“system_stm32f4xx.h”** to the folder where “main.c” is saved. You should be able to get these files thru STM32CubeMX. You could also get them by downloading the zip file “CMSIS_STM32_Device_Specific_Files.zip” from canvas site under the link Assignment\A06 folder*

*d. Enable the use of the SysTick timer and its interrupt.*

The code in **main.c** was modified to enable the SysTick timer and its interrupt:

```c
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
```

*e. Replace the delay() function with the use of the SysTick timer to blink the user LED.*

The following line was added to the **SysTick** interrupt handler to toggle the LED:

```c
void SysTick_Handler(void)
{
  // user code
  GPIOA->ODR ^= GPIO_ODR_OD5;
}
```

*f. Set a break point inside the SysTick_Handler interrupt and capture a snapshot of the stack once inside the interrupt and LR value. Explain what are the values stored on the stack at the moment the Handler gets invoked.*

When an interrupt is triggered, the following happens:

• Stacking of a number of registers, including return address to the currently selected stack. This enables an exception handler to be written as a normal C function.

• Fetching the exception vector (starting address of the exception handler/ISR). This can happen in parallel to the stacking operation to reduce latency.

• Fetching the instructions for the exception handler to be executed. After the starting address of the exception handler is determined, the instructions can be fetched.

• Update of various NVIC registers and core registers. This includes the pending status and active status of the exception, and registers in the processor core including the Program Status Register (PSR), Link Register (LR), Program Counter (PC), and Stack Pointer (SP).

The PC is updated to the starting address of the exception handler and the Link Register (LR) is updated with a special value called EXC_RETURN. This value is 32-bit, and the upper 27 bits are set to 1. Some of the lower 5 bits are used to hold status information about the exception sequence (e.g., which stack was used for stacking). This value is to be used in the exception return.

![Image of cstack and LR snapshots](https://github.com/NiceforoVC/embsys100/blob/master/assignment07/CSTACK_LR.png)

### 2. Bonus: Improve your delay function to rely on the use of the SysTick timer instead of the busywait loop.

*a. Function prototype: void delay(uint32_t delayInMilliseconds)*

The new **delay** function is as follows:

```c
#include "delay.h"

extern uint32_t tickCounter;

void delay(uint32_t volatile delayInMilliseconds)
{
  tickCounter = 0;
  while (tickCounter < delayInMilliseconds);
}
```

The **SysTick** interrupt handler was modified to count ticks every millisecond.

```c
uint32_t tickCounter;

void SysTick_Handler(void)
{
  // user code  
  tickCounter++;
}
```

*b. Use the function in your main.c file to blink the LED every 2 seconds.*

The updated **main.c** file is as follows:

```c
void main()
{
  // Enable clock to peripheral
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  
  // Set output mode
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
  
  SysTick->LOAD = (SYS_CLOCK_HZ / 1000) - 1;    // Counts from 0
  SysTick->VAL = 0x00;                          // Clears initial value
  SysTick->CTRL = 0x07;                         // Enable interrupt
  
  // Turn LED ON and OFF
  while (1)
  {
    delay(2000);    
    GPIOA->ODR ^= GPIO_ODR_OD5;
  }
}

```

*c. **Hint:** Setup the SysTick timer to trigger an interrupt every 1ms.*

To accomplish this, the load value is the system clock divided by 1000.

```c
  SysTick->LOAD = (SYS_CLOCK_HZ / 1000) - 1;    // Counts from 0
```
