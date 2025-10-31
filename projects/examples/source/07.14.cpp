///////////////////////////////////////////////////////////////

#include <format>
#include <iterator>
#include <print>
#include <stacktrace>

///////////////////////////////////////////////////////////////

void test_v1()
{
    for (auto const & entry : std::stacktrace::current())
    {
        std::print("test_v1 : entry : ");

        if (auto file = entry.source_file(); !std::empty(file))
        {
            std::print("{} : ", file);
        }

        if (auto line = entry.source_line(); line > 0)
        {
            std::print("{:0>3} : ", line);
        }

        std::print("{}\n", entry.description());
    }
}

///////////////////////////////////////////////////////////////

void test_v2() { test_v1(); }

void test_v3() { test_v2(); }

///////////////////////////////////////////////////////////////

int main()
{
    test_v3();
}

///////////////////////////////////////////////////////////////