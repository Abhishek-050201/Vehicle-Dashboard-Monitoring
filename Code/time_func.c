#include"timer_header.h"


void timer0_init(void)
{

//Power up timer0
 	LPC_SC->PCONP |= TIM0_PWR;

	//clock set to 1MHz
	LPC_SC->PCLKSEL0 &= ~TIM0_CLK;	



	//timer part
	T0->PR = 999;

	//1sec delay = 1 * 10^6   	Count = delay/PCLK = 1s/(1*10^-6)
	//count= (PR+1)(MR)
	//therefore MR = count/(PR+1)= (1*10^6)/1= 1*10^6

}
void delay(uint32_t k)
{
	T0->MR0 = k*1000 ;	

	//Interrupt and repeat
	T0->MCR |= 0x03;	

	//Tc and Pc as 0;
	T0->TCR = 1<<1; 
	
	//Start timer0 count
	T0->TCR = 1<<0;	

		//Wait for 1 sec 
	while((T0->IR & (1<<0)) == 0);
	T0->IR = 1;

}

void delay_ms(uint32_t k)
{
	T0->MR0 = k ;	

	//Interrupt and repeat
	T0->MCR |= 0x03;	

	//Tc and Pc as 0;
	T0->TCR = 1<<1; 
	
	//Start timer0 count
	T0->TCR = 1<<0;	

		//Wait for 1 sec 
	while((T0->IR & (1<<0)) == 0);
	T0->IR = 1;

}
