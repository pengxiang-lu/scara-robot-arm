/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <angelslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_open;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBox_port;
    QPushButton *pushButton_close;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_refresh;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QTextEdit *textEdit;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_toolReset;
    QPushButton *pushButton_sendAxis;
    AngelSlider *widget_y;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    AngelSlider *widget_z;
    AngelSlider *widget_x;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *pushButton_sendVoice;
    QPushButton *pushButton_toolSet;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(708, 582);
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(16777215, 150));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font1.setBold(true);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QString::fromUtf8("/* GroupBox\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QGroupBox {\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257\357\274\214\350\236\215\345\205\245\346\225\264\344\275\223 */\n"
"    border: 2px solid #ddd; /* \346\265\205\347\201\260\350\276\271\346\241\206\357\274\214\344\270\216\344\270\213\346\213\211\346\241\206\350\276\271\346\241\206\344\270\200\350\207\264 */\n"
"    border-radius: 4px; /* \347\273\237\344\270\200\345\234\206\350\247\222 */\n"
"    margin-top: 8px; /* \351\241\266\351\203\250\351\242\204\347\225\231\346\240\207\351\242\230\347\251\272\351\227\264 */\n"
"    padding: 16px 8px 8px 8px; /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\345\217\263\344\270\213\345\267\246\357\274\211 */\n"
"    color: #333333; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    font-size: 20px;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QGroupBox:disabled {\n"
"    "
                        "border-color: blue; /* \346\233\264\346\265\205\347\232\204\350\276\271\346\241\206 */\n"
"    color: #999999; /* \347\246\201\347\224\250\346\226\207\345\255\227\350\211\262 */\n"
"}\n"
"\n"
"/* \345\270\246\346\240\207\351\242\230\347\232\204GroupBox\346\277\200\346\264\273\347\212\266\346\200\201\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QGroupBox:checked {\n"
"    border-color: #4a90e2; /* \346\277\200\346\264\273\346\227\266\350\276\271\346\241\206\347\224\250\344\270\273\350\211\262 */\n"
"}\n"
"\n"
"/* \346\277\200\346\264\273\347\212\266\346\200\201\347\232\204\346\240\207\351\242\230\357\274\210\345\217\257\351\200\211\357\274\214\347\224\250\344\272\216\345\270\246\345\244\215\351\200\211\346\241\206\347\232\204GroupBox\357\274\211 */\n"
"QGroupBox:checked::title {\n"
"    color: #4a90e2; /* \346\277\200\346\264\273\346\227\266\346\240\207\351\242\230\347\224\250\344\270\273\350\211\262 */\n"
"}"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 3, 1, 1);

        pushButton_open = new QPushButton(groupBox);
        pushButton_open->setObjectName("pushButton_open");
        pushButton_open->setMinimumSize(QSize(70, 30));
        pushButton_open->setMaximumSize(QSize(70, 30));
        pushButton_open->setFont(font1);
        pushButton_open->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout->addWidget(pushButton_open, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        comboBox_port = new QComboBox(groupBox);
        comboBox_port->setObjectName("comboBox_port");
        comboBox_port->setMinimumSize(QSize(128, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font2.setBold(false);
        comboBox_port->setFont(font2);
        comboBox_port->setStyleSheet(QString::fromUtf8("/* \344\270\213\346\213\211\346\241\206\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QComboBox {\n"
"    background-color: white;      /* \347\231\275\350\211\262\350\203\214\346\231\257 */\n"
"    color: #333333;               /* \346\267\261\347\201\260\346\226\207\345\255\227 */\n"
"    border-radius: 6px;           /* \347\273\237\344\270\200\345\234\206\350\247\222 */\n"
"    border: 1px solid #ddd;       /* \346\265\205\347\201\260\350\276\271\346\241\206 */\n"
"    padding: 6px 30px 6px 16px;   /* \345\206\205\350\276\271\350\267\235\357\274\210\351\242\204\347\225\231\347\256\255\345\244\264\347\251\272\351\227\264\357\274\211 */\n"
"    font-size: 14px;              /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"    min-width: 80px;             /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\346\241\206\346\202\254\345\201\234\347\212\266\346\200\201 */\n"
"QComboBox:hover {\n"
"    border-color: #4a90e2;        /* \350\276\271\346"
                        "\241\206\345\217\230\344\270\273\350\211\262\357\274\210\344\270\216\346\214\211\351\222\256hover\345\221\274\345\272\224\357\274\211 */\n"
"    background-color: #f9f9f9;    /* \350\275\273\345\276\256\347\201\260\350\260\203 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\346\241\206\350\242\253\346\277\200\346\264\273\357\274\210\345\261\225\345\274\200\346\227\266\357\274\211 */\n"
"QComboBox:on {\n"
"    border-color: #4a90e2;        /* \346\277\200\346\264\273\347\212\266\346\200\201\350\276\271\346\241\206\350\211\262 */\n"
"    background-color: #f5f5f5;    /* \347\250\215\346\232\227\350\203\214\346\231\257 */\n"
"    border-radius: 6px 6px 0 0;   /* \351\241\266\351\203\250\344\277\235\346\214\201\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\346\241\206\347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QComboBox:disabled {\n"
"    background-color: #f5f5f5;    /* \347\246\201\347\224\250\350\203\214\346\231\257 */\n"
"    color: #999999;               /* \347\246\201\347\224"
                        "\250\346\226\207\345\255\227\350\211\262 */\n"
"    border-color: #eee;           /* \347\246\201\347\224\250\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\347\256\255\345\244\264\346\240\267\345\274\217 */\n"
"QComboBox::down-arrow {\n"
"    image: url(:/icons/gray_arrow.png); /* \347\201\260\350\211\262\347\256\255\345\244\264\357\274\210\345\217\257\346\233\277\346\215\242\344\270\272\346\267\261\350\211\262\345\233\276\346\240\207\357\274\211 */\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* \347\256\255\345\244\264\345\214\272\345\237\237 */\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257\357\274\214\344\270\216\344\270\273\345\214\272\345\237\237\350\236\215\345\220\210 */\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\345\210\227\350\241\250\346\241\206\346\240\267\345\274\217 */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;      /* \345\210"
                        "\227\350\241\250\347\231\275\350\211\262\350\203\214\346\231\257 */\n"
"    color: #333;                  /* \345\210\227\350\241\250\346\226\207\345\255\227\350\211\262 */\n"
"    border: 1px solid #ddd;       /* \345\210\227\350\241\250\350\276\271\346\241\206 */\n"
"    border-top: none;             /* \344\270\216\344\270\213\346\213\211\346\241\206\350\241\224\346\216\245\345\244\204\346\227\240\350\276\271\346\241\206 */\n"
"    border-radius: 0 0 6px 6px;   /* \345\272\225\351\203\250\345\234\206\350\247\222 */\n"
"    padding: 4px;\n"
"    selection-background-color: #4a90e2; /* \351\200\211\344\270\255\351\241\271\344\270\273\350\211\262\350\203\214\346\231\257 */\n"
"    selection-color: white;       /* \351\200\211\344\270\255\351\241\271\346\226\207\345\255\227\347\231\275 */\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* \345\210\227\350\241\250\351\241\271\346\202\254\345\201\234 */\n"
"QComboBox QAbstractItemView::item:hover {\n"
"    background-color: #f0f5ff;    /* \346\265\205\350\223\235\346\202"
                        "\254\345\201\234\350\211\262 */\n"
"}\n"
"\n"
"/* \345\210\227\350\241\250\351\241\271\351\200\211\344\270\255\344\275\206\346\234\252\346\277\200\346\264\273 */\n"
"QComboBox QAbstractItemView::item:selected:!active {\n"
"    background-color: #e6f0ff;    /* \347\250\215\346\265\205\347\232\204\351\200\211\344\270\255\350\211\262 */\n"
"}"));

        gridLayout->addWidget(comboBox_port, 0, 2, 1, 1);

        pushButton_close = new QPushButton(groupBox);
        pushButton_close->setObjectName("pushButton_close");
        pushButton_close->setMinimumSize(QSize(70, 30));
        pushButton_close->setMaximumSize(QSize(70, 30));
        pushButton_close->setFont(font1);
        pushButton_close->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout->addWidget(pushButton_close, 0, 8, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 7, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("/* \345\237\272\347\241\200\350\223\235\350\211\262\345\255\227\344\275\223Label */\n"
"QLabel {\n"
"    color: #4a90e2; /* \344\270\273\350\211\262\350\260\203\350\223\235\350\211\262\357\274\210\344\270\216\344\271\213\345\211\215\346\216\247\344\273\266\344\272\244\344\272\222\350\211\262\344\270\200\350\207\264\357\274\211 */\n"
"    font-size: 16px; /* \347\273\237\344\270\200\346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"    padding: 4px 6px; /* \350\275\273\345\276\256\345\206\205\350\276\271\350\267\235 */\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257\357\274\214\344\270\215\347\240\264\345\235\217\345\270\203\345\261\200 */\n"
"	font-weight: bold\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201\357\274\210\350\223\235\350\211\262\345\217\230\346\265\205\347\201\260\357\274\211 */\n"
"QLabel:disabled {\n"
"    color: #b3c8e8; /* \347\246\201\347\224\250\346\227\266\347\232\204\346\265\205\350\223\235\347\201\260\350\211\262 */\n"
""
                        "}\n"
"\n"
"/* \351\223\276\346\216\245\346\240\267\345\274\217\357\274\210\345\212\240\346\267\261\350\223\235\350\211\262\357\274\211 */\n"
"QLabel::link {\n"
"    color: #3a80d2; /* \346\257\224\346\231\256\351\200\232\346\226\207\345\255\227\346\233\264\346\267\261\347\232\204\350\223\235\350\211\262 */\n"
"    text-decoration: none; /* \345\216\273\351\231\244\351\273\230\350\256\244\344\270\213\345\210\222\347\272\277 */\n"
"}\n"
"\n"
"/* \351\223\276\346\216\245\346\202\254\345\201\234 */\n"
"QLabel::link:hover {\n"
"    color: #2a70c2; /* \346\202\254\345\201\234\346\227\266\346\233\264\346\267\261\347\232\204\350\223\235\350\211\262 */\n"
"    text-decoration: underline; /* \344\270\213\345\210\222\347\272\277\346\217\220\347\244\272 */\n"
"}\n"
"\n"
"/* \345\274\272\350\260\203\345\236\213\350\223\235\350\211\262Label\357\274\210\345\217\257\351\200\232\350\277\207objectName\344\275\277\347\224\250\357\274\211 */\n"
"QLabel#highlightLabel {\n"
"    color: #2d7dcb; /* \346\233\264\346\267\261\347\232\204"
                        "\350\223\235\350\211\262 */\n"
"    font-weight: bold; /* \345\212\240\347\262\227\345\274\272\350\260\203 */\n"
"    font-size: 15px;\n"
"}\n"
"\n"
"/* \346\265\205\350\211\262\350\223\235\350\211\262Label\357\274\210\350\276\205\345\212\251\346\226\207\346\234\254\357\274\211 */\n"
"QLabel#lightLabel {\n"
"    color: #7aaae0; /* \350\276\203\346\265\205\347\232\204\350\223\235\350\211\262 */\n"
"    font-size: 13px;\n"
"}"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 9, 1, 1);

        pushButton_refresh = new QPushButton(groupBox);
        pushButton_refresh->setObjectName("pushButton_refresh");
        pushButton_refresh->setMinimumSize(QSize(70, 30));
        pushButton_refresh->setMaximumSize(QSize(70, 30));
        pushButton_refresh->setFont(font1);
        pushButton_refresh->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout->addWidget(pushButton_refresh, 0, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("/* GroupBox\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QGroupBox {\n"
"    background-color: transparent; /* \351\200\217\346\230\216\350\203\214\346\231\257\357\274\214\350\236\215\345\205\245\346\225\264\344\275\223 */\n"
"    border: 2px solid #ddd; /* \346\265\205\347\201\260\350\276\271\346\241\206\357\274\214\344\270\216\344\270\213\346\213\211\346\241\206\350\276\271\346\241\206\344\270\200\350\207\264 */\n"
"    border-radius: 4px; /* \347\273\237\344\270\200\345\234\206\350\247\222 */\n"
"    margin-top: 8px; /* \351\241\266\351\203\250\351\242\204\347\225\231\346\240\207\351\242\230\347\251\272\351\227\264 */\n"
"    padding: 16px 8px 8px 8px; /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\345\217\263\344\270\213\345\267\246\357\274\211 */\n"
"    color: #333333; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    font-size: 20px;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QGroupBox:disabled {\n"
"    "
                        "border-color: blue; /* \346\233\264\346\265\205\347\232\204\350\276\271\346\241\206 */\n"
"    color: #999999; /* \347\246\201\347\224\250\346\226\207\345\255\227\350\211\262 */\n"
"}\n"
"\n"
"/* \345\270\246\346\240\207\351\242\230\347\232\204GroupBox\346\277\200\346\264\273\347\212\266\346\200\201\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QGroupBox:checked {\n"
"    border-color: #4a90e2; /* \346\277\200\346\264\273\346\227\266\350\276\271\346\241\206\347\224\250\344\270\273\350\211\262 */\n"
"}\n"
"\n"
"/* \346\277\200\346\264\273\347\212\266\346\200\201\347\232\204\346\240\207\351\242\230\357\274\210\345\217\257\351\200\211\357\274\214\347\224\250\344\272\216\345\270\246\345\244\215\351\200\211\346\241\206\347\232\204GroupBox\357\274\211 */\n"
"QGroupBox:checked::title {\n"
"    color: #4a90e2; /* \346\277\200\346\264\273\346\227\266\346\240\207\351\242\230\347\224\250\344\270\273\350\211\262 */\n"
"}"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 4, 4, 1, 1);

        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName("textEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(30);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(250, 20));
        textEdit->setMaximumSize(QSize(16777215, 80));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(14);
        textEdit->setFont(font3);

        gridLayout_3->addWidget(textEdit, 4, 1, 3, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer, 5, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 4, 2, 1, 1);

        pushButton_toolReset = new QPushButton(groupBox_2);
        pushButton_toolReset->setObjectName("pushButton_toolReset");
        pushButton_toolReset->setMinimumSize(QSize(100, 30));
        pushButton_toolReset->setMaximumSize(QSize(100, 30));
        pushButton_toolReset->setFont(font1);
        pushButton_toolReset->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout_3->addWidget(pushButton_toolReset, 6, 5, 1, 1);

        pushButton_sendAxis = new QPushButton(groupBox_2);
        pushButton_sendAxis->setObjectName("pushButton_sendAxis");
        pushButton_sendAxis->setMinimumSize(QSize(100, 30));
        pushButton_sendAxis->setMaximumSize(QSize(100, 30));
        pushButton_sendAxis->setFont(font1);
        pushButton_sendAxis->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout_3->addWidget(pushButton_sendAxis, 4, 3, 1, 1);

        widget_y = new AngelSlider(groupBox_2);
        widget_y->setObjectName("widget_y");

        gridLayout_3->addWidget(widget_y, 1, 1, 1, 5);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setFont(font3);

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer_2, 3, 1, 1, 1);

        widget_z = new AngelSlider(groupBox_2);
        widget_z->setObjectName("widget_z");

        gridLayout_3->addWidget(widget_z, 2, 1, 1, 5);

        widget_x = new AngelSlider(groupBox_2);
        widget_x->setObjectName("widget_x");

        gridLayout_3->addWidget(widget_x, 0, 1, 1, 5);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setFont(font3);

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setFont(font3);

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setFont(font3);

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);

        pushButton_sendVoice = new QPushButton(groupBox_2);
        pushButton_sendVoice->setObjectName("pushButton_sendVoice");
        pushButton_sendVoice->setMinimumSize(QSize(100, 30));
        pushButton_sendVoice->setMaximumSize(QSize(100, 30));
        pushButton_sendVoice->setFont(font1);
        pushButton_sendVoice->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout_3->addWidget(pushButton_sendVoice, 4, 5, 1, 1);

        pushButton_toolSet = new QPushButton(groupBox_2);
        pushButton_toolSet->setObjectName("pushButton_toolSet");
        pushButton_toolSet->setMinimumSize(QSize(100, 30));
        pushButton_toolSet->setMaximumSize(QSize(100, 30));
        pushButton_toolSet->setFont(font1);
        pushButton_toolSet->setStyleSheet(QString::fromUtf8("/* \346\255\243\345\270\270\347\212\266\346\200\201\346\214\211\351\222\256 */\n"
"QPushButton {\n"
"    /* \345\237\272\347\241\200\346\240\267\345\274\217 */\n"
"    background-color: #4a90e2; /* \350\203\214\346\231\257\350\211\262 */\n"
"    color: white;              /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 6px;        /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    border: none;              /* \345\216\273\351\231\244\351\273\230\350\256\244\350\276\271\346\241\206 */\n"
"    padding: 6px 16px;         /* \345\206\205\350\276\271\350\267\235\357\274\210\344\270\212\344\270\213 \345\267\246\345\217\263\357\274\211 */\n"
"    font-size: 16px;           /* \346\226\207\345\255\227\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"/* \346\202\254\345\201\234\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\346\224\276\345\234\250\346\214\211\351\222\256\344\270\212\357\274\211 */\n"
"QPushButton:hover {\n"
"    background-color: #5b9def; /* \347\250\215"
                        "\344\272\256\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"}\n"
"\n"
"/* \346\214\211\344\270\213\347\212\266\346\200\201\357\274\210\351\274\240\346\240\207\347\202\271\345\207\273\346\214\211\351\222\256\346\227\266\357\274\211 */\n"
"QPushButton:pressed {\n"
"    background-color: #3a80d2; /* \347\250\215\346\232\227\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 7px 15px 5px 17px; /* \346\250\241\346\213\237\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"/* \347\246\201\347\224\250\347\212\266\346\200\201 */\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc; /* \347\201\260\350\211\262\350\203\214\346\231\257 */\n"
"    color: #999999;            /* \347\201\260\350\211\262\346\226\207\345\255\227 */\n"
"}\n"
"\n"
"/* \345\270\246\345\233\276\346\240\207\346\214\211\351\222\256\347\232\204\351\242\235\345\244\226\346\240\267\345\274\217\357\274\210\345\217\257\351\200\211\357\274\211 */\n"
"QPushButton[icon]:not"
                        "([text=\"\"]) {\n"
"    padding-left: 28px; /* \344\270\272\345\233\276\346\240\207\351\242\204\347\225\231\347\251\272\351\227\264 */\n"
"}"));

        gridLayout_3->addWidget(pushButton_toolSet, 6, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\200\232\344\277\241\357\274\232", nullptr));
        pushButton_open->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
        pushButton_close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\235\220\346\240\207\351\205\215\347\275\256\357\274\232", nullptr));
        pushButton_toolReset->setText(QCoreApplication::translate("MainWindow", "\346\235\276\345\274\200\347\211\251\344\275\223", nullptr));
        pushButton_sendAxis->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\235\220\346\240\207", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X\345\235\220\346\240\207\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Z\345\235\220\346\240\207\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y\345\235\220\346\240\207\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\257\255\351\237\263\346\222\255\346\212\245\357\274\232", nullptr));
        pushButton_sendVoice->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\350\257\255\351\237\263", nullptr));
        pushButton_toolSet->setText(QCoreApplication::translate("MainWindow", "\345\220\270\345\217\226\347\211\251\344\275\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
