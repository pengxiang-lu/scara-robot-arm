#include "driver_config.h"
uint8_t rx_data = 0x00;
uint8_t rx_flag = 0;  	// 接收标志位
void snr9816_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能GPIOA和USART2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // 配置PA2为复用推挽输出（USART2 Tx）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置PA3为浮空输入（USART2 Rx）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART2
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
    // 使能接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    // 使能USART2
    USART_Cmd(USART2, ENABLE);
}
void snr9816_sendbyte(uint8_t byte)
{
	USART_SendData(USART2, byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形
	while (USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);	//等待发送完成
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}
void snr9816_printf(const char *format, ...) 
{
    va_list arg;           // 定义可变参数列表
    char buf[128];         // 缓冲区，用于存储格式化后的字符串（可根据需求调整大小）
    uint16_t len;          // 格式化后字符串的长度
    
    // 1. 解析可变参数，将格式化结果存入缓冲区
    va_start(arg, format);                  // 初始化可变参数列表
    len = vsnprintf(buf, sizeof(buf), format, arg);  // 格式化字符串到buf
    va_end(arg);                             // 结束可变参数列表
    
    // 2. 检查缓冲区是否溢出（可选）
    if (len >= sizeof(buf)) 
	{
        len = sizeof(buf) - 1;  // 防止越界，截断字符串
    }
    
    // 3. 通过USART3发送缓冲区内容
    for (uint16_t i = 0; i < len; i++) 
	{
        snr9816_sendbyte((uint8_t)buf[i]);  // 逐个字节发送
    }
}
// 获取芯片状态,返回1代表空闲
uint8_t snr9816tts_get_state()
{
	snr9816_sendbyte(0XFD);
	snr9816_sendbyte(0X00);
	snr9816_sendbyte(0X01);
	snr9816_sendbyte(0X21);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)		// 200ms没有收到东西
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == FREE_STATE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// 使用GB2132编码进行发送,内容可以是句子，也可以是、
// 铃声 ring_1 ring_2 ring_3 ring_4 ring_5 
// 信息提示音 message_1 message_2 message_3 message_4 message_5 
// 警示音 alert_1 alert_2 alert_3 alert_4 alert_5 
uint8_t snr9816tts_say_sentence(const char *sentence)
{
	// 等待空闲状态
	uint8_t len = strlen(sentence);
	uint8_t t_1 = 0;
	while(snr9816tts_get_state() == 0)
	{
		delay_ms(100);
		t_1++;
		if(t_1 >= 20)		// 2s过后
		{
			break;
		}
	}
	uint8_t dat_len=0;
	snr9816_sendbyte(0xFD);
	dat_len = len+2;
	snr9816_sendbyte(dat_len>>8);
	snr9816_sendbyte(dat_len);
	snr9816_sendbyte(0x01);
	snr9816_sendbyte(0x01);
	snr9816_printf((const char *)sentence);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == 0x41)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}
uint8_t snr9816tts_say_array(uint8_t *buf, uint8_t buf_len)
{
    if(buf == NULL || buf_len == 0) return 0; // 空数组直接返回失败

    // 等待空闲状态（复用原逻辑）
    uint8_t t_1 = 0;
    while(snr9816tts_get_state() == 0)
    {
        delay_ms(100);
        t_1++;
        if(t_1 >= 20) break;
    }

    // 发送指令（替换strlen，直接用传入的长度）
    uint8_t dat_len = buf_len + 2;
    snr9816_sendbyte(0xFD);
    snr9816_sendbyte(dat_len>>8);
    snr9816_sendbyte(dat_len);
    snr9816_sendbyte(0x01);
    snr9816_sendbyte(0x01);

    // 发送uint8_t数组内容（逐字节发送，替代原snr9816_printf）
    for(uint8_t i=0; i<buf_len; i++) {
        snr9816_sendbyte(buf[i]);
    }

    // 等待响应（复用原逻辑）
    uint8_t t = 0;
    while(rx_flag == 0)
    {
        delay_ms(1);
        t++;
        if(t>=200) break;
    }
    rx_flag = 0;

    return (rx_data == 0x41) ? 1 : 0;
}
// 暂停合成
uint8_t snr9816tts_stop()
{
	snr9816_sendbyte(0XFD);
	snr9816_sendbyte(0X00);
	snr9816_sendbyte(0X01);
	snr9816_sendbyte(0X03);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == 0x41)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// 继续合成
uint8_t snr9816tts_continue()
{
	snr9816_sendbyte(0XFD);
	snr9816_sendbyte(0X00);
	snr9816_sendbyte(0X01);
	snr9816_sendbyte(0X04);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == 0x41)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// 停止合成
uint8_t snr9816tts_end()
{
	snr9816_sendbyte(0XFD);
	snr9816_sendbyte(0X00);
	snr9816_sendbyte(0X01);
	snr9816_sendbyte(0X02);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == 0x41)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//发音人：[m0]为女声，[m1]为男声，默认为[m0]女声 
//音量：[v0]-[v9]，音量由小到大，默认为中间值 
//语速：[s0]-[s9]，语速由快到慢，默认为中间值正常语速 
//语调：[t0]-[t9]，语调由低到高，默认为中间值正常语调 
uint8_t snr9816tts_set_voice(const char * str)
{
	snr9816_sendbyte(0XFD);
	snr9816_sendbyte(0X00);
	snr9816_sendbyte(0X06);
	snr9816_sendbyte(0X01);
	snr9816_sendbyte(0X01);
	snr9816_printf((const char *)str);
	uint8_t t = 0;
	while(rx_flag == 0)
	{
		delay_ms(1);
		t++;
		if(t>=200)
		{
			break;
		}
	}		//等待接收标志位置1
	rx_flag = 0;
	if(rx_data == 0x41)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




void USART2_IRQHandler(void)
{   
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{	
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		rx_data = USART_ReceiveData(USART2);
		rx_flag = 1;
		//printf("rx_flag = %d ",rx_flag);
	}
}


