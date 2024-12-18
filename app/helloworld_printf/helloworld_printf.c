#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

#define CSR_MCYCLE     (0xb00)

#define CSR_CNT_STATUS 0x7C3
#define CSR_CNT_DATA   0x7C4
#define CSR_CNT_DATA_H 0x7C5

#define my_read_csr(reg) read_csr(reg) 
#define my_write_csr(reg,var) write_csr(reg,var)

//#define read_csr
typedef union{
  struct{
    uint16_t enable;
    uint16_t select;
  }fields;
  uint32_t bits;
}status_t;


int main(void)
{
  uint64_t start = my_read_csr(CSR_MCYCLE);
  printf("hello World!\n"); 

  uint64_t end = my_read_csr(CSR_MCYCLE);
  uint64_t end_cyc0 = my_read_csr(CSR_CNT_DATA);

  printf("MCycle=%ld\nCyc0=%ld\n", end - start, end_cyc0 - start);
  status_t status = {.fields = {.enable = 1, .select=0}}; 
  my_write_csr(CSR_CNT_STATUS, status.bits);

  //From now we count 
  //wait end of uart frame
  volatile int c, d;  
  for (c = 1; c <= 32767; c++)
    for (d = 1; d <= 32767; d++)
      {}
  
  status.fields.enable = 0;
  status.fields.select = 1;
  my_write_csr(CSR_CNT_STATUS, status.bits);

  uint64_t end_cyc1 = my_read_csr(CSR_CNT_DATA);
  printf("Cyc1:%ld\n", end_cyc1);

  for (c = 1; c <= 32767; c++)
    for (d = 1; d <= 32767; d++)
      {}
  return(0);
}

