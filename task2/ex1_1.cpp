#include <iostream>
#include <vector>


int main() {

    std::vector<int> my_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "Initial vector auto &:" << std::endl;
    for (auto &x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (auto &x: my_vec) {
        ++x;
    }

    std::cout << "Current vector auto &:" << std::endl;
    for (auto &x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Initial vector auto &&:" << std::endl;
    for (auto &&x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (auto &&x: my_vec) {
        ++x;
    }

    std::cout << "Current vector auto &&:" << std::endl;
    for (auto &&x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;


    return 0;
}
