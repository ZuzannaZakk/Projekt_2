#include "city.h"
City::City(string name, Vector<2> position)
{
    this->name = name;
    this->position = position;
}
Vector<2> City::getPosition()
{
    return position;
}
string City::getName()
{
    return name;
}

