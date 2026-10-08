#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "roboticarm.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void uiInit();
    void deviceStateShow(int state);
    void serialInit();
    int serialOpen();
    void serialClose();
    void updateSerialPortList();
    int sendUint8Data(char *data, int length);
    int sendAllCommands(QString fullCmd);
    void onJointValueChanged(int value);
    void onCartesianValueChanged(int value);
    bool realTimeSendFlag;
    QSerialPort*serial;
    QString portName;
    RoboticArm r1;           // 创建r1机械臂

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_sendAxis_clicked();

    void on_pushButton_sendVoice_clicked();

    void on_pushButton_toolSet_clicked();

    void on_pushButton_toolReset_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
