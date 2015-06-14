/****************************************************************************
** Meta object code from reading C++ file 'card.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../card.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'card.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Card_t {
    QByteArrayData data[7];
    char stringdata[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Card_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Card_t qt_meta_stringdata_Card = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Card"
QT_MOC_LITERAL(1, 5, 4), // "Sign"
QT_MOC_LITERAL(2, 10, 4), // "KARO"
QT_MOC_LITERAL(3, 15, 4), // "HERC"
QT_MOC_LITERAL(4, 20, 3), // "PIK"
QT_MOC_LITERAL(5, 24, 4), // "TREF"
QT_MOC_LITERAL(6, 29, 5) // "JOKER"

    },
    "Card\0Sign\0KARO\0HERC\0PIK\0TREF\0JOKER"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Card[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    5,   18,

 // enum data: key, value
       2, uint(Card::KARO),
       3, uint(Card::HERC),
       4, uint(Card::PIK),
       5, uint(Card::TREF),
       6, uint(Card::JOKER),

       0        // eod
};

void Card::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Card::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_Card.data,
      qt_meta_data_Card,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Card::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Card::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Card.stringdata))
        return static_cast<void*>(const_cast< Card*>(this));
    return QLabel::qt_metacast(_clname);
}

int Card::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
