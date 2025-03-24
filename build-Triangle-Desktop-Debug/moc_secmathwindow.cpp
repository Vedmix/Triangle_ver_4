/****************************************************************************
** Meta object code from reading C++ file 'secmathwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Triangle/secmathwindow.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'secmathwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_SecondMathMenu_t {
    uint offsetsAndSizes[24];
    char stringdata0[15];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[14];
    char stringdata5[11];
    char stringdata6[6];
    char stringdata7[20];
    char stringdata8[20];
    char stringdata9[20];
    char stringdata10[20];
    char stringdata11[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_SecondMathMenu_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_SecondMathMenu_t qt_meta_stringdata_SecondMathMenu = {
    {
        QT_MOC_LITERAL(0, 14),  // "SecondMathMenu"
        QT_MOC_LITERAL(15, 17),  // "showMatrixContent"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 25),  // "showComplexNumbersContent"
        QT_MOC_LITERAL(60, 13),  // "keyPressEvent"
        QT_MOC_LITERAL(74, 10),  // "QKeyEvent*"
        QT_MOC_LITERAL(85, 5),  // "event"
        QT_MOC_LITERAL(91, 19),  // "handleMatrixButton1"
        QT_MOC_LITERAL(111, 19),  // "handleMatrixButton2"
        QT_MOC_LITERAL(131, 19),  // "handleMatrixButton3"
        QT_MOC_LITERAL(151, 19),  // "handleMatrixButton4"
        QT_MOC_LITERAL(171, 19)   // "handleMatrixButton5"
    },
    "SecondMathMenu",
    "showMatrixContent",
    "",
    "showComplexNumbersContent",
    "keyPressEvent",
    "QKeyEvent*",
    "event",
    "handleMatrixButton1",
    "handleMatrixButton2",
    "handleMatrixButton3",
    "handleMatrixButton4",
    "handleMatrixButton5"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_SecondMathMenu[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    1,   64,    2, 0x08,    3 /* Private */,
       7,    0,   67,    2, 0x08,    5 /* Private */,
       8,    0,   68,    2, 0x08,    6 /* Private */,
       9,    0,   69,    2, 0x08,    7 /* Private */,
      10,    0,   70,    2, 0x08,    8 /* Private */,
      11,    0,   71,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SecondMathMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SecondMathMenu.offsetsAndSizes,
    qt_meta_data_SecondMathMenu,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_SecondMathMenu_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SecondMathMenu, std::true_type>,
        // method 'showMatrixContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showComplexNumbersContent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'keyPressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QKeyEvent *, std::false_type>,
        // method 'handleMatrixButton1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMatrixButton2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMatrixButton3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMatrixButton4'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMatrixButton5'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SecondMathMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SecondMathMenu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showMatrixContent(); break;
        case 1: _t->showComplexNumbersContent(); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 3: _t->handleMatrixButton1(); break;
        case 4: _t->handleMatrixButton2(); break;
        case 5: _t->handleMatrixButton3(); break;
        case 6: _t->handleMatrixButton4(); break;
        case 7: _t->handleMatrixButton5(); break;
        default: ;
        }
    }
}

const QMetaObject *SecondMathMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SecondMathMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SecondMathMenu.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SecondMathMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
