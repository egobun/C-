// ///////////////////////////////////////////////////////////

// #include <iostream>
// #include <print>

// ///////////////////////////////////////////////////////////

// int main()
// {
// 	auto x = 0;

// //  -------------------------------------------------------

// 	while (x > 0)
// 	{
// 		std::print("main : enter int x : "); std::cin >> x;
// 	}

// //  -------------------------------------------------------

// 	while (true)
// 	{
// 		std::print("main : enter int x : "); std::cin >> x;

// 	//  ---------------------------------------------------

// 		if (x == 0)
// 		{
// 			break;
// 		}
// 	}
// }

// ///////////////////////////////////////////////////////////



#include <iostream>
#include <cmath>

int main() {
    double epsilon;
    
    std::cout << "Enter epsilon: ";
    std::cin >> epsilon;
    
    if (epsilon <= 0) {
        std::cout << "Epsilon must be positive!" << std::endl;
        return 1;
    }
    
    double pi = 0.0;
    double term_pi = 1.0;
    int sign_pi = 1;
    int denominator_pi = 1;
    
    while (std::abs(term_pi) >= epsilon) {
        pi += term_pi;
        
        sign_pi *= -1;
        denominator_pi += 2;
        term_pi = sign_pi * (1.0 / denominator_pi);
    }
    
    pi *= 4.0;
    
    double e = 0.0;
    double term_e = 1.0;
    double factorial_term = 1.0;
    int n_e = 0;
    
    while (std::abs(term_e) >= epsilon) {
        e += term_e;
        
        n_e++;
        term_e /= n_e;
    }
    
    std::cout << "pi = " << pi << std::endl;
    std::cout << "e = " << e << std::endl;
    
    return 0;
}