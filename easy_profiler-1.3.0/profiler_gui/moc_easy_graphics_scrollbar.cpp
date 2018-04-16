/****************************************************************************
** Meta object code from reading C++ file 'easy_graphics_scrollbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "easy_graphics_scrollbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'easy_graphics_scrollbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EasyGraphicsScrollbar_t {
    QByteArrayData data[11];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyGraphicsScrollbar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyGraphicsScrollbar_t qt_meta_stringdata_EasyGraphicsScrollbar = {
    {
QT_MOC_LITERAL(0, 0, 21), // "EasyGraphicsScrollbar"
QT_MOC_LITERAL(1, 22, 12), // "rangeChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "valueChanged"
QT_MOC_LITERAL(4, 49, 6), // "_value"
QT_MOC_LITERAL(5, 56, 7), // "wheeled"
QT_MOC_LITERAL(6, 64, 7), // "_mouseX"
QT_MOC_LITERAL(7, 72, 11), // "_wheelDelta"
QT_MOC_LITERAL(8, 84, 19), // "onThreadViewChanged"
QT_MOC_LITERAL(9, 104, 19), // "onWindowWidthChange"
QT_MOC_LITERAL(10, 124, 6) // "_width"

    },
    "EasyGraphicsScrollbar\0rangeChanged\0\0"
    "valueChanged\0_value\0wheeled\0_mouseX\0"
    "_wheelDelta\0onThreadViewChanged\0"
    "onWindowWidthChange\0_width"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyGraphicsScrollbar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       5,    2,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   48,    2, 0x08 /* Private */,
       9,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    4,
    QMetaType::Void, QMetaType::QReal, QMetaType::Int,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   10,

       0        // eod
};

void EasyGraphicsScrollbar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EasyGraphicsScrollbar *_t = static_cast<EasyGraphicsScrollbar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rangeChanged(); break;
        case 1: _t->valueChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->wheeled((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onThreadViewChanged(); break;
        case 4: _t->onWindowWidthChange((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EasyGraphicsScrollbar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsScrollbar::rangeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (EasyGraphicsScrollbar::*_t)(qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsScrollbar::valueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (EasyGraphicsScrollbar::*_t)(qreal , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsScrollbar::wheeled)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject EasyGraphicsScrollbar::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_EasyGraphicsScrollbar.data,
      qt_meta_data_EasyGraphicsScrollbar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyGraphicsScrollbar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyGraphicsScrollbar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyGraphicsScrollbar.stringdata0))
        return static_cast<void*>(const_cast< EasyGraphicsScrollbar*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int EasyGraphicsScrollbar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void EasyGraphicsScrollbar::rangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void EasyGraphicsScrollbar::valueChanged(qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EasyGraphicsScrollbar::wheeled(qreal _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
