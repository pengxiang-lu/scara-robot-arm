/********************************************************************************
** Form generated from reading UI file 'AngleSlider.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANGLESLIDER_H
#define UI_ANGLESLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QSpinBox *spinBox;
    QSlider *horizontalSlider;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(400, 300);
        spinBox = new QSpinBox(Form);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(300, 30, 80, 30));
        spinBox->setMinimumSize(QSize(80, 30));
        horizontalSlider = new QSlider(Form);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(60, 40, 221, 21));
        horizontalSlider->setStyleSheet(QString::fromUtf8("/* \346\260\264\345\271\263\346\273\221\346\235\241\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QSlider::horizontal {\n"
"    height: 6px; /* \350\275\250\351\201\223\351\253\230\345\272\246 */\n"
"    margin: 5px 0; /* \344\270\212\344\270\213\345\244\226\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"/* \346\260\264\345\271\263\346\273\221\346\235\241\350\275\250\351\201\223\346\240\267\345\274\217 */\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #bbb; /* \350\275\250\351\201\223\350\276\271\346\241\206 */\n"
"    background: #f0f0f0; /* \350\275\250\351\201\223\350\203\214\346\231\257\350\211\262 */\n"
"    height: 6px; /* \350\275\250\351\201\223\351\253\230\345\272\246 */\n"
"    border-radius: 3px; /* \350\275\250\351\201\223\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"/* \346\260\264\345\271\263\346\273\221\346\235\241\345\267\262\345\241\253\345\205\205\351\203\250\345\210\206\357\274\210\346\273\221\345\235\227\345\267\246\344\276\247\357\274\211 */\n"
"QSlider::sub-page:horizontal {\n"
""
                        "    background: #4a90e2; /* \345\267\262\345\241\253\345\205\205\351\203\250\345\210\206\351\242\234\350\211\262 */\n"
"    border-radius: 2px; /* \345\234\206\350\247\222 */\n"
"}\n"
"\n"
"/* \346\260\264\345\271\263\346\273\221\346\235\241\346\273\221\345\235\227\346\240\267\345\274\217\357\274\210\346\255\243\345\270\270\347\212\266\346\200\201\357\274\211 */\n"
"QSlider::handle:horizontal {\n"
"    background: white; /* \346\273\221\345\235\227\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid #999; /* \346\273\221\345\235\227\350\276\271\346\241\206 */\n"
"    width: 18px; /* \346\273\221\345\235\227\345\256\275\345\272\246 */\n"
"    height: 18px; /* \346\273\221\345\235\227\351\253\230\345\272\246 */\n"
"    margin: -6px 0; /* \350\260\203\346\225\264\346\273\221\345\235\227\344\275\215\347\275\256\357\274\210\344\275\277\345\205\266\350\266\205\345\207\272\350\275\250\351\201\223\357\274\211 */\n"
"    border-radius: 9px; /* \345\234\206\345\275\242\346\273\221\345\235\227 */\n"
"}\n"
"\n"
""
                        "/* \346\273\221\345\235\227\346\202\254\345\201\234\347\212\266\346\200\201 */\n"
"QSlider::handle:horizontal:hover {\n"
"    background: #f5f5f5;\n"
"    border-color: #666;\n"
"}\n"
"\n"
"/* \346\273\221\345\235\227\346\214\211\344\270\213\347\212\266\346\200\201 */\n"
"QSlider::handle:horizontal:pressed {\n"
"    background: #e0e0e0;\n"
"    border-color: #333;\n"
"}"));
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANGLESLIDER_H
