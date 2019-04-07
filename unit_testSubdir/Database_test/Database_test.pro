QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase \
          c++14

TEMPLATE = app

SOURCES += \
    src/tst_init_classes.cpp \
    ./../../GrayonSlam/src/datastore/team.cpp \
    ./../../GrayonSlam/src/datastore/stadium.cpp \
    ./../../GrayonSlam/src/datastore/souvenir.cpp \
    ./../../GrayonSlam/src/datastore/database.cpp \
    ./../../GrayonSlam/src/utils/parser.cpp \

HEADERS += \
    ./../../GrayonSlam/src/datastore/team.hpp \
    ./../../GrayonSlam/src/datastore/stadium.hpp \
    ./../../GrayonSlam/src/datastore/souvenir.hpp \
    ./../../GrayonSlam/src/datastore/database.hpp \
    ./../../GrayonSlam/src/utils/parser.hpp \
