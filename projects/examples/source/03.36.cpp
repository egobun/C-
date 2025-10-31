////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <compare>

////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x, int y) : m_x(x), m_y(y) {}

//  -------------------------------------------------------------------

    auto operator<=>(Entity const & other) const
    {
        if (m_x == 0 || other.m_x == 0)           
        { 
            return std::partial_ordering::unordered;
        }

        if (m_x < other.m_x) { return std::partial_ordering::less;    }

        if (m_x > other.m_x) { return std::partial_ordering::greater; }

        return std::partial_ordering::equivalent;
    }

private :

    int m_x = 0, m_y = 0;
};

////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1(1, 1);
    
    Entity entity_2(2, 2);

    Entity entity_3(2, 3);

    Entity entity_4(0, 4);

//  --------------------------------------------------------------------

    assert((entity_1 <=> entity_2) <  0);

    assert((entity_2 <=> entity_3) == 0);

    assert((entity_2 <=> entity_1) >  0);

//  --------------------------------------------------------------------

    assert((entity_1 <=> entity_4) == std::partial_ordering::unordered);
}

////////////////////////////////////////////////////////////////////////