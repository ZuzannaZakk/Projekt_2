#include "testing.h"

Graph<City, double, string> Test::readCities()
    {
        Graph<City, double, string> graph;
        fstream file("test.txt");
        int howManyCities = 0, howManyRoads = 0;
        file >> howManyCities >> howManyRoads;
        string name;
        double pos[2];
        while(howManyCities--)
        {
            file >> name >> pos[0] >> pos[1];
            graph.addVertex(City(name, Vector<2>(pos)), name);
            if(!graph.existsVertex(name))
                throw invalid_argument("Nie dodano wierzchoka.");
        }
        string from, to;
        //double len;
        while(howManyRoads--)
        {
            file >> from >> to;
            graph.addEdge(from, to, (graph.getData(from).getPosition() - graph.getData(to).getPosition()).length());
            if(!graph.existsEdge(from, to, (graph.getData(from).getPosition() - graph.getData(to).getPosition()).length()))
                throw invalid_argument("Nie dodano krawedzi.");
        }
        file.close();
        return graph;
    }
void Test::findPath(string from, string to)
    {
        auto g = readCities();
        cout << g.toString() << endl;
        auto as = AStar(g, from, to, euclidHeur);
        auto d = dijkstra(g, from, to);
        double ad = as.second; //odl astar
        double dd = d.second; //odl dijkstra
        cout << "Odleglosc AStar : " << ad << endl;
        cout << "Odleglosc Dijkstra : " << dd << endl;
        cout << "AStar sciezka :" << endl;
        for(auto i : as.first)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "Dijkstra sciezka :" << endl;
        for(auto i : d.first)
        {
            cout << i << " ";
        }
    }
