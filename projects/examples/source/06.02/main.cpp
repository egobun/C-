
#include <cassert>
import library;
using namespace library;

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

int main()
{
	Rational x = 1, y(2, 1), u = 2;

//  -----------------------------------------------------------------------

	assert(equal(static_cast < double > (x), 1));

//  -----------------------------------------------------------------------

	assert(x.operator+=(y) == Rational(3, 1)); // bad

//  -----------------------------------------------------------------------

	// assert((x += y) == Rational(+3, 1));

	assert((x -= y) == Rational(+1, 1));

	assert((x *= y) == Rational(+2, 1));

	assert((x /= y) == Rational(+1, 1));

//  -----------------------------------------------------------------------

	assert((x ++  ) == Rational(+1, 1)); // support : compiler-explorer.com

	assert((x --  ) == Rational(+2, 1));

	assert((  ++ y) == Rational(+3, 1)); // support : compiler-explorer.com

	assert((  -- y) == Rational(+2, 1));

//  -----------------------------------------------------------------------

	[[maybe_unused]] auto z = 0;

//  -----------------------------------------------------------------------


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