
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += testlib

SOURCES += \
        Map.cpp \
        SimpleTest.cpp \
        TimeKeeper.cpp \
        main.cpp
QT += widgets
INSTALLS += target
CONFIG += qt
#CONFIG + = qt console warn_on depend_includepath testcase
CONFIG += qt console warn_on depend_includepath testcase
HEADERS += \
    LinkGame.h \
    SimpleTest.h
