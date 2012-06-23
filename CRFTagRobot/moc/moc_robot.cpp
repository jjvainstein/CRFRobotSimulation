/****************************************************************************
** Meta object code from reading C++ file 'robot.h'
**
** Created: Sat Jun 23 13:37:15 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/robot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Robot[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,    7,    6,    6, 0x05,
      56,   53,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Robot[] = {
    "Robot\0\0me,currentState\0"
    "sendState(Robot*,RobotState*)\0me\0"
    "arrived(Robot*)\0updatePosition()\0"
};

const QMetaObject Robot::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Robot,
      qt_meta_data_Robot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Robot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Robot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Robot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Robot))
        return static_cast<void*>(const_cast< Robot*>(this));
    return QThread::qt_metacast(_clname);
}

int Robot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendState((*reinterpret_cast< Robot*(*)>(_a[1])),(*reinterpret_cast< RobotState*(*)>(_a[2]))); break;
        case 1: arrived((*reinterpret_cast< Robot*(*)>(_a[1]))); break;
        case 2: updatePosition(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Robot::sendState(Robot * _t1, RobotState * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Robot::arrived(Robot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
