//////////////////////////////////////////////////////////////////////

// #include <print>
#include <iostream>

#include <cassert>
#include <cstddef>
#include <vector>

//////////////////////////////////////////////////////////////////////

class Warrior
{
public :

	virtual ~Warrior() = default;

//  ---------------------------------------------------------

	virtual void attack() const
	{
		devour();

		shoot();

		toxin();
	} 

	virtual int strong() const { return 1; }

private :

//  ---------------------------------------------------------

	virtual void devour() const { std::cout << "Warrior::ram\n" << std::endl; }

	virtual void shoot() const { std::cout << "Warrior::ram\n" << std::endl; }

	virtual void toxin() const { std::cout << "Warrior::ram\n" << std::endl; }

};

//////////////////////////////////////////////////////////////////////

class Goblin : public Warrior 
{ 
public	:
	int strong() const override { return 2; }
private :

	void devour() const override { std::cout << "Goblin::devour\n" << std::endl; }

};

//////////////////////////////////////////////////////////////////////

class Archer : public Warrior
{
public	:

	int strong() const override { return 3; }

private :

	void shoot() const override { std::cout << "Archer::shoot\n" << std::endl; }
	

};

//////////////////////////////////////////////////////////////////////

class Elf : public Warrior
{
public	:

	int strong() const override { return 4; }

private :

	void toxin() const override { std::cout << "Elf::toxin\n" << std::endl; }
	

};

//////////////////////////////////////////////////////////////////////

class Solider : public Warrior
{
public :

   ~Solider()
    {
        for (auto warrior : m_warriors)
        {
            delete warrior;
        }
    }

//  ------------------------------------

    void add(Warrior * warrior) 
    { 
        m_warriors.push_back(warrior);
    }

//  ------------------------------------

    int strong() const override
    {
        auto x = 0;

        for (auto warrior : m_warriors)
        {
            if (warrior) 
            {
                x += warrior->strong();
            }
        }

        return x;
    }

	void attack() const override
	{
		for(auto warrior : m_warriors)
		{
			warrior->attack();
		}
	}

	void one_clan_attack(int clan_number)
	{
		m_warriors.at(clan_number)->attack();
	}

private :
    
    std::vector < Warrior * > m_warriors;
};

//////////////////////////////////////////////////////////////////////

class Builder_solider
{
public :

    virtual ~Builder_solider() = default;

//  ------------------------------

	virtual auto make_solider(std::size_t size) -> Warrior *
	{
	    m_solider = new Solider;

	    set_solider(size);

	    return m_solider;
	}

	virtual void set_solider(std::size_t size) const = 0;


protected :

    Solider * m_solider = nullptr;
};

////////////////////////////////////////////////////////////////////

class Builder_goblins_solider : public Builder_solider
{
public :

	void set_solider(std::size_t size) const override
	{
		for (auto i = 0uz; i < size; ++i) { m_solider->add(new Goblin); }
	}

};

////////////////////////////////////////////////////////////////////

class Builder_archers_solider : public Builder_solider
{
public :

	void set_solider(std::size_t size) const override
	{
		for (auto i = 0uz; i < size; ++i) { m_solider->add(new Archer); }
	}

};

////////////////////////////////////////////////////////////////////

class Builder_elves_solider : public Builder_solider
{
public :

	void set_solider(std::size_t size) const override
	{
		for (auto i = 0uz; i < size; ++i) { m_solider->add(new Elf); }
	}

};

////////////////////////////////////////////////////////////////////



int main()
{
// 	Entity * entity = new Client;

// //  -----------------------------

// 	entity->template_method();

// //  -----------------------------
	
// 	delete entity;


//     Builder * builder = new Builder_Client;

// //  ---------------------------------------

//     delete builder->make_entity();
    
//     //!!! delete пользователь делает самостоятельно - это недостаток
//     // решается интелектуальными указателями
//     delete builder;

	Builder_solider * builder_goblins_solider = new Builder_goblins_solider;
	Builder_solider * builder_archers_solider = new Builder_archers_solider;
	Builder_solider * builder_elves_solider = new Builder_elves_solider;


	auto solider = new Solider();
	
	solider->add(builder_goblins_solider->make_solider(2));
	solider->add(builder_archers_solider->make_solider(2));
	solider->add(builder_elves_solider->make_solider(2));


	//тут вызов attack от одного из warrior

	solider->one_clan_attack(0);

	// Warrior * warrior = solider;

	std::cout << "Sum solider strong = " << solider->strong() << std::endl;

	delete solider;



	delete builder_goblins_solider;
	delete builder_archers_solider;
	delete builder_elves_solider;
	

//     auto composite = new Composite;

// //  -----------------------------------------

//     for (auto i = 0uz; i < 5; ++i)
//     {
//         composite->add(make_composite(1, 1));
//     }

// //  -----------------------------------------

//     Entity * entity = composite;

// //  -----------------------------------------
        
//     assert(entity->test() == 15);

// //  -----------------------------------------

//     delete entity;
}

//////////////////////////////////////////////////////////////////////