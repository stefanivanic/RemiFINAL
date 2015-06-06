#ifndef CHOOSECARDS_H
#define CHOOSECARDS_H

#include <QDialog>
#include <QCheckBox>

#include "card.h"

namespace Ui {
class ChooseCards;
}

class ChooseCards : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCards(QWidget *parent = 0);
    ~ChooseCards();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseCards *ui;

    QVector<QCheckBox*> boxes;
};

#endif // CHOOSECARDS_H
