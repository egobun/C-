// ////////////////////////////////////////////////////

// #include <cassert>

// ////////////////////////////////////////////////////

// struct Entity
// {
//     int x = 0, y = 0;
// };

// ////////////////////////////////////////////////////
// //!!!Федор Пикус - книга по паттернам 
// //!!! порождающие, поведенческий, .. паттерны

// class Builder
// {
// public :

//     virtual ~Builder() = default;

// //  -------------------------------

//     auto make_entity()
//     {
//         m_entity = new Entity;

//         set_x();

//         set_y();

//         return m_entity;
//     }

// //  -------------------------------

//     virtual void set_x() const = 0;

//     virtual void set_y() const = 0;

// protected :

//     Entity * m_entity = nullptr;
// };

// ////////////////////////////////////////////////////

// class Builder_Client : public Builder
// {
// public :

//     void set_x() const override { m_entity->x = 1; }

//     void set_y() const override { m_entity->y = 1; }
// };

// ////////////////////////////////////////////////////

// class Builder_Server : public Builder
// {
// public :

//     void set_x() const override { m_entity->x = 1; }

//     void set_y() const override { m_entity->y = 1; }
// };

// ////////////////////////////////////////////////////

// int main()
// {
//     Builder * builder = new Builder_Client;

// //  ---------------------------------------

//     delete builder->make_entity();
    
//     //!!! delete пользователь делает самостоятельно - это недостаток
//     // решается интелектуальными указателями
//     delete builder;


// }

////////////////////////////////////////////////////


// Реализуйте такую разновидность паттерна Builder, которая позволяет выполнять поэтапное создание состав-
// ного объекта следующим образом: auto person = builder.name("Ivan").age(25).grade(10).get(), где
// person является экземпляром класса Person, а builder является экземпляром класса Builder. Реализуйте
// класс Person для представления составного объекта. Реализуйте класс Builder для представления процесса
// создания составного объекта. Реализуйте в классе Builder конструктор по умолчанию для создания состав-
// ного объекта в начальном состоянии. Реализуйте в классе Builder публичные функции-члены для поэтапного
// создания составного объекта и публичную функцию-член get для получения созданного составного объекта.

#include <iostream>
#include <ostream>

class Person
{
public:
    Person()
    {
        name = "";
        age = 0;
        grade = 0;
    }

    std::string name;
    int age;
    int grade;

    friend auto & operator << (std::ostream & stream, Person const & person)
    {
        return stream << 
            "name  = " << person.name << std::endl <<
            "age  = " << person.age << std::endl <<
            "grade  = " << person.grade << std::endl;
    }
};

class Builder
{
    
public:
    Builder()
    {
        person = new Person;
    }

    ~Builder() = default;

    auto name(std::string name)
    {
        person->name = name;
        return *this;
    }

    auto age(int age)
    {
        person->age = age;
        return *this;
    }

    auto grade (int grade)
    {
        person->grade = grade;
        return *this;
    }

    auto get() const
    {
        return person;
    }

protected:
    Person * person = nullptr;
};

int main()
{
    Builder * builder = new Builder();

    auto person = (*builder).name("Ivan").age(25).grade(10).get();

    std::cout << *person <<std::endl;
    return 0;
}