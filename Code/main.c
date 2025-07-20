#include<LPC17xx.h>
#include<stdint.h>
#include<stdio.h>
#include"lcd_header.h"
#include"spi_header.h"
#include"adc_header.h"
#include"pwm_header.h"
#include"timer_header.h"

#define BUZZ	(1<<2)
  

int main()
{
	uint32_t speed;
	float temp;	
	int beep;
	char tempr[20];
	char speed1[20];
	

	LPC_GPIO1->FIODIR |= (0x7D << 19) | BUZZ;
	LPC_GPIO1->FIOCLR |= (0x7D << 19) | BUZZ;

	adc_init();
	spi_init();
	lcd_init();
	pwm_init();
	timer0_init();

	while(1)
	{
		lcd_cmd(0x01); //clear lcd screen

		//Acts as accelerator
		speed = adc0_conversion();

		//Pass the speed to the wheel 
		beep = pwm_power(speed);

		temp = adc1_conversion();

		sprintf(tempr,"Eng Temp: %3.1f",temp);

		lcd_str(tempr);

		temp_on_7seg(temp);

		lcd_cmd(0xC0);
		sprintf(speed1,"Speed = %dKmph",beep);
		lcd_str(speed1);
		delay(3);
		

		if((beep > 80) && (beep < 120))
		{
			LPC_GPIO1->FIOSET |= BUZZ;
			delay_ms(100);	//delay of 100 milli second
	   		LPC_GPIO1->FIOCLR |= BUZZ;
		}
		else if(beep >= 120)
		{
			LPC_GPIO1->FIOSET |= BUZZ;
			delay_ms(1000);	//delay of 1 second
	   		LPC_GPIO1->FIOCLR |= BUZZ;
		}
		else
		{
			LPC_GPIO1->FIOCLR |= BUZZ;
		}
		delay(3);
		lcd_cmd(0x01);
	}
}
