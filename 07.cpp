#include <fstream>
#include <print>
#include <set>
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

bool ipv7_ssl(const string& str) {
    set<string> aba_sets;
    set<string> bab_sets;

    bool in_square = false;
    for (size_t i = 0; i < str.size() - 2; ++i) {
        if (str[i] == '[') {
            in_square = true;
        }

        if (str[i] == ']') {
            in_square = false;
        }

        if (str[i] == str[i + 2] && str[i] != str[i + 1]) {
            if (in_square) {
                bab_sets.insert({str.begin() + i, str.begin() + i + 3});
            } else {
                aba_sets.insert({str.begin() + i, str.begin() + i + 3});
            }
        }
    }

    if (aba_sets.empty() || bab_sets.empty()) {
        return false;
    } else {
        for (auto aba : aba_sets) {
            string bab{aba[1], aba[0], aba[1]};
            if (bab_sets.contains(bab)) {
                return true;
            }
        }

        return false;
    }
}

void part1_2() {
    ifstream input("input/input07");
    uint tls_count = 0;
    uint ssl_count = 0;
    for (string line; getline(input, line);) {
        if (ipv7_tls(line)) {
            ++tls_count;
        }
        if (ipv7_ssl(line)) {
            ++ssl_count;
        }
    }
    println("{}", tls_count);
    println("{}", ssl_count);
}

int main() {
    part1_2();
    return 0;
}
