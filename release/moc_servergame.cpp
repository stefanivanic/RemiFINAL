/****************************************************************************
** Meta object code from reading C++ file 'servergame.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../servergame.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servergame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServerGame_t {
    QByteArrayData data[19];
    char stringdata[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerGame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerGame_t qt_meta_stringdata_ServerGame = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ServerGame"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "message"
QT_MOC_LITERAL(4, 32, 8), // "sendCard"
QT_MOC_LITERAL(5, 41, 4), // "card"
QT_MOC_LITERAL(6, 46, 16), // "sendGroupOfCards"
QT_MOC_LITERAL(7, 63, 5), // "cards"
QT_MOC_LITERAL(8, 69, 16), // "sendGroupIndexes"
QT_MOC_LITERAL(9, 86, 6), // "number"
QT_MOC_LITERAL(10, 93, 14), // "sendDeckSignal"
QT_MOC_LITERAL(11, 108, 15), // "sendTalonSignal"
QT_MOC_LITERAL(12, 124, 13), // "appendMessage"
QT_MOC_LITERAL(13, 138, 7), // "addCard"
QT_MOC_LITERAL(14, 146, 15), // "addGroupOfCards"
QT_MOC_LITERAL(15, 162, 12), // "returnGroups"
QT_MOC_LITERAL(16, 175, 7), // "indexes"
QT_MOC_LITERAL(17, 183, 18), // "removeCardFromDeck"
QT_MOC_LITERAL(18, 202, 19) // "removeCardFromTalon"

    },
    "ServerGame\0sendMessage\0\0message\0"
    "sendCard\0card\0sendGroupOfCards\0cards\0"
    "sendGroupIndexes\0number\0sendDeckSignal\0"
    "sendTalonSignal\0appendMessage\0addCard\0"
    "addGroupOfCards\0returnGroups\0indexes\0"
    "removeCardFromDeck\0removeCardFromTalon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerGame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    1,   77,    2, 0x08 /* Private */,
       6,    1,   80,    2, 0x08 /* Private */,
       8,    1,   83,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    0,   87,    2, 0x08 /* Private */,
      12,    1,   88,    2, 0x0a /* Public */,
      13,    1,   91,    2, 0x0a /* Public */,
      14,    1,   94,    2, 0x0a /* Public */,
      15,    1,   97,    2, 0x0a /* Public */,
      17,    0,  100,    2, 0x0a /* Public */,
      18,    0,  101,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ServerGame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerGame *_t = static_cast<ServerGame *>(_o);
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sendCard((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sendGroupOfCards((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->sendGroupIndexes((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sendDeckSignal(); break;
        case 5: _t->sendTalonSignal(); break;
        case 6: _t->appendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->addCard((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->addGroupOfCards((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->returnGroups((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->removeCardFromDeck(); break;
        case 11: _t->removeCardFromTalon(); break;
        default: ;
        }
    }
}

const QMetaObject ServerGame::staticMetaObject = {
    { &Game::staticMetaObject, qt_meta_stringdata_ServerGame.data,
      qt_meta_data_ServerGame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ServerGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerGame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ServerGame.stringdata))
        return static_cast<void*>(const_cast< ServerGame*>(this));
    return Game::qt_metacast(_clname);
}

int ServerGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Game::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
