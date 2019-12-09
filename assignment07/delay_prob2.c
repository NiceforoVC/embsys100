#include "delay.h"

extern uint32_t tickCounter;

void delay(uint32_t volatile delayInMilliseconds)
{
  tickCounter = 0;
  while (tickCounter < delayInMilliseconds);
}