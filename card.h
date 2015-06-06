#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QString>
#include <QSize>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QGraphicsEffect>
#include <QDir>
#include <QWidget>
#include <QDebug>

namespace Ui {
class Card;
}

class Card : public QLabel
{
    Q_OBJECT

public:
    enum Sign {
        KARO, HERC, PIK, TREF, JOKER
    };

    explicit Card(QWidget *parent = 0);
    Card(QWidget *parent = 0,
         short number =0,
         short value = 0,
         Sign sign = JOKER);
    virtual ~Card();

     // treba mi da uzmem enum kao string
     Q_ENUMS(Sign)

    QString name();
    short   getNumber() const { return _Number; }
    short   getValue () const { return  _Value; }
    Sign    getSign  () const { return   _Sign; }
    bool isLeftClick() const {return leftClick; }

    void setNumber(short number);
    void setValue(short value);

    QSize setImage(QString theme, bool top);

    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    QGraphicsOpacityEffect* e;
protected:
    Ui::Card *ui;

    short   _Number;
    short   _Value ;
    Sign    _Sign  ;

    bool leftClick;

    QPoint offset;
    // eksplicitno navodimo da ne bi postojala
    void mouseDoubleClickEvent(QMouseEvent* event);

    friend bool operator==(const Card& card1, const Card& card2);
    friend bool operator!=(const Card& card1, const Card& card2);

    Card(const Card& card)          = delete;
    Card& operator=(const Card& op) = delete;
};

#endif // CARD_H
