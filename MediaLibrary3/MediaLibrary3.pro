QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    cd.cpp \
    data.cpp \
    datanode.cpp \
    dialogaddcd.cpp \
    dialogaddpic.cpp \
    dialogdel.cpp \
    main.cpp \
    mainwindow.cpp \
    picture.cpp \
    table.cpp \
    tdialogadd.cpp

HEADERS += \
    book.h \
    cd.h \
    data.h \
    datanode.h \
    dialogaddcd.h \
    dialogaddpic.h \
    dialogdel.h \
    mainwindow.h \
    picture.h \
    table.h \
    tdialogadd.h

FORMS += \
    dialogaddcd.ui \
    dialogaddpic.ui \
    dialogdel.ui \
    mainwindow.ui \
    tdialogadd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Lib.qrc \
    icon.qrc \
    icon/icon2.qrc \
    res.qrc

DISTFILES += \
    icon/add-file.png
