// ///////////////////////////////////////////////////////////////////////////////////

// #include <cassert>

// ///////////////////////////////////////////////////////////////////////////////////
// //!!!сложение всех элементов пакета
// auto reduce_v1(auto ... xs) { return (     ... + xs); } // support : cppinsights.io

// auto reduce_v2(auto ... xs) { return (xs + ...     ); } // support : cppinsights.io

// auto reduce_v3(auto ... xs) { return (0  + ... + xs); } // support : cppinsights.io

// auto reduce_v4(auto ... xs) { return (xs + ... + 0 ); } // support : cppinsights.io

// ///////////////////////////////////////////////////////////////////////////////////
// //сначала возвели в квадрат элементы пакета а потом сложили их между собой
// auto transform_reduce(auto ... xs)
// {
// 	return (... + (xs * xs)); // support : cppinsights.io
// }

// ///////////////////////////////////////////////////////////////////////////////////

// int main()
// {
// 	assert(reduce_v1(1, 2, 3) == 6);
		
// 	assert(reduce_v2(1, 2, 3) == 6);

// 	assert(reduce_v3(1, 2, 3) == 6);

// 	assert(reduce_v4(1, 2, 3) == 6);

// //  ----------------------------------------

// 	assert(transform_reduce(1, 2, 3) == 14);
// }

// ///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <vector>

template <typename T> auto extract(T x){
	return 0.0;
}

template <> auto extract<double>(double x){
	return x;
}
auto sum(auto ...xs){
	return (extract(xs) + ...);
}

int main(){

	std::cout << sum(1,1.2,"ljh",2.2) << std::endl;
	return 0;
}