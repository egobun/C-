//////////////////////////////////////////////////

#include <print>

//////////////////////////////////////////////////

template < typename T1, typename T2 > class Entity
{
public :

	void test() const
	{ 
		std::print("Entity::test (1)\n");
	}
};

//////////////////////////////////////////////////
//!!!частичная специализация
template < typename T > class Entity < T, int >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (2)\n");
	}
};

//////////////////////////////////////////////////
//!!!частичная специализация - ожидаются одинаковые типы
template < typename T > class Entity < T, T >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (3)\n");
	}
};

//////////////////////////////////////////////////

template <> class Entity < double, double >
{
public :

	void test() const 
	{ 
		std::print("Entity::test (4)\n");
	}
};

//////////////////////////////////////////////////

int main()
{
	Entity < int,    double > ().test();

	Entity < double, int    > ().test();
//неопрделенность выбора спецализации <T,T> или <T,int>
//	Entity < int,    int    > ().test(); // error

	Entity < double, double > ().test();
}

//////////////////////////////////////////////////