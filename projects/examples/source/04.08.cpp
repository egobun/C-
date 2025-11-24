// /////////////////////////////////////////////////////////////////////

// #include <cassert>
// #include <utility>
// #include <vector>

// /////////////////////////////////////////////////////////////////////

// template < typename T, typename C = std::vector < T > > class Stack
// {
// public :

// 	void push(T x);

// //  -----------------

// 	auto top() const;

// //  -----------------

// 	void pop();

// private :

// 	C m_container;
// };

// /////////////////////////////////////////////////////////////////////

// template < typename T, typename C > void Stack < T, C > ::push(T x)
// {
// 	m_container.push_back(std::move(x));
// }

// /////////////////////////////////////////////////////////////////////

// template < typename T, typename C > auto Stack < T, C > ::top() const
// {
// 	return m_container.back();
// }

// /////////////////////////////////////////////////////////////////////

// template < typename T, typename C > void Stack < T, C > ::pop()
// {
// 	m_container.pop_back();
// }

// /////////////////////////////////////////////////////////////////////

// int main()
// {
//     Stack < int > stack;

// //  -------------------------

// 	stack.push(1);

// 	stack.push(2);

// //  -------------------------
	
// 	assert(stack.top() == 2);

// //  -------------------------
	
// 	stack.pop();

// //  -------------------------
	
// 	assert(stack.top() == 1);
// }

// /////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
// #include <print>
#include <iostream>
#include <utility>
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////////
template <typename T>
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
		T* m_array = new T[capacity]; 
	}
//  --------------------------------------------------------------------------------

	Vector(std::initializer_list < T > list) : m_size(std::size(list)), m_capacity(std::size(list))
	{
		// std::print("Vector:: Vector (2)\n");
		std::cout << "Vector:: Vector (2)\n";

		m_array = m_size ? new T[m_size]{} : nullptr;

		std::ranges::copy(list, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector const & other) : m_size(other.m_size) , m_capacity(other.m_capacity)
	{
		// std::print("Vector:: Vector (3)\n");
		std::cout << "Vector:: Vector (3)\n";

		m_array = m_capacity? new T[m_capacity]{} : nullptr;

		std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
		
	}

//  --------------------------------------------------------------------------------

	Vector(Vector && other)
	:
		m_array(std::exchange(other.m_array, nullptr)),

		m_size (std::exchange(other.m_size,  0      )),
		m_capacity (std::exchange(other.m_capacity,  0      ))
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

		std::swap(m_capacity,  other.m_capacity );
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
		return m_size == 0;
	}

	void clear()
	{
		m_size = 0;
	}

	void push_back(T value)
	{

		// std::cout<< typeid(value).name() <<std::endl;
		if(m_capacity == m_size){
			if(m_capacity == 0){
				m_capacity = 1;
			} else {
				m_capacity = m_capacity * 2;
			}
			T* new_array = new T[m_capacity];
			

			std::ranges::copy(m_array, m_array + m_size, new_array);
			delete[] m_array;
			m_array = new_array;
		}
		m_array[m_size++] = value;
	}

	T & operator [] (std::size_t index)
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

	T * m_array = nullptr;

	std::size_t m_size = 0;
	std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////

template <typename T> void swap (Vector<T> & lhs, Vector<T> & rhs)
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

	Vector <float> vector(5);
	std::cout << "empty = " << vector.empty() << std::endl;
	vector = {1.0, 2.1, 3.2, 4.6, 5};
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