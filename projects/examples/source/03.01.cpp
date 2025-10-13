/////////////////////////////////////////////////////////////////
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

// struct Entity 
// { 
// 	int x = 0, y = 0;
// };

/////////////////////////////////////////////////////////////////

struct Rectangle{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	Rectangle(double _x1, double _y1, double _x2, double _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

double intersection(std::vector <Rectangle>& vector){
	if(vector.empty()) {
		return 0.0;
	}
	double x_min = -std::numeric_limits<double>::infinity();
	double x_max = std::numeric_limits<double>::infinity();
	double y_min = -std::numeric_limits<double>::infinity();
	double y_max = std::numeric_limits<double>::infinity();

	for(auto i : vector){
		x_min = std::max(i.x1, x_min);
		x_max = std::min(i.x2, x_max);
		y_min = std::max(i.y1, y_min);
		y_max = std::min(i.y2, y_max);
	}

	if((x_max > x_min) && (y_max > y_min)){
		return (x_max - x_min)*(y_max - y_min);
	} else {
		return 0.0;
	}
}

int main(){
	Rectangle r1(4,5,17,8);
	Rectangle r2(6,7,15,20);
	Rectangle r3(12,5,15,20);
	std::vector <Rectangle> req;
	req.push_back(r1);
	req.push_back(r2);
	req.push_back(r3);
	double res = intersection(req);
	std::cout << res << std::endl;

//     [[maybe_unused]] Entity entity_1;
	
// 	[[maybe_unused]] Entity entity_2(2);
	
// 	[[maybe_unused]] Entity entity_3(3, 3);
		
// 	[[maybe_unused]] Entity entity_4 { .x = 4 };

// 	[[maybe_unused]] Entity entity_5 { .x = 5, .y = 5 };

// 	[[maybe_unused]] Entity entity_6 { .y = 6 };

// //	[[maybe_unused]] Entity entity_7 { .y = 7, .x = 7 }; // error
}

/////////////////////////////////////////////////////////////////