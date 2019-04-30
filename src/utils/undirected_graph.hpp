#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>

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
    bool edgeExists(const Vertex& from, const Vertex& to, const Weight&) const;
    bool edgeExists(const CompleteEdge&) const;
    bool emptyVertices() const;
    bool emptyEdges() const;

    /* Getters */
    std::set<Vertex> getVertices() const;
    const std::map<Vertex,VertexEdges>& getEdges() const;
    const VertexEdges& getVertexEdges(const Vertex&) const;

    /* Adders */
    void addVertex(const Vertex&);
    void addEdge(const Vertex& from, const Vertex& to, const Weight&);
    void addEdge(const CompleteEdge&);

    /* Removers */
    void removeVertex(const Vertex&);
    void removeEdge(const Vertex& from, const Vertex& to, const Weight&);
    void removeEdge(const CompleteEdge&);

    /* Searches */
    Weight depthFirstSearch(const Vertex& start,
                            std::set<Vertex>& visisted,
                            std::vector<CompleteEdge>& discoveredEdges,
                            std::vector<CompleteEdge>& backEdges) const;

    Weight breadthFirstSearch(const Vertex& start, std::vector<CompleteEdge>& discoveredEdges) const;

    /* Shortest-path */
    Weight dijkstraTraversal(const Vertex& vertex,
                             std::set<Vertex>& visisted,
                             std::vector<CompleteEdge>& discoveredEdges,
                             std::map<Vertex,std::pair<Weight,Vertex>>& vertexInfo) const;

    /* Minimum spanning tree */
    Weight primsMST(const Vertex& start, std::vector<CompleteEdge>& discoveryEdges);

private:
    /* Helpers */
    Weight DFSHelper(const Vertex& current,
                     const Vertex& parent,
                     std::set<Vertex>& visisted,
                     std::vector<CompleteEdge>& discoveredEdges,
                     std::vector<CompleteEdge>& backEdges) const;

    std::map<Vertex,VertexEdges> m_edges;
};

template<typename Vertex, typename Weight>
undirected_graph<Vertex,Weight>::undirected_graph(const std::vector<CompleteEdge>& edges)
{
    for(const CompleteEdge& edge : edges)
        addEdge(edge);
}

template<typename Vertex, typename Weight>
std::set<Vertex> undirected_graph<Vertex,Weight>::getVertices() const
{
    std::set<Vertex> vertices;

    for(const std::pair<Vertex,VertexEdges>& vertexEdge : m_edges)
        vertices.insert(vertexEdge.first);

    return vertices;
}

template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::vertexExists(const Vertex& vertex) const
{
    return m_edges.count(vertex) != 0;
}

template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::edgeExists(const Vertex& from, const Vertex& to, const Weight& weight) const
{
    /*
     * Get the edges of the "from" vertex and
     * see if the partial edge exists
     */
    const VertexEdges& edges = m_edges[from];
    return std::binary_search(edges.cbegin(), edges.cend(), PartialEdge(to, weight)) != edges.cend();
}

template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::edgeExists(const CompleteEdge& edge) const
{
    /* Extract vertices and weight */
    const Vertex& from = std::get<0>(edge);
    const Vertex& to = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    return edgeExists(from, to, weight);
}

template<typename Vertex, typename Weight>
bool undirected_graph<Vertex,Weight>::emptyVertices() const
{
    return m_edges.empty();
}

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

template<typename Vertex, typename Weight>
const std::map<Vertex, typename undirected_graph<Vertex,Weight>::VertexEdges>& undirected_graph<Vertex,Weight>::getEdges() const
{
    return m_edges;
}

template<typename Vertex, typename Weight>
const typename undirected_graph<Vertex,Weight>::VertexEdges& undirected_graph<Vertex,Weight>::getVertexEdges(const Vertex& vertex) const
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

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addVertex(const Vertex& vertex)
{
    if(!vertexExists(vertex))
        m_edges[vertex];
}

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addEdge(const Vertex& from, const Vertex& to, const Weight& weight)
{
    /* Store vertices */
    addVertex(from);
    addVertex(to);

    PartialEdge fromToEdge(to, weight);
    PartialEdge toFromEdge(from, weight);

    //Lambda for comparing the weights of partial edges
    auto weightCmp = [](const PartialEdge& a, const PartialEdge& b)
                     {return a.second < b.second;};

    /* Get iterator to the beginning of the upper bound and insert at that iterator */
    auto it = std::upper_bound(m_edges[from].cbegin(), m_edges[from].cend(), fromToEdge, weightCmp);
    m_edges[from].insert(it, fromToEdge);

    it = std::upper_bound(m_edges[to].cbegin(), m_edges[to].cend(), toFromEdge, weightCmp);
    m_edges[to].insert(it, toFromEdge);
}

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::addEdge(const CompleteEdge& edge)
{
    /* Extract vertices and weight */
    const Vertex& from = std::get<0>(edge);
    const Vertex& to = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    addEdge(from, to, weight);
}

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeVertex(const Vertex& vertex)
{
    /* Remove each edge of the vertex */
    for(const PartialEdge& edge : getVertexEdges(vertex))
        removeEdge(CompleteEdge(vertex, edge.first, edge.second));

    //Remove entry in edges
    m_edges.erase(vertex);
}

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeEdge(const Vertex& from, const Vertex& to, const Weight& weight)
{
    //Lambda for checking if certain edge matches removal edge
    auto matchingEdge = [&](const PartialEdge& edge)
                        {return edge.first == from && edge.second == weight;};

    /* Delete "from" end vertices from "to" edges */
    auto removeFrom = std::remove_if(m_edges[to].begin(), m_edges[to].end(), matchingEdge);
    m_edges[to].erase(removeFrom);

    /* Delete "to" end vertices from "from" edges */
    auto removeTo = std::remove_if(m_edges[from].begin(), m_edges[from].end(), matchingEdge);
    m_edges[from].erase(removeTo);
}

template<typename Vertex, typename Weight>
void undirected_graph<Vertex,Weight>::removeEdge(const CompleteEdge& edge)
{
    /* Extract vertices and weight */
    const Vertex& from = std::get<0>(edge);
    const Vertex& to = std::get<1>(edge);
    const Weight& weight = std::get<2>(edge);

    removeEdge(from, to, weight);
}

template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex,Weight>::depthFirstSearch(const Vertex& start,
                                                          std::set<Vertex>& visited,
                                                          std::vector<CompleteEdge>& discoveredEdges,
                                                          std::vector<CompleteEdge>& backEdges) const
{
    /* Clear containers */
    visited.clear();
    discoveredEdges.clear();
    backEdges.clear();

    return DFSHelper(start, Vertex(), visited, discoveredEdges, backEdges);
}

template <typename Vertex, typename Weight>
Weight undirected_graph<Vertex, Weight>::breadthFirstSearch(const Vertex& start, std::vector<CompleteEdge>& discoveredEdges) const
{
    //Clear containers
    discoveredEdges.clear();

    Weight totalWeight = Weight();

    //Check if vertex exists
    if(!vertexExists(start))
        return Weight();

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
         * For each edge in edges if the vertex hasn't been visited add to `discoveredEdges`, push
         * the vertex to `queue`, add weight to `totalWeight` and mark vertex as visited
         */
        for(const PartialEdge& edge : edges)
        {
            if(!visited[vertexToId[edge.first]])
            {
                discoveredEdges.push_back(CompleteEdge(queue.front(), edge.first, edge.second));
                totalWeight += edge.second;
                queue.push(edge.first);
                visited[vertexToId[edge.first]] = true;
            }
        }

        //Remove vertex from queue
        queue.pop();
    }

    return totalWeight;
}

template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex,Weight>::primsMST(const Vertex& start, std::vector<CompleteEdge>& discoveredEdges)
{
    //Clear containers
    discoveredEdges.clear();

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

                bool currEdgeVisited = std::find(discoveredEdges.cbegin(), discoveredEdges.cend(), currEdge) != discoveredEdges.cend();
                bool reverseCurrEdgeVisited = std::find(discoveredEdges.cbegin(), discoveredEdges.cend(), reverseCurrEdge) != discoveredEdges.cend();

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

        discoveredEdges.push_back(minEdge);

        //Mark the end vertex of the min edge as visisted
        visited.insert(endVertex);

        //Add the min edge's weight
        totalWeight += minEdgeWeight;
    }

    return totalWeight;
}

template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex, Weight>::dijkstraTraversal(const Vertex& vertex,
                                                           std::set<Vertex>& visisted,
                                                           std::vector<CompleteEdge>& discoveredEdges,
                                                           std::map<Vertex,std::pair<Weight,Vertex>>& vertexInfo) const
{
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
                discoveredEdges.push_back(CompleteEdge(startVertex, endVertex, edgeWeight));
                total += edgeWeight;
            }
        }
    }
    return total;
}

template<typename Vertex, typename Weight>
Weight undirected_graph<Vertex,Weight>::DFSHelper(const Vertex& vertex,
                                                  const Vertex& parent,
                                                  std::set<Vertex>& visited,
                                                  std::vector<CompleteEdge>& discoveredEdges,
                                                  std::vector<CompleteEdge>& backEdges) const
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
            discoveredEdges.push_back(complEdge);

            //Add the next edge's weight
            totalWeight += edgeWeight;

            //Add the weight of future traversals to total
            totalWeight += DFSHelper(endVertex, vertex, visited, discoveredEdges, backEdges);
        }
        else if(visited.size() > 1 && parent != endVertex &&
                std::find(backEdges.cbegin(), backEdges.cend(), CompleteEdge(endVertex, vertex, edgeWeight)) == backEdges.cend())
        {
            /*
             * If the next vertex was visited before,
             * we have visited more than 1 vertex,
             * the parent vertex isn't the next vertex,
             * and the next edge isn't already in the backedge list,
             * then the next edge is a backedge.
             */
            backEdges.push_back(complEdge);
        }
    }

    return totalWeight;
}
