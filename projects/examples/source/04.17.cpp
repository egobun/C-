// ////////////////////////////////////////////////////////////////////////
// //!!!Тюринг полнота
// //!!!Вычисление на этапе компиляции
// //!!!метапрограммирование шаблонов
// template < int X >
// struct Factorial
// {
// 	static inline auto const value = X * Factorial < X - 1 > ::value;
// };

// ////////////////////////////////////////////////////////////////////////
// //!!!полная специализация шаблона для нулевого значения
// template <>
// struct Factorial < 0 > 
// { 
// 	static inline auto const value = 1;
// };

// ////////////////////////////////////////////////////////////////////////
// //!!!шаблон переменной (is_convertible_v-пример в прошлых примерах)
// template < int X >
// auto const factorial_v = Factorial < X > ::value;

// ////////////////////////////////////////////////////////////////////////

// int main()
// {
//     static_assert(factorial_v < 5 > == 120); // support : cppinsights.io
// }

// ////////////////////////////////////////////////////////////////////////





// Реализуйте алгоритм вычисления N - ого числа ряда Фибоначчи на основе рекурсивного подхода. Используйте
// метапрограммирование шаблонов. Реализуйте базовый шаблон структуры Fibonacci для представления N -
// ого числа ряда Фибоначчи. Реализуйте в шаблоне структуры Fibonacci параметр типа int для указания
// номера N на этапе компиляции. Реализуйте в структуре Fibonacci статическое константное поле типа int
// для хранения вычисляемого на этапе компиляции N - ого числа ряда Фибоначчи. Реализуйте в структуре
// Fibonacci статическое утверждение static_assert для проверки переполнения типа int при вычислениях
// на этапе компиляции. Реализуйте две полные специализации шаблона структуры Fibonacci для представления
// первого и второго чисел ряда Фибоначчи. Реализуйте шаблон константы для сокращения записей обращений
// к полю шаблона структуры Fibonacci. Реализуйте тесты на основе статических утверждений static_assert.


#include <numeric>

template <int N>
struct Fibonacci
{
	static inline int const F_n = Fibonacci<N-1>::F_n + Fibonacci<N-2>::F_n ;
	static_assert(std::numeric_limits<int>::max() >= F_n);
	static_assert(std::numeric_limits<int>::min() <= F_n);
};

template <>
struct Fibonacci < 1 >
{
	static inline int const F_n = 0;

};

template <>
struct Fibonacci < 2 >
{
	static inline int const F_n = 1;

};

template <int N>
int const fibonacci_v = Fibonacci<N>::F_n;


int main()
{
    static_assert(fibonacci_v < 6 > == 5); // support : cppinsights.io
}
