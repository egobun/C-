//////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <cmath>
#include <numbers>
#include <iostream>
//////////////////////////////////////////////////////////////////////

// struct Entity
// { 
// 	int x = 0, y = 0;
// };

// //////////////////////////////////////////////////////////////////////

// int main()
// {
//     Entity entity_1(1, 1), * entity_2 = &entity_1;

// //  ------------------------------------------------------------------

// 	assert(entity_1.x == 1 && (*entity_2).x == entity_2->x);

// 	assert(entity_1.y == 1 && (*entity_2).y == entity_2->y);

// //  ------------------------------------------------------------------

// 	assert
// 	(
// 		static_cast < void * > (&entity_1  ) ==

// 		static_cast < void * > (&entity_1.x)
// 	);

// //  ------------------------------------------------------------------

// 	std::vector < Entity > entities(5);

// //  ------------------------------------------------------------------

// 	for (auto i = 0uz; i < std::size(entities); ++i)
// 	{
// 		entities[i].x = i + 1;

// 		entities[i].y = i + 1;
// 	}

// //  ------------------------------------------------------------------

// 	assert(std::ranges::is_sorted(entities, std::less(), &Entity::x));

// 	assert(std::ranges::is_sorted(entities, std::less(), &Entity::y));
//}

//////////////////////////////////////////////////////////////////////

class Figure
{
public:

	virtual ~Figure()
	{
		std::cout << "Figure::~Figure()" << std::endl;
	}
	
	virtual double perimeter() const = 0;

	virtual double square() const = 0;

	virtual std::string get_name() const {
		return name;
	}

private:

	inline static const std::string name = "Figure";

};

class Circle final : public Figure
{
public:

	Circle(double r) : r(r) {}

	~Circle()
	{
		std::cout << "Circle::~Circle()" << std::endl;
	}

	double perimeter() const override
	{
		return (2 * std::numbers::pi * r);
	}

	double square() const override
	{
		return (std::numbers::pi * r * r);
	}

	std::string get_name() const override
	{
		return name;
	}

private:	

	double r = 0;
	inline static const std::string name = "Circle"; 

};

class Square final : public Figure
{
public:

	Square(double a) : a(a) {}

	~Square()
	{
		std::cout << "Square::~Square()" << std::endl;
	}

	double square() const override
	{
		return a * a;
	}

	double perimeter() const override
	{
		return 4*a;
	}

	std::string get_name() const override
	{
		return name;
	}

private:

	double a = 0;
	inline static const std::string name = "Square";

};

class Triangle final : public Figure 
{
public:

	Triangle (double a, double b, double c) : a(a), b(b), c(c) {}

	~Triangle(){
		std::cout << "Triangle::~Triangle()" << std::endl;
	}

	double square() const override{
		double p = 0.5 * (a + b + c);
		double s = std::sqrt(p*(p-a)*(p-b)*(p-c));
		return s;
	}

	double perimeter() const override{
		return a + b + c;
	}

	std::string get_name() const override
	{
		return name;
	}

private:

	double a = 0;
	double b = 0;
	double c = 0;
	inline static const std::string name = "Triangle";


};


int main(){

	std::vector <Figure*> figures;

	Figure* circle = new Circle(5);
	Figure* square = new Square(2);
	Figure* triangle = new Triangle(10,12,3);


	figures.push_back(circle);
	figures.push_back(square);
	figures.push_back(triangle);

	for(auto fig : figures)
	{
		std::cout << fig->get_name() <<" S = " << fig->square() << "; P = " << fig->perimeter() << ";" <<std::endl;
	}

	for(auto fig : figures)
	{
		delete fig;
	}

	return 0;
}