///////////////////////////////////////////////////////////////////////////////////

#include <cassert>

///////////////////////////////////////////////////////////////////////////////////

auto reduce_v1(auto ... xs) { return (     ... + xs); } // support : cppinsights.io

auto reduce_v2(auto ... xs) { return (xs + ...     ); } // support : cppinsights.io

auto reduce_v3(auto ... xs) { return (0  + ... + xs); } // support : cppinsights.io

auto reduce_v4(auto ... xs) { return (xs + ... + 0 ); } // support : cppinsights.io

///////////////////////////////////////////////////////////////////////////////////

auto transform_reduce(auto ... xs)
{
	return (... + (xs * xs)); // support : cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(reduce_v1(1, 2, 3) == 6);
		
	assert(reduce_v2(1, 2, 3) == 6);

	assert(reduce_v3(1, 2, 3) == 6);

	assert(reduce_v4(1, 2, 3) == 6);

//  ----------------------------------------

	assert(transform_reduce(1, 2, 3) == 14);
}

///////////////////////////////////////////////////////////////////////////////////