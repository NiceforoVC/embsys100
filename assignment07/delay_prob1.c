#include "delay.h"

void delay(int volatile iteration)
{
  while (iteration > 0)
  {
    iteration--;
  }
}