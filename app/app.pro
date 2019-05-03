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
    src/main.cpp \
    src/views/dashboardview.cpp \
    src/widgets/imageslideshow.cpp \
    src/windows/mainwindow.cpp \
    src/windows/login.cpp \
    src/utils/parser.cpp \
    src/widgets/navbar.cpp \
    src/widgets/navbaritem.cpp \
    src/datastore/stadium.cpp \
    src/datastore/team.cpp \
    src/datastore/souvenir.cpp \
    src/widgets/souvenirlist.cpp \
    src/widgets/souvenirlistitem.cpp \
    src/datastore/database.cpp \
    src/views/stadiumview.cpp \
    src/widgets/stadiumlist.cpp \
    src/widgets/stadiumlistitem.cpp \
    src/views/adminview.cpp \
    src/widgets/mappainter.cpp \
    src/widgets/airplanepainter.cpp \
    src/widgets/beacon.cpp

HEADERS += \
    src/utils/stringfunctions.hpp \
    src/views/dashboardview.hpp \
    src/widgets/imageslideshow.hpp \
    src/windows/mainwindow.hpp \
    src/windows/login.hpp \
    src/utils/exceptions.hpp \
    src/utils/parser.hpp \
    src/widgets/navbar.hpp \
    src/widgets/navbaritem.hpp \
    src/datastore/stadium.hpp \
    src/datastore/team.hpp \
    src/datastore/souvenir.hpp \
    src/views/view.hpp \
    src/widgets/souvenirlist.hpp \
    src/widgets/souvenirlistitem.hpp \
    src/utils/map.hpp \
    src/datastore/database.hpp \
    src/utils/enumtools.hpp \
    src/views/stadiumview.hpp \
    src/widgets/stadiumlist.hpp \
    src/widgets/stadiumlistitem.hpp \
    src/views/adminview.hpp \
    src/widgets/mappainter.hpp \
    src/widgets/airplanepainter.hpp \
    src/widgets/beacon.hpp \
    src/utils/undirected_graph.hpp

FORMS += \
    src/views/dashboardview.ui \
    src/windows/mainwindow.ui \
    src/windows/login.ui \
    src/widgets/navbaritem.ui \
    src/widgets/souvenirlistitem.ui \
    src/views/stadiumview.ui \
    src/views/adminview.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
