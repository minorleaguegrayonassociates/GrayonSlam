QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCDIR = ../../app
INCLUDEPATH += $$INCDIR

HEADERS += \
    $$INCDIR/src/utils/undirected_graph.hpp \
    csvparser.hpp


SOURCES += \ 
    map_test.cpp
