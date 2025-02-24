#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input20");
    uint32_t a, b;
    vector<pair<uint32_t, uint32_t>> blacklist;
    while (input.good()) {
        input >> a;
        input.get();    // skip '-'
        input >> b;
        blacklist.push_back(minmax(a, b));
    }
    blacklist.pop_back();    // because of last blank line

    sort(blacklist.begin(), blacklist.end());

    uint32_t bound = 0;

    for (auto [l, h] : blacklist) {
        if (l > bound + 1) {
            println("{}", bound + 1);
            break;
        } else {
            bound = max(bound, h);
        }
    }
}

void part2() {
    ifstream input("input/input20");
    uint32_t a, b;
    vector<pair<uint32_t, uint32_t>> blacklist;
    while (input.good()) {
        input >> a;
        input.get();    // skip '-'
        input >> b;

        blacklist.push_back(minmax(a, b));
    }
    blacklist.pop_back();    // because of last blank line

    sort(blacklist.begin(), blacklist.end());

    uint32_t bound = 0;
    uint32_t count = 0;

    for (auto [l, h] : blacklist) {
        if (l > bound + 1) {
            count += l - bound - 1;
            bound = h;
        } else {
            bound = max(bound, h);
        }

        if (bound == UINT32_MAX) {
            break;
        }
    }
    count += UINT32_MAX - bound;
    println("{}", count);
}

int main() {
    part1();
    part2();
    return 0;
}
