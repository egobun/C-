//////////////////////////////////////////////////

#include <chrono>
#include <print>
#include <stop_token>
#include <thread>

//////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////

void test(std::stop_token token)
{
    auto lambda = [](){ std::print("lambda\n"); };
        
    std::stop_callback callback(token, lambda);

    while (!token.stop_requested())
    {
        std::print("test\n");

        std::this_thread::sleep_for(1s);
    }
}

//////////////////////////////////////////////////

int main()
{
    std::jthread jthread(test);

//  -----------------------------------------

    std::this_thread::sleep_for(5s);

//  -----------------------------------------

    jthread.get_stop_source().request_stop();
}

//////////////////////////////////////////////////