#include "driver_config.h"


void lcd_serial_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 1. 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  // USART3时钟（APB1，36MHz）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  // GPIO和复用时钟
    
    // 2. 配置GPIO引脚
    // PB10: USART3_TX（复用推挽输出）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // PB11: USART3_RX（浮空输入）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // 浮空输入（推荐）
    // 如需上拉输入，可改为：GPIO_Mode_IPU
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 3. 配置USART3参数（波特率115200）
    USART_InitStructure.USART_BaudRate = 115200;               // 固定波特率115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8位数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      // 1位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         // 无校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 收发模式
    USART_Init(USART3, &USART_InitStructure);

	// 使能接收中断（RXNE：接收数据寄存器非空）
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	// 配置NVIC中断优先级（抢占0，子优先级0）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 分组2（2位抢占，2位响应）
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  // 抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         // 子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
   
    // 5. 使能USART3
    USART_Cmd(USART3, ENABLE);
}
void lcd_sendbyte(uint8_t byte)
{
	USART_SendData(USART3, byte);		//将字节数据写入数据寄存器，写入后USART自动生成时序波形
	while (USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);	//等待发送完成
	/*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}
void USART3_IRQHandler(void) 
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{

        USART_ClearITPendingBit(USART3, USART_IT_RXNE); // 清除中断标志
    }
}

