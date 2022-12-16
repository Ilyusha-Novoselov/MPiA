/********************************************************************************
** Form generated from reading UI file 'paint.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINT_H
#define UI_PAINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Paint
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *Paint)
    {
        if (Paint->objectName().isEmpty())
            Paint->setObjectName(QString::fromUtf8("Paint"));
        Paint->resize(958, 657);
        graphicsView = new QGraphicsView(Paint);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(9, 50, 941, 461));
        pushButton = new QPushButton(Paint);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 540, 156, 51));
        pushButton_2 = new QPushButton(Paint);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 540, 156, 51));
        pushButton_3 = new QPushButton(Paint);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(310, 540, 161, 51));
        pushButton_4 = new QPushButton(Paint);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 600, 461, 41));
        pushButton_5 = new QPushButton(Paint);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(490, 600, 461, 41));
        pushButton_6 = new QPushButton(Paint);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(720, 540, 231, 51));
        pushButton_7 = new QPushButton(Paint);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(490, 540, 235, 51));
        label = new QLabel(Paint);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 510, 241, 21));
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(Paint);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(610, 510, 241, 21));
        label_2->setTextFormat(Qt::AutoText);
        pushButton_8 = new QPushButton(Paint);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(10, 10, 470, 35));
        pushButton_9 = new QPushButton(Paint);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(480, 10, 470, 35));
        label_3 = new QLabel(Paint);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 520, 161, 20));
        label_4 = new QLabel(Paint);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(790, 520, 161, 20));

        retranslateUi(Paint);

        QMetaObject::connectSlotsByName(Paint);
    } // setupUi

    void retranslateUi(QWidget *Paint)
    {
        Paint->setWindowTitle(QApplication::translate("Paint", "Paint", nullptr));
        pushButton->setText(QApplication::translate("Paint", " \320\242\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272", nullptr));
        pushButton_2->setText(QApplication::translate("Paint", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \321\202\320\276\321\207\320\272\320\260", nullptr));
        pushButton_3->setText(QApplication::translate("Paint", "\320\232\320\276\320\275\320\265\321\207\320\275\320\260\321\217 \321\202\320\276\321\207\320\272\320\260", nullptr));
        pushButton_4->setText(QApplication::translate("Paint", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\277\321\203\321\202\321\214", nullptr));
        pushButton_5->setText(QApplication::translate("Paint", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", nullptr));
        pushButton_6->setText(QApplication::translate("Paint", "\320\232\320\276\320\273-\320\262\320\276 \321\202\320\276\321\207\320\265\320\272 \320\263\321\200\320\260\321\204\320\260", nullptr));
        pushButton_7->setText(QApplication::translate("Paint", "\320\232\320\276\320\273-\320\262\320\276 \321\200\320\265\320\261\320\265\321\200 \320\262\320\265\321\200\321\210\320\270\320\275\321\213", nullptr));
        label->setText(QApplication::translate("Paint", "                        \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \321\201\321\206\320\265\320\275\321\213", nullptr));
        label_2->setText(QApplication::translate("Paint", "                       \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\263\321\200\320\260\321\204\320\260", nullptr));
        pushButton_8->setText(QApplication::translate("Paint", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_9->setText(QApplication::translate("Paint", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("Paint", "min = 3; max = 100", nullptr));
        label_4->setText(QApplication::translate("Paint", "min = 0; max = 1200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Paint: public Ui_Paint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINT_H
