/********************************************************************************
** Form generated from reading UI file 'cardtablecontainer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDTABLECONTAINER_H
#define UI_CARDTABLECONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CardTableContainer
{
public:

    void setupUi(QWidget *CardTableContainer)
    {
        if (CardTableContainer->objectName().isEmpty())
            CardTableContainer->setObjectName(QStringLiteral("CardTableContainer"));
        CardTableContainer->resize(125, 103);

        retranslateUi(CardTableContainer);

        QMetaObject::connectSlotsByName(CardTableContainer);
    } // setupUi

    void retranslateUi(QWidget *CardTableContainer)
    {
        CardTableContainer->setWindowTitle(QApplication::translate("CardTableContainer", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CardTableContainer: public Ui_CardTableContainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDTABLECONTAINER_H
