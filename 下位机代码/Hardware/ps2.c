#include "driver_config.h"
#include "PS2.h" 
#define DELAY_TIME  delay_us(5); 
u16 Handkey;	// 按键值读取，零时存储。
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
u16 MASK[]=
{
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	
};	//按键值与按键明

void PS2_Pin_Init()
{
	
	RCC_APB2PeriphClockCmd(PS2_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = PS2_CLK_Pin|PS2_CS_Pin|PS2_DO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PS2_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = PS2_DI_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PS2_Port, &GPIO_InitStructure);

	delay_init();
}
	
void PS2_Cmd(u8 CMD)//SPI交换字节
{ 	u8 i;
	Data[1] = 0;
	for(i=0;i<8;i++)
	{
		if(CMD&(0x01<<i))DO=1;
		else DO=0;		
	    CLK=1;                        //时钟拉高
		DELAY_TIME;
		CLK=0;
		DELAY_TIME;
		CLK=1;
		if(DI)
		Data[1] = (0x01<<i)|Data[1];
	}
	delay_us(16);
}

//判断红绿灯模式
u8 PS2_RedLight(void)
{
	CS=0;
	PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	CS=1;
	if(Data[1] == 0X73)   return 0 ;
	else return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	volatile u8 Byte=0;
	u8 i;
	CS=0;
	PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	for(Byte=2;Byte<9;Byte++)          //开始接受数据
	{
		for(i=0;i<8;i++)
		{
			CLK=1;
			DELAY_TIME;
			CLK=0;
			DELAY_TIME;
			CLK=1;
		    if(DI)
		    Data[Byte] = (0x01<<i)|Data[Byte];
		}
		
        delay_us(16);
	}
	CS=1;
}
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
//对读出来的PS2的数据进行处理,只处理按键部分  
//只有一个按键按下时按下为0，未按下为1
//若有按键按下，该函数返回按下的按键键码(取最小的那个),通过头文件键码的宏定义即可找到对应的按键
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //没有任何按键按下
}

//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}
/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: 手柄震动函数，
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:右侧小震动电机 0x00关，其他开
	   motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
******************************************************/
void PS2_Vibration(u8 motor1, u8 motor2)
{
	CS=0;
	delay_us(16);
    PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS=1;
	delay_us(16);  
}
//short poll
void PS2_ShortPoll(void)
{
	CS=0;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x42);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS=1;
	delay_us(16);	
}
//进入配置
void PS2_EnterConfing(void)
{
    CS=0;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS=1;
	delay_us(16);
}
//发送模式设置
void PS2_TurnOnAnalogMode(void)
{
	CS=0;
	PS2_Cmd(0x01);  
	PS2_Cmd(0x44);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); //analog=0x01;digital=0x00  软件设置发送模式
	PS2_Cmd(0xEE); //Ox03锁存设置，即不可通过按键“MODE”设置模式。
				   //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS=1;
	delay_us(16);
}
//振动设置
void PS2_VibrationMode(void)
{
	CS=0;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x4D);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS=1;
	delay_us(16);	
}
//完成并保存配置
void PS2_ExitConfing(void)
{
    CS=0;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS=1;
	delay_us(16);
}
//手柄配置初始化
void PS2_Init(void)
{
	PS2_Pin_Init();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		//进入配置模式
	PS2_TurnOnAnalogMode();	//“红绿灯”配置模式，并选择是否保存
	PS2_VibrationMode();	//开启震动模式
	PS2_ExitConfing();		//完成并保存配置
}
// 如果下一步到达不可到的位置，会保持当前的状态
void ps2_loop(void)
{
	static uint8_t Key;
	PS2_ClearData();   //清除缓存
	PS2_ReadData();	   //读数据
	Key = PS2_DataKey();
	if(Key)
	{	
		switch (Key)
		{
		case PSB_PINK:scara.y--;break;

		case PSB_RED:scara.y++;break;

		case PSB_BLUE:scara.x++;break;

		case PSB_GREEN:scara.x--;break;

		case PSB_PAD_UP:scara.z = Z_UP;break;

		case PSB_PAD_DOWN:scara.z = Z_DOWN;break;

		case PSB_L1:
			scara.sucker_last_state = scara.sucker_state;
			scara.sucker_state = 1;
			break;

		case PSB_L2:
			scara.sucker_last_state = scara.sucker_state;
			scara.sucker_state = 0;
			break;

		default:
			break;
		}
		if(step(&scara,scara.x,scara.y,scara.z,scara.sucker_state))
		{
			switch (Key)
			{
			case PSB_PINK: scara.y++;break;

			case PSB_RED: scara.y--;break;

			case PSB_BLUE: scara.x--;break;

			case PSB_GREEN:scara.x++;break;
			// 因为在PS2控制中，不会因为z和吸盘导致不可达，所以不考虑
			default:
				break;
			}
		}	
		
	}
}


