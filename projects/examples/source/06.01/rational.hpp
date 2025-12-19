///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

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

	void reduce(); // это может иметь внутреннее связывание static перед void + мостика между множественными определениями не будет так как это внутреннее связывание

//  -------------------------------------------------------------------------------------------

	int m_num = 0;

    int m_den = 1;

public :

	Rational(int num = 0, int den = 1);


//  -------------------------------------------------------------------------------------------

	explicit operator double() const;
//  -------------------------------------------------------------------------------------------

	Rational & operator+=(Rational const & other);

//  -------------------------------------------------------------------------------------------

	Rational & operator-=(Rational const & other);

//  -------------------------------------------------------------------------------------------

	Rational & operator*=(Rational const & other);

//  -------------------------------------------------------------------------------------------
	
	Rational & operator/=(Rational const & other);

//  -------------------------------------------------------------------------------------------
	auto const operator++(int) { auto x = *this; *this += 1; return x; }

	auto const operator--(int) { auto x = *this; *this -= 1; return x; }



 //-------------------------------------------------------------------------------------------
	auto & operator++() { *this += 1; return *this; }

	auto & operator--() { *this -= 1; return *this; }

//  -------------------------------------------------------------------------------------------

	friend auto operator+ (Rational lhs, Rational const & rhs) { return lhs += rhs; }

	friend auto operator- (Rational lhs, Rational const & rhs) { return lhs -= rhs; }

	friend auto operator* (Rational lhs, Rational const & rhs) { return lhs *= rhs; }

	friend auto operator/ (Rational lhs, Rational const & rhs) { return lhs /= rhs; }

//  -------------------------------------------------------------------------------------------

	friend auto & operator>>(std::istream & stream, Rational & rational)
	{
		return (stream >> rational.m_num).ignore() >> rational.m_den;
	}

//  -------------------------------------------------------------------------------------------

	friend auto & operator<<(std::ostream & stream, Rational const & rational)
	{
		return stream << rational.m_num << '/' << rational.m_den;
	}


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


///////////////////////////////////////////////////////////////////////////////////////////////

