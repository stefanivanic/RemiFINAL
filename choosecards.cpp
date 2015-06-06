#include "choosecards.h"
#include "ui_choosecards.h"

#include <QMetaEnum>

ChooseCards::ChooseCards(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCards)
{
    ui->setupUi(this);
    this->setStyleSheet(QStringLiteral("border-image: url(./slike/default/dark_wood.jpg);"));

    const QMetaObject &mo = Card::staticMetaObject;
    int index = mo.indexOfEnumerator("Sign"); // watch out during refactorings
    QMetaEnum metaEnum = mo.enumerator(index);

    // We can then use the QMetaEnum object as follows:
    // first, let's convert from an enum value to a string
    Card::Sign q = Card::KARO;
    QByteArray str = metaEnum.valueToKey(q);
    // str now contains "Student"

    for(int i=0; i<2; i++){
        for(int j=1; j<15; j++){
            if(j==11) continue;

            boxes.append(new QCheckBox( QString::number(j) + "K", this));
            boxes.back()->move(0, 20*j);
            boxes.append(new QCheckBox( QString::number(j) + "P", this));
            boxes.back()->move(50, 20*j);
            boxes.append(new QCheckBox( QString::number(j) + "T", this));
            boxes.back()->move(100, 20*j);
            boxes.append(new QCheckBox( QString::number(j) + "H", this));
            boxes.back()->move(150, 20*j);
        }
    }

    for(int i=0; i<4; i++) {
        boxes.append(new QCheckBox( QString("J"), this));
        boxes.back()->move(50*i, 0);
    }
}

ChooseCards::~ChooseCards()
{
    delete ui;
}

void ChooseCards::on_buttonBox_accepted()
{
    qDebug() << "kliknuto na ok";

    QVector<QString> cardNames;
    for(QCheckBox* chb : boxes) {
        if(chb->isChecked())
            cardNames.append(chb->text());
    }

    for(QString s : cardNames)
        qDebug() << s;

    emit cardsPreorderd(cardNames);
}
