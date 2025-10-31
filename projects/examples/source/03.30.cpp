////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
// #include <print>
#include <iostream>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////

class Vector
{
public :

	// Vector() : m_array(nullptr), m_size(0)
	// {
	// 	std::print("Vector:: Vector (1)\n");
	// }
	//??? если создать пустой вектор то не будет работать push_back

	Vector(std::size_t capacity) : m_capacity(capacity), m_size(0)
	{
		std::cout << "Vector:: Vector (1)\n";
		int* m_array = new int[capacity]; 
	}
//  --------------------------------------------------------------------------------

	Vector(std::initializer_list < int > list) : m_size(std::size(list))
	{
		// std::print("Vector:: Vector (2)\n");
		std::cout << "Vector:: Vector (2)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(list, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector const & other) : m_size(other.m_size)
	{
		// std::print("Vector:: Vector (3)\n");
		std::cout << "Vector:: Vector (3)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector && other)
	:
		m_array(std::exchange(other.m_array, nullptr)),

		m_size (std::exchange(other.m_size,  0      ))
	{
		// std::print("Vector:: Vector (4)\n");
		std::cout << "Vector:: Vector (4)\n";
	}

//  --------------------------------------------------------------------------------

   ~Vector()
	{
		// std::print("Vector::~Vector\n");
		std::cout << "Vector::~Vector\n";

		delete[] m_array;
	}
	
//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // error
//	{
//		std::print("Vector::operator= (1)\n");
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // bad
//	{
//		std::print("Vector::operator= (2)\n");
//
//		if (this != &other)
//		{
//			auto array = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, array);
//
//			delete[] std::exchange(m_array, array);
//
//			m_size = other.m_size;
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::print("Vector::operator= (3)\n");
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = std::exchange(other.m_array, nullptr);
//
//			m_size  = std::exchange(other.m_size,  0      );
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

	auto & operator=(Vector other)
	{
		// std::print("Vector::operator= (4)\n");
		std::cout << "Vector::operator= (4)\n";

		swap(other);

		return *this;
	}

	//!!!rvalue ссылки нужны для правильной перегрузки конструктора или оператора присваивания
	//которые могут принимать lvalue ссылку - произойдет глубокое копирование (для other вызовется конструктор с глубоким копированием данные из lvalue ссылки) 
	//потом делаем swap other и this, this возвращаем, а other умрет при выходе из функции
	//или rvalue ссылку - вызовется конструктор с перемещением и ресурсы временного объекта переместятся в other (а временный объект станет ссылкаться на nullptr), далее произойдет swap other и this, other умрет при выходе из функции

//  --------------------------------------------------------------------------------

	void swap(Vector & other)
	{
		std::swap(m_array, other.m_array); //!!!не глубокое копирование, а просто перемещение указателей

		std::swap(m_size,  other.m_size );
	}

	std::size_t capacity() const
	{
		return m_capacity;
	}

	std::size_t size() const
	{
		return m_size;
	}

	bool empty() const
	{
		if(m_size == 0) return 1; else return 0;
	}

	void clear()
	{
		m_size = 0;
		for(int i = 0; i < m_capacity; i++)
		{
			m_array[i] = 0;
		}
	}

	void push_back(int value)
	{
		if(m_capacity == m_size){
			int* new_array = new int[m_capacity*2];
			m_capacity = m_capacity * 2;

			std::ranges::copy(m_array, m_array + m_size, new_array);
			delete[] m_array;
			m_array = new_array;
		}
		m_array[m_size++] = value;
	}

	int & operator [] (std::size_t index)
	{
		return m_array[index];
	}

	void show() const
	{
		for(int i = 0; i < m_capacity; i++)
		{
			std::cout << m_array[i] << " || ";
		}
		std::cout << std::endl;
	}

private :

	int * m_array = nullptr;

	std::size_t m_size = 0;
	std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////

void swap(Vector & lhs, Vector & rhs)
{
	lhs.swap(rhs);
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
// 	Vector vector_1(5);

// 	Vector vector_2 = { 1, 2, 3, 4, 5 };

// 	Vector vector_3 = vector_2;

// 	Vector vector_4 = std::move(vector_3);

// //  --------------------------------------

// 	vector_3 = vector_2;

// 	vector_4 = std::move(vector_3);

// //  --------------------------------------

// 	swap(vector_1, vector_2);

	Vector vector(5);
	std::cout << "empty = " << vector.empty() << std::endl;
	vector = {1, 2, 3, 4, 5};
	std::cout << "show = "; vector.show(); 
	std::cout << "capacity = " << vector.capacity() << std::endl;
	std::cout << "size = " << vector.size() << std::endl; 
	std::cout << "empty = " << vector.empty() << std::endl;
	vector.push_back(254); vector.push_back(-25); vector.push_back(25);
	std::cout << "show = "; vector.show(); 
	std::cout << "capacity = " << vector.capacity() << std::endl;
	std::cout << "size = " << vector.size() << std::endl; 

}

////////////////////////////////////////////////////////////////////////////////////