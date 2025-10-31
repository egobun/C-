//////////////////////////////////////////////////////

#include <print>

//////////////////////////////////////////////////////

class Singleton
{
public :

    Singleton            (Singleton const &) = delete;

//  --------------------------------------------------

    Singleton & operator=(Singleton const &) = delete;

//  --------------------------------------------------

    void test() const
    { 
        std::print("Singleton::test\n");
    }

//  --------------------------------------------------

    static auto & get() 
    { 
        static Singleton singleton;
        
        return singleton;
    }

private :

    Singleton() = default;
};

//////////////////////////////////////////////////////

int main()
{
    Singleton::get().test();
}

//////////////////////////////////////////////////////