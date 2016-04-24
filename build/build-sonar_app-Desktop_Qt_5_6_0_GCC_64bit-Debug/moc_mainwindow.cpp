/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[432];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "sendAngleToSTM"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "readSerialData"
QT_MOC_LITERAL(4, 42, 13), // "drawDataOnMap"
QT_MOC_LITERAL(5, 56, 5), // "Echo*"
QT_MOC_LITERAL(6, 62, 7), // "echoCpy"
QT_MOC_LITERAL(7, 70, 17), // "threshold_changed"
QT_MOC_LITERAL(8, 88, 30), // "on_actionSerial_port_triggered"
QT_MOC_LITERAL(9, 119, 26), // "on_actionConnect_triggered"
QT_MOC_LITERAL(10, 146, 18), // "contextMenuRequest"
QT_MOC_LITERAL(11, 165, 3), // "pos"
QT_MOC_LITERAL(12, 169, 31), // "on_singleMeasurementBtn_clicked"
QT_MOC_LITERAL(13, 201, 33), // "contexMenu_setBothSonarsInvis..."
QT_MOC_LITERAL(14, 235, 31), // "contexMenu_setBothSonarsVisible"
QT_MOC_LITERAL(15, 267, 18), // "on_scanBtn_clicked"
QT_MOC_LITERAL(16, 286, 25), // "on_updateAngleBtn_clicked"
QT_MOC_LITERAL(17, 312, 21), // "on_connectBtn_clicked"
QT_MOC_LITERAL(18, 334, 32), // "on_cBox_left_sensor_stateChanged"
QT_MOC_LITERAL(19, 367, 4), // "arg1"
QT_MOC_LITERAL(20, 372, 33), // "on_cBox_right_sensor_stateCha..."
QT_MOC_LITERAL(21, 406, 25) // "on_cBox_alg1_stateChanged"

    },
    "MainWindow\0sendAngleToSTM\0\0readSerialData\0"
    "drawDataOnMap\0Echo*\0echoCpy\0"
    "threshold_changed\0on_actionSerial_port_triggered\0"
    "on_actionConnect_triggered\0"
    "contextMenuRequest\0pos\0"
    "on_singleMeasurementBtn_clicked\0"
    "contexMenu_setBothSonarsInvisible\0"
    "contexMenu_setBothSonarsVisible\0"
    "on_scanBtn_clicked\0on_updateAngleBtn_clicked\0"
    "on_connectBtn_clicked\0"
    "on_cBox_left_sensor_stateChanged\0arg1\0"
    "on_cBox_right_sensor_stateChanged\0"
    "on_cBox_alg1_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    1,   96,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    1,  111,    2, 0x08 /* Private */,
      20,    1,  114,    2, 0x08 /* Private */,
      21,    1,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendAngleToSTM(); break;
        case 1: _t->readSerialData(); break;
        case 2: _t->drawDataOnMap((*reinterpret_cast< Echo*(*)>(_a[1]))); break;
        case 3: _t->threshold_changed(); break;
        case 4: _t->on_actionSerial_port_triggered(); break;
        case 5: _t->on_actionConnect_triggered(); break;
        case 6: _t->contextMenuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 7: _t->on_singleMeasurementBtn_clicked(); break;
        case 8: _t->contexMenu_setBothSonarsInvisible(); break;
        case 9: _t->contexMenu_setBothSonarsVisible(); break;
        case 10: _t->on_scanBtn_clicked(); break;
        case 11: _t->on_updateAngleBtn_clicked(); break;
        case 12: _t->on_connectBtn_clicked(); break;
        case 13: _t->on_cBox_left_sensor_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_cBox_right_sensor_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_cBox_alg1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
