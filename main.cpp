#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "debug_prints.c"

#define BAUD0 115200
#define MYUBRR ((F_CPU / (8UL * BAUD0)) - 1)   // double-speed mode

#define ADC_CHANNEL0 0
#define ADC_VREF 5.0
#define ADC_QLEVELS 1024.0
#define TEMP_SENSOR_CHANNEL ADC_CHANNEL0

// Function prototypes
unsigned char ADC_Initialize(void);
unsigned int ADC_Read10bit(unsigned char channel); // 10-bit ADC read
float ADC_Convert(unsigned int ADC_value);
unsigned char VinToTemp(float Vin);
unsigned char read_temp_sensor(unsigned char ADC_channel);

int main(void)
{
	ADC_Initialize();
	DIDR0 = 0xFF;   // Disable digital input on ADC pins
	DDRD = 0xFF;    // Set PORTD as output (for binary display)

	UART0_init(MYUBRR);
	printSerialStrln(" LM35 Temperature Reading");

	unsigned char temperature;

	while (1)
	{
		printSerialStr("Temperature is: ");
		temperature = read_temp_sensor(TEMP_SENSOR_CHANNEL);
		printSerialInt(temperature);
		printSerialStrln(" °C");

		PORTD = temperature;   // Display binary value on LEDs
		_delay_ms(1000);
	}
}

//********************************************************************//

unsigned char ADC_Initialize(void)
{
	ADMUX = (1 << REFS0);                  // Vref=AVCC, right-adjust result
	ADCSRA = (1 << ADEN) |                  // Enable ADC
	(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler=128
	return 0;
}

// 10-bit ADC read: ADCL first, then ADCH
unsigned int ADC_Read10bit(unsigned char channel)
{
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // select channel
	_delay_us(10);                              // stabilize input

	ADCSRA |= (1 << ADSC);                      // start conversion
	while (ADCSRA & (1 << ADSC));               // wait for completion

	unsigned char low  = ADCL;                  // read ADCL first
	unsigned char high = ADCH;
	return ((unsigned int)high << 8) | low;    // 10-bit result
}

float ADC_Convert(unsigned int ADC_value)
{
	return (ADC_VREF * ADC_value) / ADC_QLEVELS;  // convert to voltage
}
 
unsigned char VinToTemp(float Vin)
{
	// LM35 output: 10mV per °C
	return (unsigned char)round(Vin / 0.01);
}

unsigned char read_temp_sensor(unsigned char ADC_channel)
{
	unsigned int adc_val = ADC_Read10bit(ADC_channel);
	float vin = ADC_Convert(adc_val);
	return VinToTemp(vin);
}
