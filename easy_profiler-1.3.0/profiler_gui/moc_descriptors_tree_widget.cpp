/****************************************************************************
** Meta object code from reading C++ file 'descriptors_tree_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "descriptors_tree_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'descriptors_tree_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EasyDescTreeWidget_t {
    QByteArrayData data[23];
    char stringdata0[329];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyDescTreeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyDescTreeWidget_t qt_meta_stringdata_EasyDescTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "EasyDescTreeWidget"
QT_MOC_LITERAL(1, 19, 11), // "clearSilent"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "_global"
QT_MOC_LITERAL(4, 40, 5), // "build"
QT_MOC_LITERAL(5, 46, 20), // "onSearchColumnChange"
QT_MOC_LITERAL(6, 67, 26), // "onBlockStatusChangeClicked"
QT_MOC_LITERAL(7, 94, 19), // "onCurrentItemChange"
QT_MOC_LITERAL(8, 114, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 131, 5), // "_item"
QT_MOC_LITERAL(10, 137, 5), // "_prev"
QT_MOC_LITERAL(11, 143, 12), // "onItemExpand"
QT_MOC_LITERAL(12, 156, 13), // "onDoubleClick"
QT_MOC_LITERAL(13, 170, 7), // "_column"
QT_MOC_LITERAL(14, 178, 21), // "onSelectedBlockChange"
QT_MOC_LITERAL(15, 200, 8), // "uint32_t"
QT_MOC_LITERAL(16, 209, 12), // "_block_index"
QT_MOC_LITERAL(17, 222, 19), // "onBlockStatusChange"
QT_MOC_LITERAL(18, 242, 22), // "::profiler::block_id_t"
QT_MOC_LITERAL(19, 265, 3), // "_id"
QT_MOC_LITERAL(20, 269, 27), // "::profiler::EasyBlockStatus"
QT_MOC_LITERAL(21, 297, 7), // "_status"
QT_MOC_LITERAL(22, 305, 23) // "resizeColumnsToContents"

    },
    "EasyDescTreeWidget\0clearSilent\0\0_global\0"
    "build\0onSearchColumnChange\0"
    "onBlockStatusChangeClicked\0"
    "onCurrentItemChange\0QTreeWidgetItem*\0"
    "_item\0_prev\0onItemExpand\0onDoubleClick\0"
    "_column\0onSelectedBlockChange\0uint32_t\0"
    "_block_index\0onBlockStatusChange\0"
    "::profiler::block_id_t\0_id\0"
    "::profiler::EasyBlockStatus\0_status\0"
    "resizeColumnsToContents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyDescTreeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       1,    0,   72,    2, 0x2a /* Public | MethodCloned */,
       4,    0,   73,    2, 0x0a /* Public */,
       5,    1,   74,    2, 0x08 /* Private */,
       6,    1,   77,    2, 0x08 /* Private */,
       7,    2,   80,    2, 0x08 /* Private */,
      11,    1,   85,    2, 0x08 /* Private */,
      12,    2,   88,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,
      17,    2,   96,    2, 0x08 /* Private */,
      22,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 20,   19,   21,
    QMetaType::Void,

       0        // eod
};

void EasyDescTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EasyDescTreeWidget *_t = static_cast<EasyDescTreeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearSilent((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->clearSilent(); break;
        case 2: _t->build(); break;
        case 3: _t->onSearchColumnChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->onBlockStatusChangeClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->onCurrentItemChange((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 6: _t->onItemExpand((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->onDoubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->onSelectedBlockChange((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 9: _t->onBlockStatusChange((*reinterpret_cast< ::profiler::block_id_t(*)>(_a[1])),(*reinterpret_cast< ::profiler::EasyBlockStatus(*)>(_a[2]))); break;
        case 10: _t->resizeColumnsToContents(); break;
        default: ;
        }
    }
}

const QMetaObject EasyDescTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_EasyDescTreeWidget.data,
      qt_meta_data_EasyDescTreeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyDescTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyDescTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyDescTreeWidget.stringdata0))
        return static_cast<void*>(const_cast< EasyDescTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int EasyDescTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
struct qt_meta_stringdata_EasyDescWidget_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EasyDescWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EasyDescWidget_t qt_meta_stringdata_EasyDescWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "EasyDescWidget"
QT_MOC_LITERAL(1, 15, 23), // "onSeachBoxReturnPressed"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "findNext"
QT_MOC_LITERAL(4, 49, 8), // "findPrev"
QT_MOC_LITERAL(5, 58, 16), // "findNextFromMenu"
QT_MOC_LITERAL(6, 75, 16) // "findPrevFromMenu"

    },
    "EasyDescWidget\0onSeachBoxReturnPressed\0"
    "\0findNext\0findPrev\0findNextFromMenu\0"
    "findPrevFromMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EasyDescWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       4,    1,   43,    2, 0x08 /* Private */,
       5,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void EasyDescWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EasyDescWidget *_t = static_cast<EasyDescWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSeachBoxReturnPressed(); break;
        case 1: _t->findNext((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->findPrev((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->findNextFromMenu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->findPrevFromMenu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EasyDescWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EasyDescWidget.data,
      qt_meta_data_EasyDescWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EasyDescWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EasyDescWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EasyDescWidget.stringdata0))
        return static_cast<void*>(const_cast< EasyDescWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int EasyDescWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
