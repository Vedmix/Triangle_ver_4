QT       += core gui
QT       += widgets
QT       += widgets opengl
QT       += core gui widgets opengl openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    geometry/graphics/Triangle/triangle.cpp \
    geometry/graphics/Triangle/trianglegraphic.cpp \
    geometryresult.cpp \
    geometrywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mathresult.cpp \
    mathwindow.cpp \
    secmathwindow.cpp

HEADERS += \
    geometry/graphics/Triangle/triangle.h \
    geometry/graphics/Triangle/trianglegraphic.h \
    geometryresult.h \
    geometrywindow.h \
    mainwindow.h \
    mathresult.h \
    mathwindow.h \
    secmathwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
