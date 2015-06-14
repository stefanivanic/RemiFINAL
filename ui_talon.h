/********************************************************************************
** Form generated from reading UI file 'talon.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALON_H
#define UI_TALON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Talon
{
public:
    QLabel *label;

    void setupUi(QWidget *Talon)
    {
        if (Talon->objectName().isEmpty())
            Talon->setObjectName(QStringLiteral("Talon"));
        Talon->resize(71, 101);
        Talon->setStyleSheet(QLatin1String("Talon {\n"
"	border: 3px solid black;\n"
"}"));
        label = new QLabel(Talon);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 71, 101));
        label->setStyleSheet(QLatin1String("#label {\n"
"	border: 1px solid black;\n"
"	border-image: url(\"./slike/Teme/2_talon.jpg\");\n"
"}"));

        retranslateUi(Talon);

        QMetaObject::connectSlotsByName(Talon);
    } // setupUi

    void retranslateUi(QWidget *Talon)
    {
        Talon->setWindowTitle(QApplication::translate("Talon", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Talon: public Ui_Talon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALON_H
