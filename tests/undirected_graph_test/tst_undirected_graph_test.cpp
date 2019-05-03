#include <QtTest>
#include <string>
#include "src/utils/undirected_graph.hpp"
#include "csvparser.hpp"

class undirected_graph_test : public QObject
{
    Q_OBJECT

public:
    undirected_graph_test();
    ~undirected_graph_test() = default;

private slots:
    void testLoadData();
    void testDepthFirstSearch();

private:
    nstd::undirected_graph<std::string,int> m_graph;
};

undirected_graph_test::undirected_graph_test()
{
    //Copy resource file to compile folder
    QFile(":/data.csv").copy("data.csv");
}

void undirected_graph_test::testLoadData()
{
    //Parse data file
    std::vector<std::vector<std::string>> data = loadData("data.csv");

    /* Add each row into graph (a row is an edge) */
    for(const std::vector<std::string>& row : data)
        m_graph.addEdge(row[0], row[1], std::stoi(row[2]));

    std::set<std::string> vertices = m_graph.getVertices();
    std::vector<std::pair<std::string,int>> vertexEdges;
    std::string vertex;

    /*
     * For each vertex, we check to see if they exist and
     * all their edges match the expected edges.
     *
     * This test is based off of a map of cities
     * (image should be included in folder)
     */

    vertex = "Atlanta";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Miami"), 661));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Dallas"), 781));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Houston"), 810));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 864));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("New York"), 888));

    vertex = "Boston";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("New York"), 214));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 983));

    vertex = "Chicago";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Kansas City"), 533));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("New York"), 787));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Boston"), 983));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Denver"), 1003));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("Seattle"), 2097));

    vertex = "Dallas";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Houston"), 239));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Kansas City"), 496));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Atlanta"), 781));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Los Angeles"), 1435));

    vertex = "Denver";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Kansas City"), 599));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 1003));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Los Angeles"), 1015));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("San Francisco"), 1267));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("Seattle"), 1331));\

    vertex = "Houston";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Dallas"), 239));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Atlanta"), 810));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Miami"), 1187));

    vertex = "Kansas City";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Dallas"), 496));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 533));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Denver"), 599));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Atlanta"), 864));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("New York"), 1260));
    QCOMPARE(vertexEdges[5], std::make_pair(std::string("Los Angeles"), 1663));

    vertex = "Los Angeles";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("San Francisco"), 381));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Denver"), 1015));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Dallas"), 1435));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 1663));

    vertex = "Miami";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Atlanta"), 661));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Houston"), 1187));

    vertex = "New York";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Boston"), 214));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 787));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Atlanta"), 888));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 1260));

    vertex = "San Francisco";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Los Angeles"), 381));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Seattle"), 807));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Denver"), 1267));

    vertex = "Seattle";
    QVERIFY(vertices.count(vertex) == 1);
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("San Francisco"), 807));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Denver"), 1331));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Chicago"), 2097));
}

void undirected_graph_test::testDepthFirstSearch()
{

}

QTEST_APPLESS_MAIN(undirected_graph_test)

#include "tst_undirected_graph_test.moc"
