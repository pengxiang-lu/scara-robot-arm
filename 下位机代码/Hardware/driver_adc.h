#ifndef __DRIVER_ADC_H_
#define __DRIVER_ADC_H_
#include <stdint.h>
void current_sensor_adc_init(void);
void battery_adc_init(void);
uint16_t battery_read_adc_value(uint8_t n);
void inline_current_read_adc(void);
void inline_current_adc_init(void);
#endif


