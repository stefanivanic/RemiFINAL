#include "card.h"
#include "ui_card.h"

Card::Card(QWidget *parent, short number, short value, Sign sign)
      : QLabel(parent), ui(new Ui::Card),
        _Number(number),_Value(value), _Sign(sign), leftClick(false)
{
    ui->setupUi(this);

    QString theme = "2";
    QSize size = setImage(theme, false);

    resize(size.width(), size.height());

    setCursor(Qt::PointingHandCursor);

    e = new QGraphicsOpacityEffect();
} //END CONSTRUCTOR

//cacakam card

QString Card::name(){
    QString rez;

    if(_Sign == JOKER)
        rez.append("J");
    else {
        switch(_Number) {
        case 12 : rez.append("J"); break;
        case 13 : rez.append("Q"); break;
        case 14 : rez.append("K"); break;
        default : rez.append(QString::number(_Number)); break;
        }

        switch(_Sign) {
        case HERC : rez.append("H"); break;
        case KARO : rez.append("K"); break;
        case PIK :  rez.append("P"); break;
        case TREF : rez.append("T"); break;
        default: break;
        }
    }
    return rez;
}

QSize Card::setImage(QString theme, bool top)
{
    QString image = top ? this->name() : "back" ;

    QPixmap pix(QDir::currentPath()
                + "/slike/2/" + image +
                + ".gif");
    this->setPixmap(pix);

    return pix.size();
}

void Card::mousePressEvent(QMouseEvent* event)
{
    leftClick = false;
    if(event->button() == Qt::LeftButton)
        leftClick = true;

    if( leftClick) {
        if (isWindow())
            offset = event->globalPos() - pos();
        else
            offset = event->pos();

        e->setOpacity(.5);
        this->setGraphicsEffect(e);

        this->raise();
    }
}

void Card::mouseMoveEvent(QMouseEvent* event)
{
    if(leftClick) {
        if (isWindow())
            move(event->globalPos() - offset);
        else
            move(mapToParent(event->pos() - offset));
    }
}

void Card::mouseReleaseEvent(QMouseEvent* event)
{
    if(leftClick) {
        offset = QPoint();

        e->setOpacity(1);
        this->setGraphicsEffect(e);
    }
}

bool operator==(const Card& card1, const Card& card2){
       return (card1.getNumber() == card2.getNumber() &&
               card1.getSign() == card2.getSign());
}

bool operator!=(const Card& card1, const Card& card2){
    return !(card1==card2);
}

void Card::mouseDoubleClickEvent(QMouseEvent* event)
{ event->ignore(); return; }

Card::~Card() { delete ui; }

void Card::setValue(short value)
{
    _Value = value;
}

void Card::setNumber(short number)
{
    _Number = number;
}
