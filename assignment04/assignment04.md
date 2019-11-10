# EMBSYS100 - AU19, Assignment 04

## Goal

The goals for the assignment this week:
1. Practice the use of bit-banding region.
2. Examine the assembly code generated for a function with multiple parameters.
3. Go thru a design problem exercising key concepts we viewed so far (pointers, arrays, functions,
design, API, testing…etc.)
4. Bonus: Apply usage of pointers and the understanding of Endianness.

## Problems

### 1. Using bit-band region for peripherals:

***a. Convert the Blinking Led demo to use the corresponding bit-band address instead of the register address used in the peripheral region.***

Code written in **main_LED_bit_banding.c**:

```c
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*((unsigned int*)(RCC_BASE + 0x30)))

#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (*((unsigned int*)(GPIOA_BASE + 0x00)))
#define GPIOA_ODR (*((unsigned int*)(GPIOA_BASE + 0x14)))

#define GPIOA (1<<5)

volatile int counter=0;

void main(void)
{
    
    // RCC Base Address: 0x40023800
    // RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
    // Address offset: 0x30
    // Set bit[0] to 1
    // 1. Enable clock to Peripheral
    // RCC_AHB1ENR |= 0x1;
    *((unsigned int*)(0x42000000 + (0x23830*32) + (0*4))) = 0x1;
  
    // GPIOA Base Address: 0x40020000
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // Address offset: 0x00
    // Set bit[10] to 0x01  so --> 0x400 // To enable Port5 as output
    // GPIOA_MODER |= 0x400;
    *((unsigned int*)(0x42000000 + (0x20000*32) + (10*4))) = 0x1;

    // GPIOA Base Address: 0x40020000
    // GPIO port output data register (GPIOx_ODR) (x = A..E and H)
    // Address offset: 0x14
    // Set bit[5] to 1 --> 0x20; // Turn LED ON
    // Set bit[5] to 0 --> 0x00; // Turn LED OFF
     
    while(1)
    {
    counter=0;

    while (counter < 1000000)
    {
      counter++;
    }
    // GPIOA_ODR |= GPIOA;
    *((unsigned int*)(0x42000000 + (0x20014*32) + (5*4))) = 0x1;
        
    counter=0;
    while (counter < 1000000)
    {
      counter++;
    }
    // GPIOA_ODR &= ~GPIOA;
    *((unsigned int*)(0x42000000 + (0x20014*32) + (5*4))) = 0x0;
    }
}
```

***b. What instructions does the compiler produce in assembly for the “writing” to the GPIO bit when using bit-band address?***

![Image of using bit banding](https://github.com/NiceforoVC/embsys100/blob/master/assignment04/Using_bit_banding.png)

***c. What were the instructions produced when writing to the GPIOx_ODR bit[5] directly?***

![Image of not using bit banding](https://github.com/NiceforoVC/embsys100/blob/master/assignment04/Not_using_bit_banding.png)

### 2. Create a function with multiple arguments (5 arguments for example) and call that function from within another function. Trace thru the assembler and note:

***a. How does the "calling" function pass the values to the "called" function?***

It passes the values through the stack.

***b. What extra code did the compiler generate before calling the function with the multiple arguments?***

![Image of extra code for stack](https://github.com/NiceforoVC/embsys100/blob/master/assignment04/Extra_code_for_stack.png)

***c. What extra code did the compiler generate inside the "called" function with the multiple list of arguments?***

![Image of extra code for function](https://github.com/NiceforoVC/embsys100/blob/master/assignment04/Extra_code_for_function.png)

***d. Any other observations?***

The extra code inside the "called" function also stores in the stack the return address and the values of the working registers. They are retrieved from the stack when the function returns to the "calling" function.

### 3. Following the queue data structure approach, design, implement and test a stack data structure:

***a. The following is the list of requirements:***

i. The stack should have a predefined size
ii. The stack supports “int” data types.
iii. Provide a function to initialize the stack internals.
iv. Provide a function to push an element onto the stack
v. Provide a function to pop an element off the stack.
vi. Provide a function that returns 1 if stack is empty.
vii. Provide a function that returns 1 if stack is full.

*See stack.h and stack.c in repo*

***b. Provide a list of the test cases and their implementation inside of main.c***

*See main_stack.c in repo*

***c. Separate the stack code from the rest of the test code (create stack.h & stack.c)***

*See stack.h and stack.c in repo*

### 4. Bonus: Using the power of pointers and type casting, create a function that can determine if a computer is big-endian or little-endian. Test your function in the simulator and modify the Project Options (as shown in the figure below) against:

![Image of main options](https://github.com/NiceforoVC/embsys100/blob/master/assignment04/Main_options.png)

Code written in **main_Endianness.c**:
```c
#include <assert.h>

unsigned int global = 0x01234567;

int checkEndianness(void);

int main()
{
  int result;
  
  result = checkEndianness();
  
  assert(1 == result); // Fail if little endian
  assert(2 == result); // Fail if big endian
  
  return 0;
}

int checkEndianness()
{
  int endianness = 0;

  // Get first byte
  unsigned char first = *((unsigned char*)(&global));
  
  // Big endian (MSB first)
  if (first == 0x01)
    endianness = 1;
  // Little endian (LSB first)
  if (first == 0x67)
    endianness = 2;
  
  return endianness;
}
```

***a. Device STM32F401RE***

Result: Little Endian

***b. Cortex M4 (Little endian option)***

Result: Little Endian

***c. Cortex M4 (Big Endian option)***

Result: Big Endian