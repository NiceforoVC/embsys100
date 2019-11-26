/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Source code for assignment 05 problem 5, swapPointersAsm.
	      

Copyright   : Niceforo Villanueva
            : 2019
            : All Rights Reserved
*******************************************************************************/

extern int swapPointersAsm(int** val1, int** val2);

void swap_pointers(int** x, int** y)
{
  int *temp = *x;
  
  *x = *y;
  *y = temp;
}

void swap_chars(char* x, char* y)
{
  char temp = *x;
  
  *x = *y;
  *y = temp;
}

void main(void)
{
  int x = 1;
  int y = 2;
  int *pX = &x;
  int *pY = &y;
  
  swapPointersAsm(&pX, &pY);
}








