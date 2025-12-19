////////////////////////////////////////

// #include <print>

// ////////////////////////////////////////

// class Entity
// {
// public :

// 	virtual ~Entity() = default;

// //  ------------------------------

// 	virtual void test() const = 0;
// };

// ////////////////////////////////////////

// class Client_v1 : public Entity 
// { 
// public :

// 	void test() const override 
// 	{ 
// 		std::print("Client_v1::test\n");
// 	} 
// };

// ////////////////////////////////////////

// class Server_v1 : public Entity 
// { 
// public :

// 	void test() const override 
// 	{ 
// 		std::print("Server_v1::test\n");
// 	} 
// };

// ////////////////////////////////////////

// void test_v1(Entity const & entity)
// {
// 	entity.test();
// }

// ////////////////////////////////////////

// class Client_v2 
// { 
// public :

// 	void test() const 
// 	{ 
// 		std::print("Client_v2::test\n");
// 	} 
// };

// ////////////////////////////////////////

// class Server_v2 
// { 
// public :

// 	void test() const 
// 	{ 
// 		std::print("Server_v2::test\n");
// 	} 
// };

// ////////////////////////////////////////

// void test_v2(auto const & entity)
// {
// 	entity.test();
// }

// ////////////////////////////////////////

// int main()
// {
// 	Entity * entity = new Client_v1;

// //  --------------------------------

// 	test_v1(*entity);

// //  --------------------------------

// 	delete entity;

// //  --------------------------------

// 	test_v2(Client_v2());
// }

////////////////////////////////////////

// Реализуйте такую разновидность паттерна Strategy, которая основана на статическом полиморфизме. Устра-
// ните класс Strategy. Реализуйте шаблон производного класса Entity, который является наследником реали-
// зации собственного параметра шаблона. Устраните в классе Entity конструктор и ссылку на класс Strategy.


/////////////////////////////////////////////////////////

// #include <print>
#include <iostream>
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
template <typename T>
class Entity
{
public :
//  -----------------------------------------------------

    void test() const
    {
        static_cast<const T*>(this)->test_impl();
	}
};

/////////////////////////////////////////////////////////

class Client : public Entity<Client>
{
public :

    void test_impl() const
    {
        std::cout << ("Client::test\n") << std::endl;
    }
};

/////////////////////////////////////////////////////////

class Server : public Entity<Server>
{
public :

    void test_impl() const
    {
        std::cout << ("Server::test\n") << std::endl;
    }
};


/////////////////////////////////////////////////////////

int main()
{
    Client client ;

	Server server;

	client.test();

	server.test();
}

/////////////////////////////////////////////////////////