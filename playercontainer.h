#ifndef PLAYERCONTAINER_H
#define PLAYERCONTAINER_H

#include "cardcontainer.h"
#include "group.h"

namespace Ui {
class PlayerContainer;
}

class PlayerContainer : public CardContainer
{
    Q_OBJECT

public:
    PlayerContainer(QWidget *parent = 0,
                    int x = 0, int y = 0,
                    int w = 0, int h = 0);

    void addCard(Card* card, bool background);
    void removeCard();

    // overloudujemo(ili overrajdujemo, nauci da razlikujes)
    // sta treba za drag n drop
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void resolveMouseEvent(QMouseEvent* event);

    unsigned handSize()         const { return cards.size(); }
    int      getTempCardPos()   const { return tempCardPosition;}
    Card*    getTempCard()      const { return cards[tempCardPosition]; }

    void deleteCardsFromGroup();

    Group* group;
    void refreshCardsPosition();

    bool alreadyOpened;

signals:
    void onPositionChange(); // nesrecno ime
    void onThrowCard     ();
    void onAddingCardtoGroup();
    void onEmptyGroup(bool); // nesto nije u redu ovde

private:
    const int cardDistance =
            20; // rastojanje izmedju karata u ruci

    // za 'animaciju' prilikom pomeranja redosleda karata
    Card*       tempCardObject;
    int         tempCardPosition;
    int         getCurrArea();
    void        shiftCards(bool right);

};


#endif // PLAYERCONTAINER_H
