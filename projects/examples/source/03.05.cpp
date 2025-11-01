// /////////////////////////////////////////////////////////////////

// #include <cassert>
// #include <string>

// /////////////////////////////////////////////////////////////////

// class Entity
// {
// public :

// 	Entity(int x) : m_x(x) {}

// //  -------------------------------------------------------------

// 	auto get() const
// 	{
// 		return m_x; // support : compiler-explorer.com
// 	}

// //  -------------------------------------------------------------

//     auto const & make_string() const
//     {
//         return m_cache.string(*this);
//     }

// //  -------------------------------------------------------------

//     void set(int x) 
//     {
//         if (x > 0)
//         {
//             m_x = x;

//             m_cache.clear();
//         }
//     }

// private :

// 	class Cache 
// 	{
// 	public :

// 		auto string(Entity const & entity) -> std::string const &
// 		{
// 			if (m_string.empty())
// 			{
// 				m_string = std::to_string(entity.m_x);
// 			}

// 			return m_string;
// 		}

// 	//  ---------------------------------------------------------

// 		void clear()
// 		{
// 			m_string.clear();
// 		}

// 	private :

// 		std::string m_string;
// 	};

// //  -------------------------------------------------------------

// 	int m_x = 0;

// //  -------------------------------------------------------------

// 	mutable Cache m_cache;//может изменяться внутри константных методов класса владельца Entity
// };

// /////////////////////////////////////////////////////////////////

// int main()
// {
//     Entity entity(1);

// //  ------------------------------------

// 	assert(entity.get() == 1);

// //  ------------------------------------

//     assert(entity.make_string() == "1");

// 	assert(entity.make_string() == "1");

// //  ------------------------------------

// 	entity.set(2);

// //  ------------------------------------

// 	assert(entity.make_string() == "2");
// }

// /////////////////////////////////////////////////////////////////
#include <iostream>


class Entity_v1 
{
public:

	virtual void test()
	{
		std::cout << "Entity_v1::test()" << std::endl;
	}
	
	virtual ~Entity_v1() = default;

};

class Entity_v2 
{
public:

	virtual void test()
	{
		std::cout << "Entity_v2::test()" << std::endl;
	}

	virtual ~Entity_v2() = default;

};

class Adapter_v1 : public Entity_v1
{
private:
	void test() override
	{
		test_v1();
	}
public:
	void virtual test_v1 ()
	{
		std::cout << "Adapter_v1::test_v1()" << std::endl;
	}
};

class Adapter_v2 : public Entity_v2
{
private:
	void test() override
	{
		test_v2();
	}
public:
	void virtual test_v2 ()
	{
		std::cout << "Adapter_v2::test_v2()" << std::endl;
	}
};

class Client final: public Adapter_v1, public Adapter_v2
{
public:
	void test_v1() override
	{
		std::cout << "Client::test_v1()" << std::endl;
	}

	void test_v2() override
	{
		std::cout << "Client::test_v2()" << std::endl;
	}
};

int main()
{
	Entity_v1* client1 = new Client;
	Entity_v2* client2 = new Client;

	client1->test();

	client2->test();

	delete client1;
	delete client2;
}
