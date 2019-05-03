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
    void testBreadthFirstSearch();
    void testPrimsMST();
    void testDijkstraTraversal();

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
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Miami"), 661));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Dallas"), 781));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Houston"), 810));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 864));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("New York"), 888));

    vertex = "Boston";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("New York"), 214));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 983));

    vertex = "Chicago";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Kansas City"), 533));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("New York"), 787));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Boston"), 983));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Denver"), 1003));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("Seattle"), 2097));

    vertex = "Dallas";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Houston"), 239));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Kansas City"), 496));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Atlanta"), 781));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Los Angeles"), 1435));

    vertex = "Denver";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Kansas City"), 599));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 1003));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Los Angeles"), 1015));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("San Francisco"), 1267));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("Seattle"), 1331));\

    vertex = "Houston";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Dallas"), 239));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Atlanta"), 810));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Miami"), 1187));

    vertex = "Kansas City";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Dallas"), 496));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 533));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Denver"), 599));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Atlanta"), 864));
    QCOMPARE(vertexEdges[4], std::make_pair(std::string("New York"), 1260));
    QCOMPARE(vertexEdges[5], std::make_pair(std::string("Los Angeles"), 1663));

    vertex = "Los Angeles";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("San Francisco"), 381));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Denver"), 1015));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Dallas"), 1435));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 1663));

    vertex = "Miami";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Atlanta"), 661));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Houston"), 1187));

    vertex = "New York";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Boston"), 214));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Chicago"), 787));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Atlanta"), 888));
    QCOMPARE(vertexEdges[3], std::make_pair(std::string("Kansas City"), 1260));

    vertex = "San Francisco";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("Los Angeles"), 381));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Seattle"), 807));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Denver"), 1267));

    vertex = "Seattle";
    QVERIFY(m_graph.vertexExists(vertex));
    vertexEdges = m_graph.getVertexEdges(vertex);
    QCOMPARE(vertexEdges[0], std::make_pair(std::string("San Francisco"), 807));
    QCOMPARE(vertexEdges[1], std::make_pair(std::string("Denver"), 1331));
    QCOMPARE(vertexEdges[2], std::make_pair(std::string("Chicago"), 2097));
}

void undirected_graph_test::testDepthFirstSearch()
{
    QVERIFY(m_graph.vertexExists("Dallas"));

    /* Obtain DFS data from the graph */
    auto dfsData = m_graph.depthFirstSearch("Dallas");
    auto discoveryEdges = dfsData.first;
    int totalWeight = dfsData.second;

    QCOMPARE(discoveryEdges.size(), 11);
    QCOMPARE(totalWeight, 7314);

    /*
     * Check the discovery edges, then
     * pop the front so that we can seet
     * the next edge.
     */
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Houston"), 239));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Houston"), std::string("Atlanta"), 810));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Atlanta"), std::string("Miami"), 661));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Atlanta"), std::string("Kansas City"), 864));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("Chicago"), 533));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Chicago"), std::string("New York"), 787));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("New York"), std::string("Boston"), 214));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Chicago"), std::string("Denver"), 1003));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Denver"), std::string("Los Angeles"), 1015));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Los Angeles"), std::string("San Francisco"), 381));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("San Francisco"), std::string("Seattle"), 807));
    discoveryEdges.pop_front();

    QVERIFY(discoveryEdges.empty());
}

void undirected_graph_test::testBreadthFirstSearch()
{
    QVERIFY(m_graph.vertexExists("Dallas"));

    /* Obtain BFS data from the graph */
    auto bfsData = m_graph.breadthFirstSearch("Dallas");
    auto discoveryEdges = bfsData.first;
    int totalWeight = bfsData.second;

    QCOMPARE(discoveryEdges.size(), 11);
    QCOMPARE(totalWeight, 9991);

    /*
     * Check the discovery edges, then
     * pop the front so that we can seet
     * the next edge.
     */
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Houston"), 239));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Kansas City"), 496));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Atlanta"), 781));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Los Angeles"), 1435));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Houston"), std::string("Miami"), 1187));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("Chicago"), 533));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("Denver"), 599));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("New York"), 1260));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Los Angeles"), std::string("San Francisco"), 381));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Chicago"), std::string("Boston"), 983));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Chicago"), std::string("Seattle"), 2097));
    discoveryEdges.pop_front();

    QVERIFY(discoveryEdges.empty());
}

void undirected_graph_test::testPrimsMST()
{
    QVERIFY(m_graph.vertexExists("Dallas"));

    /* Obtain Prim's MST data from the graph */
    auto primsData = m_graph.primsMST("Dallas");
    auto discoveryEdges = primsData.first;
    int totalWeight = primsData.second;

    QCOMPARE(discoveryEdges.size(), 11);
    QCOMPARE(totalWeight, 6513);

    /*
     * Check the discovery edges, then
     * pop the front so that we can seet
     * the next edge.
     */
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Houston"), 239));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Kansas City"), 496));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("Chicago"), 533));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Kansas City"), std::string("Denver"), 599));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Dallas"), std::string("Atlanta"), 781));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Atlanta"), std::string("Miami"), 661));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Chicago"), std::string("New York"), 787));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("New York"), std::string("Boston"), 214));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Denver"), std::string("Los Angeles"), 1015));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("Los Angeles"), std::string("San Francisco"), 381));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_tuple(std::string("San Francisco"), std::string("Seattle"), 807));
    discoveryEdges.pop_front();

    QVERIFY(discoveryEdges.empty());
}

void undirected_graph_test::testDijkstraTraversal()
{
    QVERIFY(m_graph.vertexExists("Dallas"));
    QVERIFY(m_graph.vertexExists("Seattle"));

    /* Obtain Dijkstra's Traversal data from the graph */
    auto dijkstraData = m_graph.dijkstraTraversal("Dallas", "Seattle");
    auto discoveryEdges = dijkstraData.first;
    int totalWeight = dijkstraData.second;

    QCOMPARE(discoveryEdges.size(), 3);
    QCOMPARE(totalWeight, 2426);

    /*
     * Check the discovery edges, then
     * pop the front so that we can seet
     * the next edge.
     */
    QCOMPARE(discoveryEdges.front(), std::make_pair(std::string("Dallas"), std::string("Kansas City")));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_pair(std::string("Kansas City"), std::string("Denver")));
    discoveryEdges.pop_front();
    QCOMPARE(discoveryEdges.front(), std::make_pair(std::string("Denver"), std::string("Seattle")));
    discoveryEdges.pop_front();

    QVERIFY(discoveryEdges.empty());
}

QTEST_APPLESS_MAIN(undirected_graph_test)

#include "tst_undirected_graph_test.moc"
