#include <algorithm>
#include <fstream>
#include <ranges>
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
        blacklist.emplace_back(a, b);
    }
    blacklist.pop_back();    // because of last blank line

    sort(blacklist.begin(), blacklist.end());

    auto [low, high] = blacklist.front();
    if (low != 0) {
        println("0");
        return;
    }

    for (auto [l, h] : blacklist | views::drop(1)) {
        if (l > high + 1) {
            println("{}", high + 1);
            break;
        } else {
            high = max(high, h);
        }
    }
}

int main() {
    part1();
    return 0;
}
