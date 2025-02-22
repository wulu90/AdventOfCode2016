#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

bool ipv7_tls(const string& str) {
    vector<size_t> abba_inxs;
    vector<pair<size_t, size_t>> square_inxs;

    for (size_t i = 0; i < str.size() - 3; ++i) {
        if (str[i] == '[') {
            square_inxs.push_back({i, 0});
        }

        if (str[i] == ']') {
            square_inxs.back().second = i;
        }

        if (str[i] == str[i + 3] && str[i + 1] == str[i + 2] && str[i] != str[i + 1]) {
            abba_inxs.push_back(i);
        }
    }

    if (abba_inxs.empty()) {
        return false;
    } else {
        for (auto [a, b] : square_inxs) {
            for (auto i : abba_inxs) {
                if (i > a && i < b) {
                    return false;
                }
            }
        }
        return true;
    }
}

void part1() {
    ifstream input("input/input07");
    uint count = 0;
    for (string line; getline(input, line);) {
        if (ipv7_tls(line)) {
            ++count;
        }
    }
    println("{}", count);
}

int main() {
    part1();
    return 0;
}
