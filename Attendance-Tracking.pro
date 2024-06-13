QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_day.cpp \
    add_snapp.cpp \
    delete_items.cpp \
    edit.cpp \
    edit_items.cpp \
    main.cpp \
    mainwindow.cpp \
    winsize.cpp

HEADERS += \
    add_day.h \
    add_snapp.h \
    delete_items.h \
    edit.h \
    edit_items.h \
    mainwindow.h \
    winsize.h

FORMS += \
    add_day.ui \
    add_snapp.ui \
    delete_items.ui \
    edit.ui \
    edit_items.ui \
    mainwindow.ui \
    winsize.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    icons.qrc

RC_ICONS = icon.ico
