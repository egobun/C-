/////////////////////////////////////////////////////////

#include <barrier>
#include <chrono>
#include <iostream>
#include <print>
#include <syncstream>
#include <thread>

/////////////////////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_barrier(3) {}

//  -----------------------------------------------------

    void test() const
    {
        trace(); m_barrier.arrive_and_wait();

        trace(); m_barrier.arrive_and_wait();

        trace();
    }

//  -----------------------------------------------------

    void release() const
    {
        m_barrier.arrive_and_drop();
    }

private :

    class Callback
    {
    public :

        void operator()() const
        {
            std::print("Entity::Callback::operator()\n");
        }
    };

//  -----------------------------------------------------

    void trace() const
    {
        std::osyncstream stream(std::cout);

        auto id = std::this_thread::get_id();

        stream << "Entity::trace : id = " << id << '\n';
    }

//  -----------------------------------------------------

    mutable std::barrier < Callback > m_barrier;
};

/////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------------------------------------

    std::jthread jthread_1(&Entity::test, &entity);

    std::jthread jthread_2(&Entity::test, &entity);

//  -----------------------------------------------

    std::this_thread::sleep_for(1s);

//  -----------------------------------------------

    entity.release();
}

/////////////////////////////////////////////////////////