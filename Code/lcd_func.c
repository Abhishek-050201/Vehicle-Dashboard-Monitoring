#include<LPC17xx.h>
#include"lcd_header.h"


void delay_lcd(uint32_t ms)
{
	uint32_t i,j;
	for(i = 0;i<ms;i++)
		for(j = 0;j<1000;j++);
}


//Write commands to LCD
void lcd_cmd(uint8_t cmd)
{
	//1.RS = 0;  Command Register -> P0.10
	P->FIOCLR |= RS;

	//2. RW = 0; already grounded

	//3. Clear data lines D0-D7 P0.15-P0.22 -> FIOCLR
	P->FIOCLR |= LCD;

	//4. Write command on the data lines : D0-D7 -> P0.15-P0.22 ->FIOSET  
	P->FIOSET |=  cmd << 15;

	//5. EN = 1; P0.11 -> 1 FIOSET
	P->FIOSET |= EN;

	//6. Delay(small)
	delay_lcd(10);

	//7. EN = 0; P0.11 ->0 FIOCLR
	P->FIOCLR |= EN;

	//8. delay(small)
	delay_lcd(10);
}


//Write data to LCD
void lcd_data(uint8_t data)
{
	//1.RS = 1;  Data Register -> P0.10
	P->FIOSET |= RS;

	//2. RW = 0; already grounded

	//3. Clear data lines D0-D7 P0.15-P0.22 -> FIOCLR
	P->FIOCLR |= LCD;

	//4. Write data on the data lines : D0-D7 -> P0.15-P0.22 ->FIOSET  
	P->FIOSET |=  data << 15;

	//5. EN = 1; P0.11 -> 1 FIOSET
	P->FIOSET |= EN;

	//6. Delay(small)
	delay_lcd(100);

	//7. EN = 0; P0.11 ->0 FIOCLR
	P->FIOCLR |= EN;

	//8. delay(small)
	delay_lcd(100);
}


void lcd_init()
{
	//Set directions of LCD ,RS, EN pins
	P->FIODIR |= (RS | EN | LCD);

	//Initialize the LCD
	//Mode of LCD
	lcd_cmd(0x38);	

	//Display and cursor
	lcd_cmd(0x0e);

	//clear screen
	lcd_cmd(0x01);

	//cursor at beginning of first row
	//lcd_cmd(0x80);	   //while clearing only it will set to first row so optional
}


void lcd_str(char *s)
{
	while(*s != '\0')
	{
		lcd_data(*s);
		s++	;
	}
}
