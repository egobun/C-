//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <ostream>
#include <numeric>
#include <cmath>

#include <sstream>
#include <vector>
#include <compare>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 >
struct Ratio
{
	constexpr static auto num = N;
	
	constexpr static auto den = D;
};


//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 >
struct Sum
{
	constexpr static auto num = R1::num * R2::den + R2::num * R1::den;

	constexpr static auto den = R1::den * R2::den;

	constexpr static auto gcd = std::gcd(num, den);

//  ------------------------------------------------------------------
	
	using type = Ratio < num / gcd,  den / gcd > ;
};

template < typename R1, typename R2 >
using sum = typename Sum < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2>
struct Sub
{
	constexpr static auto num = R1::num * R2::den - R2::num * R1::den;;
	constexpr static auto den = R1::den * R2::den;
	constexpr static auto gcd = std::gcd(num, den);

	using type = Ratio < num / gcd, den / gcd >;
};

template <typename R1, typename R2>
using sub = typename Sub < R1, R2 >::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > >
struct Duration 
{
	T x = T();

	R ratio = R();
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	using ratio_t = Ratio < 1, std::lcm(R1::den, R2::den)> ;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);
	
	return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////

template 
<
	typename T1, typename R1,
	typename T2, typename R2
>
constexpr auto operator- (Duration< T1, R1 > const & lhs, Duration< T2, R2 > const & rhs)
{
	auto rhs_c = rhs;
	rhs_c.x = (-1)*rhs.x;

	auto out = rhs_c + lhs; 
	return out;
}


//////////////////////////////////////////////////////////////////////////////////////////
template < typename R1, typename R2 >
struct Mul
{
	constexpr static auto num = R1::num * R2::num;

	constexpr static auto den = R1::den * R2::den;

	constexpr static auto gcd = std::gcd(num, den);

//  ------------------------------------------------------------------
	
	using type = Ratio < num / gcd,  den / gcd > ;
};

template <typename R1, typename R2>
using mul = typename Mul < R1, R2 >::type;

//////////////////////////////////////////////////////////////////////////////////////////

template
<
	typename T1, typename R1,
	typename T2, typename R2
>
constexpr auto operator * (Duration <T1, R1> const & lhs, Duration <T2, R2> const & rhs)
{
	using ratio_t = Ratio < 1, (R1::den * R2::den)> ;

	auto x = lhs.x * rhs.x;
	
	return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////
template < typename R1, typename R2 >
struct Div
{
	using R2_c = Ratio<R2::den, R2::num>;
	static_assert(R2::num != 0, "Division by zero");
	using type = typename Mul<R1, R2_c>::type;
};

template <typename R1, typename R2>
using divv = typename Div < R1, R2 >::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R>
auto & operator<< (std::ostream & stream, Duration < T, R > const & duration)
{
	return stream << duration.x << "/" << duration.ratio.den << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{

	using R1 = Ratio<1, 2>;  // 1/2
    using R2 = Ratio<3, 4>;  // 3/4
    

	using sum_result = sum<R1, R2>;
	using sub_result = sub<R1, R2>;
	using mul_result = mul<R1, R2>;
    using div_result = divv<R1, R2>;
	

	static_assert(sum_result::num == 5, "Numerator should be 2");
    static_assert(sum_result::den == 4, "Denominator should be 3");

	static_assert(sub_result::num == -1, "Numerator should be 2");
    static_assert(sub_result::den == 4, "Denominator should be 3");

	static_assert(mul_result::num == 3, "Numerator should be 2");
    static_assert(mul_result::den == 8, "Denominator should be 3");

    static_assert(div_result::num == 2, "Numerator should be 2");
    static_assert(div_result::den == 3, "Denominator should be 3");



	/////////////////////////////////////////////////////////////////////////////////////

	auto x = 1, y = 3;

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 5 > > duration_1(x);

	Duration < int, Ratio < 1, 15 > > duration_2(y);

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 15 > > duration_3 = duration_1 + duration_2;

	Duration <int, Ratio < 1, 15 > > duration_4 = duration_1 - duration_2;

	Duration <int, Ratio < 1, 75 > > duration_5 = duration_1 * duration_2;

//  ----------------------------------------------------------------------


	std::cout << (duration_1) << std::endl;
	std::cout << (duration_2) << std::endl;
	std::cout << (duration_3) << std::endl;
	std::cout << (duration_4) << std::endl;
	std::cout << (duration_5) << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////



// Доработайте пример 04.21 таким образом, чтобы дроби можно было вычитать, умножать и делить на эта-
// пе компиляции. Реализуйте шаблоны структур Sub, Mul и Div по аналогии с шаблоном структуры Sum для
// представления операций вычитания, умножения и деления дробей соответственно. Используйте в структурах
// Sub и Div структуры Sum и Mul соответственно для устранения дублирования кода. Реализуйте в структурах
// Sum и Mul алгоритмы сокращения дробей. Используйте стандартную функцию std::gcd. Реализуйте в струк-
// туре Div статическое утверждение static_assert для проверки деления на ноль при вычислениях на этапе
// компиляции. Реализуйте шаблоны псевдонимов для сокращения записей обращений к псевдонимам типов в
// шаблонах структур Sub, Mul и Div по аналогии с шаблоном псевдонима sum. Реализуйте шаблон перегружен-
// ного оператора вычитания интервалов со спецификатором constexpr, используя внутри него шаблон перегру-
// женного оператора сложения интервалов. Реализуйте тесты на основе статических утверждений static_assert.