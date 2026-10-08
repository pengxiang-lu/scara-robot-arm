#ifndef __DRIVER_GPIO_H_
#define __DRIVER_GPIO_H_
#include <stdint.h>
#define LED_PORT	GPIOC
#define LED_PIN		GPIO_Pin_13

#define BEEP_PORT	GPIOB
#define BEEP_PIN	GPIO_Pin_9

#define LED_ON		GPIO_ResetBits(LED_PORT,LED_PORT)
#define LED_OFF		GPIO_SetBits(LED_PORT,LED_PORT)

#define BEEP_ON		GPIO_SetBits(ENABLE_PORT,BEEP_PIN)
#define BEEP_OFF	GPIO_ResetBits(ENABLE_PORT,BEEP_PIN)
void gpio_init(void);
void key_scan(void);
void driver_gpio_loop(void);
#endif


