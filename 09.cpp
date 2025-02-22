#include <fstream>

using namespace std;

void part1() {
    ifstream input("input/input09");
    uint num = 0;
    for (char c = input.get(); input; c = input.get()) {
        if (!isspace(c)) {
            if (c != '(') {
                ++num;
            } else {
                c = input.get();
                uint a, b;
                uint n = 0;
                while (isdigit(c)) {
                    n = n * 10 + c - '0';
                    c = input.get();
                }
                a = n;
                c = input.get();    // axb -> x -> b
                n = 0;
                while (isdigit(c)) {
                    n = n * 10 + c - '0';
                    c = input.get();
                }
                b = n;    // c-> )

                num += a * b;

                for (uint i = 0; i < a;) {
                    c = input.get();
                    if (!isspace(c)) {
                        ++i;
                    }
                }
            }
        }
    }

    println("{}", num);
}

int main() {
    part1();
    return 0;
}
