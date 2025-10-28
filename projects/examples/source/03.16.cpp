/////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

/////////////////////////////////////////////////////////////

class Entity 
{
public :

// ~Entity() = default; // error

//  -------------------------------------

<<<<<<< HEAD
	virtual ~Entity() = default;
	//!!!virtual-чтобы вызвался диструктор дочернего класса
=======
	virtual ~Entity()
	{
		std::cout << "Entity::~Entity\n";
	}
>>>>>>> origin/master

//  -------------------------------------

	virtual void test() const //!!!virtual-функция может быть переопределна в дочернем классе, но не обязана
	{ 
		std::cout << "Entity::test\n";
	}
};

/////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

   ~Client() override
	{
		std::cout << "Client::~Client\n";
	}

//  -------------------------------------

	void test() const override final
	{ 
		//!!!override-проверяет сходство сигнатур, переводит в ошибку компиляции при не совпадении сигнатур
		//!!!перед void можно написать virtual, только для того чтобы подчеркнуть что эта функция переопределяет функцию из родительского класса
		//!!!final-в производных классах нельзя переопределять эту функцию
		std::cout << "Client::test\n";
	}
};

/////////////////////////////////////////////////////////////

<<<<<<< HEAD
class Server final : public Entity {};
//!!!final-дальнейшее наследование от этого класса невозможно(квадрат, круг)
=======
class Server final : public Entity 
{
public:
>>>>>>> origin/master

   ~Server() override
	{
		std::cout << "Server::~Server\n";
	}
};

/////////////////////////////////////////////////////////////

class Router : private Entity {};

/////////////////////////////////////////////////////////////

int main()
{
//  std::vector < Client > clients; // bad

//  std::vector < Server > servers; // bad

//  std::vector < Router > routers; // bad

//  ---------------------------------------------------------

	[[maybe_unused]] Entity * entity_1 = new Client;

	[[maybe_unused]] Entity * entity_2 = new Server;

//	[[maybe_unused]] Entity * entity_3 = new Router; // error

//  ---------------------------------------------------------

	std::vector < Entity * > entities;

//  ---------------------------------------------------------

    entities.push_back(entity_1);

	entities.push_back(entity_2);

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
<<<<<<< HEAD
        entity->test(); // support : compiler-explorer.com
		//!!!чтобы test вызывалась из дочерних классов она должна быть virtual
=======
        entity->test();
>>>>>>> origin/master
    }

//  ---------------------------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

/////////////////////////////////////////////////////////////