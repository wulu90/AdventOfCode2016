#include <fstream>
#include <map>
#include <print>
#include <string>
#include <vector>

using namespace std;

void part1_2() {
    ifstream input("input/input06");
    string line;
    getline(input, line);
    vector<map<char, uint>> col_char_count(line.size());
    for (size_t i = 0; i < line.size(); ++i) {
        ++col_char_count[i][line[i]];
    }
    while (getline(input, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            ++col_char_count[i][line[i]];
        }
    }

    for (auto& char_count : col_char_count) {
        char c;
        uint maxcount = 0;
        for (auto [ch, n] : char_count) {
            if (n > maxcount) {
                maxcount = n;
                c        = ch;
            }
        }
        print("{}", c);
    }

    println();

    for (auto& char_count : col_char_count) {
        char c;
        uint mincount = UINT32_MAX;
        for (auto [ch, n] : char_count) {
            if (n < mincount) {
                mincount = n;
                c        = ch;
            }
        }
        print("{}", c);
    }

    println();
}

int main() {
    part1_2();
    return 0;
}
