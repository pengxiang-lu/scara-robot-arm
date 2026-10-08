#include "driver_config.h"
// 电磁铁初始化，PWM频率1kHz
void electromagnet_init(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				// 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Prescaler = 71;         				// 预分频器：71
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// 向上计数
    TIM_TimeBaseStructure.TIM_Period = 999;           				// 自动重装载值：999
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     	// 不分频
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  				// 高级定时器重复计数（不使用）
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  				// PWM1模式：CNT < CCR时输出高
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// 使能输出
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;// 禁用互补输出
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		// 输出极性：高有效
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    
    TIM_OCInitStructure.TIM_Pulse = 0; 								// 初始占空比计算
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);                 		// 应用到通道1
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);        		// 使能通道1预装载
    
    TIM_OCInitStructure.TIM_Pulse = 0; 								// 初始占空比计算
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);                 		// 应用到通道4
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);         		// 使能通道4预装载

    TIM_ARRPreloadConfig(TIM1, ENABLE);             				// 使能自动重装载预装载
    TIM_Cmd(TIM1, ENABLE);                          				// 启动定时器
    TIM_CtrlPWMOutputs(TIM1, ENABLE);               				// 高级定时器需使能主输出
}

void airpump_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);  // 使能GPIOA和TIM1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  		// 使能复用功能时钟（如需重映射时使用）

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  			// 复用推挽输出（PWM输出必须配置为复用功能）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 1999;  					// ARR值：周期 = (72000000)/(720*(1999+1)) = 50Hz
    TIM_TimeBaseStructure.TIM_Prescaler = 719;  				// PSC值：分频后时钟 = 72MHz/(719+1) = 100KHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  	// 时钟分频因子
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  			// 高级定时器重复计数（此处不用）
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  				// PWM模式1：CNT < CCR时输出有效电平
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	// 使能输出
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;// 禁用互补输出（无反向通道）
    TIM_OCInitStructure.TIM_Pulse = 50;  							// 初始脉宽：0.5ms（舵机中位，150*10us=1500us）
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  		// 有效电平为高电平
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;  	// 互补通道极性（无用）
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;  	// 空闲状态（无用）
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;  // 互补通道空闲状态（无用）
    TIM_OC1Init(TIM1, &TIM_OCInitStructure); 			 			// 配置通道1

    TIM_OCInitStructure.TIM_Pulse = 50;  							// 初始脉宽0.5ms
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  						// 配置通道4

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  	// 使能通道1预装载
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  	// 使能通道4预装载
    TIM_ARRPreloadConfig(TIM1, ENABLE);  				// 使能自动重装载预装载
    TIM_Cmd(TIM1, ENABLE);  							// 启动定时器
}
void tool_init(void)
{
	#if TOOL == ELECTROMAGNET
	electromagnet_init();
	#elif TOOL == AIRPUMP
	airpump_init();
	#endif
}
void tool_pick_object(void)
{
	#if TOOL == ELECTROMAGNET
	if(ELECTROMAGNET_DIR == 1)
	{	
		TIM_SetCompare1(TIM1, ELECTROMAGNET_DUTY); TIM_SetCompare4(TIM1, 0); 
	}
	else
	{
		TIM_SetCompare4(TIM1, ELECTROMAGNET_DUTY); TIM_SetCompare1(TIM1, 0); 
	}
	#elif TOOL == AIRPUMP
	TIM_SetCompare1(TIM1, 250);TIM_SetCompare4(TIM1, 50);delay_ms(800);TIM_SetCompare1(TIM1, 50);
	#endif
}

void tool_put_object(void)
{
	#if TOOL == ELECTROMAGNET
	TIM_SetCompare1(TIM1, 0); TIM_SetCompare4(TIM1, 0); 
	#elif TOOL == AIRPUMP
	TIM_SetCompare1(TIM1, 50);TIM_SetCompare4(TIM1, 250);delay_ms(800);TIM_SetCompare4(TIM1, 50);
	#endif

}
	
