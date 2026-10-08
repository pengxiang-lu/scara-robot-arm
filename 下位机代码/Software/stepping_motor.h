#ifndef __STEPIPING_MOTOR_H_
#define __STEPIPING_MOTOR_H_
#include "stm32f10x.h"                  // Device header

#define ENABLE_PORT	GPIOB
#define ENABLE_PIN	GPIO_Pin_15

#define DIR_PORT	GPIOB
#define M1_DIR_PIN	GPIO_Pin_12
#define M2_DIR_PIN	GPIO_Pin_13
#define M3_DIR_PIN	GPIO_Pin_14
typedef struct
{
	int pulse_accel;				// 加速脉冲
	int pulse_accel_constant;		// 加速+匀速脉冲,不包括减速
	int pulse_target;				// 目标脉冲数,加速+匀速+减速脉冲
	int pulse_count;				// 脉冲累加计数
	
	int accel_pulse;				// 加速度,单位为脉冲/s^2
	int speed_pulse;				// 速度,单位为脉冲/s
	int speed_min_pulse;			// 初始速度,单位为脉冲/s
	int speed_min_pulse_2;			// 初始速度,单位为脉冲/s
	int speed_max_pulse;			// 最大转速,单位为脉冲/s
	int angle_pulse;				// 当前角度,单位为脉冲
	float angle;					// 当前角度,单位度
	float stepping_angle;			// 步进角
	uint16_t subdivision;			// 细分数
	float pause_deg_radio;			// 细分数/步进角，代表每一度需要多少脉冲
	uint32_t speed_arr_mul;			// 速度和ARR的积
	uint8_t dir;					// 当前旋转方向，0或者1
	
	
	uint16_t arr;					// 定时器ARR的值，用于给ARR寄存器赋值
	uint8_t end_flag;				// 运行结束标志位
	uint8_t fre_flag;				// 更改脉冲频率标志位
	TIM_TypeDef * TIMx;
	
	void (*motor_dir_set)(uint8_t dir);					// 方向	
	void (*motor_pwm_init)(uint16_t arr, uint16_t psc);		// 步进初始化
}stepping_motor_struct;
void motor_init(stepping_motor_struct*m_struct,float stepping_angle,uint16_t subdivision,float angle_init,float accel,float speed_max,float speed_min);
float motor_get_angle(stepping_motor_struct*m_struct);
void motor_move(stepping_motor_struct*m_struct,float angle);
void motor_enable(uint8_t state);
void FA_set_direction(uint8_t state);
void SA_set_direction(uint8_t state);
void Z_set_direction(uint8_t state);
void FA_pwm_init(uint16_t arr, uint16_t psc);
void SA_pwm_init(uint16_t arr, uint16_t psc);
void Z_pwm_init(uint16_t arr, uint16_t psc);
void set_speed_parama(stepping_motor_struct * motor_p,int offset);
void motor_speed_set(stepping_motor_struct * motor_p);
#endif


