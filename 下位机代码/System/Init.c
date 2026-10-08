#include "Device/Include/stm32f10x.h"   // Device header
#include "sys.h"
//****GPIOx  如下
//	GPIOA GPIOB
//****GPIO_Pin  如下
//	GPIO_Pin_0~15
//****GPIO_Mode 如下
//  GPIO_Mode_AIN               模拟输入
//  GPIO_Mode_IN_FLOATING       浮空输入
//  GPIO_Mode_IPD 				上拉输入
//  GPIO_Mode_IPU 				下拉输入
//  GPIO_Mode_Out_OD 			开漏输出
//  GPIO_Mode_Out_PP 			推挽输出
//  GPIO_Mode_AF_OD 			复用开漏
//  GPIO_Mode_AF_PP 			复用推挽
void MyGPIO_Init(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode)//GPIO初始化函数
{	u32 RCC_APB2Periph;
	if(GPIOx==GPIOA)
	{RCC_APB2Periph=RCC_APB2Periph_GPIOA;}
	if(GPIOx==GPIOB)
	{RCC_APB2Periph=RCC_APB2Periph_GPIOB;}
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&GPIO_InitStructure);
}
//****IRQn  					中断通道
//****PreemptionPriority        抢占优先级
//****SubPriority               响应优先级
void MyNVIC_Init(IRQn_Type IRQn,u8 PreemptionPriority,u8 SubPriority)//NVIC初始化函数
{
      NVIC_InitTypeDef NVIC_InitStructure;
	  NVIC_InitStructure.NVIC_IRQChannel= IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority=SubPriority;
	  NVIC_Init(&NVIC_InitStructure);
}
//****GPIOx  如下
//	GPIOA GPIOB
//****GPIO_Pin  如下
//	GPIO_Pin_0~15
//****GPIO_Mode 如下
//  GPIO_Mode_IN_FLOATING       浮空输入
//  GPIO_Mode_IPD 				上拉输入
//  GPIO_Mode_IPU 				下拉输入
//****EXYI_Trigger  如下
//EXTI_Trigger_Rising           上升沿触发
//EXTI_Trigger_Falling			下降沿触发
//EXTI_Trigger_Rising_Falling   上升下降沿均触发
//****PreemptionPriority        抢占优先级
//****SubPriority               响应优先级
void MyEXTI_Interrupt_Init(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,
EXTITrigger_TypeDef EXTI_Trigger,u8 PreemptionPriority,u8 SubPriority)
{ 	  u8 GPIO_PortSource; u8 GPIO_PinSource;u32 EXTI_Line;IRQn_Type IRQn;
	  MyGPIO_Init(GPIOx,GPIO_Pin,GPIO_Mode);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	  if(GPIOx==GPIOA)
	  {GPIO_PortSource=GPIO_PortSourceGPIOA;}
	  if(GPIOx==GPIOB)
	  {GPIO_PortSource=GPIO_PortSourceGPIOB;}
	  GPIO_PinSource=(uint8_t)log_2(GPIO_Pin);
	  EXTI_Line=(uint32_t)GPIO_Pin;
	  GPIO_EXTILineConfig(GPIO_PortSource,GPIO_PinSource);
	  EXTI_InitTypeDef EXTI_InitSructure;
	  EXTI_InitSructure.EXTI_Line=EXTI_Line;
	  EXTI_InitSructure.EXTI_LineCmd=ENABLE;
	  EXTI_InitSructure.EXTI_Mode=EXTI_Mode_Interrupt;
	  EXTI_InitSructure.EXTI_Trigger=EXTI_Trigger;
	  EXTI_Init(&EXTI_InitSructure);
	  if(EXTI_Line==EXTI_Line0)IRQn=EXTI0_IRQn;
	  if(EXTI_Line==EXTI_Line1)IRQn=EXTI1_IRQn;
	  if(EXTI_Line==EXTI_Line2)IRQn=EXTI2_IRQn;
	  if(EXTI_Line==EXTI_Line3)IRQn=EXTI3_IRQn;
	  if(EXTI_Line==EXTI_Line4)IRQn=EXTI4_IRQn;
	  if(EXTI_Line==EXTI_Line5)IRQn=EXTI9_5_IRQn ;
	  if(EXTI_Line==EXTI_Line6)IRQn=EXTI9_5_IRQn;
	  if(EXTI_Line==EXTI_Line7)IRQn=EXTI9_5_IRQn;
	  if(EXTI_Line==EXTI_Line8)IRQn=EXTI9_5_IRQn;
	  if(EXTI_Line==EXTI_Line9)IRQn=EXTI9_5_IRQn;
	  if(EXTI_Line==EXTI_Line10)IRQn=EXTI15_10_IRQn;
	  if(EXTI_Line==EXTI_Line11)IRQn=EXTI15_10_IRQn;
	  if(EXTI_Line==EXTI_Line12)IRQn=EXTI15_10_IRQn;
	  if(EXTI_Line==EXTI_Line13)IRQn=EXTI15_10_IRQn;
	  if(EXTI_Line==EXTI_Line14)IRQn=EXTI15_10_IRQn;
	  if(EXTI_Line==EXTI_Line15)IRQn=EXTI15_10_IRQn;
	  MyNVIC_Init(IRQn,PreemptionPriority,SubPriority);
}
void MyEXTIEncoder_Init(GPIO_TypeDef* GPIOx1,u16 GPIO_Pin1,u8 PreemptionPriority1,u8 SubPriority1,
GPIO_TypeDef* GPIOx2,u16 GPIO_Pin2,u8 PreemptionPriority2,u8 SubPriority2)
{   MyEXTI_Interrupt_Init(GPIOx1,GPIO_Pin1,GPIO_Mode_IPU,EXTI_Trigger_Falling,PreemptionPriority1,SubPriority1);
	MyEXTI_Interrupt_Init(GPIOx2,GPIO_Pin2,GPIO_Mode_IPU,EXTI_Trigger_Falling,PreemptionPriority2,SubPriority2);

}
	
//****TIMx 						TIM2~4
//****ARR 			    		自动重装值
//****PSC						预分频系数
//****PreemptionPriority        抢占优先级
//****SubPriority               响应优先级
//****CCR						比较值
//公式:占空比=CCR/ARR 分辨率=1/ARR 中断频率=720000/ARR/PSC
void MyTimeBase_Init(TIM_TypeDef* TIMx,u32 ARR,u32 PSC)//定时器（内部时钟）时基单元初始化
{   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	if(TIMx==TIM1)RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	if(TIMx==TIM2)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	if(TIMx==TIM3)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	if(TIMx==TIM4)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    TIM_InternalClockConfig(TIMx);
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1 ;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up   ;
	TIM_TimeBaseInitStructure.TIM_Period=ARR-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=PSC-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);
    

}
void MyTimer_Interrupt_Init(TIM_TypeDef* TIMx,u32 ARR,u32 PSC,u8 PreemptionPriority,u8 SubPriority)//定时器中断初始化
{   MyTimeBase_Init(TIMx,ARR,PSC);
	TIM_ClearFlag(TIMx,TIM_FLAG_Update); 
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    if(TIMx==TIM1) MyNVIC_Init(TIM1_UP_IRQn,PreemptionPriority,SubPriority);
	if(TIMx==TIM2) MyNVIC_Init(TIM2_IRQn,PreemptionPriority,SubPriority);
	if(TIMx==TIM3) MyNVIC_Init(TIM3_IRQn,PreemptionPriority,SubPriority);
	if(TIMx==TIM4) MyNVIC_Init(TIM4_IRQn,PreemptionPriority,SubPriority);
	TIM_Cmd(TIMx,ENABLE);
}

#define OC1     0x01
#define OC2     0x02
#define OC3     0x03
#define OC4     0x04
void MyTimer_PWM_Init(TIM_TypeDef* TIMx,u32 ARR,u32 PSC,u8 OC,u16 CCR)
{ 	MyTimeBase_Init(TIMx,ARR,PSC);
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//通过该函数给结构体成员赋值
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse=CCR;//CCR
	if(TIMx==TIM2)
	{	if(OC==OC1){MyGPIO_Init(GPIOA,GPIO_Pin_0,GPIO_Mode_AF_PP);TIM_OC1Init(TIMx,&TIM_OCInitStructure);}
	    if(OC==OC2){MyGPIO_Init(GPIOA,GPIO_Pin_1,GPIO_Mode_AF_PP);TIM_OC2Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC3){MyGPIO_Init(GPIOA,GPIO_Pin_2,GPIO_Mode_AF_PP);TIM_OC3Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC4){MyGPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_AF_PP);TIM_OC4Init(TIMx,&TIM_OCInitStructure);}
	}
	if(TIMx==TIM3)
	{	if(OC==OC1){MyGPIO_Init(GPIOA,GPIO_Pin_6,GPIO_Mode_AF_PP);TIM_OC1Init(TIMx,&TIM_OCInitStructure);}
	    if(OC==OC2){MyGPIO_Init(GPIOA,GPIO_Pin_7,GPIO_Mode_AF_PP);TIM_OC2Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC3){MyGPIO_Init(GPIOB,GPIO_Pin_0,GPIO_Mode_AF_PP);TIM_OC3Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC4){MyGPIO_Init(GPIOB,GPIO_Pin_1,GPIO_Mode_AF_PP);TIM_OC4Init(TIMx,&TIM_OCInitStructure);}
	}                                                             
	if(TIMx==TIM4)
	{	if(OC==OC1){MyGPIO_Init(GPIOB,GPIO_Pin_6,GPIO_Mode_AF_PP);TIM_OC1Init(TIMx,&TIM_OCInitStructure);}
	    if(OC==OC2){MyGPIO_Init(GPIOB,GPIO_Pin_7,GPIO_Mode_AF_PP);TIM_OC2Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC3){MyGPIO_Init(GPIOB,GPIO_Pin_8,GPIO_Mode_AF_PP);TIM_OC3Init(TIMx,&TIM_OCInitStructure);}
		if(OC==OC4){MyGPIO_Init(GPIOB,GPIO_Pin_9,GPIO_Mode_AF_PP);TIM_OC4Init(TIMx,&TIM_OCInitStructure);}
	}              
	TIM_Cmd(TIM2,ENABLE);

}
void MyTimerEncoder_Init(TIM_TypeDef* TIMx)
{   MyTimeBase_Init(TIMx,65535,1);
	if(TIMx==TIM2)MyGPIO_Init(GPIOA,GPIO_Pin_0|GPIO_Pin_1,GPIO_Mode_IPU);
	if(TIMx==TIM3)MyGPIO_Init(GPIOA,GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_IPU);
	if(TIMx==TIM4)MyGPIO_Init(GPIOB,GPIO_Pin_6|GPIO_Pin_7,GPIO_Mode_IPU);
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1 ;
	TIM_ICInitStructure.TIM_ICFilter=0xf;
    TIM_ICInit(TIMx,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter=0xf;
	TIM_ICInit(TIMx,&TIM_ICInitStructure);
	TIM_EncoderInterfaceConfig(TIMx,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_Cmd(TIMx,ENABLE);

}

//****外部中断
//void  EXTI15_10_IRQHandler (void)
//{
//   if(EXTI_GetFlagStatus(EXTI_Line14)==SET)
//  {
//      EXTI_ClearITPendingBit(EXTI_Line14);
//  }
// 
//}
//****外部中断编码器
//void  EXTI0_IRQHandler (void)
//{
//if(EXTI_GetITStatus(EXTI_Line0)==SET)
//{if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
//{Encoder_Count--;}

//EXTI_ClearITPendingBit(EXTI_Line0);}
//}
//void  EXTI1_IRQHandler (void)
//{
//if(EXTI_GetITStatus(EXTI_Line1)==SET)
//{if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
//{Encoder_Count++;}
//EXTI_ClearITPendingBit(EXTI_Line1);
//}

//}
//****定时器中断
//void TIM2_IRQHandler  (void)
//{if(TIM_GetFlagStatus(TIM2,TIM_IT_Update)==SET)
//	{
//	   
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}