/////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

/////////////////////////////////////////////////////////////////////////////

template < typename T > auto reduce(std::ranges::view auto view, T sum) -> T
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 64)
	{
        std::ranges::subrange range(begin, std::next(begin, size / 2));

		auto future = std::async(reduce < decltype(range), T > , range, T());

		sum += reduce(std::ranges::subrange(std::end(range), end), T());

		return sum + future.get();
	}
	else
	{
		return sum + *std::ranges::fold_left_first(view, std::plus());
	}
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1'000, 0);

//  --------------------------------------------------------------

	std::ranges::iota(vector, 1);

//  --------------------------------------------------------------

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}

/////////////////////////////////////////////////////////////////////////////