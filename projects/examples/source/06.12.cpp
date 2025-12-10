/////////////////////////////////////////////////

#include <print>
#include <string>

/////////////////////////////////////////////////

namespace library
{
	namespace detail
	{
		struct Entity {};
	}
}

/////////////////////////////////////////////////

namespace library::detail
{
	void test(Entity)
	{
		std::print("library::detail::test\n");
	}
}

/////////////////////////////////////////////////

void test(library::detail::Entity)
{
    std::print("test\n");
}

/////////////////////////////////////////////////

namespace library
{
	//!!! inline - мастер умолчательная версия, она вызовется при library::test()
	inline namespace v1
	{
		void test()
		{
			std::print("library::v1::test\n");
		}
	}

//  ------------------------------------------
	//!!! нужно явно прописывать namespace , libriry::v2::test() 
	namespace v2
	{
		void test()
		{
			std::print("library::v2::test\n");
		}
	}
}

/////////////////////////////////////////////////

int main()
{
	library::detail::Entity entity;

//  ---------------------------------------------
<<<<<<< HEAD
//!!! компилятоор видит что аргумент в определенном пространстве имен и поэтому 
// пытается вызвать test из того же пространства имен и возникает двойственная реализация
	test(entity);
=======

//	  test(entity); // error

	::test(entity);
>>>>>>> origin_mst

//  ---------------------------------------------

    namespace alias = library::detail;

//  ---------------------------------------------

	alias::test(entity);

//  ---------------------------------------------

    library::v1::test();

    library::v2::test();

	library::    test();
	
	//!!! вызов из глобального пространства имен
	::test();

//  ---------------------------------------------

//  using namespace std; // bad
//!!! для удобного использования суффиксов литералов
	using namespace std::literals;

//  ---------------------------------------------
//!!! s - унарный постфиксный оператор (к примеру как x++)
	auto string_1 = "aaaaa"s;

	auto string_2 = std::operator""s("aaaaa", 5);
}

/////////////////////////////////////////////////