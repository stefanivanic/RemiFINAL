#include "playercontainer.h"
#include "ui_playercontainer.h"

PlayerContainer::PlayerContainer(QWidget *parent, int x, int y, int w, int h) :
    CardContainer(parent, x, y, w, h)
{
    group = new Group();
    alreadyOpened = false;
}

void PlayerContainer::refreshCardsPosition()
{
    for(int i = 0; i < cards.size(); i++)
        cards[i]->move(position.x() + i * cardDistance,
                       position.y());
}

void PlayerContainer::deleteCardsFromGroup()
{
    for(Card* c : group->getCards()) {
        for(int i = 0; i < cards.size(); i++) {
            if( c == cards[i] ) {
                cards.erase(cards.begin() + i);
                break;
            }
        }
    }
    refreshCardsPosition();

    group->clearGroup();
    emit onEmptyGroup(false);
}

void PlayerContainer::addCard(Card *card, bool background)
{
    CardContainer::addCard(card, background);
    cards.back()->move(position.x() + (cards.size() - 1) * cardDistance,
                       position.y());
}


void PlayerContainer::removeCard()
{
    cards[tempCardPosition]->hide();
    cards.erase(cards.begin() + tempCardPosition);

    refreshCardsPosition();
}

void PlayerContainer::resolveMouseEvent(QMouseEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
        mousePressEvent(event);
    if(event->type() == QEvent::MouseMove)
        mouseMoveEvent(event);
    if(event->type() == QEvent::MouseButtonRelease)
        mouseReleaseEvent(event);
}

void PlayerContainer::mousePressEvent(QMouseEvent* event)
{
    event->accept();

    tempCardPosition = getCurrArea();
    tempCardObject = cards[tempCardPosition];

    emit onPositionChange();

    if(event->button() == Qt::RightButton) {
        // vraca true ako je grupa ubacena
        if( group->addCard(tempCardObject) ) {
            tempCardObject->move(position.x() + tempCardPosition*cardDistance,
                             position.y() - 20); // npr 20 nebitno je
            emit onAddingCardtoGroup();
        }
        else {
            // remove card vraca true ako je grupa ispraznjena
            if( group->removeCard(tempCardObject) )
                emit onEmptyGroup(true);
            tempCardObject->move(position.x() + tempCardPosition*cardDistance,
                             position.y()); // npr 20 nebitno je
        }
    }
}

void PlayerContainer::mouseMoveEvent(QMouseEvent* event)
{
    event->accept();
}

void PlayerContainer::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton) {
        return;
    }

    int areaOfCurrCard = getCurrArea();

    if( tempCardObject->isLeftClick() ) {


        /*
        cards[tempCardPosition] = tempCardObject;
        cards[tempCardPosition]->
            move(position.x() + areaOfCurrCard * cardDistance,
                 position.y());
                 */

        if(areaOfCurrCard == tempCardPosition) {
            cards[areaOfCurrCard] = tempCardObject;
            cards[areaOfCurrCard]->move(position.x() + areaOfCurrCard * cardDistance,
                                        position.y());
        }
        else if( areaOfCurrCard < tempCardPosition) {
            for(int i = tempCardPosition ; i > areaOfCurrCard ; i--) {
                cards[i] = cards[i-1];
                cards[i]->move(position.x() + i * cardDistance,
                               position.y());
            }
            cards[areaOfCurrCard] = tempCardObject;
            cards[areaOfCurrCard]->move(position.x() + areaOfCurrCard * cardDistance,
                                        position.y());
        }
        else {
            for(int i = tempCardPosition ; i < areaOfCurrCard; i++) {
                cards[i] = cards[i+1];
                cards[i]->move(position.x() + i * cardDistance,
                           position.y());
            }
            cards[areaOfCurrCard] = tempCardObject;
            cards[areaOfCurrCard]->move(position.x() + areaOfCurrCard * cardDistance,
                                        position.y());
        }

        cards[tempCardPosition]->e->setOpacity(1);
        cards[tempCardPosition]->setGraphicsEffect(cards[tempCardPosition]->e);

        tempCardPosition = -1;
        emit onPositionChange();

        //    refreshDepth();
        for(Card* c : cards)
            c->raise();
    }
}

void PlayerContainer::shiftCards(bool right)
{
    int shiftPosition = right ? 1 : -1;

    cards[tempCardPosition] = cards[tempCardPosition + shiftPosition];
    cards[tempCardPosition + shiftPosition] = tempCardObject;

    cards[tempCardPosition]->
                move(position.x() + tempCardPosition * cardDistance,
                     position.y());
}
int PlayerContainer::getCurrArea()
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    int areaOfCurrCard = p.x() / cardDistance;

    if(areaOfCurrCard >= cards.size())  areaOfCurrCard = cards.size()-1;
    if(areaOfCurrCard <   0 )           areaOfCurrCard =  0;

    return areaOfCurrCard;
}
