QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../cfg_parse.c \
    ../parse.c \
    ../s21_matrix.c \
    main.cpp \
    mainwindow.cpp \
    myopengl.cpp

HEADERS += \
    ../cfg_parse.h \
    ../parse.h \
    ../s21_matrix.h \
    mainwindow.h \
    myopengl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../CUB.obj \
    ../Makefile \
    ../airplane.obj \
    ../animal.obj \
    ../cfg.txt \
    ../human.obj
