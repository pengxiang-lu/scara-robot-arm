#include "stm32f10x.h"                  // Device header
void interrupt_global_disable(void)
{
	__asm("CPSID I");
}
void interrupt_global_enable(void)
{
	__asm("CPSIE I");
}

