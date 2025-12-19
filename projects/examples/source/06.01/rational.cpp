#include "rational.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>
#include <compare>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////

    void Rational::reduce() // это может иметь внутреннее связывание static перед void + мостика между множественными определениями не будет так как это внутреннее связывание
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

	Rational::Rational(int num, int den) : m_num(num), m_den(den)
	//!!! explicit - отключает возможность неявного вызова конструктора
	{
		reduce();
	}

//  -------------------------------------------------------------------------------------------

	Rational::operator double() const
	{ 
		return 1.0 * m_num / m_den;
	}

//  -------------------------------------------------------------------------------------------

	Rational & Rational::operator+=(Rational const & other)
	{
		auto lcm = std::lcm(m_den, other.m_den);

		m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
		
		m_den = lcm;

		reduce();

		return *this;
	}

//  -------------------------------------------------------------------------------------------

	Rational & Rational::operator-=(Rational const & other) 
	{ 
		return *this += Rational(other.m_num * -1, other.m_den);
	}

//  -------------------------------------------------------------------------------------------

	Rational & Rational::operator*=(Rational const & other)
	{
		m_num *= other.m_num;

		m_den *= other.m_den;

		reduce();

		return *this;
	}

//  -------------------------------------------------------------------------------------------
	
	Rational & Rational::operator/=(Rational const & other) 
	{ 
		return *this *= Rational(other.m_den, other.m_num);
	}

//  -------------------------------------------------------------------------------------------


	
//  -------------------------------------------------------------------------------------------