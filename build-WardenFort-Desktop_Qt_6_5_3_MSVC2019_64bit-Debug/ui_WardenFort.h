/********************************************************************************
** Form generated from reading UI file 'WardenFort.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARDENFORT_H
#define UI_WARDENFORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WardenFort
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;
    QFrame *frame_4;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *WardenFort)
    {
        if (WardenFort->objectName().isEmpty())
            WardenFort->setObjectName("WardenFort");
        WardenFort->resize(1088, 562);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WardenFort->sizePolicy().hasHeightForWidth());
        WardenFort->setSizePolicy(sizePolicy);
        WardenFort->setMinimumSize(QSize(1088, 562));
        WardenFort->setMaximumSize(QSize(1088, 562));
        WardenFort->setCursor(QCursor(Qt::ArrowCursor));
        WardenFort->setStyleSheet(QString::fromUtf8(""));
        WardenFort->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(WardenFort);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 20, 221, 521));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 60, 75);\n"
"border-radius: 10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 200, 221, 321));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(63, 93, 128);\n"
"border-radius: 10px;\n"
"border-top-left-radius: 25px;\n"
"border-top-right-radius: 25px;\n"
"border-bottom-left-radius: 10px;\n"
"border-bottom-right-radius: 10px;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(270, 20, 141, 106));
        frame_3->setMinimumSize(QSize(141, 106));
        frame_3->setMaximumSize(QSize(141, 106));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 60, 75);\n"
"border-radius: 10px;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(430, 20, 141, 106));
        frame_4->setMinimumSize(QSize(141, 106));
        frame_4->setMaximumSize(QSize(141, 106));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(44, 60, 75);\n"
"border-radius: 10px;"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(270, 160, 701, 22));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 230, 701, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 260, 701, 231));
        WardenFort->setCentralWidget(centralwidget);

        retranslateUi(WardenFort);

        QMetaObject::connectSlotsByName(WardenFort);
    } // setupUi

    void retranslateUi(QMainWindow *WardenFort)
    {
        WardenFort->setWindowTitle(QCoreApplication::translate("WardenFort", "WardenFort", nullptr));
        label->setText(QCoreApplication::translate("WardenFort", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("WardenFort", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WardenFort: public Ui_WardenFort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARDENFORT_H
