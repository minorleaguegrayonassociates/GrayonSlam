#include <QtTest>
#include <string>
#include "csvparser.hpp"
#include "src/utils/map.hpp"

class map_test : public QObject
{
    Q_OBJECT

public:
    map_test();
    ~map_test()  = default;

private slots:
    void testLoadData();
    void testIterator();
    void testStringHash();

private:
    nstd::map<int,std::string> m_map;
};

map_test::map_test()
{
    //Copy resource file to compile folder
    QFile(":/map_data.csv").copy("map_data.csv");
}

void map_test::testLoadData()
{
    //Parse data file
    std::vector<std::vector<std::string>> data = loadData("map_data.csv");

    /* Add each row into graph (a row is an edge) */
    for(const std::vector<std::string>& row : data)
        m_map[std::stoi(row[3])] = row[4];

    QVERIFY(!m_map.empty());
    QVERIFY(static_cast<unsigned int>(m_map.size()) == data.size());

   //make sure all stadiums are read in and present in the map
    QCOMPARE("Angel Stadium", *m_map.find(62));
    QCOMPARE("Dodger Stadium", *m_map.find(63));
    QCOMPARE("Marlins Park", *m_map.find(64));
    QCOMPARE("Miller Park", *m_map.find(65));
    QCOMPARE("Target Field", *m_map.find(66));
    QCOMPARE("Citi Field", *m_map.find(67));
    QCOMPARE("Yankee Stadium", *m_map.find(68));
    QCOMPARE("Oakland-Alameda County Coliseum", *m_map.find(69));
    QCOMPARE("Citizens Bank Park", *m_map.find(70));
    QCOMPARE("PNC Park", *m_map.find(71));
    QCOMPARE("Petco Park", *m_map.find(72));
    QCOMPARE("AT&T Park", *m_map.find(73));
    QCOMPARE("Safeco Field", *m_map.find(74));
    QCOMPARE("Busch Stadium", *m_map.find(75));
    QCOMPARE("Tropicana Field", *m_map.find(76));
    QCOMPARE("Globe Life Park in Arlington", *m_map.find(77));
    QCOMPARE("Rogers Centre", *m_map.find(78));
    QCOMPARE("Nationals Park", *m_map.find(79));
    QCOMPARE("Chase Field", *m_map.find(50));
    QCOMPARE("Sun Trust Park", *m_map.find(51));
    QCOMPARE("Oriole Park at Camden Yards", *m_map.find(52));
    QCOMPARE("Fenway Park", *m_map.find(53));
    QCOMPARE("Wrigley Field", *m_map.find(54));
    QCOMPARE("Guaranteed Rate Field", *m_map.find(55));
    QCOMPARE("Great American Ball Park", *m_map.find(56));
    QCOMPARE("Progressive Field", *m_map.find(57));
    QCOMPARE("Coors Field", *m_map.find(58));
    QCOMPARE("Comerica Park", *m_map.find(59));
    QCOMPARE("Minute Maid Park", *m_map.find(60));
    QCOMPARE("Kauffman Stadium", *m_map.find(61));

    //testing negative hash with positive hash and repeat keys
    m_map[-1] = "harro";
    m_map[1] = "hi";
    m_map[2] ="hi";

    QCOMPARE("harro", *m_map.find(-1));
    QCOMPARE("hi", *m_map.find(1));
    QCOMPARE("hi", *m_map.find(2));
}

void map_test::testIterator()
{
    std::vector<std::string> forwardIterations;
    std::vector<std::string> backwardIterations;

    //test iteratiing forward through the map
    for(nstd::map<int,std::string>::iterator it = m_map.begin(); it != m_map.end(); ++it)
    {
        forwardIterations.push_back(*it);
    }

    //testing iterating backwards through the map
    for(nstd::map<int,std::string>::iterator it = (--m_map.end());!it.isNull();--it)
    {
       backwardIterations.push_back(*it);
    }

    //check that I have the same amount of traversals
    QVERIFY(backwardIterations.size() == static_cast<unsigned int>(m_map.size()));
    QVERIFY(backwardIterations.size() == forwardIterations.size());

    //check if the elements are the same
    std::reverse(backwardIterations.begin(),backwardIterations.end());
    for(unsigned int i = 0; i < backwardIterations.size(); ++i)
    {
        QCOMPARE(backwardIterations[i], forwardIterations[i]);
    }
}

void map_test::testStringHash()
{

    //check if string hashing works
    nstd::map<std::string,std::string> users;

    users["password"] = "username";
    users["username"] = "password";
    QCOMPARE("username",users["password"]);
    QCOMPARE("password",users["username"]);

    //check if copy constructor works
    nstd::map<std::string,std::string> users2(users);
    QCOMPARE("username",users["password"]);
    QCOMPARE("password",users["username"]);

    //verifying different loop techniques with the strings
    std::vector<std::string> stlForLoopIterations;
    std::vector<std::string> forEachLoopIterations;
    for(nstd::map<std::string,std::string>::iterator it2 = users2.begin(); it2 != users2.end(); ++it2)
    {
            stlForLoopIterations.push_back(*it2);
    }


    for(std::string user : users2)
    {
        forEachLoopIterations.push_back(user);

    }
    //make sure same amount of elements
    QVERIFY(stlForLoopIterations.size() == forEachLoopIterations.size());

    //make sure all elems are the same
    for(unsigned int i = 0; i < forEachLoopIterations.size(); ++i)
    {
        QCOMPARE(stlForLoopIterations[i], forEachLoopIterations[i]);
    }

}

QTEST_APPLESS_MAIN(map_test)

#include "map_test.moc"
