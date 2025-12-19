// Реализуйте шаблон свойств is_class по аналогии со стандартным шаблоном свойств std::is_class. Не до-
// бавляйте стандартный шаблон свойств std::is_union в собственную реализацию шаблона свойств is_class.
// Объясните концепцию указателя на член класса в реализации стандартного шаблона свойств std::is_class.
// Реализуйте шаблоны свойств add_const и remove_const по аналогии со стандартными шаблонами свойств
// std::add_const и std::remove_const соответственно. Реализуйте шаблон свойств decay по аналогии со
// стандартным шаблоном свойств std::decay. Реализуйте шаблон свойств conditional по аналогии со стан-
// дартным шаблоном свойств std::conditional. Реализуйте необходимые шаблоны псевдонимов и шаблоны
// переменных для всех шаблонов свойств. Реализуйте тесты на основе статических утверждений static_assert.

#include <cassert>
#include <type_traits>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct remove_reference          { using type = T; };

template < typename T > struct remove_reference < T &  > { using type = T; };

template < typename T > struct remove_reference < T && > { using type = T; };

template < typename T > using  remove_reference_t = typename remove_reference < T > ::type;

/////////////////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////////

template < typename T >
struct is_function : std::integral_constant 
<
    bool, !std::is_const_v < T const > && !std::is_reference_v < T >

> {};

template < typename T > constexpr auto is_function_v = is_function < T > ::value;

/////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    // template<class T>
    // std::integral_constant<bool, !std::is_union<T>::value> test(int T::*);
 
	template<class T>
	std::true_type test(void (T::*)(int));
	// std::true_type test(int (T::*));

    template<class>
    std::false_type test(...);
}
 
template <class T>
struct is_class : decltype(detail::test<T>(nullptr)) {};

template <class T>
constexpr bool is_class_v = is_class<T>::value;

//////////////////////////////////////////////////////////////////////

template<class T>
struct add_const { typedef const T type; };

template <typename T>
using add_const_t = typename add_const<T>::type;

//////////////////////////////////////////////////////////////////////

template<class T>
struct remove_const { typedef T type; };

template<class T>
struct remove_const<const T> { typedef T type; };

template< class T >
using remove_const_t = typename remove_const<T>::type;

//////////////////////////////////////////////////////////////////////

template<bool B, class T, class F>
struct conditional { using type = T; };
 
template<class T, class F>
struct conditional<false, T, F> { using type = F; };

template< bool B, class T, class F >
using conditional_t = typename conditional<B,T,F>::type;

//////////////////////////////////////////////////////////////////////


template<class T>
struct decay
{
private:
    typedef typename remove_reference<T>::type U;
public:
    typedef typename conditional< 
        std::is_array<U>::value,
        typename std::add_pointer<typename std::remove_extent<U>::type>::type,
        typename conditional< 
            is_function<U>::value,
            typename std::add_pointer<U>::type,
            typename std::remove_cv<U>::type
        >::type
    >::type type;
};

template< class T >
using decay_t = typename decay<T>::type;

//////////////////////////////////////////////////////////////////////


int main()
{
    struct A{};
    class B{};
    union C{};
    
    // is_class
    static_assert(is_class_v<A>, "A should be a class");
    static_assert(is_class_v<B>, "B should be a class");
    static_assert(!is_class_v<C>, "C should not be a class (it's a union)");
    static_assert(!is_class_v<int>, "int should not be a class");
    static_assert(!is_class_v<double>, "double should not be a class");
    
    // add_const
    static_assert(std::is_same_v<add_const_t<int>, const int>, "add_const_t<int> should be const int");
    static_assert(std::is_same_v<add_const_t<const int>, const int>, "add_const_t<const int> should be const int");
    static_assert(std::is_same_v<add_const_t<int*>, int* const>, "add_const_t<int*> should be int* const");
    static_assert(std::is_same_v<add_const_t<int&>, int&>, "add_const_t<int&> should be int& (references can't be const-qualified)");
    
    // remove_const
    static_assert(std::is_same_v<remove_const_t<const int>, int>, "remove_const_t<const int> should be int");
    static_assert(std::is_same_v<remove_const_t<int>, int>, "remove_const_t<int> should be int");
    static_assert(std::is_same_v<remove_const_t<const volatile int>, volatile int>, "remove_const_t<const volatile int> should be volatile int");
    static_assert(std::is_same_v<remove_const_t<const int*>, const int*>, "remove_const_t<const int*> should be const int* (pointer to const, not const pointer)");
    static_assert(std::is_same_v<remove_const_t<int* const>, int*>, "remove_const_t<int* const> should be int*");
    
    //  conditional
    static_assert(std::is_same_v<conditional_t<true, int, double>, int>, "conditional_t<true, int, double> should be int");
    static_assert(std::is_same_v<conditional_t<false, int, double>, double>, "conditional_t<false, int, double> should be double");
    static_assert(std::is_same_v<conditional_t<(sizeof(int) > 2), int, char>, int>, "conditional_t<(sizeof(int) > 2), int, char> should be int");
    static_assert(std::is_same_v<conditional_t<(sizeof(int) < 2), int, char>, char>, "conditional_t<(sizeof(int) < 2), int, char> should be char");
    
    //  decay
    static_assert(std::is_same_v<decay_t<int>, int>, "decay_t<int> should be int");
    static_assert(std::is_same_v<decay_t<int&>, int>, "decay_t<int&> should be int");
    static_assert(std::is_same_v<decay_t<int&&>, int>, "decay_t<int&&> should be int");
    static_assert(std::is_same_v<decay_t<const int&>, int>, "decay_t<const int&> should be int");
    static_assert(std::is_same_v<decay_t<int[5]>, int*>, "decay_t<int[5]> should be int*");
    static_assert(std::is_same_v<decay_t<int(int)>, int(*)(int)>, "decay_t<int(int)> should be int(*)(int)");
    static_assert(std::is_same_v<decay_t<const int[5]>, const int*>, "decay_t<const int[5]> should be const int*");
    static_assert(std::is_same_v<decay_t<volatile int&&>, volatile int>, "decay_t<volatile int&&> should be volatile int");
    
    //  remove_reference
    static_assert(std::is_same_v<remove_reference_t<int>, int>, "remove_reference_t<int> should be int");
    static_assert(std::is_same_v<remove_reference_t<int&>, int>, "remove_reference_t<int&> should be int");
    static_assert(std::is_same_v<remove_reference_t<int&&>, int>, "remove_reference_t<int&&> should be int");
    static_assert(std::is_same_v<remove_reference_t<const int&>, const int>, "remove_reference_t<const int&> should be const int");
    static_assert(std::is_same_v<remove_reference_t<volatile int&&>, volatile int>, "remove_reference_t<volatile int&&> should be volatile int");
    
    // Комплексные тесты
    static_assert(std::is_same_v<add_const_t<remove_reference_t<int&>>, const int>, "add_const_t<remove_reference_t<int&>> should be const int");
    static_assert(std::is_same_v<remove_const_t<add_const_t<int>>, int>, "remove_const_t<add_const_t<int>> should be int");
    static_assert(std::is_same_v<conditional_t<is_class_v<A>, add_const_t<A>, remove_const_t<A>>, const A>, "Complex conditional test 1");
    static_assert(std::is_same_v<conditional_t<is_class_v<int>, add_const_t<int>, remove_const_t<int>>, int>, "Complex conditional test 2");
    
    // Тесты с пользовательскими типами
    struct MyStruct { int x; };
    static_assert(std::is_same_v<decay_t<MyStruct>, MyStruct>, "decay_t<MyStruct> should be MyStruct");
    static_assert(std::is_same_v<decay_t<MyStruct&>, MyStruct>, "decay_t<MyStruct&> should be MyStruct");
    static_assert(std::is_same_v<decay_t<MyStruct&&>, MyStruct>, "decay_t<MyStruct&&> should be MyStruct");
    static_assert(std::is_same_v<add_const_t<MyStruct>, const MyStruct>, "add_const_t<MyStruct> should be const MyStruct");
    static_assert(std::is_same_v<remove_const_t<const MyStruct>, MyStruct>, "remove_const_t<const MyStruct> should be MyStruct");
    
    // Тесты с указателями
    static_assert(std::is_same_v<decay_t<int*>, int*>, "decay_t<int*> should be int*");
    static_assert(std::is_same_v<decay_t<const int*>, const int*>, "decay_t<const int*> should be const int*");
    static_assert(std::is_same_v<decay_t<int* const>, int*>, "decay_t<int* const> should be int*");
    
    // Тесты с функциями
    using FuncType = int(int, double);
    static_assert(std::is_same_v<decay_t<FuncType>, int(*)(int, double)>, "decay_t<int(int, double)> should be int(*)(int, double)");
    static_assert(std::is_same_v<decay_t<FuncType&>, int(*)(int, double)>, "decay_t<int(int, double)&> should be int(*)(int, double)");
    static_assert(std::is_same_v<decay_t<FuncType&&>, int(*)(int, double)>, "decay_t<int(int, double)&&> should be int(*)(int, double)");
    
    // Проверка, что наша реализация соответствует std
    static_assert(std::is_same_v<add_const_t<int>, std::add_const_t<int>>, "add_const_t should match std::add_const_t");
    static_assert(std::is_same_v<remove_const_t<const int>, std::remove_const_t<const int>>, "remove_const_t should match std::remove_const_t");
    static_assert(std::is_same_v<conditional_t<true, int, double>, std::conditional_t<true, int, double>>, "conditional_t should match std::conditional_t");
    static_assert(std::is_same_v<decay_t<int&>, std::decay_t<int&>>, "decay_t should match std::decay_t");

    return 0;
}