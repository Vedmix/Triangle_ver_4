QT       += core gui
QT       += widgets
QT       += widgets opengl
QT       += core gui widgets opengl openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    geometry/Tetragon/tetragon.cpp \
    geometry/Tetragon/tetragongraphic.cpp \
    geometry/Triangle/triangle.cpp \
    geometry/Triangle/trianglegraphic.cpp \
    math/matrix.cpp \
    math/fraction.cpp \
    math/generalMathFunctions.cpp \
    geometryresult.cpp \
    geometrywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    math/vectors.cpp \
    mathresult.cpp \
    mathwindow.cpp \
    secmathwindow.cpp \

HEADERS += \
    geometry/Tetragon/tetragon.hpp \
    geometry/Tetragon/tetragongraphic.hpp \
    geometry/Triangle/triangle.hpp \
    geometry/Triangle/trianglegraphic.hpp \
    math/matrix.hpp \
    math/fraction.hpp \
    math/generalMathFunctions.hpp \
    geometryresult.hpp \
    geometrywindow.hpp \
    mainwindow.hpp \
    math/vectors.hpp \
    mathresult.hpp \
    mathwindow.hpp \
    secmathwindow.hpp \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
