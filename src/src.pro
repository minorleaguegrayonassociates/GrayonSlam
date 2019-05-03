#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T19:52:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GrayonSlam
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    views/dashboardview.cpp \
    widgets/imageslideshow.cpp \
    windows/mainwindow.cpp \
    windows/login.cpp \
    utils/parser.cpp \
    widgets/navbar.cpp \
    widgets/navbaritem.cpp \
    datastore/stadium.cpp \
    datastore/team.cpp \
    datastore/souvenir.cpp \
    widgets/souvenirlist.cpp \
    widgets/souvenirlistitem.cpp \
    datastore/database.cpp \
    views/stadiumview.cpp \
    widgets/stadiumlist.cpp \
    widgets/stadiumlistitem.cpp \
    views/adminview.cpp \
    widgets/mappainter.cpp \
    widgets/airplanepainter.cpp \
    widgets/beacon.cpp

HEADERS += \
    utils/stringfunctions.hpp \
    views/dashboardview.hpp \
    widgets/imageslideshow.hpp \
    windows/mainwindow.hpp \
    windows/login.hpp \
    utils/exceptions.hpp \
    utils/parser.hpp \
    widgets/navbar.hpp \
    widgets/navbaritem.hpp \
    datastore/stadium.hpp \
    datastore/team.hpp \
    datastore/souvenir.hpp \
    views/view.hpp \
    widgets/souvenirlist.hpp \
    widgets/souvenirlistitem.hpp \
    utils/map.hpp \
    datastore/database.hpp \
    utils/enumtools.hpp \
    views/stadiumview.hpp \
    widgets/stadiumlist.hpp \
    widgets/stadiumlistitem.hpp \
    views/adminview.hpp \
    widgets/mappainter.hpp \
    widgets/airplanepainter.hpp \
    widgets/beacon.hpp \
    utils/undirected_graph.hpp

FORMS += \
    views/dashboardview.ui \
    windows/mainwindow.ui \
    windows/login.ui \
    widgets/navbaritem.ui \
    widgets/souvenirlistitem.ui \
    views/stadiumview.ui \
    views/adminview.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
