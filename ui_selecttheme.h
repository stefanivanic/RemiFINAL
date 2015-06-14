/********************************************************************************
** Form generated from reading UI file 'selecttheme.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTTHEME_H
#define UI_SELECTTHEME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>

QT_BEGIN_NAMESPACE

class Ui_SelectTheme
{
public:
    QDialogButtonBox *buttonBox;
    QListView *listView;

    void setupUi(QDialog *SelectTheme)
    {
        if (SelectTheme->objectName().isEmpty())
            SelectTheme->setObjectName(QStringLiteral("SelectTheme"));
        SelectTheme->resize(400, 300);
        buttonBox = new QDialogButtonBox(SelectTheme);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listView = new QListView(SelectTheme);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(40, 20, 256, 181));

        retranslateUi(SelectTheme);
        QObject::connect(buttonBox, SIGNAL(accepted()), SelectTheme, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SelectTheme, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectTheme);
    } // setupUi

    void retranslateUi(QDialog *SelectTheme)
    {
        SelectTheme->setWindowTitle(QApplication::translate("SelectTheme", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectTheme: public Ui_SelectTheme {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTTHEME_H
