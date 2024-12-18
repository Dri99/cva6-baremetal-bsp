#include <stdio.h>
void __attribute__((weak)) timer_irq(){
    printf("Not used\n");
    return;
} 