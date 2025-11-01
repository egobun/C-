// //////////////////////////////////////////////////////////////

// #include <iostream>
// #include <print>

// //////////////////////////////////////////////////////////////

// class Entity
// {
// private :

//     friend class Attorney;

// //  ----------------------------------------------------------

//     static void test_v1() { std::print("Entity::test_v1\n"); }

//     static void test_v2() { std::print("Entity::test_v2\n"); }
// };

// //////////////////////////////////////////////////////////////

// class Attorney 
// {
// private :

//     friend class Client;

// //  --------------------------------------

//     static void test_v1() 
//     {
//         std::print("Attorney::test_v1\n");

//         Entity::test_v1();
//     }

// //  --------------------------------------

//     static void test_v2() 
//     {
//         std::print("Attorney::test_v2\n");
//     }
// };


// ///////////////////////////////////////////////////////////////
// //!!!если мы хотим вызвать функции test_v1 и v2 у конкретного экземпляра Entity
// //в main создается экземпляр entuty и client, clirnt принимает этот экземпляр entity
// //и передает его в функцию test от Attorney, где Attorney вызывает функцию test у принятого экземпляра класса Entity 

// class Client
// {
// public :

//     static void test()
//     {
//         Attorney::test_v1();

//         Attorney::test_v2();
//     }
// };

// //////////////////////////////////////////////////////////////

// int main()
// {
//     Client::test();
// }

// //////////////////////////////////////////////////////////////
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <compare>
#include <initializer_list>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <cassert>


class IPv4 
{
    
public:
    IPv4() = default;

    IPv4(std::initializer_list <std::uint8_t> list)
    {
        std::copy(list.begin(),list.end(),addr);
    }

    friend auto operator<=>(IPv4 const & lhs, IPv4 const & rhs)
    {
        if(lhs.addr[0] != rhs.addr[0])
        {
            return lhs.addr[0] <=> rhs.addr[0];
        } else if (lhs.addr[1] != rhs.addr[1])
        {
            return lhs.addr[1] <=> rhs.addr[1];
        } else if (lhs.addr[2] != rhs.addr[2])
        {
            return lhs.addr[2] <=> rhs.addr[2];    
        } else if (lhs.addr[3] != rhs.addr[3])
        {
            return lhs.addr[3] <=> rhs.addr[3];
        } else
        {
            return std::strong_ordering::equal;
        }
    }

    friend auto operator==(IPv4 const & lhs, IPv4 const & rhs){
        if(std::equal(lhs.addr,lhs.addr + 4,rhs.addr))
        {
            return true;
        } else {
            return false;
        }

    }

    //префиксный
    auto & operator++()
    {
        if (static_cast<int>(addr[3]) != 255)
        {
            addr[3] += static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[2]) != 255) 
        {
            addr[2] += static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[1]) != 255)
        { 
            addr[1] += static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[0]) != 255)
        {
            for(int i = 0; i < 4; i++)
            {
                addr[i] = static_cast<std::uint8_t>(0);
            }
        }
        return *this;
    }

    // постфиксный
    auto const operator++(int)
    {
        auto x = *this;
        if (static_cast<int>(addr[3]) != 255)
        {
            addr[3] += static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[2]) != 255) 
        {
            addr[2] += static_cast<std::uint8_t>(1);
            addr[3] = static_cast<std::uint8_t>(0);
        } else if (static_cast<int>(addr[1]) != 255)
        { 
            addr[1] += static_cast<std::uint8_t>(1);
            addr[2] = static_cast<std::uint8_t>(0);
            addr[3] = static_cast<std::uint8_t>(0);
        } else if (static_cast<int>(addr[0]) != 255)
        {
            addr[0] += static_cast<std::uint8_t>(1);
            addr[1] = static_cast<std::uint8_t>(0);
            addr[2] = static_cast<std::uint8_t>(0);
            addr[3] = static_cast<std::uint8_t>(0);
        } else 
        {
            for(int i = 0; i < 4; i++)
            {
                addr[i] = static_cast<std::uint8_t>(0);
            }
        }
        return x;
    }

    // //префиксный
    auto & operator--()
    {
        if (static_cast<int>(addr[3]) != 0)
        {
            addr[3] -= static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[2]) != 0) 
        {
            addr[2] -= static_cast<std::uint8_t>(1);
            addr[3] = static_cast<std::uint8_t>(255);
        } else if (static_cast<int>(addr[1]) != 0)
        { 
            addr[1] -= static_cast<std::uint8_t>(1);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        } else if (static_cast<int>(addr[0]) != 255)
        {
            addr[0] -= static_cast<std::uint8_t>(1);
            addr[1] = static_cast<std::uint8_t>(255);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        } else 
        {
            addr[0] = static_cast<std::uint8_t>(255);
            addr[1] = static_cast<std::uint8_t>(255);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        }
        return *this;
    }

    // //постфиксный
    auto const operator--(int)
    {
        auto x = *this;
        if (static_cast<int>(addr[3]) != 0)
        {
            addr[3] -= static_cast<std::uint8_t>(1);
        } else if (static_cast<int>(addr[2]) != 0) 
        {
            addr[2] -= static_cast<std::uint8_t>(1);
            addr[3] = static_cast<std::uint8_t>(255);
        } else if (static_cast<int>(addr[1]) != 0)
        { 
            addr[1] -= static_cast<std::uint8_t>(1);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        } else if (static_cast<int>(addr[0]) != 255)
        {
            addr[0] -= static_cast<std::uint8_t>(1);
            addr[1] = static_cast<std::uint8_t>(255);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        } else 
        {
            addr[0] = static_cast<std::uint8_t>(255);
            addr[1] = static_cast<std::uint8_t>(255);
            addr[2] = static_cast<std::uint8_t>(255);
            addr[3] = static_cast<std::uint8_t>(255);
        }
        return x;
    }

    friend auto & operator>>(std::istream & stream, IPv4 & ipv4)
    {
        int array[4];
        auto & out_stream = (((stream >> array[0]).ignore() >> array[1]).ignore() >> array[2]).ignore() >> array[3];
        //??? насколько корректно тут писать ссылку?

        for(int i = 0; i < 4; i++)
        {
            ipv4.addr[i] = static_cast<std::uint8_t> (array[i]);
        }

        return out_stream;
    }

    friend auto & operator<<(std::ostream & stream, IPv4 const & ipv4)
    {
        return stream << static_cast<int>(ipv4.addr[0]) << "." << static_cast<int>(ipv4.addr[1]) << "." << static_cast<int>(ipv4.addr[2]) << "." << static_cast<int>(ipv4.addr[3]) << std::endl;
    }


private:
    std::uint8_t addr[4] = {0};
};

int main()
{
    IPv4 ipv4_1 = {255,255,255,34};
     

    std::stringstream stream_2("255.255.255.34|255.255.255.14");

    IPv4 ipv4_2;
    stream_2 >> ipv4_2 ;
    stream_2.ignore();

    IPv4 ipv4_3;
    stream_2 >> ipv4_3;

    

    assert((ipv4_1 <=> ipv4_2) == 0);
    assert((ipv4_3 <=> ipv4_2) < 0);
    assert((ipv4_1 <=> ipv4_3) > 0);


    IPv4 ipv4_incr = {255,255,5,255};
    assert((ipv4_incr++) == IPv4({255,255,5,255})); 
    assert((++ipv4_incr) == IPv4({255,255,6,1}));

    IPv4 ipv4_decr = {255,255,5,0};
    assert((ipv4_decr--) == IPv4({255,255,5,0})); 
    assert((--ipv4_decr) == IPv4({255,255,4,254}));

    

    std::cout << "ipv4_1 = " << ipv4_1 << "ipv4_2 = " << ipv4_2 << "ipv4_3 = " << ipv4_3;

    std::cout << (ipv4_1 < ipv4_2) << "||" << (ipv4_1 > ipv4_2) << "||" << (ipv4_1 == ipv4_2) << std::endl;
    
}