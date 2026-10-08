#ifndef  __PS2_H
#define  __PS2_H
#include "delay.h"
#include "sys.h"
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File：PS2驱动程序
Author：pinggai    Version:1.1     Data:2015/10/20
Description: PS2驱动程序
             增加功能：
			 1、软件设置“红灯模式”、“绿灯模式”，并可以设置“保存”，通过手柄“模式按键”无法改变
			 2、设置手柄震动：通过数值的设置，改变左侧大震动电机震动频率。
			                  通过数值的设置，开关右侧小震动电机。
History:  
V1.0: 	2015/05/16
1、手柄解码，识别按键值，读取模拟值。       
**********************************************************/	 
#define PS2_Port		GPIOA
#define PS2_RCC			RCC_APB2Periph_GPIOA
#define PS2_DI_Pin		GPIO_Pin_6
#define PS2_DO_Pin		GPIO_Pin_7
#define PS2_CS_Pin		GPIO_Pin_4
#define PS2_CLK_Pin		GPIO_Pin_5

#define DI 		PAin(6)        //DAT
#define DO 		PAout(7)       //CMD
#define CS 		PAout(4)       //CS
#define CLK 	PAout(5)       //CLK


//键码
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //右摇杆X轴数据
#define PSS_RY 6				//右摇杆Y轴数据
#define PSS_LX 7				//左摇杆X轴数据
#define PSS_LY 8				//左摇杆Y轴数据

extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Pin_Init(void);
u8 PS2_RedLight(void);   //判断是否为红灯模式
void PS2_ReadData(void); //读手柄数据
void PS2_Cmd(u8 CMD);		  //向手柄发送命令
u8 PS2_DataKey(void);		  //按键值读取
u8 PS2_AnologData(u8 button); //得到一个摇杆的模拟量
void PS2_ClearData(void);	  //清除数据缓冲区
void PS2_Vibration(u8 motor1, u8 motor2);//振动设置motor1  0xFF开，其他关，motor2  0x40~0xFF

void PS2_EnterConfing(void);	 //进入配置
void PS2_TurnOnAnalogMode(void); //发送模拟量
void PS2_VibrationMode(void);    //振动设置
void PS2_ExitConfing(void);	     //完成配置
void PS2_Init(void);		     //配置初始化
void ps2_loop(void);
#endif

