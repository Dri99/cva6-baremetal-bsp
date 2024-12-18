#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"
  
int stack[1000];

int main(int argc, char* arg[]) {
	printf("Initial cycles:%lu\n",read_csr(mcycle));
	printf("Initial instr:%lu\n",read_csr(minstret));
	printf("%d: Hello World !", 0);
	
	for(int i=0; i<1000;i++){
		stack[i] = 0xaaaa;
	}
	
	printf("Final cycles:%lu\n",read_csr(mcycle));
	printf("Final instr:%lu\n",read_csr(minstret));
}
