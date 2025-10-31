////////////////////////////////////////////////////////////////////

#include <print>
#include <utility>

////////////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(               ) { std::print("Entity:: Entity (1)\n"); }

	Entity(Entity const & ) { std::print("Entity:: Entity (2)\n"); }

	Entity(Entity       &&) { std::print("Entity:: Entity (3)\n"); }

   ~Entity(               ) { std::print("Entity::~Entity    \n"); }
};

////////////////////////////////////////////////////////////////////

auto make_entity_v1() 
{
	std::print("make_entity_v1\n");

	return Entity(); 
}

////////////////////////////////////////////////////////////////////

auto make_entity_v2()
{
	std::print("make_entity_v2\n");

	Entity entity;

//	return std::move(entity); // error
	
	return entity;
	//!!! retuen value optimization
	// если явно указывать возврат prvalue то это приведет к вызову дополительного конструктора 
	// а именно перемещающий конструктор переместит данные и присвоит  nullptr старому владельцу
	// если же вернуть lvalue то компилятор оптимизирует это и не будет делать глубокого копирования и вызывать два раза констрктор,
	// компилятор просто вызовет один раз конструктор, вот это  auto entity_1 = make_entity_v1(); оптимизируется в просто создание entity_1 
}

////////////////////////////////////////////////////////////////////

auto make_entity_v3(Entity entity)
{
	std::print("make_entity_v3\n");

	return entity;
}

////////////////////////////////////////////////////////////////////

int main()
{
    [[maybe_unused]] auto entity_1 = make_entity_v1();
	
	[[maybe_unused]] auto entity_2 = make_entity_v2();

//  ----------------------------------------------------------

	[[maybe_unused]] auto entity_3 = make_entity_v3(Entity());
}

////////////////////////////////////////////////////////////////////