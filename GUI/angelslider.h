#ifndef ANGELSLIDER_H
#define ANGELSLIDER_H

#include <QWidget>

namespace Ui {
class AngelSlider;
}

class AngelSlider : public QWidget
{
    Q_OBJECT

public:
    explicit AngelSlider(QWidget *parent = nullptr);
    ~AngelSlider();
    int getNum();
    void setNum(int num);
    void setMaxMin(int min,int max);
signals:
    // 定义自定义信号，例如当spinBox值变化时触发
    void valueChanged(int value);  // 信号参数为变化后的值
private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::AngelSlider *ui;
};

#endif // ANGELSLIDER_H
