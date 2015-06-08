#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H

#include "card.h"
#include <QMouseEvent>
#include <QDebug>
#include <chrono>

namespace Ui {
class CardContainer;
}

class CardContainer : public QWidget
{
    Q_OBJECT

public:
    explicit CardContainer(QWidget *parent = 0,
                           int x = 0, int y = 0,
                           int w = 0, int h = 0);
    virtual ~CardContainer() = 0;

    void addCard(Card* card1, bool background);
    bool isInArea();
    QVector<Card*> getCards();

    void refreshDepth();
    Card* getLastCard();

    bool isCardTargeted(QObject* target);

    QString printCards();

    // overloudujemo sta treba za drag n drop
//    void mousePressEvent(QMouseEvent* event);
//    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

protected:
    Ui::CardContainer *ui;

    QVector<Card*> cards;

    QPoint position;

    int width;
    int height;
};

#endif // CARDCONTAINER_H
