#include <fstream>
#include <map>
#include <print>
#include <string>

using namespace std;

void next_digit(uint8_t& curr, char dire) {
    static const map<pair<uint8_t, char>, uint8_t> mat{
        {{1, 'R'}, 2}, {{1, 'D'}, 4}, {{2, 'R'}, 3}, {{2, 'L'}, 1}, {{2, 'D'}, 5}, {{3, 'D'}, 6}, {{3, 'L'}, 2}, {{4, 'R'}, 5},
        {{4, 'D'}, 7}, {{4, 'U'}, 1}, {{5, 'R'}, 6}, {{5, 'D'}, 8}, {{5, 'U'}, 2}, {{5, 'L'}, 4}, {{6, 'U'}, 3}, {{6, 'L'}, 5},
        {{6, 'D'}, 9}, {{7, 'R'}, 8}, {{7, 'U'}, 4}, {{8, 'U'}, 5}, {{8, 'L'}, 7}, {{8, 'R'}, 9}, {{9, 'U'}, 6}, {{9, 'L'}, 8}};

    if (mat.contains({curr, dire}))
        curr = mat.at({curr, dire});
}

void part1() {
    ifstream input("input/input02");
    uint8_t curr = 5;
    for (string line; getline(input, line);) {
        for (auto c : line) {
            next_digit(curr, c);
        }
        print("{}", curr);
    }
    println();
}

void next_key(char& curr, char dire) {
    // clang-format off
    static const map<pair<char, char>, char> mat{
       {{'1', 'D'}, '3'},
       {{'2', 'R'}, '3'}, {{'2', 'D'}, '6'},
       {{'3', 'U'}, '1'}, {{'3', 'R'}, '4'}, {{'3', 'D'}, '7'}, {{'3', 'L'}, '2'},
       {{'4', 'D'}, '8'}, {{'4', 'L'}, '3'},
       {{'5', 'R'}, '6'},
       {{'6', 'U'}, '2'}, {{'6', 'R'}, '7'}, {{'6', 'D'}, 'A'}, {{'6', 'L'}, '5'},
       {{'7', 'U'}, '3'}, {{'7', 'R'}, '8'}, {{'7', 'D'}, 'B'}, {{'7', 'L'}, '6'},
       {{'8', 'U'}, '4'}, {{'8', 'R'}, '9'}, {{'8', 'D'}, 'C'}, {{'8', 'L'}, '7'},
       {{'9', 'L'}, '8'},
       {{'A', 'U'}, '6'}, {{'A', 'R'}, 'B'},
       {{'B', 'U'}, '7'}, {{'B', 'R'}, 'C'}, {{'B', 'D'}, 'D'}, {{'B', 'L'}, 'A'},
       {{'C', 'U'}, '8'}, {{'C', 'L'}, 'B'},
       {{'D', 'U'}, 'B'}
    };
    // clang-format on

    if (mat.contains({curr, dire}))
        curr = mat.at({curr, dire});
}

void part2() {
    ifstream input("input/input02");
    char curr = '5';
    for (string line; getline(input, line);) {
        for (auto c : line) {
            next_key(curr, c);
        }
        print("{}", curr);
    }
    println();
}

int main() {
    part1();
    part2();
    return 0;
}
