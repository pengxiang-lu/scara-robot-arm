#include "driver_config.h"
scara_struct scara;
extern uint8_t scara_uart_flag;
int main(void)
{
	delay_init();								// 延时初始化
	
	interface_init();							// 底层接口函数与结构体的绑定初始化
	
	interrupt_global_disable();					// 关闭所有中断
	 
	scara_init(&scara);							// 机械臂初始化，最大速度 50度/s,加速度 500度/s^2
	
	gpio_init();								// gpio初始化	
	
	computer_serial_init();						// 与上位机通信串口初始化
	
	lcd_serial_init();							// 与串口屏通信初始化
	
	snr9816_init();								// snr9816串口通信初始化
	
	PS2_Init();									// PS2手柄初始化
	
	interrupt_global_enable();					// 关闭所有中断
	
	delay_ms(2000);

	reset_coordinate(&scara,X_INIT, Y_INIT, Z_INIT);	// 开始校准

	snr9816tts_set_voice("[m1]");						// 设为男声
//	
//	snr9816tts_say_sentence("ring_1");

//	snr9816tts_say_sentence("龙虾机器人");

	while(1)
	{
		delay_ms(DRIVER_RESPONSE_CYCLE);
		
		driver_gpio_loop();						// GPIO主循环
		
		ps2_loop();								// ps2手柄循环
		
		scara_uart_loop();						// 串口接收响应循环
	}
}



