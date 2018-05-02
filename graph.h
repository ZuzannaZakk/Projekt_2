#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <list>
#include <exception>
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
                : destination(destination), weight(weight) {}
    };
    struct Vertex
    {
        TData data;
        TIndex id;
        multiset<Edge> adj;    //wychodzace "sasiedztwo"
        multiset<Edge> revAdj; //wchodzace "sasiedztwo"
        Vertex(const TData &data, const TIndex &id)
                : data(data), id(id) {}
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
    list<TIndex> getVertices() const //lista z "zawartoscia" wierzcholkow
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
    void deleteVertex(const TIndex &id)
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
    }
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
                    vertices.find(to)->second.revAdj.insert(Edge(from, weight));
                }
    }
    void deleteEdge(const TIndex &from, const TIndex &to, const TDist &weight)
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
    }
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
};

#endif
