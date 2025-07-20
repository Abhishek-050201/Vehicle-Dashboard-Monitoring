#include<lpc17xx.h>
#include<stdint.h>

#define T0	LPC_TIM0
#define TIM0_PWR	(1<<1)
#define TIM0_CLK	(0x03<<2)

void timer0_init(void);
void delay(uint32_t k);
void delay_ms(uint32_t k);
