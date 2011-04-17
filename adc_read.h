#ifndef ADC_READ_H
#define ADC_READ_H

#define NUMADC 27
void Adc_Init();
unsigned int Adc_Read(int ch);
float Adc_IR(int ch);

#endif
