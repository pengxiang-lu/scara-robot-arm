#include "driver_config.h"
// 底层接口初始化绑定，将函数绑定到相应的结构体下
void interface_init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	scara.enable_motor = motor_enable;		// 电机使能函数接口
	
	scara.FA.motor_dir_set = FA_set_direction;
	scara.SA.motor_dir_set = SA_set_direction;
	scara.Z.motor_dir_set = Z_set_direction;
	
	scara.FA.motor_pwm_init = FA_pwm_init;
	scara.SA.motor_pwm_init = SA_pwm_init;
	scara.Z.motor_pwm_init = Z_pwm_init;
	
	scara.FA.TIMx = TIM2;
	scara.SA.TIMx = TIM3;
	scara.Z.TIMx = TIM4;
	
	scara.tool_init = tool_init;
	scara.pick_object = tool_pick_object;
	scara.put_object = tool_put_object;
}
