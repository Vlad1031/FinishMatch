/****************************************************************************
** Meta object code from reading C++ file 'match3model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Match3Model/match3model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'match3model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Match3model_t {
    QByteArrayData data[15];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Match3model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Match3model_t qt_meta_stringdata_Match3model = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Match3model"
QT_MOC_LITERAL(1, 12, 11), // "neighboring"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "from"
QT_MOC_LITERAL(4, 30, 2), // "to"
QT_MOC_LITERAL(5, 33, 4), // "move"
QT_MOC_LITERAL(6, 38, 7), // "shaffle"
QT_MOC_LITERAL(7, 46, 12), // "combinations"
QT_MOC_LITERAL(8, 59, 6), // "remove"
QT_MOC_LITERAL(9, 66, 5), // "score"
QT_MOC_LITERAL(10, 72, 8), // "gameOver"
QT_MOC_LITERAL(11, 81, 6), // "myRows"
QT_MOC_LITERAL(12, 88, 9), // "myColumns"
QT_MOC_LITERAL(13, 98, 8), // "myColors"
QT_MOC_LITERAL(14, 107, 14) // "QList<QString>"

    },
    "Match3model\0neighboring\0\0from\0to\0move\0"
    "shaffle\0combinations\0remove\0score\0"
    "gameOver\0myRows\0myColumns\0myColors\0"
    "QList<QString>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Match3model[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x02 /* Public */,
       5,    2,   69,    2, 0x02 /* Public */,
       6,    0,   74,    2, 0x02 /* Public */,
       7,    0,   75,    2, 0x02 /* Public */,
       8,    0,   76,    2, 0x02 /* Public */,
       9,    0,   77,    2, 0x02 /* Public */,
      10,    0,   78,    2, 0x02 /* Public */,
      11,    0,   79,    2, 0x02 /* Public */,
      12,    0,   80,    2, 0x02 /* Public */,
      13,    0,   81,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Int,
    0x80000000 | 14,

       0        // eod
};

void Match3model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Match3model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->neighboring((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->shaffle(); break;
        case 3: { bool _r = _t->combinations();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->remove(); break;
        case 5: { int _r = _t->score();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->gameOver();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->myRows();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->myColumns();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { QList<QString> _r = _t->myColors();
            if (_a[0]) *reinterpret_cast< QList<QString>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Match3model::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_Match3model.data,
    qt_meta_data_Match3model,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Match3model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Match3model::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Match3model.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int Match3model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
