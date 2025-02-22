#include <array>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

pair<size_t, size_t> parse(const string& str) {
    size_t a, b;
    bool isa = false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            uint n = 0;
            while (isdigit(str[i])) {
                n = n * 10 + str[i] - '0';
                ++i;
            }
            if (!isa) {
                a   = n;
                isa = true;
            } else {
                b = n;
            }
        }
    }
    return {a, b};
}

void part1_2() {
    array<bool, 50> row_off;
    row_off.fill(false);
    array<array<bool, 50>, 6> screen;
    screen.fill(row_off);

    ifstream input("input/input08");
    for (string line; getline(input, line);) {
        auto [a, b] = parse(line);
        if (line.starts_with("rect")) {
            for (size_t i = 0; i < b; ++i) {
                for (size_t j = 0; j < a; ++j) {
                    screen[i][j] = true;
                }
            }
        } else if (line.starts_with("rotate row")) {
            vector<size_t> row_on;
            for (size_t i = 0; i < 50; ++i) {
                if (screen[a][i]) {
                    row_on.push_back(i);
                    screen[a][i] = false;
                }
            }

            for (auto i : row_on) {
                screen[a][(i + b) % 50] = true;
            }

        } else {
            vector<size_t> col_on;
            for (size_t i = 0; i < 6; ++i) {
                if (screen[i][a]) {
                    col_on.push_back(i);
                    screen[i][a] = false;
                }
            }

            for (auto i : col_on) {
                screen[(i + b) % 6][a] = true;
            }
        }
    }

    uint num = 0;
    for (auto& row : screen) {
        for (auto b : row) {
            if (b) {
                ++num;
            }
        }
    }

    println("{}", num);

    for (auto& row : screen) {
        for (auto b : row) {
            if (b) {
                print("#");
            } else {
                print(" ");
            }
        }
        println();
    }
}

int main() {
    part1_2();
    return 0;
}
