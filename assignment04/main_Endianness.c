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






