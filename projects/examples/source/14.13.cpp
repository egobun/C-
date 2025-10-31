////////////////////////////////////////////////////

#include <chrono>
#include <future>
#include <print>
#include <thread>

////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_future(m_promise.get_future()) {}

//  ------------------------------------------------

    void test() const
    {
        trace(); m_future.wait();

        trace();
    }

//  ------------------------------------------------

    void release() const
    {
        m_promise.set_value();
    }

private :

    void trace() const
    {
        auto id = std::this_thread::get_id();

        std::print("Entity::trace : id = {}\n", id);
    }

//  ------------------------------------------------

    mutable std::promise < void > m_promise;

    mutable std::shared_future < void > m_future;
};

////////////////////////////////////////////////////

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

////////////////////////////////////////////////////