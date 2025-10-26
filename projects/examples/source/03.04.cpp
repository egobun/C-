//////////////////////////////////

#include <cassert>
#include <iostream>

//////////////////////////////////

class Entity
{
public :

    Entity(int x) : m_x(x) {}

//  -------------------------

    auto get() const //внутри функции нельзя изменять поля класса и вызывать не константные методы этого класса 
    { 
    //	++m_x; // error

        return m_x;
    }

//  -------------------------

//	void set_v1(int x) // bad
//  { 
//      m_x = x; 
//  }

//  -------------------------

    void set_v2(int x) 
    { 
        if (x > 0)
        {
            m_x = x;
        }
    }

//  -------------------------

    void test() const;

private :

    int m_x = 0;
};

//////////////////////////////////

void Entity::test() const
{
    std::cout << "Entity::test\n";
}

//////////////////////////////////

int main()
{
	Entity       entity_1(1);

    Entity const entity_2(2); //!!!нельзя изменять его поля и вызывать не const методы после создания

//  ----------------------------
		
    assert(entity_1.get() == 1);

    assert(entity_2.get() == 2);

//  ----------------------------

	entity_1.set_v2(2);

//  entity_2.set_v2(3); // error

//  ----------------------------
		
    assert(entity_1.get() == 2);

    assert(entity_2.get() == 2);

//  ----------------------------

    entity_1.test();
}

//////////////////////////////////