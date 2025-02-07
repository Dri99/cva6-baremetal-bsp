#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"
#include "clic.h"

//#define CSR_MCYCLE     (0xb00)

#define CSR_CNT_STATUS 0x7C3
#define CSR_CNT_DATA   0x7C4
#define CSR_CNT_DATA_H 0x7C5
#define CSR_LAST_SP    0x7C6
#define CSR_SHADOW_STATUS    0x7C7
#define CSR_SHADOW_REG 0x7C8
#define CSR_LOAD_ESF   0x7C9

#define my_set_csr(reg,var) set_csr(reg,var) 
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
void timer_irq(uint64_t* sp, uint64_t* last_sp){
  printf("Check shadow status: %lx\n", my_read_csr(CSR_SHADOW_STATUS));
  printf("Check save activations: %lx\n",read_csr(mhpmcounter6));
  printf("Check save conclusions: %lx\n",read_csr(mhpmcounter7));
  printf("Timer handler Called\n");
  printf("ra = %lx\n", sp[ 0]);
  printf("t0 = %lx\n", sp[ 1]);
  printf("t1 = %lx\n", sp[ 2]);
  printf("t2 = %lx\n", sp[ 3]);
  printf("a0 = %lx\n", sp[ 4]);
  printf("a1 = %lx\n", sp[ 5]);
  printf("a2 = %lx\n", sp[ 6]);
  printf("a3 = %lx\n", sp[ 7]);
  printf("a4 = %lx\n", sp[ 8]);
  printf("a5 = %lx\n", sp[ 9]);
  printf("a6 = %lx\n", sp[10]);
  printf("a7 = %lx\n", sp[11]);
  printf("t3 = %lx\n", sp[12]);
  printf("t4 = %lx\n", sp[13]);
  printf("t5 = %lx\n", sp[14]);
  printf("t6 = %lx\n", sp[15]);
  // my_write_csr(CSR_SHADOW_STATUS, 0x0000);
  // printf("shadow ra = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0100);
  // printf("shadow t0 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0200);
  // printf("shadow t1 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0300);
  // printf("shadow t2 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0400);
  // printf("shadow a0 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0500);
  // printf("shadow a1 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0600);
  // printf("shadow a2 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0700);
  // printf("shadow a3 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0800);
  // printf("shadow a4 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0900);
  // printf("shadow a5 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0a00);
  // printf("shadow a6 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0b00);
  // printf("shadow a7 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0c00);
  // printf("shadow t3 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0d00);
  // printf("shadow t4 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0e00);
  // printf("shadow t5 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  // my_write_csr(CSR_SHADOW_STATUS, 0x0f00);
  // printf("shadow t6 = %lx @mstatus=%lx\n", my_read_csr(CSR_SHADOW_REG), my_read_csr(CSR_SHADOW_STATUS));
  //my_write_csr(CSR_LOAD_ESF, (uint64_t)sp);
  
  printf("Actual sp = %lx\n",(uint64_t) sp);
  printf("Last sp = %lx\n", (uint64_t)last_sp);

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
	//clear_csr(mip, MIP_MTIP);


}
/*
This app, after the initial setup and some avoidable reading, checks that the 
__timer_irq_handler is correctly called, together with context stacking and unstacking

It does so by setting caller-saved registers to known values before waiting for the timer interrupt 
to be called in a known section of code (the infinite loop). The __timer_irq_handler sets end_loop
which allows advancing. Then, all previuosly set registers are checked against the expected value.

Note that this test works because there is only one interrupt, raised in a point where the core is in
a known state. In the general case interupts happen at any time.

The section at the beginning of the __asm__ inline part hacks the stack to be across two pages, to test 
the behavior of the shru (shadown register unit) and the cache.
*/
int main(void)
{
	//Sets bit 28 in CSR_SHADOW_STATUS = CSR_SHADOW_STATUS.en_reg_save
	my_set_csr(CSR_SHADOW_STATUS, (0x1ULL<28));
	printf("Test started\n");

	write_csr(mhpmevent3, 23);
	write_csr(mhpmevent4, 24);
	write_csr(mhpmevent5, 25);
	write_csr(mhpmevent6, 26);
	write_csr(mhpmevent7, 27);
	//set_csr(dcsr, (1u<<15));
	printf("Check mstatus before: %lx\n",read_csr(mstatus));
	set_csr(mstatus, MSTATUS_MIE);
	printf("Check mstatus: %lx\n",read_csr(mstatus));
	//mip, mie, mstatus
  //Setup timecmp and interrupts
  //write_csr(mtvec, __isr_wrapper);

	// uint64_t start_rtc = mtime, start = read_csr(mcycle);
	// for(volatile int i=0;i<1000000;i++);
	// start_rtc = mtime - start_rtc;
	// start = read_csr(mcycle) - start;
	// printf("Mcycle passed: %lu, mtime passed: %lu\n", start, start_rtc);

	printf("Last sp before int: %lx\n", my_read_csr(CSR_LAST_SP));
	printf("Check shadow status: %lx\n", my_read_csr(CSR_SHADOW_STATUS));
	
	mtimecmp = ~(0x0ULL);
	while(mtimecmp != ~(0x0ULL));
	//
	//uint64_t old_csr = clear_csr(mip, MIP_MTIP);
	set_csr(mie, MIP_MTIP);
	
	uint64_t now = mtime;
	mtimecmp = now + CLOCK_PER_USEC * 50;

	__asm__ goto (
					"addi t0,sp,-64\n"
					"srli t0,t0,12\n"
					"slli t0,t0,12\n"
					"addi t0,t0,64\n"
					"sub  t1,sp,t0\n"
					"mv sp,t0\n"
					"addi sp,sp,-8\n"
					"sd t1,(sp)\n"
					"li t0, 5\n"
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
					"ld t1,(sp)\n"
					"addi sp,sp,8\n"
					"add sp,sp,t1\n"
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

