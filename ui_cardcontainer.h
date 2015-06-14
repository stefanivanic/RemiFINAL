/********************************************************************************
** Form generated from reading UI file 'cardcontainer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDCONTAINER_H
#define UI_CARDCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardContainer
{
public:

    void setupUi(QWidget *CardContainer)
    {
        if (CardContainer->objectName().isEmpty())
            CardContainer->setObjectName(QStringLiteral("CardContainer"));
        CardContainer->resize(400, 300);
        CardContainer->setStyleSheet(QLatin1String("#Talon{\n"
"	border: 1px solid red;\n"
"}"));

        retranslateUi(CardContainer);

        QMetaObject::connectSlotsByName(CardContainer);
    } // setupUi

    void retranslateUi(QWidget *CardContainer)
    {
        CardContainer->setWindowTitle(QApplication::translate("CardContainer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CardContainer: public Ui_CardContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDCONTAINER_H
