//////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

//////////////////////////////////////////////////////////////

class Entity
{
private :

    friend class Attorney;

//  ----------------------------------------------------------

    static void test_v1() { std::print("Entity::test_v1\n"); }

    static void test_v2() { std::print("Entity::test_v2\n"); }
};

//////////////////////////////////////////////////////////////

class Attorney 
{
private :

    friend class Client;

//  --------------------------------------

    static void test_v1() 
    {
        std::print("Attorney::test_v1\n");

        Entity::test_v1();
    }

//  --------------------------------------

    static void test_v2() 
    {
        std::print("Attorney::test_v2\n");
    }
};


///////////////////////////////////////////////////////////////
//!!!если мы хотим вызвать функции test_v1 и v2 у конкретного экземпляра Entity
//в main создается экземпляр entuty и client, clirnt принимает этот экземпляр entity
//и передает его в функцию test от Attorney, где Attorney вызывает функцию test у принятого экземпляра класса Entity 

class Client
{
public :

    static void test()
    {
        Attorney::test_v1();

        Attorney::test_v2();
    }
};

//////////////////////////////////////////////////////////////

int main()
{
    Client::test();
}

//////////////////////////////////////////////////////////////