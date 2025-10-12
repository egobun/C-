////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

// void order(std::vector < int > & vector, std::size_t left, std::size_t right)
// {
// 	for (auto i = left + 1; i < right; ++i) 
// 	{
// 		for (auto j = i; j > left; --j)
// 		{
// 			if (vector[j - 1] > vector[j]) 
// 			{
// 				std::swap(vector[j], vector[j - 1]);
// 			}
// 		}
// 	}
// }

std::size_t partition(std::vector<int>& A, std::size_t low, std::size_t high) {
    int pivot = A[low];
    std::size_t left = low + 1;
    std::size_t right = high;

    while (true) {
        while (left <= right && A[left] <= pivot) ++left;
        while (left <= right && A[right] > pivot) --right;

        if (left > right) break;
        std::swap(A[left], A[right]);
    }
    std::swap(A[low], A[right]);
    return right;
}


void order(std::vector<int>& vector, std::size_t left, std::size_t right) {
    if (right - left <= 1) return; // 0 или 1 элемент — базовый случай

    std::size_t pivot_index = partition(vector, left, right - 1); // правый -1 для индекса последнего элемента
    
    order(vector, left, pivot_index); // левая часть: [left, pivot_index)
    order(vector, pivot_index + 1, right); // правая часть: [pivot_index+1, right)
}
////////////////////////////////////////////////////////////////////////////////////

void merge(std::vector < int > & vector_1, std::size_t left, std::size_t right)
{
	auto middle = std::midpoint(left, right), size = right - left;

	std::vector < int > vector_2(size, 0);

	for (auto i = left, j = middle, k = 0uz; k < size; ++k) 
	{
		if (i < middle && ((j < right && vector_1[i] <= vector_1[j]) || j == right))
		{
			vector_2[k] = vector_1[i++];
		}
		else
		{
			vector_2[k] = vector_1[j++];
		}
	}

	for (auto i = 0uz, j = 0uz; j < size; ++j) 
	{
		vector_1[left + i++] = vector_2[j];
	}
}

////////////////////////////////////////////////////////////////////////////////////

void split(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	if (right - left > 16)
	{
		auto middle = std::midpoint(left, right);

		split(vector, left,   middle);
		
		split(vector, middle, right );

		merge(vector, left,   right );
	}
	else
	{
		order(vector, left,   right );
	}
}

////////////////////////////////////////////////////////////////////////////////////

void sort(std::vector < int > & vector)
{
	split(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 1'000uz;

//  ---------------------------------------

	std::vector < int > vector(size, 0);

//  ---------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		vector[i] = std::rand()%1000;
	}

//  ---------------------------------------

	sort(vector);

//  ---------------------------------------

	assert(std::ranges::is_sorted(vector));
}

////////////////////////////////////////////////////////////////////////////////////