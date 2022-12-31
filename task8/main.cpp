#include <iostream>
#include <fstream>
#include <iterator>
#include <cstring>
#include <unordered_map>
#include <vector>

std::string input_file_name = "input.txt";
std::string output_file_name = "output.txt";
std::string bin_file_name = "graph.bin";


void serialize() {
    std::ifstream input(input_file_name, std::ios::in);
    std::ofstream output(bin_file_name, std::ios::binary);

    uint32_t a_node, b_node, value, count_of_elements;
    uint8_t small_size_value;

    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>> my_map;

    while (input >> a_node >> b_node >> value) {
//        std::cout << a_node << " " << b_node << " " << true_value << std::endl;
        my_map[value].push_back(std::make_pair(a_node, b_node));
    }

    for (auto &[my_value, my_pairs]: my_map) {
        small_size_value = my_value;
        output.write(reinterpret_cast<char *>(&small_size_value), sizeof(small_size_value));

        count_of_elements = my_pairs.size();
        output.write(reinterpret_cast<char *>(&count_of_elements), sizeof(count_of_elements));

        for (auto &[my_a_node, my_b_node]: my_pairs) {
            output.write(reinterpret_cast<char *>(&my_a_node), sizeof(my_a_node));
            output.write(reinterpret_cast<char *>(&my_b_node), sizeof(my_b_node));
        }
    }

    input.close();
    output.close();
}

void deserialize() {
    std::ifstream input(bin_file_name, std::ios::binary);
    std::ofstream output(output_file_name);

    uint32_t a_node, b_node, value, count_of_elements;
    uint8_t small_size_value;

    bool was_output = false;

    while (input) {
        input.read(reinterpret_cast<char *>(&small_size_value), sizeof(small_size_value));
        value = small_size_value;
        input.read(reinterpret_cast<char *>(&count_of_elements), sizeof(count_of_elements));

        if (!input) {
            break;
        }

        for (size_t i = 0; i < count_of_elements; ++i) {
            input.read(reinterpret_cast<char *>(&a_node), sizeof(a_node));
            input.read(reinterpret_cast<char *>(&b_node), sizeof(b_node));


            if (was_output) {
                output << std::endl;
            } else {
                was_output = true;
            }
            output << a_node << '\t' << b_node << '\t' << value;
        }
        if (!input) {
            break;
        }
//        std::cout << a_node << " " << b_node << " " << true_value << std::endl;

    }

    input.close();
    output.close();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Unexpected number of arguments.\n";
        exit(1);
    }
    if (strcmp(argv[1], "-s") == 0) {
        std::cout << "Started serializing.\n";
        serialize();
        std::cout << "Serializing done.\n";
    } else if (strcmp(argv[1], "-d") == 0) {
        std::cout << "Started deserializing.\n";
        deserialize();
        std::cout << "Deserializing done.\n";
    } else {
        std::cout << "Unexpected command line properties.\n";
    }
}
