////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <print>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

class Vector 
{
public :

    Vector(std::initializer_list < int > list) : m_vector(list) {}

//  --------------------------------------------------------------------------------

    auto const & operator[](std::size_t index) const 
    {
        std::print("Vector::operator[] (1)\n");

        return m_vector[index];
    }

//  --------------------------------------------------------------------------------

    auto & operator[](std::size_t index)
    {
        std::print("Vector::operator[] (2)\n");

        return const_cast < int & > (static_cast < Vector const & > (*this)[index]);
    }

private :

    std::vector < int > m_vector;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto const x = 1, & y = x;

//  ----------------------------------

    ++(const_cast < int & > (y));

//  ----------------------------------

    assert(x == 2);

//  ----------------------------------

    Vector vector = { 1, 2, 3, 4, 5 };

//  ----------------------------------

    assert(vector[0] == 1);
}

////////////////////////////////////////////////////////////////////////////////////