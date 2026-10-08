#ifndef __INIT_H_
#define __INIT_H_
void MyGPIO_Init(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);
void MyEXTI_Interrupt_Init(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,
EXTITrigger_TypeDef EXTI_Trigger,u8 PreemptionPriority,u8 SubPriority);
void MyEXTIEncoder_Init(GPIO_TypeDef* GPIOx1,u16 GPIO_Pin1,u8 PreemptionPriority1,u8 SubPriority1,
GPIO_TypeDef* GPIOx2,u16 GPIO_Pin2,u8 PreemptionPriority2,u8 SubPriority2);
void MyTimeBase_Init(TIM_TypeDef* TIMx,u32 ARR,u32 ms);
void MyTimer_Interrupt_Init(TIM_TypeDef* TIMx,u8 PreemptionPriority,u8 SubPriority);
void MyTimer_PWM_Init(TIM_TypeDef* TIMx,u8 OC,u16 CCR);
void MyTimerEncoder_Init(TIM_TypeDef* TIMx);
#endif