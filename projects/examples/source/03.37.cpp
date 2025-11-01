/////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <istream>
#include <ostream>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  ---------------------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Entity & entity)
    {
        //!!! если за entity будет скрываться Client то будет вызвана реализация 
        // функции get из Client
        return entity.get(stream.ignore()).ignore();
    }

//  ---------------------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, Entity const & entity)
    //!!! важно что приходит ссылка на entity чтобы мы могли вытянуть из него Client
    {        
        return entity.put(stream << "{ ") << " }";
        //!!! вызывается put из дочернего класса:
        // в реализации put дочернего класса сначала выполняется put базового класса
        // потом выводится m_y а потом уже добавляется " }" из реализации оператора << 
    }

protected :

    virtual std::istream & get(std::istream & stream)       { return stream >> m_x; }

    virtual std::ostream & put(std::ostream & stream) const { return stream << m_x; }

//  ---------------------------------------------------------------------------------

    int m_x = 0;
};

/////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity 
{
public :

    std::istream & get(std::istream & stream) override
    {
        return Entity::get(stream).ignore() >> m_y;
    }

//  --------------------------------------------------------

    std::ostream & put(std::ostream & stream) const override
    { 
        return Entity::put(stream) << ", " << m_y;
    }

private :

    int m_y = 0;
};

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream_1("{ 1, 1 }");

    std::stringstream stream_2;

//  -----------------------------------------
    
    Entity * entity = new Client;

//  -----------------------------------------
//!!! мы хотим вызывать операторы ввода вывода реализованные не для базового класса а для потомка 
// так как операторы являются внешними их перегружать невозможно
// но возможно в их реализации вызывать virtual перегруженные функции
// и тогда операторы << >> для различных классов (детей и родителей) будут различными
    stream_1 >> *entity;

    stream_2 << *entity;

//  -----------------------------------------

    delete entity;

//  -----------------------------------------

    assert(stream_2.str() == stream_1.str());
}

/////////////////////////////////////////////////////////////////////////////////////