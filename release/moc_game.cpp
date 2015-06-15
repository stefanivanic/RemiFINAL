/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[27];
    char stringdata[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 12), // "onNewMessage"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "message"
QT_MOC_LITERAL(4, 27, 12), // "onCardThrown"
QT_MOC_LITERAL(5, 40, 4), // "card"
QT_MOC_LITERAL(6, 45, 20), // "onGroupOfCardsThrown"
QT_MOC_LITERAL(7, 66, 5), // "cards"
QT_MOC_LITERAL(8, 72, 16), // "onGroupsReturned"
QT_MOC_LITERAL(9, 89, 6), // "number"
QT_MOC_LITERAL(10, 96, 15), // "onDeckCardTaken"
QT_MOC_LITERAL(11, 112, 16), // "onTalonCardTaken"
QT_MOC_LITERAL(12, 129, 14), // "onGroupCardAdd"
QT_MOC_LITERAL(13, 144, 31), // "on_actionSelect_theme_triggered"
QT_MOC_LITERAL(14, 176, 21), // "on_throwGroup_clicked"
QT_MOC_LITERAL(15, 198, 17), // "changeTempPosText"
QT_MOC_LITERAL(16, 216, 12), // "changePlayer"
QT_MOC_LITERAL(17, 229, 17), // "showOnThrowButton"
QT_MOC_LITERAL(18, 247, 17), // "hideOnThrowButton"
QT_MOC_LITERAL(19, 265, 10), // "slotReboot"
QT_MOC_LITERAL(20, 276, 20), // "on_undoGroup_clicked"
QT_MOC_LITERAL(21, 297, 15), // "cardsPreordered"
QT_MOC_LITERAL(22, 313, 16), // "QVector<QString>"
QT_MOC_LITERAL(23, 330, 9), // "cardNames"
QT_MOC_LITERAL(24, 340, 31), // "on_actionChoose_cards_triggered"
QT_MOC_LITERAL(25, 372, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(26, 398, 28) // "on_undoTookTalonCard_clicked"

    },
    "Game\0onNewMessage\0\0message\0onCardThrown\0"
    "card\0onGroupOfCardsThrown\0cards\0"
    "onGroupsReturned\0number\0onDeckCardTaken\0"
    "onTalonCardTaken\0onGroupCardAdd\0"
    "on_actionSelect_theme_triggered\0"
    "on_throwGroup_clicked\0changeTempPosText\0"
    "changePlayer\0showOnThrowButton\0"
    "hideOnThrowButton\0slotReboot\0"
    "on_undoGroup_clicked\0cardsPreordered\0"
    "QVector<QString>\0cardNames\0"
    "on_actionChoose_cards_triggered\0"
    "on_lineEdit_returnPressed\0"
    "on_undoTookTalonCard_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    1,  112,    2, 0x06 /* Public */,
       6,    1,  115,    2, 0x06 /* Public */,
       8,    1,  118,    2, 0x06 /* Public */,
      10,    0,  121,    2, 0x06 /* Public */,
      11,    0,  122,    2, 0x06 /* Public */,
      12,    1,  123,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  126,    2, 0x08 /* Private */,
      14,    0,  127,    2, 0x08 /* Private */,
      15,    0,  128,    2, 0x08 /* Private */,
      16,    0,  129,    2, 0x08 /* Private */,
      17,    1,  130,    2, 0x08 /* Private */,
      18,    1,  133,    2, 0x08 /* Private */,
      19,    0,  136,    2, 0x08 /* Private */,
      20,    0,  137,    2, 0x08 /* Private */,
      21,    1,  138,    2, 0x08 /* Private */,
      24,    0,  141,    2, 0x08 /* Private */,
      25,    0,  142,    2, 0x08 /* Private */,
      26,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        switch (_id) {
        case 0: _t->onNewMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onCardThrown((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onGroupOfCardsThrown((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onGroupsReturned((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onDeckCardTaken(); break;
        case 5: _t->onTalonCardTaken(); break;
        case 6: _t->onGroupCardAdd((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_actionSelect_theme_triggered(); break;
        case 8: _t->on_throwGroup_clicked(); break;
        case 9: _t->changeTempPosText(); break;
        case 10: _t->changePlayer(); break;
        case 11: _t->showOnThrowButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->hideOnThrowButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->slotReboot(); break;
        case 14: _t->on_undoGroup_clicked(); break;
        case 15: _t->cardsPreordered((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 16: _t->on_actionChoose_cards_triggered(); break;
        case 17: _t->on_lineEdit_returnPressed(); break;
        case 18: _t->on_undoTookTalonCard_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Game::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onNewMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (Game::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onCardThrown)) {
                *result = 1;
            }
        }
        {
            typedef void (Game::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onGroupOfCardsThrown)) {
                *result = 2;
            }
        }
        {
            typedef void (Game::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onGroupsReturned)) {
                *result = 3;
            }
        }
        {
            typedef void (Game::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onDeckCardTaken)) {
                *result = 4;
            }
        }
        {
            typedef void (Game::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onTalonCardTaken)) {
                *result = 5;
            }
        }
        {
            typedef void (Game::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::onGroupCardAdd)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject Game::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata))
        return static_cast<void*>(const_cast< Game*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Game::onNewMessage(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Game::onCardThrown(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Game::onGroupOfCardsThrown(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Game::onGroupsReturned(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Game::onDeckCardTaken()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Game::onTalonCardTaken()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void Game::onGroupCardAdd(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
