/****************************************************************************
** Meta object code from reading C++ file 'playercontainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playercontainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playercontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayerContainer_t {
    QByteArrayData data[6];
    char stringdata[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerContainer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerContainer_t qt_meta_stringdata_PlayerContainer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlayerContainer"
QT_MOC_LITERAL(1, 16, 16), // "onPositionChange"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "onThrowCard"
QT_MOC_LITERAL(4, 46, 19), // "onAddingCardtoGroup"
QT_MOC_LITERAL(5, 66, 12) // "onEmptyGroup"

    },
    "PlayerContainer\0onPositionChange\0\0"
    "onThrowCard\0onAddingCardtoGroup\0"
    "onEmptyGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void PlayerContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerContainer *_t = static_cast<PlayerContainer *>(_o);
        switch (_id) {
        case 0: _t->onPositionChange(); break;
        case 1: _t->onThrowCard(); break;
        case 2: _t->onAddingCardtoGroup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onEmptyGroup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayerContainer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerContainer::onPositionChange)) {
                *result = 0;
            }
        }
        {
            typedef void (PlayerContainer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerContainer::onThrowCard)) {
                *result = 1;
            }
        }
        {
            typedef void (PlayerContainer::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerContainer::onAddingCardtoGroup)) {
                *result = 2;
            }
        }
        {
            typedef void (PlayerContainer::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayerContainer::onEmptyGroup)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject PlayerContainer::staticMetaObject = {
    { &CardContainer::staticMetaObject, qt_meta_stringdata_PlayerContainer.data,
      qt_meta_data_PlayerContainer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PlayerContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerContainer.stringdata))
        return static_cast<void*>(const_cast< PlayerContainer*>(this));
    return CardContainer::qt_metacast(_clname);
}

int PlayerContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CardContainer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PlayerContainer::onPositionChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void PlayerContainer::onThrowCard()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PlayerContainer::onAddingCardtoGroup(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayerContainer::onEmptyGroup(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
