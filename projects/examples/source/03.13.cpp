/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////////////////

class Entity
{ 
public : 

	void test_v1() const
	{
		std::cout << "Entity::test_v1\n";
	}

//  -------------------------------------

	static void test_v2()
	{
		std::cout << "Entity::test_v2\n";
	}

private :

	int m_x = 0;
};

/////////////////////////////////////////////////////////////////////////////////

class Client_v1 : public         Entity {};

class Client_v2 : public virtual Entity {};//!!!virtual нужен чтобы вместо вилки получить ромбик

class Server_v1 : public         Entity {};

class Server_v2 : public virtual Entity {};//!!!virtual нужен чтобы вместо вилки получить ромбик

/////////////////////////////////////////////////////////////////////////////////

class Router_v1 : public Client_v1, public Server_v1 { public : Router_v1() {} };

class Router_v2 : public Client_v2, public Server_v2 { public : Router_v2() {} };

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	Router_v1 router_v1; // support : compiler-explorer.com

//  -------------------------------------------------------

//	router_v1.test_v1(); // error //!!!не понятно функцию какого экземпляра entity необходимо вызывать

	router_v1.test_v2();

//  -------------------------------------------------------

	Router_v2 router_v2; // support : compiler-explorer.com

//  -------------------------------------------------------

	router_v2.test_v1();

	router_v2.test_v2();

//  -------------------------------------------------------

	Client_v2 client_v2; // support : compiler-explorer.com
}

/////////////////////////////////////////////////////////////////////////////////