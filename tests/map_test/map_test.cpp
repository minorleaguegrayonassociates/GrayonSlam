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
    //Copy resource file to compile folder
    QFile(":/data.csv").copy("data.csv");
}

map_test::~map_test()
{

}

void map_test::test_case1()
{
    //Parse data file
    std::vector<std::vector<std::string>> data = loadData("data.csv");
}

QTEST_APPLESS_MAIN(map_test)

#include "map_test.moc"
