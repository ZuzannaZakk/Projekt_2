#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <list>
#include <exception>
#include <queue>
#include <sstream>
using namespace std;
template<typename TData, typename TDist = double, typename TIndex = TData>
class Graph
{
private:
    struct Edge
    {
        TIndex destination;
        TDist weight;
        Edge(const TIndex &destination, const TDist &weight)
                : destination(destination), weight(weight){}
        bool operator<(const Edge &b) const
        {
            return weight < b.weight;
        }
    };
    struct Vertex
    {
        TData data;
        TIndex id;
        multiset<Edge> adj;    //wychodzace "sasiedztwo"
        //multiset<Edge> revAdj; //wchodzace "sasiedztwo"
        Vertex(const TData &data, const TIndex &id)
                : data(data), id(id){}
        string toString() const
        {
            ostringstream oss;
            oss << id << "\n";
            for(const auto &e : adj)
            {
                oss << "\"" << id << "\"" << " -> " << "\"" << e.destination << "\"" << "\n";
            }
            return oss.str();
        }
    };
    map<TIndex, Vertex> vertices;
    bool existsVertices(const TIndex &a, const TIndex &b) const
    {
        return existsVertex(a) && existsVertex(b);
    }
public:
    bool existsVertex(const TIndex &id) const
    {
        return vertices.find(id) != vertices.end();
    }
    list<TIndex> getVertices() const
    {
        list<TIndex> res;
        for (const auto &v : vertices)
        {
            res.push_back(v.second.id);
        }
        return res;
    }
    void addVertex(const TData &data, const TIndex &id)
    {
        if(existsVertex(id))
        {
            throw invalid_argument("Podany wierzcholek istnieje.");
        }
            else
            {
            vertices.insert(make_pair(id, Vertex(data, id)));
            }
    }
    void addVertex(const TData &data)
    {
        addVertex(data, data);
    }
    /*void deleteVertex(const TIndex &id)
    {
        if(!existsVertex(id))
        {
            throw invalid_argument("Brak podanego wierzchoka.");
        } else
            {
                const Vertex &v = vertices.find(id)->second;
                for(const auto &a : v.revAdj)
                {
                    vertices.find(a.destination)->second.adj.erase(Edge(id, a.weight));
                }
                for(const auto &a : v.adj)
                {
                    vertices.find(a.destination)->second.revAdj.erase(Edge(id, a.weight));
                }
                vertices.erase(id);
            }
    }*/
    bool existsEdge(const TIndex &from, const TIndex &to, const TDist &weight)
    {
        return (vertices.find(from) != vertices.end() && vertices.find(to) != vertices.end() && vertices.find(from)->second.adj.find(Edge(to, weight))!= vertices.find(from)->second.adj.end());
    }
    void addEdge(const TIndex &from, const TIndex &to, const TDist &weight)
    {
        if(!existsVertices(from, to))
            {
            throw invalid_argument("Brak podanego wierzchoka.");
            }
                else
                {
                    vertices.find(from)->second.adj.insert(Edge(to, weight));
                    //vertices.find(to)->second.revAdj.insert(Edge(from, weight));
                }
    }
    /*void deleteEdge(const TIndex &from, const TIndex &to, const TDist &weight)
    {
        if (!existsVertices(from, to))
        {
            throw invalid_argument("Brak podanego wierzchoka.");
        } else if(!existsEdge(from, to, weight))
            {
                throw invalid_argument("Brak podanej krawedzi.");
            } else
                {
                vertices.find(from)->second.adj.erase(Edge(to, weight));
                vertices.find(to)->second.revAdj.erase(Edge(from, weight));
                }
    }*/
    TData getData(const TIndex &id) const
    {
        if(!existsVertex(id))
            {
                throw invalid_argument("Brak podanego wierzcholka.");
            } else
                {
                return vertices.find(id)->second.data;
                }
    }
    list<pair<TIndex, TDist>> getAdjacencyList(const TIndex &id) const //krawedzi
    {
        if(!existsVertex(id))
            {
                throw invalid_argument("Brak podanego wierzcholka.");
            } else
                {
                    const Vertex &v = vertices.find(id)->second;
                    list<pair<TIndex, TDist>> result;
                    for(const auto &a : v.adj)
                    {
                        result.push_back(make_pair(a.destination, a.weight));
                    }
                    return result;
                }
    }
    string toString() const
    {
        ostringstream oss;
        oss << "graph {\n";
        for (const auto &v : vertices)
        {
            oss << v.second.toString();
        }
        oss << "}\n";
        return oss.str();
    }
};

template<typename TData, typename TDist = double, typename TIndex = TData>
pair<list<TIndex>, TDist> AStar(const Graph<TData, TDist, TIndex> &graph, const TIndex &start, const TIndex &destination, TDist (*heur)(const Graph<TData, TDist, TIndex>&, const TIndex&, const TIndex&))
{
    typedef pair<TDist, TIndex> qData;
    priority_queue<qData, vector<qData>, greater<qData>> queue;
    map<TIndex, TDist> g; //droga od wierzcholka start
    map<TIndex, TDist> f; //przewidywany dystans do celu
    map<TIndex, bool> proced; //czy odwiedzony
    map<TIndex, TIndex> predecessor; //poprzednicy
    predecessor[start] = start;
    g[start] = 0;
    f[start] = 0 + heur(graph, start, destination);
    queue.push(make_pair((TDist)f[start], start));
    bool reachedDestination = false;
    while (!queue.empty() && !reachedDestination)
    {
        qData proc = queue.top();
        queue.pop();
        TIndex pId = proc.second;
        if(pId != destination)
        {
            if(proced.find(pId) == proced.end())
            {
                list<pair<TIndex, TDist>> adj = graph.getAdjacencyList(pId);

                for(const auto &a : adj)
                {
                    TIndex aId = a.first;
                    TDist edgeWeight = a.second;
                    if(g.find(aId) == g.end() || g[aId] > g[pId] + edgeWeight)
                    {

                        g[aId] = g[pId] + edgeWeight;

                        predecessor[aId] = pId;
                        f[aId] = g[aId] + heur(graph, aId, destination);
                        queue.push(make_pair(f[aId], aId));
                    }
                }
                proced[pId] = true;
            }
        } else
            {
                reachedDestination = true;
            }
    }
    if (g.find(destination) == g.end())
    {
        cout << "Brak drogi." << endl;
        return make_pair(list<TIndex>(), (TDist) -1);
    } else //odtworz sciezke
        {
            pair<list<TIndex>, TDist> result = make_pair(list<TIndex>(), g[destination]);
            TIndex pos = destination;
            result.first.push_front(destination);
            pos = predecessor[pos];
            while(pos != start)
            {
                result.first.push_front(pos);
                pos = predecessor[pos];
            }
            if (destination != start)
            {
                result.first.push_front(start);
            }
            return result;
        }
}
template<typename TData, typename TDist = double, typename TIndex = TData>
TDist dijkstraHeur(const Graph<TData, TDist, TIndex> &graph, const TIndex &start, const TIndex &destination)
{
    return (TDist) 0;
}
template<typename TData, typename TDist = double, typename TIndex = TData>
TDist euclidHeur(const Graph<TData, TDist, TIndex> &graph, const TIndex &start, const TIndex &destination)
{
    return (graph.getData(start).getPosition() - graph.getData(destination).getPosition()).length();
}
template<typename TData, typename TDist = double, typename TIndex = TData>
pair<list<TIndex>, TDist> dijkstra(const Graph<TData, TDist, TIndex> &graph, const TIndex &start, const TIndex &destination)
{
    return AStar(graph, start, destination, dijkstraHeur);
}
#endif
