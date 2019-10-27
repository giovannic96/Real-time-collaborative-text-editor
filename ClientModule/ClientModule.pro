QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = client

MOC_DIR     += generated/mocs
UI_DIR      += generated/uis
RCC_DIR     += generated/rccs
OBJECTS_DIR += generated/objs

CONFIG += c++11

QMAKE_CXXFLAGS += -DWIN32_LEAN_AND_MEAN

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS BOOST_SYSTEM_NO_DEPRECATED BOOST_THREAD_USE_LIB

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debugroom.cpp \
    editorwindow.cpp \
    jsonUtility.cpp \
    main.cpp \
    menuwindow.cpp \
    message.cpp \
    myClient.cpp \
    startwindow.cpp \
    userprofile.cpp \
    versioninfo.cpp

HEADERS += \
    debugroom.h \
    editorwindow.h \
    json.hpp \
    jsonUtility.h \
    menuwindow.h \
    message.h \
    myClient.h \
    startwindow.h \
    userprofile.h \
    versioninfo.h

FORMS += \
    debugroom.ui \
    editorwindow.ui \
    menuwindow.ui \
    startwindow.ui \
    userprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Risorse.qrc

DISTFILES += \
    Db/texteditor_users.sqlite \
    changelog.md

win32 {
    INCLUDEPATH += C:/Boost/include/boost-1_66
    LIBS += -LC:/Boost/lib \
            -lboost_serialization-mgw73-mt-x64-1_66 \
            -lboost_filesystem-mgw73-mt-x64-1_66 \
            -lboost_system-mgw73-mt-x64-1_66 \
            -lboost_thread-mgw73-mt-x64-1_66 \
            -lws2_32
}
