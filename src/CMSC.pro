QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CPU.cpp \
    Exceptions.cpp \
    PCB.cpp \
    contextswitchinterrupt.cpp \
    feedbackqueue.cpp \
    fileoptionsdialog.cpp \
    instruction.cpp \
    interrupt.cpp \
    kernel.cpp \
    loadfiledialog.cpp \
    longtermscheduler.cpp \
    main.cpp \
    mainmemory.cpp \
    mainwindow.cpp \
    mutex.cpp \
    page.cpp \
    pagetable.cpp \
    priorityqueue.cpp \
    queue.cpp \
    randomfileoptionsdialog.cpp \
    shorttermscheduler.cpp

HEADERS += \
    CPU.hpp \
    PCB.hpp \
    contextswitchinterrupt.h \
    feedbackqueue.h \
    fileoptionsdialog.h \
    instruction.hpp \
    interrupt.h \
    kernel.h \
    loadfiledialog.h \
    longtermscheduler.h \
    main.hpp \
    mainmemory.h \
    mainwindow.h \
    mutex.h \
    page.h \
    pagetable.h \
    priorityqueue.hpp \
    queue.hpp \
    randomfileoptionsdialog.h \
    shorttermscheduler.h

FORMS += \
    fileoptionsdialog.ui \
    loadfiledialog.ui \
    mainwindow.ui \
    randomfileoptionsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../tests/bobby.txt \
    ../tests/chrome.txt \
    ../tests/notepad.txt \
    ../tests/skyrim.txt
