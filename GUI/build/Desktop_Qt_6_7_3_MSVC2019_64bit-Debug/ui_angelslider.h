/********************************************************************************
** Form generated from reading UI file 'angelslider.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANGELSLIDER_H
#define UI_ANGELSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AngelSlider
{
public:
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;

    void setupUi(QWidget *AngelSlider)
    {
        if (AngelSlider->objectName().isEmpty())
            AngelSlider->setObjectName("AngelSlider");
        AngelSlider->resize(461, 49);
        horizontalLayout = new QHBoxLayout(AngelSlider);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSlider = new QSlider(AngelSlider);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMinimumSize(QSize(0, 30));
        horizontalSlider->setMaximumSize(QSize(16777215, 25));
        horizontalSlider->setStyleSheet(QString::fromUtf8("/* \346\260\264\345\271\263\346\273\221\346\235\241\346\225\264\344\275\223\345\256\271\345\231\250 */\n"
"QSlider::horizontal {\n"
"    height: 12px;\n"
"    margin: 8px 0;\n"
"}\n"
"\n"
"/* \346\273\221\346\235\241\350\275\250\351\201\223\357\274\210\346\234\252\351\200\211\344\270\255\351\203\250\345\210\206\357\274\211 */\n"
"QSlider::groove:horizontal {\n"
"    background-color: #f0f0f0;\n"
"    border-radius: 6px;\n"
"    height: 6px;\n"
"}\n"
"\n"
"/* \346\273\221\346\235\241\345\267\262\351\200\211\344\270\255\351\203\250\345\210\206 */\n"
"QSlider::sub-page:horizontal {\n"
"    background-color: #409eff;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"/* \346\273\221\345\235\227\346\240\267\345\274\217\357\274\210\346\255\243\345\270\270\347\212\266\346\200\201\357\274\211 */\n"
"QSlider::handle:horizontal {\n"
"    background-color: white;\n"
"    border: 2px solid #409eff;\n"
"    width: 10px;\n"
"    height: 10px;\n"
"    margin: -7px 0; /* \345\261\205\344\270\255\350\275\250\351\201\223 */\n"
"    bor"
                        "der-radius: 4px;\n"
"}\n"
"\n"
"/* \346\273\221\345\235\227\346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\347\224\250\350\276\271\346\241\206\345\212\240\347\262\227\346\233\277\344\273\243\346\224\276\345\244\247\357\274\211 */\n"
"QSlider::handle:horizontal:hover {\n"
"    background-color: #f0f7ff;\n"
"    border-width: 3px; /* \346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\345\217\230\347\262\227\357\274\214\350\247\206\350\247\211\344\270\212\346\224\276\345\244\247 */\n"
"}\n"
"\n"
"/* \346\273\221\345\235\227\346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\347\224\250\351\242\234\350\211\262\345\212\240\346\267\261\346\233\277\344\273\243\347\274\251\345\260\217\357\274\211 */\n"
"QSlider::handle:horizontal:pressed {\n"
"    background-color: #e6f7ff;\n"
"    border-color: #1890ff; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QSlider:disabled {\n"
"    QSlid"
                        "er::groove:horizontal {\n"
"        background-color: #f5f5f5;\n"
"    }\n"
"    QSlider::sub-page:horizontal {\n"
"        background-color: #d9d9d9;\n"
"    }\n"
"    QSlider::handle:horizontal {\n"
"        background-color: white;\n"
"        border-color: #d9d9d9;\n"
"    }\n"
"}"));
        horizontalSlider->setMaximum(180);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        spinBox = new QSpinBox(AngelSlider);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimumSize(QSize(80, 30));
        spinBox->setMaximumSize(QSize(80, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(10);
        spinBox->setFont(font);
        spinBox->setStyleSheet(QString::fromUtf8(""));
        spinBox->setFrame(true);
        spinBox->setKeyboardTracking(false);
        spinBox->setMaximum(180);

        horizontalLayout->addWidget(spinBox);


        retranslateUi(AngelSlider);

        QMetaObject::connectSlotsByName(AngelSlider);
    } // setupUi

    void retranslateUi(QWidget *AngelSlider)
    {
        AngelSlider->setWindowTitle(QCoreApplication::translate("AngelSlider", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AngelSlider: public Ui_AngelSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANGELSLIDER_H
