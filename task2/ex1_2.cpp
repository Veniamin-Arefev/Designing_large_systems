#include <iostream>
#include <vector>


int main() {

    std::vector<bool> my_vec = {true, false, false, true, true};


    //doesn't compile with this
    /*
    std::cout << "Initial vector auto &:" << std::endl;
    for (auto &x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (auto &x: my_vec) {
        x = !x;
    }

    std::cout << "Current vector auto &:" << std::endl;
    for (auto &x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl << std::endl;
    */
    std::cout << "Initial vector auto &&:" << std::endl;
    for (auto &&x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (auto &&x: my_vec) {
        x = !x;
    }

    std::cout << "Current vector auto &&:" << std::endl;
    for (auto &&x: my_vec) {
        std::cout << x << " ";
    }
    std::cout << std::endl;


    return 0;
}
