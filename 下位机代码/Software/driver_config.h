#ifndef __DRIVER_CONFIG_H_
#define __DRIVER_CONFIG_H_

#include "tool.h"
#include "delay.h"
#include "serial.h"
#include "driver_gpio.h"
#include "driver_adc.h"
#include "flash.h"
#include "interface.h"
#include "interrupt.h"
#include "stepping_motor.h"
#include "driver_gpio.h"
#include "snr9816.h"
#include "serial_lcd.h"
#include "ps2.h"
#include "scara.h"
#include "scara_uart.h"

#define  TIM_CLOCK_FREQ			72000000			// 时钟主频				
// 步进电机参数
#define  STEPPING_ANGLE			1.8					// 步进角，单位度
#define  SUBDIVISION			32					// 细分数，常见32细分，16细分，8细分等	
// 机械臂参数
#define  FA_REDUCTION_RATIO 	5.1 				// 主臂减速比，原来是6
#define  SA_REDUCTION_RATIO 	3.9 				// 副臂减速比，原来是5
#define  LEAD 					2.0 				// z轴丝杆导程,2mm
#define  L_FA 					177.0 				// 主臂长度，单位mm
#define  L_SA 					177.0 				// 副臂长度，单位mm
#define  L_FA_2 				(L_FA * L_FA)
#define  L_SA_2 				(L_SA * L_SA)

// 初始坐标
#define  X_INIT					177
#define  Y_INIT					-177
#define  Z_INIT					25
#define  Z_UP					50
#define  Z_DOWN					25

// 关节限幅
#define  FA_ANGLE_MAX					90
#define  FA_ANGLE_MIN					-90		
#define  SA_ANGLE_MAX					180
#define  SA_ANGLE_MIN					15
#define  Z_HEIGHT_MAX					83					// 最高为100mm,保险最高位96mm
#define  Z_HEIGHT_MIN					2					// 最低为0mm,保险最低为2mm


#define  M_PI 3.14159265358979323846
#define  RAD2DEG (180.0 / M_PI)

#define  DRIVER_RESPONSE_CYCLE  		10

#define  ELECTROMAGNET					(0)
#define  AIRPUMP						(1)
#define  TOOL							AIRPUMP

#define  ELECTROMAGNET_DIR				0
#define  ELECTROMAGNET_DUTY				1000-1 	// 电磁铁占空比，满占空比为1000



#endif


