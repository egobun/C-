//////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////

class Entity 
{
public :

// ~Entity() = default; // error

//  ----------------------------------

	virtual ~Entity() = default;
	//!!!virtual-чтобы вызвался диструктор дочернего класса

//  ----------------------------------

	virtual void test() const //!!!virtual-функция может быть переопределна в дочернем классе, но не обязана
	{ 
		std::cout << "Entity::test\n";
	}
};

//////////////////////////////////////////////////////////

class Client : public Entity
{
public :

	void test() const override final
	{ 
		//!!!override-проверяет сходство сигнатур, переводит в ошибку компиляции при не совпадении сигнатур
		//!!!перед void можно написать virtual, только для того чтобы подчеркнуть что эта функция переопределяет функцию из родительского класса
		//!!!final-в производных классах нельзя переопределять эту функцию
		std::cout << "Client::test\n";
	}
};

//////////////////////////////////////////////////////////

class Server final : public Entity {};
//!!!final-дальнейшее наследование от этого класса невозможно(квадрат, круг)

//////////////////////////////////////////////////////////

class Router : private Entity {};

//////////////////////////////////////////////////////////

int main()
{
//  std::vector < Client > clients; // bad

//  std::vector < Server > servers; // bad

//  ------------------------------------------------------

    Client client;

	Server server;

	Router router;

//  ------------------------------------------------------

	[[maybe_unused]] Entity * entity_1 = &client;

	[[maybe_unused]] Entity * entity_2 = &server;
	
	[[maybe_unused]] Entity & entity_3 =  client;

//	[[maybe_unused]] Entity   entity_4 =  server; // error

//	[[maybe_unused]] Entity * entity_5 = &router; // error

//  ------------------------------------------------------

	std::vector < Entity * > entities;

//  ------------------------------------------------------

    entities.push_back(new Client);

	entities.push_back(new Server);

//  ------------------------------------------------------

    for (auto entity : entities)
    {
        entity->test(); // support : compiler-explorer.com
		//!!!чтобы test вызывалась из дочерних классов она должна быть virtual
    }

//  ------------------------------------------------------

    for (auto entity : entities)
    {
        delete entity;
    }
}

//////////////////////////////////////////////////////////