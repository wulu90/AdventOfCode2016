#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void swap_position(string& str, size_t x, size_t y) {
    swap(str[x], str[y]);
}

void swap_letter(string& str, char x, char y) {
    vector<size_t> x_indexs, y_indexs;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == x) {
            x_indexs.push_back(i);
            continue;
        }
        if (str[i] == y) {
            y_indexs.push_back(i);
        }
    }

    for (auto i : x_indexs) {
        str[i] = y;
    }
    for (auto i : y_indexs) {
        str[i] = x;
    }
}

void rotate_steps(string& str, bool left, size_t steps) {
    steps %= str.size();
    if (left) {
        rotate(str.begin(), str.begin() + steps, str.end());
    } else {
        rotate(str.rbegin(), str.rbegin() + steps, str.rend());
    }
}

void rotate_letter(string& str, char x) {
    auto pos   = str.find(x);
    auto steps = 1 + pos + (pos >= 4 ? 1 : 0);
    rotate_steps(str, false, steps);
}

void reverse_pos(string& str, size_t x, size_t y) {
    reverse(str.begin() + x, str.begin() + y + 1);
}

void move_pos(string& str, size_t x, size_t y) {
    auto c = str[x];
    str.erase(x, 1);
    str.insert(str.begin() + y, c);
}

void part1() {
    ifstream input("input/input21");
    string str{"abcdefgh"};

    for (string line; getline(input, line);) {
        if (line.starts_with("swap po")) {
            swap_position(str, line[14] - '0', line.back() - '0');
        } else if (line.starts_with("swap le")) {
            swap_letter(str, line[12], line[26]);
        } else if (line.starts_with("rotate left")) {
            rotate_steps(str, true, line[12] - '0');
        } else if (line.starts_with("rotate right")) {
            rotate_steps(str, false, line[13] - '0');
        } else if (line.starts_with("rotate based")) {
            rotate_letter(str, line.back());
        } else if (line.starts_with("reverse")) {
            reverse_pos(str, line[18] - '0', line.back() - '0');
        } else {    // move position
            move_pos(str, line[14] - '0', line.back() - '0');
        }
    }

    println("{}", str);
}

void part2() {
    ifstream input("input/input21");
    string str{"abcdefgh"};
    vector<string> scrambler_vec;
    for (string line; getline(input, line);) {
        scrambler_vec.push_back(line);
    }

    do {
        auto tmp = str;
        for (auto& line : scrambler_vec) {
            if (line.starts_with("swap po")) {
                swap_position(str, line[14] - '0', line.back() - '0');
            } else if (line.starts_with("swap le")) {
                swap_letter(str, line[12], line[26]);
            } else if (line.starts_with("rotate left")) {
                rotate_steps(str, true, line[12] - '0');
            } else if (line.starts_with("rotate right")) {
                rotate_steps(str, false, line[13] - '0');
            } else if (line.starts_with("rotate based")) {
                rotate_letter(str, line.back());
            } else if (line.starts_with("reverse")) {
                reverse_pos(str, line[18] - '0', line.back() - '0');
            } else {    // move position
                move_pos(str, line[14] - '0', line.back() - '0');
            }
        }

        if (str == "fbgdceah") {
            println("{}", tmp);
            break;
        }
    } while (next_permutation(str.begin(), str.end()));
}

int main() {
    part1();
    part2();
    return 0;
}
