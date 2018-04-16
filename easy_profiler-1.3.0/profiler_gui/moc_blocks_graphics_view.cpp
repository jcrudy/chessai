/****************************************************************************
** Meta object code from reading C++ file 'blocks_graphics_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "blocks_graphics_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blocks_graphics_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EasyGraphicsView_t {
    QByteArrayData data[29];
    char stringdata0[461];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyGraphicsView_t qt_meta_stringdata_EasyGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 16), // "EasyGraphicsView"
QT_MOC_LITERAL(1, 17, 12), // "sceneUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "treeChanged"
QT_MOC_LITERAL(4, 43, 15), // "intervalChanged"
QT_MOC_LITERAL(5, 59, 32), // "const::profiler_gui::TreeBlocks&"
QT_MOC_LITERAL(6, 92, 7), // "_blocks"
QT_MOC_LITERAL(7, 100, 23), // "::profiler::timestamp_t"
QT_MOC_LITERAL(8, 124, 19), // "_session_begin_time"
QT_MOC_LITERAL(9, 144, 5), // "_left"
QT_MOC_LITERAL(10, 150, 6), // "_right"
QT_MOC_LITERAL(11, 157, 7), // "_strict"
QT_MOC_LITERAL(12, 165, 12), // "repaintScene"
QT_MOC_LITERAL(13, 178, 24), // "onGraphicsScrollbarWheel"
QT_MOC_LITERAL(14, 203, 7), // "_mouseX"
QT_MOC_LITERAL(15, 211, 11), // "_wheelDelta"
QT_MOC_LITERAL(16, 223, 22), // "onScrollbarValueChange"
QT_MOC_LITERAL(17, 246, 30), // "onGraphicsScrollbarValueChange"
QT_MOC_LITERAL(18, 277, 16), // "onFlickerTimeout"
QT_MOC_LITERAL(19, 294, 13), // "onIdleTimeout"
QT_MOC_LITERAL(20, 308, 21), // "onHierarchyFlagChange"
QT_MOC_LITERAL(21, 330, 6), // "_value"
QT_MOC_LITERAL(22, 337, 22), // "onSelectedThreadChange"
QT_MOC_LITERAL(23, 360, 23), // "::profiler::thread_id_t"
QT_MOC_LITERAL(24, 384, 3), // "_id"
QT_MOC_LITERAL(25, 388, 21), // "onSelectedBlockChange"
QT_MOC_LITERAL(26, 410, 12), // "_block_index"
QT_MOC_LITERAL(27, 423, 17), // "onRefreshRequired"
QT_MOC_LITERAL(28, 441, 19) // "onThreadViewChanged"

    },
    "EasyGraphicsView\0sceneUpdated\0\0"
    "treeChanged\0intervalChanged\0"
    "const::profiler_gui::TreeBlocks&\0"
    "_blocks\0::profiler::timestamp_t\0"
    "_session_begin_time\0_left\0_right\0"
    "_strict\0repaintScene\0onGraphicsScrollbarWheel\0"
    "_mouseX\0_wheelDelta\0onScrollbarValueChange\0"
    "onGraphicsScrollbarValueChange\0"
    "onFlickerTimeout\0onIdleTimeout\0"
    "onHierarchyFlagChange\0_value\0"
    "onSelectedThreadChange\0::profiler::thread_id_t\0"
    "_id\0onSelectedBlockChange\0_block_index\0"
    "onRefreshRequired\0onThreadViewChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyGraphicsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    5,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   97,    2, 0x08 /* Private */,
      13,    2,   98,    2, 0x08 /* Private */,
      16,    1,  103,    2, 0x08 /* Private */,
      17,    1,  106,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,
      19,    0,  110,    2, 0x08 /* Private */,
      20,    1,  111,    2, 0x08 /* Private */,
      22,    1,  114,    2, 0x08 /* Private */,
      25,    1,  117,    2, 0x08 /* Private */,
      27,    0,  120,    2, 0x08 /* Private */,
      28,    0,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, QMetaType::UInt,   26,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EasyGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EasyGraphicsView *_t = static_cast<EasyGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sceneUpdated(); break;
        case 1: _t->treeChanged(); break;
        case 2: _t->intervalChanged((*reinterpret_cast< const::profiler_gui::TreeBlocks(*)>(_a[1])),(*reinterpret_cast< ::profiler::timestamp_t(*)>(_a[2])),(*reinterpret_cast< ::profiler::timestamp_t(*)>(_a[3])),(*reinterpret_cast< ::profiler::timestamp_t(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 3: _t->repaintScene(); break;
        case 4: _t->onGraphicsScrollbarWheel((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onScrollbarValueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onGraphicsScrollbarValueChange((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->onFlickerTimeout(); break;
        case 8: _t->onIdleTimeout(); break;
        case 9: _t->onHierarchyFlagChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onSelectedThreadChange((*reinterpret_cast< ::profiler::thread_id_t(*)>(_a[1]))); break;
        case 11: _t->onSelectedBlockChange((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 12: _t->onRefreshRequired(); break;
        case 13: _t->onThreadViewChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EasyGraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsView::sceneUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (EasyGraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsView::treeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (EasyGraphicsView::*_t)(const ::profiler_gui::TreeBlocks & , ::profiler::timestamp_t , ::profiler::timestamp_t , ::profiler::timestamp_t , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EasyGraphicsView::intervalChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject EasyGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_EasyGraphicsView.data,
      qt_meta_data_EasyGraphicsView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyGraphicsView.stringdata0))
        return static_cast<void*>(const_cast< EasyGraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int EasyGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void EasyGraphicsView::sceneUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void EasyGraphicsView::treeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void EasyGraphicsView::intervalChanged(const ::profiler_gui::TreeBlocks & _t1, ::profiler::timestamp_t _t2, ::profiler::timestamp_t _t3, ::profiler::timestamp_t _t4, bool _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_EasyThreadNamesWidget_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyThreadNamesWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyThreadNamesWidget_t qt_meta_stringdata_EasyThreadNamesWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "EasyThreadNamesWidget"
QT_MOC_LITERAL(1, 22, 25), // "setVerticalScrollbarRange"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 9), // "_minValue"
QT_MOC_LITERAL(4, 59, 9), // "_maxValue"
QT_MOC_LITERAL(5, 69, 12), // "onTreeChange"
QT_MOC_LITERAL(6, 82, 13), // "onIdleTimeout"
QT_MOC_LITERAL(7, 96, 12) // "repaintScene"

    },
    "EasyThreadNamesWidget\0setVerticalScrollbarRange\0"
    "\0_minValue\0_maxValue\0onTreeChange\0"
    "onIdleTimeout\0repaintScene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyThreadNamesWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x08 /* Private */,
       5,    0,   39,    2, 0x08 /* Private */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EasyThreadNamesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EasyThreadNamesWidget *_t = static_cast<EasyThreadNamesWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setVerticalScrollbarRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onTreeChange(); break;
        case 2: _t->onIdleTimeout(); break;
        case 3: _t->repaintScene(); break;
        default: ;
        }
    }
}

const QMetaObject EasyThreadNamesWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_EasyThreadNamesWidget.data,
      qt_meta_data_EasyThreadNamesWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyThreadNamesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyThreadNamesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyThreadNamesWidget.stringdata0))
        return static_cast<void*>(const_cast< EasyThreadNamesWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int EasyThreadNamesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_EasyGraphicsViewWidget_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyGraphicsViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyGraphicsViewWidget_t qt_meta_stringdata_EasyGraphicsViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 22) // "EasyGraphicsViewWidget"

    },
    "EasyGraphicsViewWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyGraphicsViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void EasyGraphicsViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject EasyGraphicsViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EasyGraphicsViewWidget.data,
      qt_meta_data_EasyGraphicsViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyGraphicsViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyGraphicsViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyGraphicsViewWidget.stringdata0))
        return static_cast<void*>(const_cast< EasyGraphicsViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EasyGraphicsViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
