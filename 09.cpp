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

uint64_t decompress_len(string str) {
    uint64_t len = 0;
    for (size_t i = 0; i < str.size();) {
        if (str[i] != '(') {
            ++len;
            ++i;
        } else {
            uint64_t a, b;
            uint64_t n = 0;
            ++i;
            while (isdigit(str[i])) {
                n = n * 10 + str[i] - '0';
                ++i;
            }
            a = n;
            n = 0;
            ++i;
            while (isdigit(str[i])) {
                n = n * 10 + str[i] - '0';
                ++i;
            }
            b = n;

            ++i;
            string tmp;
            tmp.reserve(a);
            size_t j = a;
            while (j > 0) {
                if (!isspace(str[i])) {
                    tmp.push_back(str[i]);
                    --j;
                }
                ++i;
            }
            len += b * decompress_len(tmp);
        }
    }
    return len;
}

void part2() {
    ifstream input("input/input09");
    string line;
    getline(input, line);
    println("{}", decompress_len(line));
}

int main() {
    part1();
    part2();
    return 0;
}
