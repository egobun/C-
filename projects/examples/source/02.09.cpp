////////////////////////////////////////////////////

#include <initializer_list>

////////////////////////////////////////////////////


#include <iostream>
#include <numeric>



int gcd_recursive(int a, int b) {
    if (b == 0) return a;
    return gcd_recursive(b, a % b);
}

int gcd_iterative(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm_via_gcd(int a, int b) {
    if (a == 0 || b == 0) return 0;
    int gcd_val = gcd_iterative(a, b);
    return (a / gcd_val) * b;
}

int main() {
    int x, y;
    std::cout << "cin x  y: ";
    std::cin >> x >> y;

    int gcd_rec = gcd_recursive(x, y);
    int gcd_it = gcd_iterative(x, y);
    int lcm_calc = lcm_via_gcd(x, y);

    std::cout << "recursive gcd: " << gcd_rec << "\n";
    std::cout << "iterative gcd: " << gcd_it << "\n";
    std::cout << "lcm: " << lcm_calc << "\n";

    std::cout << "std::gcd: " << std::gcd(x, y) << "\n";
    std::cout << "std::lcm: " << std::lcm(x, y) << "\n";

    return 0;
}



////////////////////////////////////////////////////