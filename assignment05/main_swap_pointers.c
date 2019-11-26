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








