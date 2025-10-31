////////////////////////////////////////////////////////////////////

#include <print>

////////////////////////////////////////////////////////////////////
//!!!passkey не может разграничть доступ к полям родительского класса, только к методам
class Key_v1 { private : friend class Client; Key_v1() = default; };

class Key_v2 { private :                      Key_v2() = default; };

////////////////////////////////////////////////////////////////////

class Entity
{
private :

    friend class Client;

//  --------------------------------------------------------------

    static void test(Key_v1) { std::print("Entity::test (1)\n"); }
    
    static void test(Key_v2) { std::print("Entity::test (2)\n"); }
};

////////////////////////////////////////////////////////////////////

class Client
{
public :

    static void test()
    {
        Entity::test(Key_v1());

    //  Entity::test(Key_v2()); // error
    }
};

////////////////////////////////////////////////////////////////////

int main()
{
    Client::test();
}

////////////////////////////////////////////////////////////////////