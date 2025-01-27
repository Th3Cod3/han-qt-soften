QT += core gui widgets statemachine
CONFIG += c++17

INCLUDEPATH += \
    src/app \
    src/ui

SOURCES += \
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

testcase {
  message("Building test case")
  TARGET = StatemachineTests
  CONFIG += testlib console
  QT += testlib
  SOURCES += tests/test_statemachine.cpp

  test.target = test
  test.commands = ./StatemachineTests
  QMAKE_EXTRA_TARGETS += test
} else {
  message("Building application")
  TARGET = SOFTEN
  SOURCES += main.cpp
}
