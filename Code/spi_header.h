#include<LPC17xx.h>
#include<stdint.h>

#define SPI1 	LPC_SSP1

void spi_init(void);
void spi1_data_write(uint16_t data);
void temp_on_7seg(float temp);
uint8_t num(int num);
