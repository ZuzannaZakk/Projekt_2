#ifndef GRAPH_TESTING_H
#define GRAPH_TESTING_H
Graph<City, double, string> readCities(istream &ss)
{
    Graph<City, double, string> graph;
    int howManyCities = 0, howManyRoads = 0;
    ss >> howManyCities >> howManyRoads;
    string name;
    double pos[2];
    while(howManyCities--)
    {
        ss >> name >> pos[0] >> pos[1];
        graph.addVertex(City(name, Vector<2>(pos)), name);
        if(!graph.existsVertex(name))
            throw invalid_argument("Nie dodano wierzchoka.");
    }
    string from, to;
    //double len;
    while(howManyRoads--)
    {
        ss >> from >> to;
        graph.addEdge(from, to, (graph.getData(from).getPosition() - graph.getData(to).getPosition()).length());
        if(!graph.existsEdge(from, to, (graph.getData(from).getPosition() - graph.getData(to).getPosition()).length()))
            throw invalid_argument("Nie dodano krawedzi.");
    }
    return graph;
}

#endif //GRAPH_TESTING_H
