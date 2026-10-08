#ifndef __SCARA_H_
#define __SCARA_H_
#include "driver_config.h"

typedef struct
{
	// 定义三个电机
	stepping_motor_struct FA;					// 控制主臂的电机
	stepping_motor_struct SA;					// 控制副臂的电机
	stepping_motor_struct Z;					// 控制上下的电机
	
	float FA_angle_last,SA_angle_last,Z_height_last;		// 上一次参数
	float FA_angle,SA_angle,Z_height;						// FA角度，SA角度，Z高度
	int16_t x,y,z;											// 机械臂末端笛卡尔坐标系,x,y,z
	uint8_t sucker_state;								    // 夹爪状态，1代表吸附，0代表不吸附
	uint8_t sucker_last_state;								// 上次的夹爪状态
	float FA_angle_offset,SA_angle_offset,Z_height_offset;	// 偏移量
	

	void (*enable_motor)(uint8_t state);		// 电机使能
	void (*tool_init)(void);					// 工具初始化
	void (*pick_object)(void);					// 捡起物体
	void (*put_object)(void);					// 放置物体
}scara_struct;
extern scara_struct scara;

void scara_init(scara_struct * scara_p);
uint8_t g1_move(scara_struct * scara_p,int16_t x, int16_t y, int16_t z);
uint8_t reset_coordinate(scara_struct * scara_p,int16_t x, int16_t y, int16_t z);
uint8_t g0_move(scara_struct * scara_p,float FA_angle, float SA_angle, float Z_height);
uint8_t step(scara_struct * scara_p,int16_t x, int16_t y, int16_t z, uint8_t sucker_state);
#endif

