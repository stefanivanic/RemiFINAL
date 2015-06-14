/********************************************************************************
** Form generated from reading UI file 'deck.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECK_H
#define UI_DECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Deck
{
public:

    void setupUi(QWidget *Deck)
    {
        if (Deck->objectName().isEmpty())
            Deck->setObjectName(QStringLiteral("Deck"));
        Deck->resize(177, 145);

        retranslateUi(Deck);

        QMetaObject::connectSlotsByName(Deck);
    } // setupUi

    void retranslateUi(QWidget *Deck)
    {
        Deck->setWindowTitle(QApplication::translate("Deck", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Deck: public Ui_Deck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECK_H
