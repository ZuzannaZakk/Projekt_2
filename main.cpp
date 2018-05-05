#include "graph.h"
#include "city.h"
#include "testing.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string a[] = {"10 4\n",
    "Warszawa 0 0\n",
    "NewYork 100 100\n",
    "Radom 12.5 13.5\n",
    "Sopot -13 -12.0\n",
    "Orlean 123 1238\n",
    "Waszyngton 9 9\n",
    "SanEscobar 256 128\n",
    "Rzym -500 -200\n",
    "Sosnowiec -0.5 -0.7\n",
    "Radkom 11 19\n",
    "Warszawa NewYork\n",
    "NewYork Radkom\n",
    "NewYork Warszawa\n"
    "Radkom Radom"};
    string s;
    for(auto i: a)
    {
        s += i;
    }
    istringstream input(s);
    auto graph = readCities(input);
   // cout << graph.toString() << endl;
    auto ar = AStar(graph, string("Warszawa"), string("Radom"), euclidHeur);
    auto dr = dijkstra(graph, string("Warszawa"), string("Radom"));
    double ad = ar.second; //odl astar
    double dd = dr.second; //odl dijkstra
    cout << "Odleglosc AStar : " << ad << endl;
    cout << "Odleglosc Dijkstra : " << dd << endl;
    cout << "AStar sciezka :" << endl;
    for(auto i : ar.first)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "Dijkstra sciezka :" << endl;
    for(auto i : dr.first)
    {
        cout << i << " ";
    }
    cout << endl;

    fstream file("test.txt");
    auto g = readCities(file);
   // cout << g.toString() << endl;
    auto as = AStar(g, string("Aberdeen"), string("Amarillo"), euclidHeur);
    auto d = dijkstra(g, string("Aberdeen"), string("Amarillo"));
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
    file.close();
}
