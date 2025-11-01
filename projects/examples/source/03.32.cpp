///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>
#include <compare>

///////////////////////////////////////////////////////////////////////////////////////////////

class Rational
{

private :

	void reduce()
	{
		if (m_den < 0)
		{
			m_num = -m_num;

			m_den = -m_den;
		}

		auto gcd = std::gcd(m_num, m_den);

		m_num /= gcd;

		m_den /= gcd;
	}

//  -------------------------------------------------------------------------------------------

	int m_num = 0, m_den = 1;

public :

	/* explicit */ Rational(int num = 0, int den = 1) : m_num(num), m_den(den)
	//!!! explicit - отключает возможность неявного вызова конструктора
	{
		reduce();
	}

//  -------------------------------------------------------------------------------------------

	explicit operator double() const
	{ 
		return 1.0 * m_num / m_den;
	}

	//!!! тут обязателен explicit так как у нас есть неявный конструктор Rational
	//к примеру при (x + 1) так как конструктор неявный, то от 1 вызовется конструктор появится экземпляр Rational
	//и произведется сложение двух Rational
	//если же double был бы неявным то компилятор бы захотел x привести к double, сделать встроенное преобраование int (1) к double
	//и провести сложение двух double --> получается двойственность поведения
	//кто то должен быть explicit либо конструктор либо оператор double() 
	//за один раз может быть одно пользовательское преобразование и одно встроенное
//  -------------------------------------------------------------------------------------------

	auto & operator+=(Rational const & other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
		
		m_den = lcm;

		reduce();

		return *this;
		//!!!результат возвращаем по ссылке чтобы можно было реализовывать цепочки операторов
	}

//  -------------------------------------------------------------------------------------------

	auto & operator-=(Rational const & other) 
	{ 
		return *this += Rational(other.m_num * -1, other.m_den);
	}

//  -------------------------------------------------------------------------------------------

	auto & operator*=(Rational const & other)
	{
		m_num *= other.m_num;

		m_den *= other.m_den;

		reduce();

		return *this;
	}

//  -------------------------------------------------------------------------------------------
	
	auto & operator/=(Rational const & other) 
	{ 
		return *this *= Rational(other.m_den, other.m_num);
		//чтобы не произошло деление на 0 необходио проверять это в конструкторе Rational
	}

//  -------------------------------------------------------------------------------------------
//!!! это постфиксная версия
//для различия версий используем перегрузку-передаем int
//компилятор инициирует передачу некоторого фиктивного int

	auto const operator++(int) { auto x = *this; *this += 1; return x; }
	//тут при выходе из функции происходит копирование ???
	//const для того чтобы нельзя было сделать x++++; так как x++ вернет const который нельзя изменять.
	//Но сам this модифицируется и может быть изенен дальше в программе

	auto const operator--(int) { auto x = *this; *this -= 1; return x; }



//  -------------------------------------------------------------------------------------------
//!!! это префиксная версия
	auto & operator++() { *this += 1; return *this; }

	auto & operator--() { *this -= 1; return *this; }

//  -------------------------------------------------------------------------------------------

	friend auto operator+ (Rational lhs, Rational const & rhs) { return lhs += rhs; }

	friend auto operator- (Rational lhs, Rational const & rhs) { return lhs -= rhs; }

	friend auto operator* (Rational lhs, Rational const & rhs) { return lhs *= rhs; }

	friend auto operator/ (Rational lhs, Rational const & rhs) { return lhs /= rhs; }

// 	//!!! friend дает доступ к приватным полям класса и говрит что эти функции являются внешними по отношению к этому классу
// 	// стандартно в классе должно быть только объявление friend фунции, но может быть и определение
// 	// эти операторы должны быть внешними чтобы слево от оператора мог стоять не экземпляр класса
// //  -------------------------------------------------------------------------------------------

// 	friend auto operator< (Rational const & lhs, Rational const & rhs)
// 	{
// 		return lhs.m_num * rhs.m_den < rhs.m_num * lhs.m_den;
// 	}

//  -------------------------------------------------------------------------------------------

	// friend auto operator> (Rational const & lhs, Rational const & rhs) { return  (rhs < lhs); }
	
	// friend auto operator<=(Rational const & lhs, Rational const & rhs) { return !(lhs > rhs); }

	// friend auto operator>=(Rational const & lhs, Rational const & rhs) { return !(lhs < rhs); }

//  -------------------------------------------------------------------------------------------

	// friend auto operator==(Rational const & lhs, Rational const & rhs)
	// {
	// 	return !(lhs < rhs) && !(rhs < lhs);
	// }
	//!!! оператор != генерируется по умолчанию

//  -------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Rational & rational)
	//!!! тут испольщуем именно ссылку на поток ввода, чтобы можно было передать его ребенка по ссылке
	// например универсальный поток stringstream который является наследником двух потоков  istream и ostream
	// или же передать ссылку на поток fstream
	{
		return (stream >> rational.m_num).ignore() >> rational.m_den;
	}

//  -------------------------------------------------------------------------------------------

	friend auto & operator<<(std::ostream & stream, Rational const & rational)
	{
		return stream << rational.m_num << '/' << rational.m_den;
	}

	//!!! stream возвращаем по ссылке, чтобы можно было реализовывать цепочки операторов

	// friend auto operator<=> (Rational const & lhs, Rational const & rhs)
	// {	
	// 	return static_cast<double>(lhs) <=> static_cast<double>(rhs);
	// }

	// friend auto operator<=>(Rational const & lhs, Rational const & rhs)
	// {
	// 	auto comparison = (lhs.m_num <=> rhs.m_num);
		
	// 	if(comparison == std::strong_ordering::equal)
	// 	{
	// 		return lhs.m_den <=> rhs.m_den;
	// 	}
	// 	return comparison;
	// }

	friend auto operator<=>(Rational const & lhs, Rational const & rhs)
	{
		auto lcm = std::lcm(lhs.m_den,rhs.m_den);
		return (lhs.m_num * lcm / lhs.m_den) <=> (rhs.m_num * lcm / rhs.m_den);	
	}

	friend auto operator== (Rational const & lhs, Rational const & rhs)
	{
		return (lhs.m_num == rhs.m_num) && (lhs.m_den == rhs.m_den);
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Rational x = 1, y(2, 1), u = 2;
	//!!! x = 1 не будет работать если конструктор Rational который принимает одно или два числа explicit
//  -----------------------------------------------------------------------

//	std::vector < int > vector_1 = 5; // error
//!!! тут ошибка так как конструктор vector который принимает одно число explicit 
//т.к. не ясно мы создаем вектор из 5ти каких-то элементов или из 5ти нулей

	std::vector < int > vector_2(5);

	std::vector < int > vector_3 = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------------------

	assert(equal(static_cast < double > (x), 1));

//  -----------------------------------------------------------------------

//	assert(x.operator+=(y) == Rational(3, 1)); // bad

//  -----------------------------------------------------------------------

	assert((x += y) == Rational(+3, 1));

	assert((x -= y) == Rational(+1, 1));

	assert((x *= y) == Rational(+2, 1));

	assert((x /= y) == Rational(+1, 1));

//  -----------------------------------------------------------------------

	assert((x ++  ) == Rational(+1, 1)); // support : compiler-explorer.com

	assert((x --  ) == Rational(+2, 1));

	assert((  ++ y) == Rational(+3, 1)); // support : compiler-explorer.com

	assert((  -- y) == Rational(+2, 1));

//  -----------------------------------------------------------------------

//	x++++; // error

//  -----------------------------------------------------------------------

	[[maybe_unused]] auto z = 0;

//  -----------------------------------------------------------------------

//	z++++; // error
// так не пишут потому что в первый ++ мы отмодифицируем this а во второй раз мы отмодифицируем копию,
// которая получится при копировании из возваращаемого x из operator++ (тут копирование или все таки перемещение prvalue???)
//в итоге получится что x все равно будет инкрементирован только один раз

//  -----------------------------------------------------------------------

//	assert(operator+(x, y) == Rational(3, 1)); // bad

//  -----------------------------------------------------------------------

	assert((x +  y) == Rational(+3, 1));

	assert((x -  y) == Rational(-1, 1));

	assert((x *  y) == Rational(+2, 1));

	assert((x /  y) == Rational(+1, 2));

//  -----------------------------------------------------------------------

	assert((x += 1) == Rational(+2, 1));

//	assert((1 += x) == Rational(+3, 1)); // error

	assert((x +  1) == Rational(+3, 1));

	assert((1 +  y) == Rational(+3, 1));

	assert((1 +  1) == Rational(+2, 1));

//  -----------------------------------------------------------------------

	assert((x <  y) == 0);
	
	assert((x >  y) == 0);

	assert((x <= y) == 1);

	assert((x >= y) == 1);

	assert((x == y) == 1);

	assert((x != y) == 0);

	// assert((x <=> y) > 0);
	assert((x <=> y) == 0);
	// assert((x <=> y) < 0);

//  -----------------------------------------------------------------------

	//!!! свой поток-замена потока ввода вывода
	std::stringstream stream_1("1/2");

	std::stringstream stream_2;

	std::stringstream stream_3("3/2");

	std::stringstream stream_4("5/3");

	//!!! два потока и для записи и для чтение одного типа, хотя наши перегруженные операторы ожидают istream и ostream
	//
//  -----------------------------------------------------------------------

	stream_1 >> x;

	stream_2 << x;

	stream_3 >> y;

	stream_4 >> u;

//  -----------------------------------------------------------------------

	assert(stream_2.str() == stream_1.str());
	assert(stream_3.str() < stream_4.str());
	assert(stream_4.str() > stream_3.str());


	assert(y < u);
	assert(u > x);
	
	//!!! stringstream позволяет писать тесты на assert для проверки того что ввелось и вывелось
}

///////////////////////////////////////////////////////////////////////////////////////////////