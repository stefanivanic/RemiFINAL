#include "choosecards.h"
#include "ui_choosecards.h"

#include <QMetaEnum>

ChooseCards::ChooseCards(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCards)
{
    ui->setupUi(this);

    for(int i=0; i<2; i++){
        for(int j=1; j<15; j++){
            if(j==11) continue;

            const QMetaObject &mo = Card::staticMetaObject;
            int index = mo.indexOfEnumerator("Sign"); // watch out during refactorings
            QMetaEnum metaEnum = mo.enumerator(index);

           // We can then use the QMetaEnum object as follows:

            // first, let's convert from an enum value to a string
            Sign q = Sign::TREF;
            QByteArray str = metaEnum.valueToKey(q);
            // str now contains "Student"

            boxes.append(new QCheckBox( QString::number(j) + str, this));
                                        /*)
            addCard(new Card(parentWidget(), j,j, TREF), false);
            addCard(new Card(parentWidgt(), j,j, PIK) , false);
            addCard(new Card(parentWidget(), j,j, HERC), false);
                                        */
        }
    }
    for(int i=0; i<4; i++);
        //addCard(new Card(parentWidget(), 0,0, JOKER), false);
}

ChooseCards::~ChooseCards()
{
    delete ui;
}

void ChooseCards::on_buttonBox_accepted()
{
    for(QCheckBox* chb : boxes)
        qDebug() << chb->isChecked();
}
