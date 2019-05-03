QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCDIR = ../../src
INCLUDEPATH += $$INCDIR

HEADERS += \
    $$INCDIR/utils/undirected_graph.hpp \
    csvparser.hpp

SOURCES += \
    tst_undirected_graph_test.cpp

RESOURCES += \
    res.qrc
