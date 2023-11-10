#include <stdio.h>
#include <stdlib.h>

main(uint8_t integer, uint8_t decimal){
  int16_t i = integer;
  int16_t bits = (i << 8) + decimal;
  
