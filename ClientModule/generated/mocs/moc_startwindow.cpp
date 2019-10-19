/****************************************************************************
** Meta object code from reading C++ file 'startwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../startwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StartWindow_t {
    QByteArrayData data[17];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StartWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StartWindow_t qt_meta_stringdata_StartWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "StartWindow"
QT_MOC_LITERAL(1, 12, 21), // "on_exitButton_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 31), // "on_ForgotPasswordButton_clicked"
QT_MOC_LITERAL(4, 67, 21), // "on_LoginAdmin_clicked"
QT_MOC_LITERAL(5, 89, 25), // "on_RegisterButton_clicked"
QT_MOC_LITERAL(6, 115, 22), // "on_LoginButton_clicked"
QT_MOC_LITERAL(7, 138, 23), // "on_SignUpButton_clicked"
QT_MOC_LITERAL(8, 162, 23), // "on_AccediButton_clicked"
QT_MOC_LITERAL(9, 186, 23), // "on_LogoutButton_clicked"
QT_MOC_LITERAL(10, 210, 19), // "on_Username_clicked"
QT_MOC_LITERAL(11, 230, 9), // "setStatus"
QT_MOC_LITERAL(12, 240, 9), // "newStatus"
QT_MOC_LITERAL(13, 250, 13), // "showFormPopup"
QT_MOC_LITERAL(14, 264, 6), // "result"
QT_MOC_LITERAL(15, 271, 5), // "title"
QT_MOC_LITERAL(16, 277, 3) // "msg"

    },
    "StartWindow\0on_exitButton_clicked\0\0"
    "on_ForgotPasswordButton_clicked\0"
    "on_LoginAdmin_clicked\0on_RegisterButton_clicked\0"
    "on_LoginButton_clicked\0on_SignUpButton_clicked\0"
    "on_AccediButton_clicked\0on_LogoutButton_clicked\0"
    "on_Username_clicked\0setStatus\0newStatus\0"
    "showFormPopup\0result\0title\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StartWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x0a /* Public */,
      13,    3,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   14,   15,   16,

       0        // eod
};

void StartWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StartWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_exitButton_clicked(); break;
        case 1: _t->on_ForgotPasswordButton_clicked(); break;
        case 2: _t->on_LoginAdmin_clicked(); break;
        case 3: _t->on_RegisterButton_clicked(); break;
        case 4: _t->on_LoginButton_clicked(); break;
        case 5: _t->on_SignUpButton_clicked(); break;
        case 6: _t->on_AccediButton_clicked(); break;
        case 7: _t->on_LogoutButton_clicked(); break;
        case 8: _t->on_Username_clicked(); break;
        case 9: _t->setStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->showFormPopup((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StartWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_StartWindow.data,
    qt_meta_data_StartWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StartWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StartWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int StartWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
