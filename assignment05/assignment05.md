# EMBSYS100 - AU19, Assignment 05

## Goal

The goals for the assignment this week:

1. To gain in depth understanding of the pass-by-value nature of C.
2. To gain hands on experience with the ARM Cortex-M4 assembly language.

## Problems

### 1. Create a function that allows swapping of two pointers.

```c
/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Source code for assignment 05 problem 1, swap_pointers.
	      

Copyright   : Niceforo Villanueva
            : 2019
            : All Rights Reserved
*******************************************************************************/
void swap_pointers(int** x, int** y)
{
  int *temp = *x;
  
  *x = *y;
  *y = temp;
}

void main(void)
{
  int x = 1;
  int y = 2;
  int *pX = &x;
  int *pY = &y;
  
  swap_pointers(&pX, &pY);
}
```

*a. Explain what the “main” function does to the CSTACK in order setup the input arguments prior to calling the swap_pointer() function?*

It decremented the SP and stored the values of the parameters in the stack (in this case the parameters were the addresses of the variables in main).

*b. And what are the values in R0 & R1 when swap_pointer() is called?*

R0 and R1 contain the addresses where the values of the variables are stored. 

![Image of Entering Swap](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/SwapPointers_entering.png)

*c. Share a screen shot of the local variables inside of “main” after the function swap_pointer() returns, showing the values of the pointers and what they are pointing to.*

![Image of Returning Swap](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/SwapPointers_returning.png)

### 2. Run sqrAsm code from the class demo:

*a. Copy **HelloWorld** from Assignment 1.*

*b. Download the file **sqrAsm.s** and copy it to the project directory.*

*c. In IAR, add sqrAsm.s file to your project. Now you should be able to see the file from the Workspace Window.*

*d. Modify main.c to call sqrAsm function.*

```c
/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Source code for assignment 05 problem 2, sqrAsm.
	      

Copyright   : Niceforo Villanueva
            : 2019
			: All Rights Reserved
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nucleoboard.h"
#include "hw_init.h"
#include "print.h"

char clr_scrn[] = { 27, 91, 50, 74, 0 };              // esc[2J
/* Public variables ----------------------------------------------------------*/
__IO uint32_t timer;
char *myCstr = "Calling assembly function...";
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/
void delay(uint32_t time);

extern int sqrAsm(int val);

/*******************************************************************************
Function Name   : main
Description     : 
Parameters      :
Return value    :               */
void main() {
  uint8_t foo;
  int squaredResult = 0;
  char szAux[100];

  foo = 10;
  Hw_init();

  PrintString(clr_scrn); /* Clear entire screen */
  // Change [My name] to your name      //
  PrintString("Niceforo's Nucleo STM32F401 is ... alive!!!\n");
  RETAILMSG(1, ("Programming Assignment #5: Built %s %s.\r\n\r\n",
              __DATE__,
              __TIME__));  

  
  PrintString("EMBSYS CP100A: University of Washington - Calling assembly code\n\n");
  while (foo) {
    GPIO_ToggleBits(GPIO_PORT_LD2, GPIO_PIN_LD2);    
    
    squaredResult = sqrAsm(foo);
    sprintf(szAux, "The square of %i is %i\n", foo, squaredResult);    
    PrintString(szAux);
    
    delay(1000);
    GPIO_ToggleBits(GPIO_PORT_LD2, GPIO_PIN_LD2);
    
    delay(1000);
    foo--;
  }
  while (1) {
    // loop forever
    asm("nop");
  }
}

void delay(uint32_t time) {
  
  timer = time;
  while(timer) {}
}

void SystemInit(void) {
  // System init is called from the assembly .s file
  // We will configure the clocks in hw_init
  asm("nop");
}  
```

*e. Run your program on the board, and capture a snapshot image of the output from TeraTerm.*

Screen output of **sqrAsm** execution:

![Image of sqrAsm](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/sqrAsm.png)

### 3. Create a new file div2Asm.s and add the file to the same HelloWorld project above.

*a. Write the assembly code to take an input argument, divide it by 2, and return the result.*

*b. Invoke the function “PrintString” from within divAsm before doing the division computation.*

*c. Add a comment for every statement in your assembly function code.*

*d. In the main.c, invoke div2Asm(foo) and capture the screen output from TeraTerm.*

Assembly code of **div2Asm**:

```asm
/*******************************************************************************
Function Name   : div2Asm
Description     : Calls C code to print a string; 
                  divides the input argument by 2
C Prototype     : int div2Asm(val)
                : Where val is the value to calculate it's square
Parameters      : R0: Address of val
Return value    : R0
*******************************************************************************/  
  
div2Asm
    PUSH {R0,LR}        // save the input argument and return address
    LDR R0,=myCstr      // load (global) address of address of string into R0
    LDR R0,[R0]         // load address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0,LR}         // Restore R0 and LR
    MOV R1, R0          // R1 = R0
    ASR R0, R1,#1       // R0 = R1 >> 1 (divide by 2 using shift right)
    BX LR               // return (with function result in R0)
    END
```

Screen output of **div2Asm** execution:

![Image of div2Asm](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/div2Asm.png)

### 4. Implement a swap function in assembly and call it “swapCharsAsm”:

*a. It takes as input two variables of char data type and swaps the two chars.*

*b. Add a comment for every statement in your assembly function code.*

*c. **Bonus:** Returns 0 if the two chars are identical; otherwise, return 1.*

Assembly code of **swapCharsAsm**:

```asm
/*******************************************************************************
Function Name   : swapCharsAsm
Description     : Calls C code to print a string; 
                  swaps the 2 input arguments
C Prototype     : int swapCharsAsm(val1, val2)
                : Where val1 and val2 are chars that will be swapped by the function
Parameters      : R0: Address of val1
                : R1: Address of val2
Return value    : R0: 1 -> chars are different, 0 -> chars are equal
*******************************************************************************/  
  
swapCharsAsm
    PUSH {R0,R1,LR}     // save the input arguments and return address
    LDR R0,=myCstr      // load (global) address of address of string into R0
    LDR R0,[R0]         // load address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0,R1,LR}      // Restore R0, R1 and LR
    LDRB R2,[R0]        // Load R2 with contents of address at R0
    LDRB R3,[R1]        // Load R3 with contents of address at R1
    STRB R3,[R0]        // Store R3 in address at R0 
    STRB R2,[R1]        // Store R2 in address at R1 
    CMP R2,R3           // Compare values of R0 & R1
    MOV R0,#0           // Return 0 if chars are equal (Default)
    BEQ equal           // If equal, branch to equal label
    MOV R0,#1           // Return 1 if chars are different
equal    
    BX LR               // return (with function result in R0)
    END
```

Screen output of **swapCharsAsm** execution:

![Image of swapChars](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/SwapChars.png)

### 5. Bonus: Implement the swap_pointer() function from #1 above in assembly and call it swapPointersAsm().

*a. Add a comment for every statement in your assembly function code.*

*b. Take a snapshot of the output after invoking the swapPointerAsm() subroutine.*

Assembly code of **swapPointersAsm**:

```asm
/*******************************************************************************
Function Name   : swapPointersAsm
Description     : swaps the 2 input arguments
C Prototype     : int swapPointersAsm(val1, val2)
                : Where val1 and val2 are pointers that will be swapped by the function
Parameters      : R0: Address of val1
                : R1: Address of val2
Return value    : R0
*******************************************************************************/  
  
swapPointersAsm
    LDR R2,[R0]        // Load R2 with contents of address at R0
    LDR R3,[R1]        // Load R3 with contents of address at R1
    STR R3,[R0]        // Store R3 in address at R0 
    STR R2,[R1]        // Store R2 in address at R1 
    BX LR              // return
    END
```

Snapshot of **swapPointersAsm**:

![Image of SwapPointersAsm](https://github.com/NiceforoVC/embsys100/blob/master/assignment05/SwapPointersAsm.png)