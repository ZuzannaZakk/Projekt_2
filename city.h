#ifndef GRAPH_CITY_H
#define GRAPH_CITY_H
#include <string>
#include "vector.h"
using namespace std;
class City
{
private:
    Vector<2> position;
    string name;
public:
    City(){};
    City(string name, Vector<2> position);
    Vector<2> getPosition();
    string getName();
};

#endif //GRAPH_CITY_H
