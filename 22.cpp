#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t> parse(const string& str) {
    static const regex pattern{R"(\d+)"};
    sregex_iterator it(str.begin(), str.end(), pattern);

    return {
        stoi(it++->str()), stoi(it++->str()), stoi(it++->str()), stoi(it++->str()), stoi(it++->str()), stoi(it->str()),
    };
}

void part1() {
    ifstream input("input/input22");
    using disk = tuple<uint32_t, uint32_t, uint32_t, uint32_t>;    // size, used, avial, use%
    map<pair<uint32_t, uint32_t>, disk> storage_grid;
    string line;
    getline(input, line);
    getline(input, line);

    while (getline(input, line)) {
        auto [x, y, s, u, a, p] = parse(line);
        storage_grid.insert({{x, y}, {s, u, a, p}});
    }
    map<uint32_t, vector<pair<uint32_t, uint32_t>>> avail_coords;
    for (auto [coord, node] : storage_grid) {
        auto [s, u, a, p] = node;
        avail_coords[a].push_back(coord);
    }

    uint32_t fits = 0;
    for (auto [coord, node] : storage_grid) {
        auto [s, u, a, p] = node;

        if (u == 0) {
            continue;
        }

        for (auto [a_b, vec] : avail_coords) {
            if (u <= a_b) {
                fits += vec.size();
            }
        }
        if (u <= a) {
            --fits;
        }
    }

    println("{}", fits);
}

int main() {
    part1();
    return 0;
}
