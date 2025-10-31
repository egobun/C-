//////////////////////////////////

#include <cassert>
#include <iostream>

//////////////////////////////////

// class Entity
// {
// public :

//     Entity(int x) : m_x(x) {}

// //  -------------------------

//     auto get() const //внутри функции нельзя изменять поля класса и вызывать не константные методы этого класса 
//     { 
//     //	++m_x; // error

//         return m_x;
//     }

// //  -------------------------

// //	void set_v1(int x) // bad
// //  { 
// //      m_x = x; 
// //  }

// //  -------------------------

//     void set_v2(int x) 
//     { 
//         if (x > 0)
//         {
//             m_x = x;
//         }
//     }

// //  -------------------------

//     void test() const;

// private :

//     int m_x = 0;
// };

// //////////////////////////////////

// void Entity::test() const
// {
//     std::cout << "Entity::test\n";
// }

// //////////////////////////////////

// int main()
// {
// 	Entity       entity_1(1);

//     Entity const entity_2(2); //!!!нельзя изменять его поля и вызывать не const методы после создания

// //  ----------------------------
		
//     assert(entity_1.get() == 1);

//     assert(entity_2.get() == 2);

// //  ----------------------------

// 	entity_1.set_v2(2);

// //  entity_2.set_v2(3); // error

// //  ----------------------------
		
//     assert(entity_1.get() == 2);

//     assert(entity_2.get() == 2);

// //  ----------------------------

//     entity_1.test();
// }

//////////////////////////////////

class Entity
{
public:
    friend class Attorney1;
    friend class Attorney2;

private:

    auto static inline name1 = "My name for tester1";
    
    auto static inline name2 = "My name for tester2";

    auto test_v1()
    {
        return "Entity test_v1";
    }
    auto test_v2() 
    {
        return "Entity test_v2";
    }
};

class Attorney1
{
public:

    friend class Tester1;

    static auto test_v1(Entity & entity)
    {   
       return entity.test_v1();
    }

    static auto get_Entity_name1 (Entity & entity)
    {
        return entity.name1;
    } 
};

class Attorney2
{
public:

    friend class Tester2;

    static auto test_v2(Entity & entity) 
    {   
        return entity.test_v2();
    }

    static auto get_Entity_name2 (Entity & entity)
    {
        return entity.name2;
    } 
};

class Tester1
{
public:

    void test(Entity & entity)
    {   
        std::cout << Attorney1::test_v1(entity) << std::endl;
        std::cout << Attorney1::get_Entity_name1(entity) << std::endl;
    }

private:

};

class Tester2
{
public:
    void test(Entity & entity)
    {   
        std::cout << Attorney2::test_v2(entity) << std::endl;
        std::cout << Attorney2::get_Entity_name2(entity) << std::endl;
    }
    
private:

};

int main()
{

    Entity entity;

    Tester1 tester1;
    Tester2 tester2;

    tester1.test(entity);
    tester2.test(entity);

    
}