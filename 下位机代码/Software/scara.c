#include "driver_config.h"
// 传入机械臂结构体，加速度(单位 度/s^2)和最大速度(单位 度/s)
void scara_init(scara_struct * scara_p)
{
	// 使能电机
	scara_p->enable_motor(1);
	// 设置初始参数，传入 步进角和细分数，电机初始角度默认都为0度，加速度，最大速度和最小速度
	motor_init(&scara_p->FA,STEPPING_ANGLE,SUBDIVISION,0,50,30,10);
	motor_init(&scara_p->SA,STEPPING_ANGLE,SUBDIVISION,0,50,30,10);
	motor_init(&scara_p->Z,STEPPING_ANGLE,SUBDIVISION,0,80,80,15);
	// 初始化工具
	scara_p->tool_init();
}

// 正运动学解算
uint8_t forward_kinematics(scara_struct * scara_p,float FA_angle, float SA_angle, float Z_height)
{
	
	scara_p->x = L_FA * cos(FA_angle) - L_SA * cos(SA_angle - FA_angle);
	scara_p->y = L_FA * sin(FA_angle) + L_SA * sin(SA_angle - FA_angle);
	scara_p->z = Z_height;
	
	scara_p->FA_angle_offset = scara_p->FA_angle - scara_p->FA_angle_last;
	scara_p->SA_angle_offset = scara_p->SA_angle - scara_p->SA_angle_last;
	scara_p->Z_height_offset = scara_p->Z_height - scara_p->Z_height_last;
	
	scara_p->FA_angle_last = scara_p->FA_angle;					//保存坐标，下次计算
	scara_p->SA_angle_last = scara_p->SA_angle;
	scara_p->Z_height_last = scara_p->Z_height;

	return 0;//结果合理
}
// 逆运动解算,考虑关节

uint8_t inverse_kinematics(scara_struct *scara_p, int16_t x, int16_t y, int16_t z)
{
	
    float L_TA_2 = y * y + x * x;
	if(L_TA_2 > (L_FA + L_SA) * (L_FA + L_SA))
		return 6;   // 超出最大工作半径
	if(L_TA_2 < (L_FA - L_SA) * (L_FA - L_SA))
		return 7;   // 小于最小工作半径
	
    float alpha  = atan2(-y, x) * RAD2DEG;
    float beta   = acos((L_FA_2 + L_TA_2 - L_SA_2) / (2.0f * L_FA * sqrtf(L_TA_2))) * RAD2DEG;

    scara_p->SA_angle = acos((L_FA_2 + L_SA_2 - L_TA_2) / (2.0f * L_FA * L_SA)) * RAD2DEG;
    scara_p->FA_angle = 90.0f - alpha - beta;
    scara_p->Z_height = z;

    /* ---------- 关节限幅判断 ---------- */
    if (scara_p->FA_angle > FA_ANGLE_MAX ||
        scara_p->FA_angle < FA_ANGLE_MIN)
        return 3;

    if (scara_p->SA_angle > SA_ANGLE_MAX ||
        scara_p->SA_angle < SA_ANGLE_MIN)
        return 4;

    if (scara_p->Z_height > Z_HEIGHT_MAX ||
        scara_p->Z_height < Z_HEIGHT_MIN)
        return 5;

    /* ---------- NaN / Inf 判断 ---------- */
    if (isnan(scara_p->FA_angle) || isnan(scara_p->SA_angle))
        return 1;
    if (isinf(scara_p->FA_angle) || isinf(scara_p->SA_angle))
        return 2;

    /* ---------- 速度前馈 / offset 计算 ---------- */
    scara_p->FA_angle_offset = scara_p->FA_angle - scara_p->FA_angle_last;
    scara_p->SA_angle_offset = scara_p->SA_angle - scara_p->SA_angle_last;
    scara_p->Z_height_offset = scara_p->Z_height - scara_p->Z_height_last;

    scara_p->FA_angle_last = scara_p->FA_angle;
    scara_p->SA_angle_last = scara_p->SA_angle;
    scara_p->Z_height_last = scara_p->Z_height;

    return 0;
}

// 重新设置机械臂的当前坐标
uint8_t reset_coordinate(scara_struct * scara_p,int16_t x, int16_t y, int16_t z)//传入参数为主臂角度，副臂角度，z轴高度mm
{
	scara_p->x = x;
	scara_p->y = y;
	scara_p->z = z;
	scara_p->sucker_state = 0;
	scara_p->sucker_last_state = 0;
 	return inverse_kinematics(scara_p,x,y,z);
}

// 坐标移动代码
uint8_t g1_move(scara_struct * scara_p,int16_t x, int16_t y, int16_t z)//x坐标，y坐标，z坐标，加速度，最大速度
{
	
	int res = inverse_kinematics(scara_p,x, y, z);
	if(res != 0)
	{
		return res;		//逆运动计算有误
	}
	scara_p->x = x;
	scara_p->y = y;
	scara_p->z = z;
	// 先将实际参数单位转化为以脉冲为单位再传入
	set_speed_parama(&scara_p->FA,scara_p->FA_angle_offset * scara_p->FA.pause_deg_radio * FA_REDUCTION_RATIO + 0.5);
	set_speed_parama(&scara_p->SA,scara_p->SA_angle_offset * scara_p->SA.pause_deg_radio * SA_REDUCTION_RATIO + 0.5);
	set_speed_parama(&scara_p->Z,scara_p->Z_height_offset * 360 * scara_p->Z.pause_deg_radio / LEAD + 0.5);

	if(scara_p->FA.pulse_target != 0) TIM_Cmd(TIM2,ENABLE); else scara_p->FA.end_flag = true;
	if(scara_p->SA.pulse_target != 0) TIM_Cmd(TIM3,ENABLE); else scara_p->SA.end_flag = true;
	if(scara_p->Z.pulse_target != 0)  TIM_Cmd(TIM4,ENABLE); else scara_p->Z.end_flag  = true;

	while(!(scara_p->FA.end_flag & scara_p->SA.end_flag & scara_p->Z.end_flag))	// 这里要一直等待所有动作完成
	{
		if(!scara_p->FA.end_flag) motor_speed_set(&scara_p->FA);
		if(!scara_p->SA.end_flag) motor_speed_set(&scara_p->SA);
		if(!scara_p->Z.end_flag)  motor_speed_set(&scara_p->Z);
	}
	return 0;
}

uint8_t g0_move(scara_struct * scara_p,float FA_angle, float SA_angle, float Z_height)
{
	// 关节限幅判断 
    if (FA_angle > FA_ANGLE_MAX || FA_angle < FA_ANGLE_MIN)
        return 1;

    if (SA_angle > SA_ANGLE_MAX || SA_angle < SA_ANGLE_MIN)
        return 2;

    if (Z_height > Z_HEIGHT_MAX || Z_height < Z_HEIGHT_MIN)
        return 3;
	scara_p->FA_angle = FA_angle;					//保存坐标，下次计算
	scara_p->SA_angle = SA_angle;
	scara_p->Z_height = Z_height;
	forward_kinematics(scara_p,FA_angle,SA_angle,Z_height);
	// 先将实际参数单位转化为以脉冲为单位再传入
	set_speed_parama(&scara_p->FA,scara_p->FA_angle_offset * scara_p->FA.pause_deg_radio * FA_REDUCTION_RATIO + 0.5);
	set_speed_parama(&scara_p->SA,scara_p->SA_angle_offset * scara_p->SA.pause_deg_radio * SA_REDUCTION_RATIO + 0.5);
	set_speed_parama(&scara_p->Z,scara_p->Z_height_offset * 360 * scara_p->Z.pause_deg_radio / LEAD + 0.5);

	if(scara_p->FA.pulse_target != 0) TIM_Cmd(TIM2,ENABLE); else scara_p->FA.end_flag = true;
	if(scara_p->SA.pulse_target != 0) TIM_Cmd(TIM3,ENABLE); else scara_p->SA.end_flag = true;
	if(scara_p->Z.pulse_target != 0)  TIM_Cmd(TIM4,ENABLE); else scara_p->Z.end_flag  = true;

	while(!(scara_p->FA.end_flag & scara_p->SA.end_flag & scara_p->Z.end_flag))	// 这里要一直等待所有动作完成
	{
		if(!scara_p->FA.end_flag) motor_speed_set(&scara_p->FA);
		if(!scara_p->SA.end_flag) motor_speed_set(&scara_p->SA);
		if(!scara_p->Z.end_flag)  motor_speed_set(&scara_p->Z);
	}
	return 0;
}
// step优先处理吸盘控制，吸盘状态和上一次不一样才会执行动作。
uint8_t step(scara_struct * scara_p,int16_t x, int16_t y, int16_t z, uint8_t sucker_state)
{
	if(scara_p->sucker_last_state != scara_p->sucker_state)
	{
		if(sucker_state)
		{
			scara_p->pick_object();
		}
		else
		{
			scara_p->put_object();
		}
	}
	uint8_t s = g1_move(scara_p,x,y,z);
	return s;
}
