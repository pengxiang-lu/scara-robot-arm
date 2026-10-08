#include "driver_config.h"
//本文件用于存放和指示灯以及开关有关的GPIO初始化操作
// 所有gpio初始化
void gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义GPIO初始化结构体
    
    // 1. 使能对应GPIO端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    
    // 2. 配置PB9、PB12、PB13、PB14、PB15（GPIOB端口）
    // 模式：推挽输出；速度：50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    // 推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 输出速度50MHz
    // 引脚：PB9、PB12、PB13、PB14、PB15（组合为一个引脚掩码）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_12 | 
                                 GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  // 初始化GPIOB
    
    // 3. 配置PC13（GPIOC端口）
    // 复用同一结构体，只需修改引脚参数（模式和速度不变）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  // 引脚：PC13
    GPIO_Init(GPIOC, &GPIO_InitStructure);      // 初始化GPIOC
    
    // 4. 初始电平设置（可选，此处设为低电平）
    GPIO_ResetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | 
                  GPIO_Pin_14 | GPIO_Pin_15);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void led_toggle()
{
	if(GPIO_ReadOutputDataBit(LED_PORT,LED_PIN)==0)
	{
		GPIO_SetBits(LED_PORT,LED_PIN);
	}
	else
	{
		GPIO_ResetBits(LED_PORT,LED_PIN);
	}
}
void driver_gpio_loop()
{
	static uint8_t gpio_loop_count=0;
//	static uint8_t high_freq_count = (100 / DRIVER_RESPONSE_CYCLE);
    static uint8_t mid_freq_count  = (500 / DRIVER_RESPONSE_CYCLE);
//	static uint8_t low_freq_count  = (1000 / DRIVER_RESPONSE_CYCLE);
	if(gpio_loop_count >= mid_freq_count)
	{
		led_toggle();
		gpio_loop_count = 0;
	}
	gpio_loop_count++;
}

	
