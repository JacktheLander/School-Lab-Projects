#include <stdio.h>
#include <stdlib.h>

main(uint8_t integer, uint8_t decimal){
  int16_t i = integer;
  int8_t d = decimal >> 7;
  int16_t bits = (i << 8) + d;

  decimal = (int8_t)(bits & 0x00FF);
  i = bits>>8;
  integer = (int8_t)(i & 0x00FF);

  printf("integer bits = %d, decimal bits = %d", integer, decimal);
  return integer, decimal;
}
  
