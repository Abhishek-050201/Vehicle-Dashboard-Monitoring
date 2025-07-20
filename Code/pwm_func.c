#include"pwm_header.h"

void pwm_init(void)
{
	//Enable power for PWM1
	 	LPC_SC->PCONP |= (1<<6);
		
		//1MHz for PWM1	Reset PWM1 pins	
		LPC_SC->PCLKSEL0 &= ~(0x03 << 12);	
		
		//Configure P1.20 pin as PWM1.2 using PINSEL0 (alternate function)
		LPC_PINCON->PINSEL3	|= (1<<9);
		LPC_PINCON->PINSEL3 &= ~(1<<8);
	
		//Timer part
	
	  	PWM1->PCR |= (1<<10);	//Enable PWM1.2 Module 
		PWM1->PCR &= ~(1<<2);	//Enable PWM1.2 in single edge mode
	
		PWM1->PR = 0;
	
		PWM1->TCR = (1<<3);	  //Enable PWM Operation
	
	
		PWM1->MCR |= (1<<1) | (1<<0);	  //Repeat on match  for MR0 and MR7
		PWM1->MR0 = 4095;	//Load MR0 as time period  i.e 10ms
		PWM1->LER |= (1<<0);	  //Latch enable for MR0  and MR2

		PWM1->TCR |= (1<<0);	  //start pwm timer COunter

		PWM1->MR2 = 0;   //Load MR2 as Duty Cycle 	//20% of full	
		PWM1->LER |= (1<<2) ;	  //Latch enable for MR0  and MR2

}

uint32_t pwm_conversion(uint32_t val)
{
 	uint32_t num;

	num =  (float)(val/ 20.475);

	return num;
}

int pwm_power(uint32_t speed)
{
	int num = 0;

	if(speed >  SPEED_LOCK)
	{
	 	speed = 3000;
	}

	num = pwm_conversion(speed);


	PWM1->MR2 = speed;   //Load MR2 as Duty Cycle 	//20% of full	
	PWM1->LER |= (1<<2) ;	  //Latch enable for MR0  and MR2

	return num;
}
