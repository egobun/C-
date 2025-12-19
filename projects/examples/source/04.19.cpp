// //////////////////////////////////////////////////////////////////////

// #include <cassert>
// #include <type_traits>
// #include <vector>

// /////////////////////////////////////////////////////////////
// //!!!спецификаторы для вычислений на этапе компиляции
// constexpr auto test_v1(int x) { return x; } //!!!функция может быть вычислена на этапе компиляции (если ее аргументы известны на этапе компиляции)

// consteval auto test_v2(int x) { return x; } //!!! обязана быть вызвана на этапе компиляции, в runtime не вызывать ее

// //////////////////////////////////////////////////////////////////////

// consteval auto factorial_v1(int x) -> int 
// {
// 	return x > 1 ? x * factorial_v1(x - 1) : 1;
// }

// //////////////////////////////////////////////////////////////////////

// consteval auto factorial_v2(int x)
// {
//     for (auto i = x - 1; i > 1; x *= i, --i);

//     return x;
// }

// //////////////////////////////////////////////////////////////////////

// consteval void test_v3()
// {
// 	std::vector < int > vector = { 1, 2, 3, 4, 5 };
// }

// //////////////////////////////////////////////////////////////////////

// constinit auto g_x = test_v1(1);

// //////////////////////////////////////////////////////////////////////

// int main()
// {
//               auto x = 1;

//     constexpr auto y = 2; // support : compiler-explorer.com //!!!константа значение которой известо на этапе компиляции (она только для чтения)

// //  ------------------------------------------------------------------

// //  ++y; // error

// //  ------------------------------------------------------------------

// //  [[maybe_unused]] constexpr auto z1 = test_v1(x); // error

// 	[[maybe_unused]] constexpr auto z2 = test_v1(y);

// //  ------------------------------------------------------------------

//     [[maybe_unused]]           auto z3 = test_v1(x);

//     [[maybe_unused]]           auto z4 = test_v1(y);

// //  ------------------------------------------------------------------

// //  [[maybe_unused]] constexpr auto z5 = test_v2(x); // error

// 	[[maybe_unused]] constexpr auto z6 = test_v2(y);

// //  ------------------------------------------------------------------

// //  [[maybe_unused]]           auto z7 = test_v2(x); // error

// 	[[maybe_unused]]           auto z8 = test_v2(y);

// //  ------------------------------------------------------------------

//     static_assert(factorial_v1(5) == 120);

//     static_assert(factorial_v2(5) == 120);

// //  ------------------------------------------------------------------

//     test_v3();

// //  ------------------------------------------------------------------

// //  constexpr std::vector < int > vector = { 1, 2, 3, 4, 5 }; // error

// //  ------------------------------------------------------------------

//     assert(++g_x == 2);
// }

// //////////////////////////////////////////////////////////////////////





#include <iostream>
#include <cassert>
#include <cmath>
#include <array>


consteval double calculate_pi(double epsilon)
{
    double pi = 0.0;
    double term_pi = 1.0;
    int sign_pi = 1;
    int denominator_pi = 1;
    
    while (std::abs(term_pi) >= epsilon) {
        pi += term_pi;
        
        sign_pi *= -1;
        denominator_pi += 2;
        term_pi = static_cast<double>(sign_pi) / denominator_pi;
    }

    return pi * 4.0;
}


consteval double calculate_e (double epsilon)
{
    double e = 0.0;
    double term_e = 1.0;
    double factorial_term = 1.0;
    int n_e = 0;
    
    while (std::abs(term_e) >= epsilon) {
        e += term_e;
        
        n_e++;
        term_e /= n_e;
    }

    return e;
}



int main() {

    std::cout << "Фактические значения:\n";
    std::cout << "epsilon = 0.1: pi = " << calculate_pi(0.1) 
              << ", e = " << calculate_e(0.1) << "\n";
    std::cout << "epsilon = 0.01: pi = " << calculate_pi(0.01) 
              << ", e = " << calculate_e(0.01) << "\n";
    std::cout << "epsilon = 0.001: pi = " << calculate_pi(0.001) 
              << ", e = " << calculate_e(0.001) << "\n\n";

    constexpr std::array <double, 3> epsilons = {0.1, 0.01, 0.001}; 

    // epsilon = 0.1
    static_assert(calculate_pi(epsilons[0]) > 3.0 && calculate_pi(epsilons[0]) < 3.35);
    static_assert(calculate_e(epsilons[0]) > 2.6 && calculate_e(epsilons[0]) < 2.8);
    
    // epsilon = 0.01
    static_assert(calculate_pi(epsilons[1]) > 3.1 && calculate_pi(epsilons[1]) < 3.15);
    static_assert(calculate_e(epsilons[1]) > 2.7 && calculate_e(epsilons[1]) < 2.72);
    
    // epsilon = 0.001
    static_assert(calculate_pi(epsilons[2]) > 3.13 && calculate_pi(epsilons[2]) < 3.15);
    static_assert(calculate_e(epsilons[2]) > 2.718 && calculate_e(epsilons[2]) < 2.719);
    
    return 0;
}