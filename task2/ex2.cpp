#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <tuple>
#include <set>
#include <utility>


template<typename T>
constexpr bool IsTuple = false;
template<typename ... types>
constexpr bool IsTuple<std::tuple<types...>> = true;

struct Printer {
    std::ostringstream ostrstream;

    std::string str() const {
        return ostrstream.str();
    }


    template<
            typename T, //real type
            typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
    >
    Printer &format(T my_number) {
        ostrstream << my_number;
        return *this;
    }


    Printer &format(const std::string &string) {
        ostrstream << string;
        return *this;
    }

    //( item, item )
    template<typename type1, typename type2>
    Printer &format(const std::pair<type1, type2> &pair) {
        return format("(").format(pair.first).format(", ").format(pair.second).format(")");
    }

    template<typename Container>
    Printer &container_printer(const Container &container, const std::string &begin, const std::string &end) {
        format(begin + " ");
        for (auto iter = container.begin(); iter != container.end();) {
            format(*iter);
            if (++iter != container.end()) {
                format(", ");
            }
        }
        return format(" " + end);
    }

    //[ element, ..., element ]
    template<typename type1>
    Printer &format(const std::vector<type1> &vector) {
        return container_printer(vector, "[", "]");
    }

    // { element, ..., element }
    template<typename type1>
    Printer &format(const std::set<type1> &set) {
        return container_printer(set, "{", "}");
    }

    //( element, ..., element ).
    template<typename TupleType, std::size_t... Indexes>
    void deal_with_tuple_index(const TupleType &tp, std::index_sequence<Indexes...>) {
        size_t index = 0;
        auto format_element = [&index, this](const auto &x) {
            if (index++ > 0) {
                format(", ");
            }
            format(x);
        };

        format("( ");
        (format_element(std::get<Indexes>(tp)), ...);
        format(" )");
    }

    template<typename Tuple, std::size_t TupleSize = std::tuple_size_v<Tuple>>
    void deal_with_tuple(const Tuple &tuple) {
        deal_with_tuple_index(tuple, std::make_index_sequence<TupleSize>{});
    }

    template<typename... Tuple>
    Printer &format(const std::tuple<Tuple...> &t) {
        deal_with_tuple(t);
        return *this;
    }

};


int main() {
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4},
                                           {5, 6}};

    std::cout << Printer().format(" vector: ").format(v).str() << std::endl;
    std::cout << " vector: [ (1, 4), (5, 6) ]" << std::endl << std::endl;

    std::cout << Printer().format(t).format(" ! ").format(0).str() << std::endl;
    std::cout << "( xyz, 1, 2 ) ! 0" << std::endl << std::endl;


    auto t2 = std::make_tuple(
            std::make_tuple(
                    std::numeric_limits<signed short>::min(),
                    std::numeric_limits<signed short>::max(),
                    std::numeric_limits<unsigned short>::min(),
                    std::numeric_limits<unsigned short>::max()
            ), "\n",
            std::make_tuple(
                    std::numeric_limits<signed int>::min(),
                    std::numeric_limits<signed int>::max(),
                    std::numeric_limits<unsigned int>::min(),
                    std::numeric_limits<unsigned int>::max()
            ), "\n",
            std::make_tuple(
                    std::numeric_limits<signed long>::min(),
                    std::numeric_limits<signed long>::max(),
                    std::numeric_limits<unsigned long>::min(),
                    std::numeric_limits<unsigned long>::max()
            ), "\n",
            std::make_tuple(
                    std::numeric_limits<signed long long>::min(),
                    std::numeric_limits<signed long long>::max(),
                    std::numeric_limits<unsigned long long>::min(),
                    std::numeric_limits<unsigned long long>::max()
            ), "\n"
    );

    std::cout << Printer().format(t2).str() << std::endl;
    std::cout << "( ( -32768, 32767, 0, 65535 ),\n"
                 ", ( -2147483648, 2147483647, 0, 4294967295 ),\n"
                 ", ( -9223372036854775808, 9223372036854775807, 0, 18446744073709551615 ),\n"
                 ", ( -9223372036854775808, 9223372036854775807, 0, 18446744073709551615 ),\n"
                 " )" << std::endl << std::endl;

    return 0;
}
