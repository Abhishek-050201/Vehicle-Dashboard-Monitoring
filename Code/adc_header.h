#include<LPC17xx.h>
#include<stdint.h>

#define ADC		LPC_ADC
#define ch0		(1<<1)
#define ch1		(1<<2)

void adc_init(void);
uint32_t adc0_conversion(void);
float adc1_conversion(void);
