/********************************************************************************
** Form generated from reading UI file 'initwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITWINDOW_H
#define UI_INITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitWindow
{
public:
    QWidget *buttonWidget;
    QPushButton *pushButtonCreate;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonExit;
    QLineEdit *inputIp;
    QLineEdit *inputPort;

    void setupUi(QDialog *InitWindow)
    {
        if (InitWindow->objectName().isEmpty())
            InitWindow->setObjectName(QStringLiteral("InitWindow"));
        InitWindow->resize(580, 376);
        InitWindow->setStyleSheet(QLatin1String("#InitWindow {\n"
"}"));
        buttonWidget = new QWidget(InitWindow);
        buttonWidget->setObjectName(QStringLiteral("buttonWidget"));
        buttonWidget->setGeometry(QRect(0, 0, 581, 381));
        buttonWidget->setStyleSheet(QLatin1String("#buttonWidget{\n"
"	border-image: url(\"./slike/Teme/2_init.jpg\");\n"
"}"));
        pushButtonCreate = new QPushButton(buttonWidget);
        pushButtonCreate->setObjectName(QStringLiteral("pushButtonCreate"));
        pushButtonCreate->setGeometry(QRect(170, 80, 241, 51));
        pushButtonCreate->setStyleSheet(QLatin1String("#pushButtonCreate {\n"
"	border: 1px solid back;\n"
"	border-image: url(\"./slike/Teme/2_create.jpg\");\n"
"}"));
        pushButtonLoad = new QPushButton(buttonWidget);
        pushButtonLoad->setObjectName(QStringLiteral("pushButtonLoad"));
        pushButtonLoad->setGeometry(QRect(170, 160, 241, 51));
        pushButtonLoad->setStyleSheet(QLatin1String("#pushButtonLoad {\n"
"	border: 1px solid back;\n"
"    border-image: url(\"./slike/Teme/2_load.jpg\");\n"
"}"));
        pushButtonExit = new QPushButton(buttonWidget);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(170, 300, 241, 51));
        pushButtonExit->setStyleSheet(QLatin1String("#pushButtonExit {\n"
"	border: 1px solid back;\n"
"	border-image: url(\"./slike/Teme/2_exit.jpg\");\n"
"}"));
        inputIp = new QLineEdit(buttonWidget);
        inputIp->setObjectName(QStringLiteral("inputIp"));
        inputIp->setGeometry(QRect(170, 220, 113, 20));
        inputPort = new QLineEdit(buttonWidget);
        inputPort->setObjectName(QStringLiteral("inputPort"));
        inputPort->setGeometry(QRect(170, 250, 113, 20));

        retranslateUi(InitWindow);

        QMetaObject::connectSlotsByName(InitWindow);
    } // setupUi

    void retranslateUi(QDialog *InitWindow)
    {
        InitWindow->setWindowTitle(QApplication::translate("InitWindow", "Remi", 0));
        pushButtonCreate->setText(QString());
        pushButtonLoad->setText(QString());
        pushButtonExit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InitWindow: public Ui_InitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITWINDOW_H
