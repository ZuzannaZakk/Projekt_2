#ifndef GRAPH_VECTOR_H
#define GRAPH_VECTOR_H
#include <cmath>
using namespace std;
template<size_t dim>
class Vector
{
private:
    double cords[dim];
public:
    Vector()
    {
        for (size_t i = 0; i < dim; i++)
        {
            cords[i] = 0;
        }
    }
    Vector(double *arr)
    {
        for (size_t i = 0; i < dim; i++)
        {
            cords[i] = arr[i];
        }
    }
    Vector<dim> operator+(const Vector<dim> &b) const
    {
        Vector<dim> result = Vector<dim>();
        for (size_t i = 0; i < dim; i++)
        {
            result.cords[i] = cords[i] + b.cords[i];
        }
        return result;
    }
    Vector<dim> operator-(const Vector<dim> &b) const
    {
        Vector<dim> result = Vector<dim>();
        for (size_t i = 0; i < dim; i++)
        {
            result.cords[i] = cords[i] - b.cords[i];
        }
        return result;
    }

    double length() const
    {
        double res = 0.0;
        for (size_t i = 0; i < dim; i++)
        {
            res += cords[i] * cords[i];
        }
        return sqrt(res);
    }
};

#endif //GRAPH_VECTOR_H
