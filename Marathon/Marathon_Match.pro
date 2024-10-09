QT        += core gui sql
QTPLUGIN  += qcncodecs

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Athlete.cpp \
    AthleteDatabase.cpp \
    DeleteDialog.cpp \
    FindDialog.cpp \
    Match_time.cpp \
    MedalDialog.cpp \
    SignUpDialog.cpp \
    SigninTimeDialog.cpp \
    editwindow.cpp \
    genderdelegate.cpp \
    listdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    over50dialog.cpp \
    showwindow.cpp \
    signup.cpp

HEADERS += \
    Athlete.h \
    AthleteDatabase.h \
    DeleteDialog.h \
    FindDialog.h \
    Match_time.h \
    MedalDialog.h \
    SignUpDialog.h \
    SigninTimeDialog.h \
    editwindow.h \
    genderdelegate.h \
    listdialog.h \
    mainwindow.h \
    over50dialog.h \
    showwindow.h \
    signup.h

FORMS += \
    DeleteDialog.ui \
    FindDialog.ui \
    MedalDialog.ui \
    SignUpDialog.ui \
    SigninTimeDialog.ui \
    editwindow.ui \
    listdialog.ui \
    mainwindow.ui \
    over50dialog.ui \
    showwindow.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
