#include "roboticarm.h"
#include "qDebug.h"
RoboticArm::RoboticArm(QObject *parent)
    : QObject{parent}
{   // 参数初始化

}
// 机械臂控制协议     包头 0x55 + 坐标X高8位 + 坐标X低8位 + 坐标Y高8位 + 坐标Y低8位 + 坐标Z高8位 + 坐标Z低8位 + 校验和
// 语音播报协议		包头 0x66 + 汉字句子编码(包含字符串结尾的'\0'字符)
// 工具指令			包头 0x77 + 工具指令(吸取为0x01,放下为0x00) + 校验和
void RoboticArm::uartTranAxisData()
{
    int sum = 0;
    dataSend[0] = 0x55;
    dataSend[1] = (x>>8)&0xFF;
    dataSend[2] = x&0xFF;
    dataSend[3] = (y>>8)&0xFF;
    dataSend[4] = y&0xFF;
    dataSend[5] = (z>>8)&0xFF;
    dataSend[6] = z&0xFF;
    for(int i = 0;i < 7;i ++)
    {
        sum += dataSend[i];
    }
    dataSend[7] = sum;
    sendlenth = 8;
}
void RoboticArm::uartTranVoiceData()
{
    dataSend[0] = 0x66;
    QByteArray byteArray = voiceData.toLocal8Bit();
    sendlenth = byteArray.size() + 2;
    memcpy(&dataSend[1], byteArray.data(), byteArray.size());
    dataSend[sendlenth - 1] = '\0';
}
// toolState:1代表吸取,0代表放下
void RoboticArm::uartTranToolData(uint8_t toolState)
{
    dataSend[0] = 0x77;
    dataSend[1] = toolState;
    dataSend[2] = dataSend[0] + dataSend[1];
    sendlenth = 3;
}
