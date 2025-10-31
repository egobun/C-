///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <chrono>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <new>
#include <ranges>
#include <thread>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer() : m_begin(clock_t::now()) {}

//  -----------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (clock_t::now() - m_begin);
	}

private :

    using clock_t = std::chrono::steady_clock;

//  -----------------------------------------------------------------------
	
	clock_t::time_point m_begin;
};

///////////////////////////////////////////////////////////////////////////////////

class Task
{
public :

    virtual ~Task() = default;

//  -------------------------------------------------------------

    auto operator()(std::barrier <> & barrier, std::size_t index)
    {
        barrier.arrive_and_wait();

        Timer timer;

        test(index);

        return timer.elapsed().count();
    }

//  -------------------------------------------------------------

    virtual void test(std::size_t index) = 0;
};

///////////////////////////////////////////////////////////////////////////////////

class Task_v1 : public Task
{
public :

    Task_v1(std::size_t size) : m_entities(size) {}

//  -----------------------------------------------

    void test(std::size_t index) override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            m_entities.at(index).x.store(1);
        }
    }

private :

    struct Entity
    {
        std::atomic < int > x = 0;
    };

//  -----------------------------------------------

    std::vector < Entity > m_entities;
};

///////////////////////////////////////////////////////////////////////////////////

class Task_v2 : public Task
{
public :

    Task_v2(std::size_t size) : m_entities(size) {}

//  -------------------------------------------------------------------

    void test(std::size_t index) override
    {
        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            m_entities.at(index).x.store(1);
        }
    }

private :

    struct alignas(std::hardware_constructive_interference_size) Entity
    {
        std::atomic < int > x = 0;
    };

//  -------------------------------------------------------------------

    std::vector < Entity > m_entities;
};

///////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task > task;
    
    if (state.range(0) == 1) { task = std::make_shared < Task_v1 > (concurrency); }

    if (state.range(0) == 2) { task = std::make_shared < Task_v2 > (concurrency); }

    std::barrier <> barrier(concurrency + 1);

    auto lambda = [](auto & future){ return future.get(); };
	
    for (auto element : state)
    {
        for (auto i = 0uz; i < concurrency; ++i)
        {
            futures[i] = std::async
            (
                std::launch::async, &Task::operator(), task, std::ref(barrier), i
            );
        }
        
        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::ranges::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(*task);
    }
}

///////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2);

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////