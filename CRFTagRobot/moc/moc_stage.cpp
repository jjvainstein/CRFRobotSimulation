/****************************************************************************
** Meta object code from reading C++ file 'stage.h'
**
** Created: Sat Jun 23 13:36:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/stage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Stage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    7,    6,    6, 0x09,
      41,   36,    6,    6, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Stage[] = {
    "Stage\0\0r\0destinationReached(Robot*)\0"
    "r,rs\0updateState(Robot*,RobotState*)\0"
};

const QMetaObject Stage::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Stage,
      qt_meta_data_Stage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Stage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Stage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Stage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Stage))
        return static_cast<void*>(const_cast< Stage*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Stage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: destinationReached((*reinterpret_cast< Robot*(*)>(_a[1]))); break;
        case 1: updateState((*reinterpret_cast< Robot*(*)>(_a[1])),(*reinterpret_cast< RobotState*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
