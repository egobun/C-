////////////////////////////////////////////////////

// #include <print>
#include <iostream>
////////////////////////////////////////////////////

class Entity 
{
public :

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

////////////////////////////////////////////////////

class Client : public virtual Entity 
{ 
public : 
    
    void test() const override 
    { 
        std::cout << "Client::test\n" << std::endl;
    } 
};

////////////////////////////////////////////////////

class Server : public virtual Entity 
{ 
public : 
    
    void test() const override 
    { 
        std::cout << "Server::test\n" << std::endl;
    } 
};

////////////////////////////////////////////////////

template < typename T >
class Decorator : public virtual Entity, public T
{
public :
//  ------------------------------------------------

    void test() const override
    { 
        std::cout << "Decorator::test : " << std::endl;
        
        T::test();
    }

};

////////////////////////////////////////////////////

int main()
{
    Entity * entity_1 = new Client;
    entity_1->test();

    Entity * entity_2 = new Decorator <Client>;
    entity_2->test();

    Entity * entity_3 = new Decorator <Server>;
    entity_3->test();

    Entity * entity_4 = new Decorator <Decorator<Server>>;
    entity_4->test();

//  ---------------------------------------------
    delete entity_1;
     
    delete entity_2;

    delete entity_3;
     
    delete entity_4;
}

////////////////////////////////////////////////////


// Реализуйте такую разновидность паттерна Decorator, которая основана на шаблоне. Реализуйте шаблон про-
// изводного класса Decorator, который является наследником интерфейса класса Entity и наследником реа-
// лизации собственного параметра шаблона. Используйте класс Entity как виртуальный базовый класс, чтобы
// предотвратить неоднозначности выбора. Устраните в классе Decorator конструктор и ссылку на класс Entity.