QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets statemachine
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src/app \
    src/ui

SOURCES += \
    main.cpp \
    src/app/mainwindow.cpp \
    src/app/statemachine.cpp \
    src/ui/ui_mainwindow.cpp \
    src/ui/controlwidget.cpp \
    src/ui/userwidget.cpp

HEADERS += \
    src/app/mainwindow.h \
    src/app/statemachine.h \
    src/ui/ui_mainwindow.h \
    src/ui/controlwidget.h \
    src/ui/userwidget.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
