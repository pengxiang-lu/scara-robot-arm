#include "driver_config.h"
#define func_abs(x)             ((x) >= 0 ? (x): -(x))

void motor_enable(uint8_t state)
{
	if(state == 0)
	{
		GPIO_SetBits(ENABLE_PORT,ENABLE_PIN);
	}
	else
	{
		GPIO_ResetBits(ENABLE_PORT,ENABLE_PIN);
	}
}
void FA_set_direction(uint8_t state)
{
	if(state == 0)
	{
		GPIO_SetBits(DIR_PORT,M1_DIR_PIN);
	}
	else
	{
		GPIO_ResetBits(DIR_PORT,M1_DIR_PIN);
	}
}
void SA_set_direction(uint8_t state)
{
	if(state == 0)
	{
		GPIO_SetBits(DIR_PORT,M2_DIR_PIN);
	}
	else
	{
		GPIO_ResetBits(DIR_PORT,M2_DIR_PIN);
	}
}
void Z_set_direction(uint8_t state)
{
	if(state == 0)
	{
		GPIO_SetBits(DIR_PORT,M3_DIR_PIN);
	}
	else
	{
		GPIO_ResetBits(DIR_PORT,M3_DIR_PIN);
	}
}

void FA_pwm_init(uint16_t arr, uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	GPIO_StructInit(&GPIO_InitStructure);					//将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;				//PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//复用推挽模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	TIM_DeInit(TIM2);										//把寄存器值设置为缺省值
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);			//将参数设置为缺省值
	TIM_TimeBaseStructure.TIM_Period = arr; 				//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 				//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 			//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;  		//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
	TIM_OCInitStructure.TIM_Pulse = arr/2;					//CH1 PWM脉宽值
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); 		//使能输出比较预装载寄存器
	
	//定时器2中断配置
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel						= TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ARRPreloadConfig(TIM2,ENABLE);						//使能自动重装载的预装载寄存器允许位
	TIM_Cmd(TIM2, DISABLE);
}
void SA_pwm_init(uint16_t arr, uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能TIM3时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);//使能GPIOB时钟和复用时钟

	GPIO_StructInit(&GPIO_InitStructure);				//将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//PB0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
                      
	TIM_DeInit(TIM3);	//把寄存器值设置为缺省值
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr; 					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 					//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能 PWM 输出到端口
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
	TIM_OCInitStructure.TIM_Pulse = arr/2; //CH3 PWM 的值
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//初始化 TIM3 OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器

	//定时器3中断配置
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd	= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能自动重装载的预装载寄存器允许位
	TIM_Cmd(TIM3,DISABLE);//失能定时器
	
}
void Z_pwm_init(uint16_t arr, uint16_t psc) 
{
    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能TIM4时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOB时钟和  X复用时钟 | RCC_APB2Periph_AFIO

	GPIO_StructInit(&GPIO_InitStructure);//将GPIO_InitStruct中的参数按缺省值输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_DeInit(TIM4);											//把寄存器值设置为缺省值
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr; 					//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 				//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;  			//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; 
	TIM_OCInitStructure.TIM_Pulse = arr/2;						//CCR3 的值
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);			//使能预装载寄存器

	//定时器2中断配置
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd	= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ARRPreloadConfig(TIM4,ENABLE);//使能自动重装载的预装载寄存器允许位
	TIM_Cmd(TIM4,DISABLE);//失能定时器
}

void set_speed_parama(stepping_motor_struct * motor_p,int offset)	//设置运动参数，第几轴，加速度，最大速度，位移量
{
	motor_p->pulse_target = offset;															// 得到需要的脉冲数量
	
	// x = (v_1^2-v_0^2) / 2a
	motor_p->pulse_accel = ((motor_p->speed_max_pulse * motor_p->speed_max_pulse - motor_p->speed_min_pulse_2) / motor_p->accel_pulse)>>1;	// 假设能加速到最大速度，加减速过程所需脉冲
	
	if(motor_p->pulse_target >= 0) 
	{
		motor_p->dir = 0;
		motor_p->motor_dir_set(motor_p->dir);
	}
	else 
	{
		motor_p->dir = 1;
		motor_p->motor_dir_set(motor_p->dir); 
		motor_p->pulse_target = -motor_p->pulse_target;
	}
	
	// 判断是否能够到达最大速度，如果可以进行梯形加减速，如果不行，进行三角形加减速
	(motor_p->pulse_target >= (motor_p->pulse_accel * 2)) ? 
	(motor_p->pulse_accel_constant = motor_p->pulse_target - motor_p->pulse_accel): 
	(motor_p->pulse_accel = motor_p->pulse_accel_constant = motor_p->pulse_target >> 1);	

	TIM_Cmd(motor_p->TIMx, DISABLE);		// 关闭电机
	// 设置初始速度
	motor_p->TIMx->ARR = motor_p->speed_arr_mul/motor_p->speed_min_pulse-1;
	motor_p->TIMx->PSC = 1-1;
	motor_p->TIMx->CCR1 = (motor_p->speed_arr_mul/motor_p->speed_min_pulse-1)>>1;

	motor_p->pulse_count = 0;				// 将脉冲计数变量清零
	motor_p->end_flag = false;				// 运行结束标志位置0
	motor_p->fre_flag = false;				// 寄存器更新标志位置0
}
// 调速函数
void motor_speed_set(stepping_motor_struct * motor_p)
{
	if(motor_p->pulse_count < motor_p->pulse_accel)					// 加速过程
	{
		// v^2 = 2ax + v0^2
		motor_p->speed_pulse = sqrt((motor_p->accel_pulse * motor_p->pulse_count << 1) + motor_p->speed_min_pulse_2);
		motor_p->arr = motor_p->speed_arr_mul / (motor_p->speed_pulse + 1);				// 计算寄存器的值
	}
	else if(motor_p->pulse_count >= motor_p->pulse_accel_constant)	// 减速过程
	{
		motor_p->speed_pulse = sqrt((motor_p->accel_pulse * (motor_p->pulse_target - motor_p->pulse_count) << 1) + motor_p->speed_min_pulse_2);
		motor_p->arr = motor_p->speed_arr_mul / (motor_p->speed_pulse + 1);				// 计算寄存器的值
	}
	
	motor_p->fre_flag = true;										// 完成一次计算，可以更新寄存器
}
// 电机回调函数
void motor_callback(stepping_motor_struct * motor_p)
{
	motor_p->pulse_count += 1;		//脉冲计数变量+1
	motor_p->angle_pulse += (motor_p->dir==1)?1:-1;
	if(motor_p->pulse_count >= motor_p->pulse_target)	//脉冲达到设定值，退出
	{
		TIM_Cmd(motor_p->TIMx,DISABLE); 	
		motor_p->end_flag = true;
		return;
	}
	if(motor_p->fre_flag)
	{
		motor_p->TIMx->ARR = motor_p->arr - 1;			//更新ARR重装载值寄存器
		motor_p->TIMx->CCR1 = motor_p->arr >> 1;		//更新CCRX值为ARR/2，即占空比为50%
		motor_p->fre_flag = false;						//清除更新标志位
	}
}
void motor_init(stepping_motor_struct*motor_p,float stepping_angle,uint16_t subdivision,float angle_init,float accel,float speed_max,float speed_min)
{
	motor_p->motor_pwm_init(1500-1,72-1);		// 随便给的参数，不需要在意
	motor_p->stepping_angle = stepping_angle;
	motor_p->subdivision = subdivision;
	motor_p->pause_deg_radio = ((float)subdivision)/stepping_angle;
	motor_p->angle = angle_init;
	motor_p->angle_pulse = motor_p->angle * motor_p->pause_deg_radio;
	motor_p->speed_arr_mul = (uint32_t)((float)TIM_CLOCK_FREQ/motor_p->pause_deg_radio);
	// 参数初始化，将参数单位从度转化为脉冲，度和脉冲的关系，脉冲 = 度/步进角*细分数
	motor_p->accel_pulse = accel*motor_p->pause_deg_radio;
	motor_p->speed_max_pulse = speed_max*motor_p->pause_deg_radio;
	motor_p->speed_min_pulse = speed_min*motor_p->pause_deg_radio;
	motor_p->speed_min_pulse_2 = motor_p->speed_min_pulse * motor_p->speed_min_pulse;
}
// 获取电机角度函数
float motor_get_angle(stepping_motor_struct*motor_p)
{
	return motor_p->angle_pulse / motor_p->pause_deg_radio;
}
// TIM2中断服务函数
void TIM2_IRQHandler(void)
{
    // 检查是否是更新中断触发
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
		motor_callback(&scara.FA);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

// TIM3中断服务函数
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        motor_callback(&scara.SA);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

// TIM4中断服务函数
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        motor_callback(&scara.Z);
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

