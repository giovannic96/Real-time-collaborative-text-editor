/****************************************************************************
** Meta object code from reading C++ file 'infowindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ClientModule/infowindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_infoWindow_t {
    QByteArrayData data[9];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_infoWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_infoWindow_t qt_meta_stringdata_infoWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "infoWindow"
QT_MOC_LITERAL(1, 11, 15), // "closeInfoWindow"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 21), // "on_exitButton_clicked"
QT_MOC_LITERAL(4, 50, 23), // "on_exitButton_2_clicked"
QT_MOC_LITERAL(5, 74, 19), // "on_giovanni_clicked"
QT_MOC_LITERAL(6, 94, 20), // "on_francesco_clicked"
QT_MOC_LITERAL(7, 115, 18), // "on_rinaldo_clicked"
QT_MOC_LITERAL(8, 134, 17) // "on_enrico_clicked"

    },
    "infoWindow\0closeInfoWindow\0\0"
    "on_exitButton_clicked\0on_exitButton_2_clicked\0"
    "on_giovanni_clicked\0on_francesco_clicked\0"
    "on_rinaldo_clicked\0on_enrico_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_infoWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void infoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<infoWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeInfoWindow(); break;
        case 1: _t->on_exitButton_clicked(); break;
        case 2: _t->on_exitButton_2_clicked(); break;
        case 3: _t->on_giovanni_clicked(); break;
        case 4: _t->on_francesco_clicked(); break;
        case 5: _t->on_rinaldo_clicked(); break;
        case 6: _t->on_enrico_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (infoWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&infoWindow::closeInfoWindow)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject infoWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_infoWindow.data,
    qt_meta_data_infoWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *infoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *infoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_infoWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int infoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void infoWindow::closeInfoWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
