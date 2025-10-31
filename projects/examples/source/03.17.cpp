/////////////////////////////////////////////

#include <print>
#include <vector>

/////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -----------------------------------------

    virtual void test_v1() const = 0;
    //!!!обязаны переопределить данную функцию в дочернем классе
    //!!!теперь Entity абстрактный базовый класс, нельзя создать его экземпляр

//  -----------------------------------------

//	virtual void test_v2() const = 0 // error
//	{
//		std::print("Entity::test_v2\n");
//	}
};

/////////////////////////////////////////////

void Entity::test_v1() const
{ 
	std::print("Entity::test_v1\n");
}
//определение чисто вирутальной функции возможно, но только за пределами класса

/////////////////////////////////////////////

class Client : public Entity
{
public :

    void test_v1() const override 
	{ 
		std::print("Client::test_v1\n");
		
		Entity::test_v1();
	}
};

/////////////////////////////////////////////

class Server : public Entity
{
public :

    void test_v1() const override 
	{ 
		std::print("Server::test_v1\n");
		
		Entity::test_v1();
	}
};

/////////////////////////////////////////////

int main()
{
    std::vector < Entity * > entities;

//  ----------------------------------

    entities.push_back(new Client);

    entities.push_back(new Server);

//  ----------------------------------

    for (auto entity : entities)
    {
        entity->test_v1();
    }

//  ----------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }

//  ----------------------------------

//	Entity entity; // error
}

/////////////////////////////////////////////