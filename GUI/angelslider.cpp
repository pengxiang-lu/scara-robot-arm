#include "angelslider.h"
#include "ui_angelslider.h"

AngelSlider::AngelSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AngelSlider)
{
    ui->setupUi(this);
    // QSpinBox移动,QSlider跟着移动
    void(QSpinBox::*spSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spSignal,ui->horizontalSlider,&QSlider::setValue);

    // QSlider滑动 QSpinBox数字跟着改变
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
}

AngelSlider::~AngelSlider()
{
    delete ui;
}
int AngelSlider::getNum()
{
    return ui->spinBox->value();
}
void AngelSlider::setNum(int num)
{
    ui->spinBox->setValue(num);
}
void AngelSlider::setMaxMin(int min,int max)
{
    ui->spinBox->setMaximum(max);
    ui->spinBox->setMinimum(min);
    ui->horizontalSlider->setMaximum(max);
    ui->horizontalSlider->setMinimum(min);
}
void AngelSlider::on_spinBox_valueChanged(int arg1)
{
    qDebug()<<arg1;
    emit valueChanged(arg1);
}

