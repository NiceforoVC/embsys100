/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Sample program to use dev board LD2 to display Morse code

Author      : Niceforo Villanueva
            : 2019
*******************************************************************************/

#define RCC_BASE                0x40023800
#define RCC_AHB1ENR             *((unsigned int*)(RCC_BASE + 0x30))
#define GPIOA_BASE              0x40020000
#define GPIOA_MODER             *((unsigned int*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR               *((unsigned int*)(GPIOA_BASE + 0x14))

#define UNIT                    100
#define DOT_DURATION            1
#define DASH_DURATION           3
#define SPACE_BETWEEN_PARTS     1
#define SPACE_BETWEEN_LETTERS   3
#define SPACE_BETWEEN_WORDS     7

/*******************************************************************************
Function Name	: Delay
Description	: Loops a requested number of cycles to cause a time delay
Parameters	: nLoops - Integer with number of loops to run
Return value	: None
Author          : Niceforo Villanueva  */
void Delay(int nLoops)
{
  volatile int localCounter = nLoops * 1000;
  while(localCounter)
  {
    localCounter--;
  }
}

/*******************************************************************************
Function Name	: DelayUnits
Description	: Delays the requested number of units
Parameters	: nUnits - Integer with number of units to wait
Return value	: None
Author          : Niceforo Villanueva  */
void DelayUnits(int nUnits)
{
  Delay(nUnits*UNIT);
}

/*******************************************************************************
Function Name	: LED_On
Description	: Turns ON LD2 for the duration defined by the parameter
Parameters	: None
Return value	: None
Author          : Niceforo Villanueva  */
void LED_On(int duration)
{
  GPIOA_ODR |= 0x20;
  DelayUnits(duration);
  GPIOA_ODR &= ~0x20;
}

/*******************************************************************************
Function Name	: WriteLetterCode
Description	: Uses LD2 to write the letter Morse Code indicated by the 
                  parameter 
Parameters	: szLetterCode - Morse code representing a letter
Return value	: None
Author          : Niceforo Villanueva  */
void WriteLetterCode(char *szLetterCode)
{
  char *pAux = szLetterCode;
  
  while (*pAux)
  {
    switch (*pAux)
    {
      case '.':
        LED_On(DOT_DURATION);
        break;
      case '-':
        LED_On(DASH_DURATION);
        break;
    }    
    pAux++;
    if (*pAux)
      DelayUnits(SPACE_BETWEEN_PARTS);
  }
}

/*******************************************************************************
Function Name	: WriteMorseCode
Description	: Converts the passing string to International Morse Code and 
                  uses LD2 to display the code
Parameters	: szString - String to convert
Return value	: None
Author          : Niceforo Villanueva  */
void WriteMorseCode(char *szString)
{
  char *pAux = szString;
  
  while (*pAux)
  {
    switch (*pAux)
    {
      case 'N':
        WriteLetterCode("-.");
        break;
      case 'I':
        WriteLetterCode("..");
        break;
      case 'C':
        WriteLetterCode("-.-.");
        break;
      case 'E':
        WriteLetterCode(".");
        break;
      case 'F':
        WriteLetterCode("..-.");
        break;
      case 'O':
        WriteLetterCode("---");      
        break;
      case 'R':
        WriteLetterCode(".-.");
        break;
    }    
    pAux++;
    if (*pAux)
      DelayUnits(SPACE_BETWEEN_LETTERS);
  }
}

int main()
{
  // Enable clock to peripheral
  RCC_AHB1ENR = 0x01;
  
  // Set output mode
  GPIOA_MODER |= 0x400;
    
  // Write 'NICEFORO' in Morse Code
  while (1)
  {
    WriteMorseCode("NICEFORO");
    DelayUnits(SPACE_BETWEEN_WORDS);
  }
  
  return 0;
}