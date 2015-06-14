/********************************************************************************
** Form generated from reading UI file 'playercontainer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERCONTAINER_H
#define UI_PLAYERCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerContainer
{
public:

    void setupUi(QWidget *PlayerContainer)
    {
        if (PlayerContainer->objectName().isEmpty())
            PlayerContainer->setObjectName(QStringLiteral("PlayerContainer"));
        PlayerContainer->resize(355, 104);
        PlayerContainer->setAutoFillBackground(false);

        retranslateUi(PlayerContainer);

        QMetaObject::connectSlotsByName(PlayerContainer);
    } // setupUi

    void retranslateUi(QWidget *PlayerContainer)
    {
        PlayerContainer->setWindowTitle(QApplication::translate("PlayerContainer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayerContainer: public Ui_PlayerContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERCONTAINER_H
