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

int main() {
    part1();
    return 0;
}
