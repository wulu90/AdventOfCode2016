#include <fstream>
#include <print>

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

int main() {
    part1();
    return 0;
}
