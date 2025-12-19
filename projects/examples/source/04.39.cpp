////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <type_traits>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts >
struct Deque {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
struct Size {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts >
struct Size < Deque < Ts ... > >
{
    constexpr static auto value = sizeof...(Ts);
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
constexpr auto size_v = Size < D > ::value;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
constexpr auto is_empty_v = size_v < D > == 0;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
struct Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts >
struct Front < Deque < T, Ts ... > > 
{ 
    using type = T;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
using front = typename Front < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D >
struct Push_Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts >
struct Push_Front < T, Deque < Ts ... > >
{
    using type = Deque < T, Ts ... > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D >
using push_front = typename Push_Front < T, D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
struct Pop_Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts >
struct Pop_Front < Deque < T, Ts ... > >
{
    using type = Deque < Ts ... > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
using pop_front = typename Pop_Front < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
struct Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T >
struct Back < Deque < T > > 
{ 
    using type = T;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts >
struct Back < Deque < T, Ts ... > > 
{ 
    using type = typename Back < Deque < Ts ... > > ::type;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using back = typename Back < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D, bool C = is_empty_v < D > > struct Push_Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > struct Push_Back < T, D, false >
{
    using type = push_front < front < D > , typename Push_Back < T, pop_front < D > > ::type > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > struct Push_Back < T, D, true >
{
    using type = push_front < T, D > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > using push_back = typename Push_Back < T, D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Pop_Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct Pop_Back < Deque < T > > 
{ 
    using type = Deque <> ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Pop_Back < Deque < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < Deque < Ts ... > > ::type > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_back = typename Pop_Back < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, std::size_t I > class Nth : public Nth < pop_front < D > , I - 1 > {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Nth < D, 0 > : public Front < D > {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, std::size_t I > using nth = typename Nth < D, I > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, bool C = is_empty_v < D > >
class Max_Type {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
class Max_Type < D, false >
{
private :

    using current_t = front < D > ;

    using max_t = typename Max_Type < pop_front < D > > ::type;

public :

    using type = std::conditional_t < sizeof(current_t) >= sizeof(max_t), current_t, max_t > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
class Max_Type < D, true > 
{ 
public : 

    using type = std::byte;
};


////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D >
using max_type = typename Max_Type < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

// Доработайте пример 04.39 таким образом, чтобы пользователь мог проверить наличие некоторого типа T
// в очереди. Реализуйте базовый шаблон структуры Has, а также две частичные специализации для пустой и
// непустой очередей соответственно по аналогии с шаблоном класса Max_Type. Используйте стандартный шаб-
// лон свойств std::is_same для сравнения типов. Реализуйте шаблон константы для сокращения записей обра-
// щений к полю шаблона структуры Has. Реализуйте тесты на основе статических утверждений static_assert.

template <typename Deque, typename T, bool C = is_empty_v<Deque>>
struct Has;

template <typename Deque, typename T>
struct Has <Deque, T, true>
{
    static constexpr bool value = false;
};

template <typename Head, typename... Tail, typename T>
struct Has<Deque<Head, Tail...>, T, false>
{
    static constexpr bool value = std::is_same_v <Head, T> || Has<Deque<Tail...> , T>::value;
};

template < typename Deque, typename T>
constexpr auto has_v = Has < Deque, T>::value;



int main()
{
    static_assert(size_v < Deque <     > > == 0 && is_empty_v < Deque <     > > == 1);

    static_assert(size_v < Deque < int > > == 1 && is_empty_v < Deque < int > > == 0);

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <      front <      Deque < int > > ,         int        > );

    static_assert(std::is_same_v < push_front < int, Deque < int > > , Deque < int, int > > );

    static_assert(std::is_same_v <  pop_front <      Deque < int > > , Deque <          > > );

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <       back <      Deque < int > > ,              int   > );

    static_assert(std::is_same_v <  push_back < int, Deque < int > > , Deque < int, int > > );

    static_assert(std::is_same_v <   pop_back <      Deque < int > > , Deque <          > > );

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < nth < Deque < int, int >, 0 > , int > );

    static_assert(std::is_same_v < nth < Deque < int, int >, 1 > , int > );

//  ------------------------------------------------------------------------------------------
    static_assert(std::is_same_v < max_type < Deque < int, double > > , double > );

//  ------------------------------------------------------------------------------------------

    static_assert(has_v<Deque<float, double, int>, int> == true);

}

////////////////////////////////////////////////////////////////////////////////////////////////


