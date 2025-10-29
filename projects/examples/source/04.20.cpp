///////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <print>

///////////////////////////////////////////////////////////////////////

void show(auto x, auto ... ys)
{
	std::print("show : x = {} sizeof...(ys) = {}\n", x, sizeof...(ys));

	if constexpr (sizeof...(ys) > 0) // support : cppinsights.io
	{
		show(ys...);
	}
}

///////////////////////////////////////////////////////////////////////

constexpr auto test(int x, int y)
{
	if consteval // support : cppinsights.io
	{
		return std::max(x, y);
	}
	else
	{
		return std::min(x, y);
	}
} 

///////////////////////////////////////////////////////////////////////

int main()
{
	show(1, 2.0, "aaaaa");

//  -------------------------------

    auto x = 1, y = 2;

//  -------------------------------

	 		  auto z1 = test(x, y);

	constexpr auto z2 = test(1, 2);

//  -------------------------------

	assert(z1 == 1);

	assert(z2 == 2);
}

///////////////////////////////////////////////////////////////////////