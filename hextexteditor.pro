#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T20:51:12
#
#-------------------------------------------------

QT       += widgets

TARGET = hextexteditor
TEMPLATE = lib

DEFINES += HEXTEXTEDITOR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
<<<<<<< HEAD
    ./hexeditdialog.cpp \
    ./hextexteditor.cpp \
    ./hextexteditorcolorConfigure.cpp \
    ./tokenlist.cpp

HEADERS += \
    ./hexeditdialog.h \
    ./hextexteditor.h \
    ./hextexteditorcolorConfigure.h \
    ./tokenlist.h
=======
    src/hexeditdialog.cpp \
    src/hextexteditor.cpp \
    src/hextexteditorcolorConfigure.cpp \
    src/tokenlist.cpp

HEADERS += \
    src/hexeditdialog.h \
    src/hextexteditor.h \
    src/hextexteditorcolorConfigure.h \
    src/tokenlist.h
>>>>>>> cadc24a707c05efa91a7093eddf4b3140f91e739

unix {
    target.path = /usr/lib
    INSTALLS += target
}
