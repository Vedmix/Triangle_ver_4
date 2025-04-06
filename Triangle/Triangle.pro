QT       += core gui
QT       += widgets
QT       += widgets opengl
QT       += core gui widgets opengl openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    geometry/graphics/Triangle/triangle.cpp \
    geometry/graphics/Triangle/trianglegraphic.cpp \
    geometryresult.cpp \
    geometrywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mathresult.cpp \
    mathwindow.cpp \
    secmathwindow.cpp \

HEADERS += \
    geometry/graphics/Triangle/triangle.h \
    geometry/graphics/Triangle/trianglegraphic.h \
    geometryresult.h \
    geometrywindow.h \
    mainwindow.h \
    mathresult.h \
    mathwindow.h \
    secmathwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
