#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uiInit();               // ui界面初始化
    deviceStateShow(0);     // 显示设备状态(默认未连接)
    qDebug()<<"界面初始化完成";
    serialInit();           // 串口参数初始化
    updateSerialPortList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ui界面初始化函数
void MainWindow::uiInit()
{
    setWindowTitle("SCARA机械臂上位机");             // 设置窗口标题
    QIcon icon(":/image/HMI_icon.png");
    setWindowIcon(icon);                           // 设置窗口图标

    ui->widget_x->setMaxMin(0,354);
    ui->widget_y->setMaxMin(-354,100);
    ui->widget_z->setMaxMin(25,110);

    ui->widget_x->setNum(177);
    ui->widget_y->setNum(-177);
    ui->widget_z->setNum(50);
}
// 更新转态栏函数
void MainWindow::deviceStateShow(int state)
{
    if(state == 0)
    {
        statusBar()->setStyleSheet
            (
                "QStatusBar { "
                "background-color: rgb(200,200,200); "
                "color: red; "
                "font-weight: 500; "
                "font-family: 'SimHei';"
                "}"
                );
        ui->statusbar->showMessage(" × 串口未连接");
    }
    else if(state == 1)   // state=1代表设备已连接
    {
        statusBar()->setStyleSheet
            (
                "QStatusBar { "
                "background-color: rgb(200,200,200); "
                "color: green; "
                "font-weight: 500; "
                "font-family: 'SimHei';"
                "}"
                );
        ui->statusbar->showMessage(QString(" √ %1已打开").arg(portName));
    }
    else if(state == 2)   // state=1代表设备已连接
    {
        statusBar()->setStyleSheet
            (
                "QStatusBar { "
                "background-color: rgb(200,200,200); "
                "color: yellow; "
                "font-weight: 500; "
                "font-family: 'SimHei';"
                "}"
                );
        ui->statusbar->showMessage(" ! 串口已打开,切换串口需要关闭");
    }
    else if(state == 3)   // state=1代表设备已连接
    {
        statusBar()->setStyleSheet
            (
                "QStatusBar { "
                "background-color: rgb(200,200,200); "
                "color: yellow; "
                "font-weight: 500; "
                "font-family: 'SimHei';"
                "}"
                );
        ui->statusbar->showMessage(" ! 请先打开串口");
    }

}
void MainWindow::serialInit()
{
    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud115200);           // 波特率设置 115200
    serial->setDataBits(QSerialPort::Data8);                // 位数
    serial->setParity(QSerialPort::NoParity);               // 无校验
    serial->setStopBits(QSerialPort::OneStop);              // 1位停止位
    serial->setFlowControl(QSerialPort::NoFlowControl);     // 无硬件流控
    ui->comboBox_port->setCurrentIndex(0);
}
int MainWindow::serialOpen()
{
    portName = ui->comboBox_port->currentText();
    serial->setPortName(portName);
    if (serial->open(QIODevice::ReadWrite))
    {
        // 打开成功
        qDebug() << "串口"<<portName<<"打开成功";
        return 1;
    }
    else
    {
        // 打开失败，输出错误信息
        qDebug() << "串口打开失败：" << serial->errorString();
        if(serial->errorString() == "Device is already open")
        {
            return 2;
        }
        return 0;
    }
}
void MainWindow::serialClose()
{
    if (serial->isOpen())
    {
        serial->close();
        qDebug() << "串口关闭成功";
    }
    else
    {
        qDebug() << "串口未打开";
    }
}
// 封装获取串口列表的函数
void MainWindow::updateSerialPortList()
{
    // 清空现有列表（例如：QComboBox的选项）
    ui->comboBox_port->clear();

    // 枚举所有可用串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        // 添加到下拉框（显示端口名+描述，便于用户识别）
        ui->comboBox_port->addItem
            (
                QString("%1").arg(info.portName()),
                info.portName() // 存储实际端口名作为用户数据
                );
    }
}
int MainWindow::sendUint8Data(char *data, int length)
{
    // 检查串口指针有效性
    if (serial == nullptr) {
        qDebug() << "错误：串口指针为空";
        return -1;
    }

    // 检查串口是否已打开且可写
    if (!serial->isOpen()) {
        qDebug() << "错误：串口未打开";
        return -1;
    }
    if (!serial->isWritable()) {
        qDebug() << "错误：串口不可写";
        return -1;
    }

    // 检查数据和长度有效性
    if (data == nullptr || length <= 0) {
        qDebug() << "错误：数据为空或长度无效";
        return -1;
    }

    // 发送数据（转换uint8_t*为char*）
    qint64 bytesWritten = serial->write(
        reinterpret_cast<const char*>(data), // 类型转换（安全，均为1字节）
        length                               // 发送长度
        );

    // 输出发送结果
    if (bytesWritten == -1) {
        qDebug() << "发送失败：" << serial->errorString();
    } else {
        qDebug() << "发送成功，字节数：" << bytesWritten;
    }

    return bytesWritten;
}
int MainWindow::sendAllCommands(QString fullCmd)
{
    if (!serial || !serial->isOpen()) {
        qDebug() << "串口未打开，发送失败";
        return -1;
    }

    QByteArray data = fullCmd.toUtf8();
    qint64 bytesWritten = serial->write(data);

    if (bytesWritten == -1)
    {
        qDebug() << "批量发送失败：" << serial->errorString();
        return -1;
    }
    else
    {
        serial->waitForBytesWritten(100); // 等待100毫秒
        qDebug() << QString("批量发送成功，共发送 %1 字节").arg(bytesWritten);
        return 1;
    }
}
void MainWindow::on_pushButton_open_clicked()
{
    deviceStateShow(serialOpen());
}
void MainWindow::on_pushButton_close_clicked()
{
    serialClose();
    deviceStateShow(0);
}
void MainWindow::on_pushButton_refresh_clicked()
{
    updateSerialPortList();
}
void MainWindow::on_pushButton_sendAxis_clicked()
{
    r1.x = ui->widget_x->getNum();
    r1.y = ui->widget_y->getNum();
    r1.z = ui->widget_z->getNum();
    r1.uartTranAxisData();
    if(sendUint8Data(r1.dataSend,r1.sendlenth)==-1)
    {
        QMessageBox::critical(
            nullptr,                // 父窗口（nullptr表示无父窗口，居中显示）
            "错误",                 // 弹窗标题
            "请检查串口连接",          // 错误内容（支持换行\n）
            QMessageBox::Ok         // 按钮类型（仅确定按钮）
            );
        return;
    }
}


void MainWindow::on_pushButton_sendVoice_clicked()
{
    r1.voiceData = ui->textEdit->toPlainText();
    r1.uartTranVoiceData();
    if(sendUint8Data(r1.dataSend,r1.sendlenth)==-1)
    {
        QMessageBox::critical(
            nullptr,                // 父窗口（nullptr表示无父窗口，居中显示）
            "错误",                 // 弹窗标题
            "请检查串口连接",          // 错误内容（支持换行\n）
            QMessageBox::Ok         // 按钮类型（仅确定按钮）
            );
        return;
    }
}


void MainWindow::on_pushButton_toolSet_clicked()
{
    r1.uartTranToolData(1);
    if(sendUint8Data(r1.dataSend,r1.sendlenth)==-1)
    {
        QMessageBox::critical(
            nullptr,                // 父窗口（nullptr表示无父窗口，居中显示）
            "错误",                 // 弹窗标题
            "请检查串口连接",          // 错误内容（支持换行\n）
            QMessageBox::Ok         // 按钮类型（仅确定按钮）
            );
        return;
    }
}


void MainWindow::on_pushButton_toolReset_clicked()
{
    r1.uartTranToolData(0);
    if(sendUint8Data(r1.dataSend,r1.sendlenth)==-1)
    {
        QMessageBox::critical(
            nullptr,                // 父窗口（nullptr表示无父窗口，居中显示）
            "错误",                 // 弹窗标题
            "请检查串口连接",          // 错误内容（支持换行\n）
            QMessageBox::Ok         // 按钮类型（仅确定按钮）
            );
        return;
    }
}

