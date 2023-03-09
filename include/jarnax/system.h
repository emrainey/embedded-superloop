#include <cstdint>
#include "cortex_m4.h"
#include "stm32.h"

extern void * __bss_start;
extern void * __bss_end;

namespace system {
void entry(void);
void initialize(void);
void configure(void);
void main(void);
}
