#ifndef GRAPH_TESTING_H
#define GRAPH_TESTING_H
#include <fstream>
#include <string>
#include "graph.h"
#include "city.h"

class Test {
    Graph<City, double, string> readCities();
public:
    Test(){};
    void findPath(string from, string to);
};

#endif //GRAPH_TESTING_H
