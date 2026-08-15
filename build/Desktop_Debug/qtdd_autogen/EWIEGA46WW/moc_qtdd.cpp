/****************************************************************************
** Meta object code from reading C++ file 'qtdd.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../qtdd.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtdd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN4qtddE_t {};
} // unnamed namespace

template <> constexpr inline auto qtdd::qt_create_metaobjectdata<qt_meta_tag_ZN4qtddE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "qtdd",
        "on_btn_exit_clicked",
        "",
        "on_btn_refreshdev_clicked",
        "on_checkBox_alldev_toggled",
        "checked",
        "refreshDevices",
        "on_btn_select_bootsel_clicked",
        "on_comboBox_part_schem_currentIndexChanged",
        "index",
        "on_comboBox_imageopt_currentIndexChanged",
        "on_btn_start_clicked",
        "on_btn_cancel_clicked",
        "readProcessOutput",
        "processFinished",
        "exitCode",
        "QProcess::ExitStatus",
        "exitStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_btn_exit_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_refreshdev_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_checkBox_alldev_toggled'
        QtMocHelpers::SlotData<void(bool)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 5 },
        }}),
        // Slot 'refreshDevices'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_select_bootsel_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_comboBox_part_schem_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Slot 'on_comboBox_imageopt_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 9 },
        }}),
        // Slot 'on_btn_start_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_cancel_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'readProcessOutput'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'processFinished'
        QtMocHelpers::SlotData<void(int, QProcess::ExitStatus)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { 0x80000000 | 16, 17 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<qtdd, qt_meta_tag_ZN4qtddE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject qtdd::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4qtddE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4qtddE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4qtddE_t>.metaTypes,
    nullptr
} };

void qtdd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<qtdd *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_btn_exit_clicked(); break;
        case 1: _t->on_btn_refreshdev_clicked(); break;
        case 2: _t->on_checkBox_alldev_toggled((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->refreshDevices(); break;
        case 4: _t->on_btn_select_bootsel_clicked(); break;
        case 5: _t->on_comboBox_part_schem_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_comboBox_imageopt_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->on_btn_start_clicked(); break;
        case 8: _t->on_btn_cancel_clicked(); break;
        case 9: _t->readProcessOutput(); break;
        case 10: _t->processFinished((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QProcess::ExitStatus>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *qtdd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qtdd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4qtddE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int qtdd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
