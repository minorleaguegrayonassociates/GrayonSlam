#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>

namespace nstd
{
/**
 * @class nstd::undirected_graph class
 *
 * A data-structure that holds vertices and edges connecting the vertices.
 * Similar to a tree, vertices can be connected to other vertrices using
 * edges; a graph can hold up to as many vertices and edges as you need to.
 *
 * This class has more use than just holding vertices and edges: graph
 * algorithms can be used on the graph. Depth-first and breadth-first
 * searches, Dijkstra's shortest-path, and Prim's minimum spanning
 * tree (MST) algorithms can be operated on this graph (built-in functions).
 *
 * This graph is implemented with @a std::map only. This is because we can
 * associate a whole list of edges (@a VertexEdges) to a single vertex.
 * With @a std::map, we are also able to iterate through the map to obtain
 * the vertices since the iterators return a @a std::pair<Vertex,VertexEdges>.
 *
 * @tparam Vertex Vertex type of the graph
 * @tparam Weight Weight type of the edges connecting the vertices
 */
template<typename Vertex, typename Weight>
class undirected_graph
{
public:
    /* Aliases */
    using PartialEdge = std::pair<Vertex,Weight>; //"to" vertex and weight
    using CompleteEdge = std::tuple<Vertex,Vertex,Weight>; //"from" vertex, "to" vertex, and weight
    using VertexEdges = std::vector<PartialEdge>; //Partial edges of a "from" vertex

    /* Constructors */
    undirected_graph() = default;
    undirected_graph(const std::vector<CompleteEdge>& edges);

    /* Checks */
    bool vertexExists(const Vertex&) const;
    bool edgeExists(const Vertex& end1, const Vertex& end2, const Weight&) const;
    bool edgeExists(const CompleteEdge&) const;
    bool emptyVertices() const;
    bool emptyEdges() const;

    /* Getters */
    std::set<Vertex> getVertices() const;
    const std::map<Vertex,VertexEdges>& getEdges() const;
    const VertexEdges& getVertexEdges(const Vertex&) const;

    /* Adders */
    void addVertex(const Vertex&);
    void addEdge(const Vertex& end1, const Vertex& end2, const Weight&);
    void addEdge(const CompleteEdge&);

    /* Removers */
    void removeVertex(const Vertex&);
    void removeEdge(const Vertex& end1, const Vertex& end2, const Weight&);
    void removeEdge(const CompleteEdge&);

    /* Searches */
    std::pair<std::list<CompleteEdge>,Weight> depthFirstSearch(const Vertex& start) const;
    std::pair<std::list<CompleteEdge>,Weight> breadthFirstSearch(const Vertex& start) const;

    /* Minimum spanning tree */
    std::pair<std::list<CompleteEdge>,Weight> primsMST(const Vertex& start) const;

    /* Shortest-path */
    Weight dijkstraTraversal(const Vertex& vertex,
                             std::map<Vertex,std::pair<Weight,Vertex>>& vertexInfo) const;

    std::pair<std::list<std::pair<Vertex,Vertex>>,Weight> dijkstraTraversal(const Vertex& vertexFrom,
                                                                              const Vertex& vertexTo) const;

private:
    /* Helpers */
    Weight DFSHelper(const Vertex& current,
                     std::set<Vertex>& visisted,
                     std::list<CompleteEdge>& discoveryEdges) const;

    std::map<Vertex,VertexEdges> m_edges;
};

/**
 * Constructs a undirected graph and adds the given edges into the graph.
 *
 * If a vertex in @a edges doesn't exist, the vertex will be added.
 *
 * This essentially calls @a addEdge() on each @a CompleteEdge in the container.
 *
 * @param edges Container containing edges to vertices
 */
template<typename Vertex, typename Weight>
undirected_graph<Vertex,Weight>::undirected_graph(const std::vector<CompleteEdge>& edges)
{
    for(const CompleteEdge& edge : edges)
        addEdge(edge);
}

/**
 * Checks if a vertex exists within the graph.
 *
 * @param vertex Vertex to check
 * @return Whether the given vertex exists or not
 */
template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::vertexExists(const Vertex& vertex) const
{
    return m_edges.count(vertex) != 0;
}

/**
 * Checks if an edge exists within the graph. The order of the vertices
 * doesn't matter.
 *
 * @param end1 First end vertex of the edge
 * @param end2 Second end vertex of the edge
 * @param weight Weight of the edge
 * @return Whether the given edge exists or not
 */
template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::edgeExists(const Vertex& end1, const Vertex& end2, const Weight& weight) const
{
    /* Check if the vertices exist */
    if(!vertexExists(end1) || !vertexExists(end2))
        return false;

    /* Get the edges of both end vertices */
    const VertexEdges& end1Edges = getVertexEdges(end1);
    const VertexEdges& end2Edges = getVertexEdges(end2);

    /* See if the partial edges exist on at least one of them */
    return std::binary_search(end1Edges.cbegin(), end1Edges.cend(), PartialEdge(end2, weight)) != end1Edges.cend() ||
           std::binary_search(end2Edges.cbegin(), end2Edges.cend(), PartialEdge(end1, weight)) != end2Edges.cend();
}

/**
 * Checks if an edge exists within the graph.
 *
 * This is an overloaded function that extracts all the values from @a edge
 * and passes them into the other function.
 *
 * @param edge Edge to check
 * @return Whether the given edge exists or not
 */
template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::edgeExists(const CompleteEdge& edge) const
{
    /* Extract vertices and weight */
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    return edgeExists(end1, end2, weight);
}

/**
 * Checks if the graph contains any vertices--connected or not.
 *
 * @return Whether there are vertices or not
 */
template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::emptyVertices() const
{
    return m_edges.empty();
}

/**
 * Checks if the graph contains any edges.
 *
 * Note:
 * A graph can contain vertices that never connect.
 *
 * @return Whether there are edges connecting vertices or not
 */
template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::emptyEdges() const
{
    for(const std::pair<Vertex,VertexEdges>& pair : m_edges)
    {
        const VertexEdges& edges = pair.second;

        /*
         * If at least one vertex's edges isn't empty,
         * then there are edges in the graph
         */
        if(!edges.empty())
            return false;
    }

    return true;
}

/**
 * Returns all the vertices in the graph--connected or not.
 *
 * Iterates through the @a std::map and collects the @a std::pair::first
 * for each key-value pair.
 *
 * @return A set of all the vertices in the graph
 */
template<typename Vertex, typename Weight>
std::set<Vertex> undirected_graph<Vertex,Weight>::getVertices() const
{
    std::set<Vertex> vertices;

    for(const std::pair<Vertex,VertexEdges>& vertexEdge : m_edges)
        vertices.insert(vertexEdge.first);

    return vertices;
}

/**
 * Returns the internal map structure that holds all the vertex-edges
 * information about the graph.
 *
 * The data-type for this is a @a std::map<Vertex,VertexEdges>. This
 * allows the ability to explore the graph data more deeply since this
 * is the exact data that @a undirected_graph holds.
 *
 * @return A map containing all the vertex-edges pairs
 */
template<typename Vertex, typename Weight>
const std::map<Vertex, typename undirected_graph<Vertex,Weight>::VertexEdges>& //return type
undirected_graph<Vertex,Weight>::getEdges() const                              //function signature
{
    return m_edges;
}

/**
 * Returns a vector containing all @a PartialEdges that the given vertex
 * connects to.
 *
 * If the vertex doesn't exist in the graph, an empty vector is returned.
 *
 * @param vertex Vertex to obtain all the edges from
 * @return A vector of all the edges of the given vertex
 */
template<typename Vertex, typename Weight>
const typename undirected_graph<Vertex,Weight>::VertexEdges&                //return type
undirected_graph<Vertex,Weight>::getVertexEdges(const Vertex& vertex) const //function signature
{
    static VertexEdges error;
    error = VertexEdges();

    /*
     * Return the vertex edges if vertex exists;
     * otherwise return an empty one
     */
    auto it = m_edges.find(vertex);
    return it != m_edges.cend() ? it->second : error;
}

/**
 * Adds a vertex to the graph. This vertex won't be connected to any
 * other vertex in the graph.
 *
 * @param vertex Vertex to add to the graph
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addVertex(const Vertex& vertex)
{
    if(!vertexExists(vertex))
        m_edges[vertex];
}

/**
 * Adds a edge to the graph that connects the given vertices.
 *
 * If either given vertex doesn't exist, the vertex will be added.
 *
 * @param end1 First end vertex of the new edge
 * @param end2 Second end vertex of the new edge
 * @param weight Weight of the new edge
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addEdge(const Vertex& end1, const Vertex& end2, const Weight& weight)
{
    /* Make sure end vertices exist */
    addVertex(end1);
    addVertex(end2);

    PartialEdge end1End2Edge(end2, weight);
    PartialEdge end2End1Edge(end1, weight);

    VertexEdges& end1Edges = m_edges[end1];
    VertexEdges& end2Edges = m_edges[end2];

    //Lambda for comparing the weights of partial edges
    auto weightCmp = [](const PartialEdge& a, const PartialEdge& b)
                     {return a.second < b.second;};

    /* Get iterator to the beginning of the upper bound and insert at that iterator */
    auto it = std::upper_bound(end1Edges.cbegin(), end1Edges.cend(), end1End2Edge, weightCmp);
    end1Edges.insert(it, end1End2Edge);

    it = std::upper_bound(end2Edges.cbegin(), end2Edges.cend(), end2End1Edge, weightCmp);
    end2Edges.insert(it, end2End1Edge);
}

/**
 * Adds a edge to the graph that connects the given vertices.
 *
 * This is an overloaded function that extracts all the values from @a edge
 * and passes them into the other function.
 *
 * @param edge Edge to add
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addEdge(const CompleteEdge& edge)
{
    /* Extract vertices and weight */
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    addEdge(end1, end2, weight);
}

/**
 * Removes a vertex and all edges connecting to the vertex.
 *
 * This function calls @a removeEdge() on each partial edge that
 * connects to the given vertex. This confirms that all edges
 * with connections to the given vertex are removed.
 *
 * @param vertex Vertex to remove from the graph
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeVertex(const Vertex& vertex)
{
    /* Remove each edge of the vertex */
    for(const PartialEdge& edge : getVertexEdges(vertex))
        removeEdge(CompleteEdge(vertex, edge.first, edge.second));

    //Remove entry in edges
    m_edges.erase(vertex);
}

/**
 * Removes an edge from the graph. The edge is removed from both end
 * vertices.
 *
 * Vertices aren't touched, allowing vertices to exist unconnected.
 *
 * @param end1 First end vertex of the edge to remove
 * @param end2 Second end vertex of the edge to remove
 * @param weight Weight of the edge to remove
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeEdge(const Vertex& end1, const Vertex& end2, const Weight& weight)
{
    PartialEdge end1End2Edge(end2, weight);
    PartialEdge end2End1Edge(end1, weight);

    VertexEdges& end1Edges = getVertexEdges(end1);
    VertexEdges& end2Edges = getVertexEdges(end2);

    /* Delete end2 vertices from end1's edges */
    auto removeEnd2 = std::remove_if(end1Edges.begin(), end1Edges.end(), end1End2Edge);
    end1Edges.erase(removeEnd2);

    /* Delete end1 vertices from end2's edges */
    auto removeEnd1 = std::remove_if(end2Edges.begin(), end2Edges.end(), end2End1Edge);
    end2Edges.erase(removeEnd1);
}

/**
 * Removes an edge from the graph. The edge is removed from both end
 * vertices.
 *
 * This is an overloaded function that extracts all the values from @a edge
 * and passes them into the other function.
 *
 * @param edge Edge to remove
 */
template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeEdge(const CompleteEdge& edge)
{
    /* Extract vertices and weight */
    const Vertex& end1 = std::get<0>(edge);
    const Vertex& end2 = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    removeEdge(end1, end2, weight);
}

/**
 * An algorithm that searches through the graph recursively.
 *
 * The search is accomplished by finding the smallest weighted edge
 * of the current vertex (thanks to @a addEdge(), the edges are
 * ascendingly sorted by weight) and traversing to the end
 * vertex of that edge. This is repeated until all vertices have
 * been traversed or no more edges can be discovered.
 *
 * Each traversed edge is put into the discovery edge list and is
 * returned along with the total weight of the discovery edges.
 *
 * Note:
 * If vertices are unconnected, they will not be traversed since
 * they do not have edges. In addition, any sub-graph that is
 * unconnected to another sub-graph may not be traversed if the
 * starting vertex isn't in the sub-graph.
 *
 * @param start Vertex to start the search from
 * @return An @a std::pair of the discovery edges and total weight of
 *         the discovery edges
 */
template<typename Vertex, typename Weight>
std::pair<std::list<typename undirected_graph<Vertex,Weight>::CompleteEdge>,Weight> //return type
undirected_graph<Vertex,Weight>::depthFirstSearch(const Vertex& start) const        //function signature
{
    std::set<Vertex> visited;
    std::list<CompleteEdge> discoveryEdges;
    Weight totalWeight = DFSHelper(start, visited, discoveryEdges);

    return std::make_pair(discoveryEdges, totalWeight);
}

/**
 * An algorithm that searches through the graph.
 *
 * The search is accomplished by pushing the end vertices of all the
 * vertex's edges of the current vertex onto a queue with smallest
 * weight first (thanks to @a addEdge(), the edges are ascendingly
 * sorted by weight). For each of these edges, the weight of the
 * edge is added to the total and the edge is added to the
 * discovery edge list. The queue is then popped and the current
 * vertex is now the queue's front. This is repeated until the queue
 * is empty.
 *
 * Each traversed edge is put into the discovery edge list and is
 * returned along with the total weight of the discovery edges.
 *
 * Note:
 * If vertices are unconnected, they will not be traversed since
 * they do not have edges. In addition, any sub-graph that is
 * unconnected to another sub-graph may not be traversed if the
 * starting vertex isn't in the sub-graph.
 *
 * @param start Vertex to start the search from
 * @return An @a std::pair of the discovery edges and total weight of
 *         the discovery edges
 */
template<typename Vertex, typename Weight>
std::pair<std::list<typename undirected_graph<Vertex,Weight>::CompleteEdge>,Weight> //return type
undirected_graph<Vertex, Weight>::breadthFirstSearch(const Vertex& start) const     //function signature
{
    /* Returned variables */
    std::list<CompleteEdge> discoveryEdges;
    Weight totalWeight = Weight();

    /* Check if vertex exists */
    if(!vertexExists(start))
        return std::make_pair(discoveryEdges, Weight());

    std::map<Vertex,int> vertexToId;
    std::queue<Vertex> queue;
    bool visited[getVertices().size()];
    int id = 0;
    int idStart;

    /* Go through all verticies and assign an id and bool value for visited */
    for(const Vertex& vertex : getVertices())
    {
        visited[id] = false;
        vertexToId[vertex] = id;

        /* Set idStart to start id */
        if(vertex == start)
            idStart = id;

        id++;
    }

    /* Pushing start to the queue and setting idStart to visited */
    queue.push(start);
    visited[idStart] = true;

    while(!queue.empty())
    {
        //Get edges for the vertex at the front of the queue
        const VertexEdges& edges = getVertexEdges(queue.front());

        /*
         * For each edge in edges if the vertex hasn't been visited add to `discoveryEdges`, push
         * the vertex to `queue`, add weight to `totalWeight` and mark vertex as visited
         */
        for(const PartialEdge& edge : edges)
        {
            if(!visited[vertexToId[edge.first]])
            {
                discoveryEdges.push_back(CompleteEdge(queue.front(), edge.first, edge.second));
                totalWeight += edge.second;
                queue.push(edge.first);
                visited[vertexToId[edge.first]] = true;
            }
        }

        //Remove vertex from queue
        queue.pop();
    }

    return std::make_pair(discoveryEdges, totalWeight);
}

/**
 * An algorithm that finds the minimum spanning tree of the graph.
 *
 * This algorithm is accomplished by finding the smallest weighted
 * edge that is connected to the collection of vertices (the vertex
 * cloud). Each of these edges are added to the discovery edge list
 * and their weight is added to a total. This is done until the
 * collection of vertices is equal to the total number of vertices.
 *
 * Each traversed edge is put into the discovery edge list and is
 * returned along with the total weight of the discovery edges.
 *
 * Note:
 * Prim's MST algorithm  doesn't work well when a sub-graph is
 * unconnected to another sub-graph.
 *
 * @param start Vertex to start Prim's MST algorithm from
 * @return An @a std::pair of the discovery edges and total weight of
 *         the discovery edges
 */
template<typename Vertex, typename Weight>
std::pair<std::list<typename undirected_graph<Vertex,Weight>::CompleteEdge>,Weight> //return type
undirected_graph<Vertex,Weight>::primsMST(const Vertex& start) const                //function signature
{
    /* Returned variables */
    std::list<CompleteEdge> discoveryEdges;
    Weight totalWeight = Weight();

    /* Mark start as visited */
    std::set<Vertex> visited;
    visited.insert(start);

    while(visited.size() != getVertices().size())
    {
        /* Minimum edge data */
        CompleteEdge minEdge;
        const Vertex& endVertex = std::get<1>(minEdge);
        const Weight& minEdgeWeight = std::get<2>(minEdge);
        bool minEdgeInitialized = false;

        /* Find next min edge connecting to the visited vertices */
        for(const Vertex& vertex : visited)
        {
            /* Look through the current vertex's edges */
            for(const PartialEdge& edge : getVertexEdges(vertex))
            {
                /* Extract "to" vertex and weight */
                const Vertex& to = edge.first;
                const Weight& weight = edge.second;

                /* Check if the "to" vertex has been visited */
                if(visited.count(to) != 0)
                    continue;

                CompleteEdge currEdge(vertex, to, weight);
                CompleteEdge reverseCurrEdge(to, vertex, weight);

                bool currEdgeVisited = std::find(discoveryEdges.cbegin(), discoveryEdges.cend(), currEdge) != discoveryEdges.cend();
                bool reverseCurrEdgeVisited = std::find(discoveryEdges.cbegin(), discoveryEdges.cend(), reverseCurrEdge) != discoveryEdges.cend();

                /* Check if edge has been discovered */
                if(!currEdgeVisited && !reverseCurrEdgeVisited)
                {
                    if(!minEdgeInitialized)
                    {
                        /*
                         * We need an initial edge to compare the rest
                         * of the edges with, so we initialize the first
                         * non-discovered edge to the minimum edge
                         */
                        minEdge = currEdge;
                        minEdgeInitialized = true;
                    }
                    else if(weight < minEdgeWeight)
                    {
                        /*
                         * If the current edge and reverse of the current edge
                         * hasn't been discovered yet and the current edge has
                         * less weight than the current minimum edge, then
                         * mark the current edge as the new minimum edge
                         */
                        minEdge = currEdge;
                    }
                }
            }
        }

        discoveryEdges.push_back(minEdge);

        //Mark the end vertex of the min edge as visisted
        visited.insert(endVertex);

        //Add the min edge's weight
        totalWeight += minEdgeWeight;
    }

    return std::make_pair(discoveryEdges, totalWeight);
}

/**
 * An algorithm that finds the shortest path to all the vertices
 * from a starting vertex.
 *
 * @param vertex Vertex to start Dijkstra's algorithm from
 * @param visited Set of all visited vertices
 * @param discoveryEdges Vector of all discovery edges
 * @param vertexInfo Vertex-cost of each vertex in the graph
 */
template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex, Weight>::dijkstraTraversal(const Vertex& vertex,
                                                           std::map<Vertex,std::pair<Weight,Vertex>>& vertexInfo) const
{
    std::set<Vertex> visisted;
    std::vector<CompleteEdge> discoveryEdges;
    Weight total = Weight();
    using VertexInfo = std::pair<Weight,Vertex>;
    if(!vertexExists(vertex))
        return total;
    else
    {
        //add starting vertex to the cloud and visited verticies
        std::vector<Vertex> externalCloudNodes;
        vertexInfo[vertex] = std::pair<Weight,Vertex>(Weight(),vertex);
        externalCloudNodes.push_back(vertex);
        visisted.insert(vertex);
        //actual dijkstra's starts here
        while(externalCloudNodes.size() != 0)
        {
            //make first element in externalCloudNode the starting node
            Vertex startVertex = externalCloudNodes[0];
            Vertex endVertex = startVertex;
            Weight edgeWeight, totalEdgeWeight;
            //collect in first non visited edge from external node cloud
            for(const PartialEdge& edge: getVertexEdges(externalCloudNodes[0]))
            {
                //if not visited add this to current vertex to denote the starting edge
                if(visisted.count(edge.first) != 1)
                {
                    endVertex = edge.first;
                    edgeWeight = edge.second;
                    totalEdgeWeight = (*vertexInfo.find(externalCloudNodes[0])).second.first +edge.second;
                    break;
                }
            }
            //loop through all external cloud nodes and find edge of least weight and of a non visited node
            for(typename std::vector<Vertex>::iterator it = externalCloudNodes.begin(); it != externalCloudNodes.end(); ++it)
            {
                int externalNonvisitedChildren = 0; //used to tell if node becomes internal
                //loop through all edges of an external node to find the least costly edge
                for(const PartialEdge& edge : getVertexEdges(*it))
                {
                    //get the current cost to travel to that node from the current external node
                    typename std::map<Vertex,VertexInfo>::iterator currentCost = vertexInfo.find(*it);
                    bool  needToVisit = visisted.count(edge.first) != 1;
                    if(needToVisit) ++externalNonvisitedChildren; //if has unvisited connections increment
                    //if connected node is unvisited and has the cheapest cost set it to currently cheapest edge
                    if(needToVisit &&  (currentCost != vertexInfo.end() && (*currentCost).second.first + edge.second < totalEdgeWeight))
                    {
                        startVertex = *it;
                        endVertex = edge.first;
                        edgeWeight = edge.second;
                        totalEdgeWeight = (*currentCost).second.first + edge.second;
                    }
                }
                //make node internal if it has no external connections
                if(externalNonvisitedChildren == 0)
                {
                    typename std::vector<Vertex>::iterator tmp = std::find(externalCloudNodes.begin(), externalCloudNodes.end(),*it);
                    int dist = tmp - externalCloudNodes.begin();
                    externalCloudNodes.erase(tmp);
                    it = externalCloudNodes.begin() +(dist-1);
                }
            }
            //if found a suitable edge, add it to the cloud, discovered edges, and add the weight of the edge to running total
            if(endVertex != startVertex)
            {
                vertexInfo[endVertex] = std::pair<Weight,Vertex>(totalEdgeWeight,startVertex);
                visisted.insert(endVertex);
                externalCloudNodes.push_back(endVertex);
                discoveryEdges.push_back(CompleteEdge(startVertex, endVertex, edgeWeight));
                total += edgeWeight;
            }
        }
    }
    return total;
}

/**
 * This function takes two verticies and returns all the edges between the
 * two verticies and the total Weight of all the edges
 *
 * @param vertexFrom records all edges starting from this Vertex (origin)
 * @param vertexTo records all edges between start and this vertex (destination)
 */
template<typename Vertex, typename Weight>
std::pair<std::list<std::pair<Vertex,Vertex>>,Weight>
undirected_graph<Vertex, Weight>::dijkstraTraversal(const Vertex& vertexFrom, const Vertex& vertexTo) const
{
    std::map<Vertex,std::pair<Weight,Vertex>> routes;
    std::list<std::pair<Vertex,Vertex>> route;

    if(vertexExists(vertexFrom) && vertexExists(vertexFrom))
    {
        /* Get all possible routes */
        dijkstraTraversal(vertexFrom, routes);

        /* Declare and initializing variable needed to trace back from vertexTo until I reach vertexFrom*/
        bool finished = false;
        Vertex parentFrom = routes[vertexTo].second;
        Vertex parentTo = vertexTo;

        // Record the total distance
        Weight totalDistance = routes[vertexTo].first;

        /* Keep tracing back to the parent until the parent is `vertexFrom` */
        while (!finished)
        {
            route.push_front(std::pair<Vertex,Vertex>(parentFrom,parentTo));
            if (parentFrom == vertexFrom)
            {
                finished = true;
            }
            else
            {
                parentTo = parentFrom;
                parentFrom = routes[parentFrom].second;
            }
        }
        return std::pair<std::list<std::pair<Vertex,Vertex>>,Weight>(route,totalDistance);
    }
    return std::pair<std::list<std::pair<Vertex,Vertex>>,Weight>(route,Weight());
}

/**
 * The helper for @a depthFirstSearch().
 *
 * Actually computes the depth-first search.
 *
 * @param vertex Current vertex
 * @param visited Set of all visited vertices
 * @param discoveryEdges List of all discovered edges
 * @return Total weight of the depth-first search.
 */
template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex,Weight>::DFSHelper(const Vertex& vertex,
                                                  std::set<Vertex>& visited,
                                                  std::list<CompleteEdge>& discoveryEdges) const
{
    //Visit current vertex
    visited.insert(vertex);

    Weight totalWeight = Weight();

    /* Visit each edge of the current vertex */
    for(const PartialEdge& edge : getVertexEdges(vertex))
    {
        const Vertex& endVertex = edge.first;
        const Weight& edgeWeight = edge.second;
        CompleteEdge complEdge(vertex, endVertex, edgeWeight);

        bool endVertexVisited = visited.count(endVertex) == 1;

        if(!endVertexVisited)
        {
            //Track the next edge
            discoveryEdges.push_back(complEdge);

            //Add the next edge's weight
            totalWeight += edgeWeight;

            //Add the weight of future traversals to total
            totalWeight += DFSHelper(endVertex, visited, discoveryEdges);
        }
    }

    return totalWeight;
}
}
