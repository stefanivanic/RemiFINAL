/********************************************************************************
** Form generated from reading UI file 'choosecards.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSECARDS_H
#define UI_CHOOSECARDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ChooseCards
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChooseCards)
    {
        if (ChooseCards->objectName().isEmpty())
            ChooseCards->setObjectName(QStringLiteral("ChooseCards"));
        ChooseCards->resize(799, 314);
        buttonBox = new QDialogButtonBox(ChooseCards);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(410, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ChooseCards);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooseCards, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooseCards, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseCards);
    } // setupUi

    void retranslateUi(QDialog *ChooseCards)
    {
        ChooseCards->setWindowTitle(QApplication::translate("ChooseCards", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ChooseCards: public Ui_ChooseCards {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSECARDS_H
