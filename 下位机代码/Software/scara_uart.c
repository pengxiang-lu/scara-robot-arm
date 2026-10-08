#include "driver_config.h"

uint8_t scara_uart_flag = 0, tts_uart_flag = 0, tool_uart_flag = 0, step_uart_flag = 0;

#define SCARA_PACKET_HEAD    0x55
#define TTS_PACKET_HEAD      0x66
#define TOOL_PACKET_HEAD     0x77
#define STEP_PACKET_HEAD	 0x88
// 全局变量
uint8_t state = 0;          // 状态标志
uint8_t packet_p = 0;       // 包元素计数
uint8_t sum = 0;            // 校验和
uint8_t packet_type = 0;    // 包类型
uint8_t packet_buffer[128] = {0};  // 缓存区


// 机械臂控制回调函数
void scara_driver_control_callback(uint8_t receive_data)
{   
    switch(state)
    {
        case 0:     // 等待包头
            // 判断包头类型
            if(receive_data == SCARA_PACKET_HEAD || 
               receive_data == TTS_PACKET_HEAD || 
               receive_data == TOOL_PACKET_HEAD ||
			   receive_data == STEP_PACKET_HEAD)
            {
                packet_p = 0;
                sum = 0;                // 重置校验和
                packet_type = receive_data;
                sum += receive_data;     // 包头参与校验
                
                state = 1;
            }
            break;
            
        case 1:     // 接收数据
            switch(packet_type)
            {
                case SCARA_PACKET_HEAD:  // 机械臂控制协议
                    if(packet_p < 6)     // 接收6个数据字节
                    {
                        packet_buffer[packet_p] = receive_data;
                        sum += receive_data;
                        packet_p++;
                        
                        if(packet_p >= 6)  // 已接收6个数据字节，等待校验和
                        {
                            state = 2;  // 进入校验状态
                        }
                    }
                    break;
                    
                case TTS_PACKET_HEAD:    // 语音播报协议
                    packet_buffer[packet_p] = receive_data;
                    packet_p++;
                    
                    if(receive_data == '\0')  // 遇到字符串结束符
                    {
                        tts_uart_flag = 1;
                        state = 0;  // 重置状态
                    }
                    else if(packet_p >= sizeof(packet_buffer) - 1)  // 防止缓冲区溢出
                    {
                        state = 0;  // 错误，重置状态
                        packet_p = 0;
                    }
                    break;
                    
                case TOOL_PACKET_HEAD:   // 工具指令
                    if(packet_p < 1)     // 接收1个数据字节
                    {
                        packet_buffer[packet_p] = receive_data;
                        sum += receive_data;
                        packet_p++;
                        
                        if(packet_p >= 1)  // 已接收1个数据字节，等待校验和
                        {
                            state = 2;  // 进入校验状态
                        }
                    }
                    break;
					
				case STEP_PACKET_HEAD:  // 机械臂控制协议
                    if(packet_p < 7)     // 接收6个数据字节
                    {
                        packet_buffer[packet_p] = receive_data;
                        sum += receive_data;
                        packet_p++;
                        
                        if(packet_p >= 7)  // 已接收6个数据字节，等待校验和
                        {
                            state = 2;  // 进入校验状态
                        }
                    }
                    break;
            }
            break;
            
        case 2:     // 校验状态
            if(receive_data == sum)      // 校验通过
            {
                if(packet_type == SCARA_PACKET_HEAD)
                {
				// 串口协议解析
					scara.x = ((int16_t)packet_buffer[0] << 8) | packet_buffer[1];
					scara.y = ((int16_t)packet_buffer[2] << 8) | packet_buffer[3];
					scara.z = ((int16_t)packet_buffer[4] << 8) | packet_buffer[5];
                    scara_uart_flag = 1;
                }
                else if(packet_type == TOOL_PACKET_HEAD)
                {
                    tool_uart_flag = 1;
					scara.sucker_last_state = scara.sucker_state;
					scara.sucker_state = packet_buffer[0];
                }
				else if(packet_type == STEP_PACKET_HEAD)
				{
					step_uart_flag = 1;
					scara.x = ((int16_t)packet_buffer[0] << 8) | packet_buffer[1];
					scara.y = ((int16_t)packet_buffer[2] << 8) | packet_buffer[3];
					scara.z = ((int16_t)packet_buffer[4] << 8) | packet_buffer[5];
					scara.sucker_last_state = scara.sucker_state;
					scara.sucker_state = (uint8_t)packet_buffer[6];
				}
            }
            // 重置状态，无论校验是否通过
            state = 0;
            packet_p = 0;
            sum = 0;
            break;
    }
}

void scara_uart_loop(void)
{
    if(scara_uart_flag == 1)
    {
        scara_uart_flag = 0;
        if(g1_move(&scara, scara.x, scara.y, scara.z))
			printf("Target position unreachable\r\n");
    }
    
    if(tts_uart_flag == 1)
    {
        tts_uart_flag = 0;
        // packet_p包含结束符，所以要减1
        if(packet_p > 0)
        {
            snr9816tts_say_array(packet_buffer, packet_p-1);
        }
        packet_p = 0;  // 重置包计数器
		delay_ms((packet_p-1)*300);		// 假设说一个字要300ms
		printf("Voice executed successfully\r\n");
    }
    
    if(tool_uart_flag == 1)
    {
        tool_uart_flag = 0;
        if(scara.sucker_state == 0x01)  // 修正下标
        {
            scara.pick_object();
        }
        else if(scara.sucker_state == 0x00)
        {
            scara.put_object();
        }
    }
	
	if(step_uart_flag == 1)
    {
        step_uart_flag = 0;
		if(step(&scara, scara.x, scara.y, scara.z, scara.sucker_state))
			printf("Target position unreachable\r\n");
		else
			printf("Action executed successfully\r\n");
    }
}

