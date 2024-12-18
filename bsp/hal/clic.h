#include<stdint.h>

#define CLINTBase    0x02000000

#define MTIME_REG	    (CLINTBase + 0xbff8U)
#define MTIMECMP_REG    (CLINTBase + 0x4000U)

//volatile uint64_t *mtime_addr = MTIME_REG;

#define CLOCK_PER_SEC   25000000
#define CLOCK_PER_MSEC  25000
#define CLOCK_PER_USEC  25

#define mtime      *((volatile uint64_t*)MTIME_REG)
#define mtimecmp   *((volatile uint64_t*)MTIMECMP_REG)