#include "driver_config.h"
//  Attention: flash擦写次数为10万次，故不可在死循环中反复调用flash函数  //
#define motor_data_addr	0x0800FF00
/**
  * @brief    擦除指定FLASH地址页内的内容
  * @param    add 32位FLASH地址
  * @retval   无
  */
void Flash_Erase(uint32_t add)
{
	FLASH_Unlock(); //解锁FLASH编程擦除控制器
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
	FLASH_ErasePage(add);    //擦除指定地址页
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
	FLASH_Lock();    //锁定FLASH编程擦除控制器
}
/**
  * @brief   flash写入数据 
  * @param   add 32位flash地址
  * @param	 dat 16位数据
  * @retval  无
  */
void Flash_WriteHalfWord(uint32_t add,uint16_t data)
{
	 FLASH_Unlock(); //解锁FLASH编程擦除控制器
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     //FLASH_ErasePage(add);    //擦除指定地址页
     FLASH_ProgramHalfWord(add,data); //从指定页的addr地址开始写
     FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
     FLASH_Lock();    //锁定FLASH编程擦除控制器
}

/**
  * @brief    FLASH读出数据
  * @param    add 32位读出FLASH地址
  * @retval   16位数据
  */
u16 FLASH_Read(uint32_t add)
{
	u16 a;
    a = *(__IO uint16_t*)add;
	return a;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     电机 FLASH 参数 读取
// 参数说明     void
// 返回参数     void
// 使用示例     motor_flash_read();
// 备注信息       
//-------------------------------------------------------------------------------------------------------------------
void motor_flash_read(void)
{
//    main_motor.zero_location=FLASH_Read(motor_data_addr);         //零点
//	main_motor.rotation_direction=FLASH_Read(motor_data_addr+2); 
//	main_motor.pole_pairs=FLASH_Read(motor_data_addr+4);  
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     电机 FLASH 参数 写入
// 参数说明     void
// 返回参数     void
// 使用示例     motor_flash_write();
// 备注信息       
//-------------------------------------------------------------------------------------------------------------------
void motor_flash_write(void)
{
//	Flash_Erase(motor_data_addr);
//	Flash_WriteHalfWord(motor_data_addr,main_motor.zero_location);
//	Flash_WriteHalfWord(motor_data_addr+2,main_motor.rotation_direction);
//	Flash_WriteHalfWord(motor_data_addr+4,main_motor.pole_pairs);

}












