#ifndef ROBOTICARM_H
#define ROBOTICARM_H

#include <QObject>
// 机械臂类
class RoboticArm : public QObject
{
    Q_OBJECT
public:

    QString fullCmd;                    // 完整的窗口指令
    int x,y,z;                          // 笛卡尔空间参数,临时变量
    QString voiceData;                  // 语音文本
    int sendlenth;                      // 发送数据的长度
    char dataSend[128];              // 发送的数据包
    void uartTranAxisData();            // 发送坐标数据
    void uartTranVoiceData();           // 发送语音数据
    void uartTranToolData(uint8_t toolState);   // 发送工具数据
    explicit RoboticArm(QObject *parent = nullptr);
signals:
};

#endif
