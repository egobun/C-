/////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////

class Entity
{
public :

	void test_v1() const 
	{ 
		std::cout << "Entity::test_v1\n";
	}

protected :

	void test_v2() const 
	{ 
		std::cout << "Entity::test_v2\n";
	}
};

/////////////////////////////////////////
//!!!множественное наследование может потянуть ряд проблем
class Server_v1 : private Entity //!!!закрытое наследование(все из entity попадает в private Server_v1)
{
public :

	void test() const
	{
		Entity::test_v1();

		Entity::test_v2();
	}
};

//!!!наследование protected вообще не используется

/////////////////////////////////////////

class Server_v2 
{
public :

	void test() const
	{
		m_entity.test_v1(); //!!!тут можем вызывать только публичные методы m_entity

	//	m_entity.test_v2(); // error
	}

private : 

	Entity m_entity;
};

/////////////////////////////////////////

int main()
{
	Server_v1 server_v1;

//  -----------------------------

//	server_v1.test_v1(); // error

//	server_v1.test_v2(); // error

//  -----------------------------

	server_v1.test();

//  -----------------------------

	Server_v2 server_v2;

//  -----------------------------

//	server_v2.test_v1(); // error

//	server_v2.test_v2(); // error

//  -----------------------------

	server_v2.test();
}

/////////////////////////////////////////