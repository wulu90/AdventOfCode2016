#include <fstream>
#include <print>
#include <vector>

using namespace std;

bool valid_triangle(uint a, uint b, uint c) {
    return a + b > c && b + c > a && c + a > b;
}

void part1() {
    ifstream input("input/input03");
    uint a, b, c;
    uint valid_count = 0;
    while (input.good()) {
        input >> a;
        input >> b;
        input >> c;
        if (valid_triangle(a, b, c)) {
            ++valid_count;
        }
    }
    println("{}", valid_count);
}

uint triangle_in_column(const vector<uint>& vec) {
    uint valid = 0;
    for (size_t i = 0; i < vec.size() - 2; i += 3) {
        if (valid_triangle(vec[i], vec[i + 1], vec[i + 2])) {
            ++valid;
        }
    }
    return valid;
}

void part2() {
    ifstream input("input/input03");
    uint a, b, c;
    vector<vector<uint>> vec_vec(3);
    while (input.good()) {
        input >> a;
        input >> b;
        input >> c;
        vec_vec[0].push_back(a);
        vec_vec[1].push_back(b);
        vec_vec[2].push_back(c);
    }
    uint valid_count = 0;
    for (size_t i = 0; i < 3; ++i) {
        valid_count += triangle_in_column(vec_vec[i]);
    }

    println("{}", valid_count);
}

int main() {
    part1();
    part2();
    return 0;
}
