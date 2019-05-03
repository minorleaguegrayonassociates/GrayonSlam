#include <QtTest>
#include <string>
#include "csvparser.hpp"
#include "src/utils/map.hpp"
// add necessary includes here

class map_test : public QObject
{
    Q_OBJECT

public:
    map_test();
    ~map_test();

private slots:
    void test_case1();

};

map_test::map_test()
{

}

map_test::~map_test()
{

}

void map_test::test_case1()
{

}

QTEST_APPLESS_MAIN(map_test)

#include "map_test.moc"
