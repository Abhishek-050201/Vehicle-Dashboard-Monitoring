#include "adc_header.h"

// ADC0 (P0.24 ? AD0.1) for Potentiometer
// ADC1 (P0.25 ? AD1.1) for Temperature Sensor

void adc_init(void)
{
	// Power up ADC peripheral
	LPC_SC->PCONP |= (1 << 12);   // PCADC

	// Configure P0.24 as AD0.1
	LPC_PINCON->PINSEL1 &= ~(0x03 << 16);  // Clear bits 17:16
	LPC_PINCON->PINSEL1 |=  (0x01 << 16);  // Set bit 16 = 1 (function 01)

	// Configure P0.25 as AD1.1
	LPC_PINCON->PINSEL1 &= ~(0x03 << 18);  // Clear bits 19:18
	LPC_PINCON->PINSEL1 |=  (0x01 << 18);  // Set bit 18 = 1 (function 01)

	// Common ADC configuration: CLKDIV = 10, PDN = 1 (Power up)
	ADC->ADCR = (10 << 8) | (1 << 21);  // Don't select any channel here
}

uint32_t adc0_conversion(void)
{
	uint32_t value;

	// Select only AD0.1 (channel 1)
	ADC->ADCR &= ~(0xFF);       // Clear SEL bits (bits 7:0)
	ADC->ADCR |= (1 << 1);      // Select channel 1

	// Start conversion now
	ADC->ADCR &= ~(7 << 24);    // Clear START bits
	ADC->ADCR |= (1 << 24);     // Start conversion (START = 001)

	// Wait for DONE bit in ADDR1
	while (!(ADC->ADDR1 & (1U << 31)));

	// Extract 12-bit result
	value = (ADC->ADDR1 >> 4) & 0xFFF;

	// Stop conversion
	ADC->ADCR &= ~(7 << 24);    // Clear START bits

	return value;
}

float adc1_conversion(void)
{
	uint32_t val;
	float voltage, temp;

	// Select only AD1.1 (channel 2)
	ADC->ADCR &= ~(0xFF);       // Clear SEL bits
	ADC->ADCR |= (1 << 2);      // Select channel 2

	// Start conversion now
	ADC->ADCR &= ~(7 << 24);    // Clear START bits
	ADC->ADCR |= (1 << 24);     // START = 001

	// Wait for DONE bit in ADDR2
	while (!(ADC->ADDR2 & (1U << 31)));

	// Extract 12-bit result
	val = (ADC->ADDR2 >> 4) & 0xFFF;

	// Stop conversion
	ADC->ADCR &= ~(7 << 24);    // Clear START bits

	// Convert to voltage and temperature (assuming LM35: 10mV/°C)
	voltage = ((float)val * 3.3f) / 4095.0f;
	temp = voltage / 0.01f;

	return temp;
}
