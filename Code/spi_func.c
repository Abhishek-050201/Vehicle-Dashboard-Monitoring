#include"spi_header.h" 

uint8_t num(int num)
{
	switch(num)
	{
	 	case 1:
				return 0x30;
		
		case 2:
				return 0x6D;

		case 3:
				return 0x79;

		case 4:
				return 0x33;

		case 5:
				return 0x5B;

		case 6:
				return 0x5F;

		case 7:
				return 0x70;

		case 8:
				return 0x7F;

		case 9:
				return 0x73;

		case 0:
				return 0x7E;
	}

 return 0;
}

void spi_init(void)
{
	LPC_SC->PCONP |= (1<<10);

	LPC_SC->PCLKSEL0 &= ~(0x03 <<20);	//select pclk = cclk/4  //resets ssp port


	//Only MOSI and SCLK enough cause we r sending data
	LPC_PINCON->PINSEL0 |= (1<<15);	//P0.7 as SCK1,
	LPC_PINCON->PINSEL0 &= ~(1<<14);

  	LPC_PINCON->PINSEL0 |= (1<<17);	//P0.9 as MISO,
	LPC_PINCON->PINSEL0 &= ~(1<<16);

 	LPC_PINCON->PINSEL0 |= (1<<19);	//P0.9 as MOSI,
	LPC_PINCON->PINSEL0 &= ~(1<<18);

	//u can use ssel pin as gpio pin 
	LPC_GPIO0->FIODIR |= (1<<6);	//P0.6 as GPIO output pin



	LPC_SSP1->CR0 |= 0x0B;	  	//12 bit data transfer

	//MODE 0 operation
	LPC_SSP1->CR0 &= ~(0x01 << 6);	  //CPOL = 0
	LPC_SSP1->CR0 &= ~(0x01 << 7);	  //CPHA = 0

	LPC_SSP1->CR0 &= ~(0xFF << 8);    //Set scr = 0


	LPC_SSP1->CR1 &= ~(1<<0);	   //Normal operation

	LPC_SSP1->CR1 &= ~(1<<2);		//Master mode


	LPC_SSP1->CPSR = 10;		  //ssp speed or baud rate = pclk/((cpsr)*(scr+1)) -> 1MHz/(10)*(0+1) = 100KHz

	LPC_SSP1->CR1 |= (1<<1);		//enable ssp	   //should be done after configuing everything

}

void spi1_data_write(uint16_t data)
{
	 //Enable slave(connect to slave)
	LPC_GPIO0->FIOCLR |= (1<<6);


	while((LPC_SSP1->SR & (1<<1)) == 0);	  //wait for tx buffer to get loaded with data

	 LPC_SSP1->DR = data;	//load to data to fifo

	while((LPC_SSP1->SR & (1<<4)) != 0);	//wait if bus is busy

	

	  //DIsable slave(DIsconnect slave)
	LPC_GPIO0->FIOSET |= (1<<6);
}

void temp_on_7seg(float temp)
{
	int dec_part,int_part,units,tens,deci,unit,ten;
	spi1_data_write(0x0900); // Decode mode for digits 0-3
	spi1_data_write(0x0A0F); // Max intensity
	spi1_data_write(0x0B03); // Scan digits 0 to 3
	spi1_data_write(0x0C01); // Shutdown=0, Normal Operation

	
	int_part = (int)temp;
	units = (int_part %10);
	tens = (int_part/10);
	ten = num(tens);

	dec_part = (int)((temp - int_part)*10);
	deci = num(dec_part);
	unit = num(units | 0x80);

	

	// Display digits
	spi1_data_write(0x0100 | ten);               // Digit 4: Tens
	spi1_data_write(0x0200 | unit);     // Digit 3: Units + Decimal Point
	spi1_data_write(0x0300 | deci);               // Digit 2: Decimal part
	
	spi1_data_write(0x0900);                      // Disable decode mode (for char)
	spi1_data_write(0x0400 | 0x4E);               // Digit 1: 'C'

	//check this
	spi1_data_write(0x0C01);		//shutdown mode
}
