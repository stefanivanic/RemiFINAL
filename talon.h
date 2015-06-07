#ifndef TALON_H
#define TALON_H

#include "cardcontainer.h"

namespace Ui {
class Talon;
}

class Talon : public CardContainer
{
    Q_OBJECT

public:
    Talon(QWidget *parent, int x, int y, int w, int h);

    void printCards();
private:

protected:
    Ui::Talon *ui;
};


#endif // TALON_H
