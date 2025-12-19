//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts >
class Tuple {};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts >
class Tuple < T, Ts ... >
{
public :

	constexpr Tuple(T && x, Ts && ... xs)
	:
		m_head(std::forward < T  > (x )   ),
		
		m_tail(std::forward < Ts > (xs)...)
	{}

//  ------------------------------------------------

	template < std::size_t I >
	constexpr auto get() const
	{
		if constexpr (I > 0)
		{
			return m_tail.template get < I - 1 > ();
		}
		else
		{
			return m_head;
		}
	}

	constexpr auto size() const
	{
		return (1 + (sizeof...(Ts)));
	}

private :

	T m_head;
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	constexpr Tuple < int, double, int, double > tuple(1, 2.0, 5, 125.23);

//  ----------------------------------------------------------

	static_assert(tuple.get < 0 > () == 1);

	static_assert(tuple.size() == 4);
}

//////////////////////////////////////////////////////////////////


// Доработайте пример 04.22 таким образом, чтобы кортеж можно было использовать на этапе компиляции. До-
// бавьте пользовательскому конструктору и шаблону функции-члена get класса Tuple спецификатор constexpr.
// Реализуйте в классе Tuple публичную функцию-член size со спецификатором constexpr для получения зна-
// чения размера кортежа. Используйте оператор sizeof... для определения размера пакета параметров шабло-
// на класса Tuple в функции-члене size. Реализуйте тесты на основе статических утверждений static_assert.