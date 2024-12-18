#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"
#include "clic.h"

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

int end_loop = 0;

//Overwrites weak definition
void timer_irq(){
  printf("Timer handler Called\n");
  end_loop = 1;
	__asm__ volatile (
					"li a0,  0xaaaaaa\n"
					"li a1,  0xaaaaaa\n"
					"li a2,  0xaaaaaa\n"
					"li a3,  0xaaaaaa\n"
					"li a4,  0xaaaaaa\n"
					"li a5,  0xaaaaaa\n"
					"li a6,  0xaaaaaa\n"
					"li a7,  0xaaaaaa\n"
					// "li s2,  0xaaaaaa\n"
					// "li s3,  0xaaaaaa\n"
					// "li s4,  0xaaaaaa\n"
					// "li s5,  0xaaaaaa\n"
					// "li s6,  0xaaaaaa\n"
					// "li s7,  0xaaaaaa\n"
					// "li s8,  0xaaaaaa\n"
					// "li s9,  0xaaaaaa\n"
					// "li s10, 0xaaaaaa\n"
					// "li s11, 0xaaaaaa\n"
					// "li t3,  0xaaaaaa\n"
					// "li t4,  0xaaaaaa\n"
					// "li t5,  0xaaaaaa\n"
				: 
				: 		
				: "a0","a1","a2","a3","a4","a5","a6","a7");	
	//Disable successive irqs
	mtimecmp = 0xffffffffffffffff;
	clear_csr(mip, MIP_MTIP);


}

int main(void)
{
  
	printf("Test started\n");

	write_csr(mhpmevent3, 23);
	write_csr(mhpmevent4, 24);
	write_csr(mhpmevent5, 25);
	write_csr(mhpmevent6, 26);
	write_csr(mhpmevent7, 27);
	//set_csr(dcsr, (1u<<15));
	printf("Check mstatus before: %x\n",read_csr(mstatus));
	set_csr(mstatus, MSTATUS_MIE);
	printf("Check mstatus: %x\n",read_csr(mstatus));
	//mip, mie, mstatus
  //Setup timecmp and interrupts
  //write_csr(mtvec, __isr_wrapper);

	uint64_t now = mtime;
	mtimecmp = now + CLOCK_PER_MSEC * 2;
	
	uint64_t old_csr = clear_csr(mip, MIP_MTIP);
	set_csr(mie, MIP_MTIP);
	
	__asm__ goto ("li t0, 5\n"
					"li t1,  6\n"
					"li t2,  7\n"
					"li a0,  10\n"
					"li a1,  11\n"
					"li a2,  12\n"
					"li a3,  13\n"
					"li a4,  14\n"
					"li a5,  15\n"
					"li a6,  16\n"
					"li a7,  17\n"
					"li s2,  18\n"
					"li s3,  19\n"
					"li s4,  20\n"
					"li s5,  21\n"
					"li s6,  22\n"
					"li s7,  23\n"
					"li s8,  24\n"
					"li s9,  25\n"
					"li s10, 26\n"
					"li s11, 27\n"
					"li t3,  28\n"
					"li t4,  29\n"
					"li t5,  30\n"
					"infinite_loop : lw t6, 0(%[end_loop])\n"
					"beqz t6, infinite_loop\n"
					"li t6,  5\n"
					"bne t0,  t6, %l[fail]\n"
					"li t6,  6\n"
					"bne t1,  t6, %l[fail]\n"
					"li t6,  7\n"
					"bne t2,  t6, %l[fail]\n"
					"li t6,  10\n"
					"bne a0,  t6, %l[fail]\n"
					"li t6,  11\n"
					"bne a1,  t6, %l[fail]\n"
					"li t6,  12\n"
					"bne a2,  t6, %l[fail]\n"
					"li t6,  13\n"
					"bne a3,  t6, %l[fail]\n"
					"li t6,  14\n"
					"bne a4,  t6, %l[fail]\n"
					"li t6,  15\n"
					"bne a5,  t6, %l[fail]\n"
					"li t6,  16\n"
					"bne a6,  t6, %l[fail]\n"
					"li t6,  17\n"
					"bne a7,  t6, %l[fail]\n"
					"li t6,  18\n"
					"bne s2,  t6, %l[fail]\n"
					"li t6,  19\n"
					"bne s3,  t6, %l[fail]\n"
					"li t6,  20\n"
					"bne s4,  t6, %l[fail]\n"
					"li t6,  21\n"
					"bne s5,  t6, %l[fail]\n"
					"li t6,  22\n"
					"bne s6,  t6, %l[fail]\n"
					"li t6,  23\n"
					"bne s7,  t6, %l[fail]\n"
					"li t6,  24\n"
					"bne s8,  t6, %l[fail]\n"
					"li t6,  25\n"
					"bne s9,  t6, %l[fail]\n"
					"li t6, 26\n"
					"bne s10, t6, %l[fail]\n"
					"li t6, 27\n"
					"bne s11, t6, %l[fail]\n"
					"li t6,  28\n"
					"bne t3,  t6, %l[fail]\n"
					"li t6,  29\n"
					"bne t4,  t6, %l[fail]\n"
					"li t6,  30\n"
					"bne t5,  t6, %l[fail]\n"
					"j %l[pass]"
				: 
				: [end_loop] "r" (&end_loop)		
				: "t0","t1","t2","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6"
				: fail, pass); //"memory" probably unneeded			
		
fail:
	printf("Error encountered\n");
  return(1);
pass:
	printf("Main successfully ended\n");
  return(0);
}

