/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Source code for assignment 05 problem 3, div2Asm.
	      

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
char *myCstr = "Calling div2Asm function...";
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */
/* Private prototype ---------------------------------------------------------*/
void delay(uint32_t time);

extern int div2Asm(int val);

/*******************************************************************************
Function Name   : main
Description     : 
Parameters      :
Return value    :               */
void main() {
  uint8_t foo;
  int opResult = 0;
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
    
    opResult = div2Asm(foo);
    sprintf(szAux, "The result of %i / 2 is %i\n", foo, opResult);    
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
  