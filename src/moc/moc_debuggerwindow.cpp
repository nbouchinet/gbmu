/****************************************************************************
** Meta object code from reading C++ file 'debuggerwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ui/debuggerwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debuggerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DebuggerWindow_t {
    QByteArrayData data[11];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DebuggerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DebuggerWindow_t qt_meta_stringdata_DebuggerWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DebuggerWindow"
QT_MOC_LITERAL(1, 15, 21), // "on_stepButton_clicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 28), // "on_runOneFrameButton_clicked"
QT_MOC_LITERAL(4, 67, 28), // "on_runDurationButton_clicked"
QT_MOC_LITERAL(5, 96, 30), // "on_addBreakpointButton_clicked"
QT_MOC_LITERAL(6, 127, 34), // "on_breakpointsEdit_editingFin..."
QT_MOC_LITERAL(7, 162, 33), // "on_deleteBreakpointButton_cli..."
QT_MOC_LITERAL(8, 196, 26), // "on_DebuggerWindow_rejected"
QT_MOC_LITERAL(9, 223, 33), // "on_deleteWatchpointButton_cli..."
QT_MOC_LITERAL(10, 257, 33) // "on_memoryLineEdit_editingFini..."

    },
    "DebuggerWindow\0on_stepButton_clicked\0"
    "\0on_runOneFrameButton_clicked\0"
    "on_runDurationButton_clicked\0"
    "on_addBreakpointButton_clicked\0"
    "on_breakpointsEdit_editingFinished\0"
    "on_deleteBreakpointButton_clicked\0"
    "on_DebuggerWindow_rejected\0"
    "on_deleteWatchpointButton_clicked\0"
    "on_memoryLineEdit_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DebuggerWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

       0        // eod
};

void DebuggerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DebuggerWindow *_t = static_cast<DebuggerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_stepButton_clicked(); break;
        case 1: _t->on_runOneFrameButton_clicked(); break;
        case 2: _t->on_runDurationButton_clicked(); break;
        case 3: _t->on_addBreakpointButton_clicked(); break;
        case 4: _t->on_breakpointsEdit_editingFinished(); break;
        case 5: _t->on_deleteBreakpointButton_clicked(); break;
        case 6: _t->on_DebuggerWindow_rejected(); break;
        case 7: _t->on_deleteWatchpointButton_clicked(); break;
        case 8: _t->on_memoryLineEdit_editingFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DebuggerWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DebuggerWindow.data,
      qt_meta_data_DebuggerWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DebuggerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DebuggerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DebuggerWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DebuggerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
