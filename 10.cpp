#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct bot {
    uint v1;
    uint v2;
    uint vc;    // value count; 0,1,2
};

tuple<uint, uint, uint> parse_num(const string& str) {
    tuple<uint, uint, uint> res;
    get<0>(res) = 123;

    uint inx = 0;
    uint n   = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            n = 0;
            while (isdigit(str[i])) {
                n = n * 10 + str[i] - '0';
                ++i;
            }

            if (inx == 0) {
                get<0>(res) = n;
                inx         = 1;
            } else if (inx == 1) {
                get<1>(res) = n;
                inx         = 2;
            } else {
                get<2>(res) = n;
            }
        }
    }

    return res;
}

void part1() {
    ifstream input("input/input10");
    map<uint, set<uint>> id_bot;
    vector<tuple<uint, uint, uint>> bot_give_vec;
    set<uint> unvalued_bot;
    for (string line; getline(input, line);) {
        auto [a, b, c] = parse_num(line);
        if (line.starts_with("value")) {
            id_bot[b].insert(a);
            unvalued_bot.insert(b);
        } else {
            bot_give_vec.push_back({a, b, c});
            unvalued_bot.insert(a);
            unvalued_bot.insert(b);
            unvalued_bot.insert(c);
        }
    }

    bool find = false;
    while (!unvalued_bot.empty()) {
        for (auto [a, b, c] : bot_give_vec) {
            if (id_bot[a].size() == 2) {
                id_bot[b].insert(*id_bot[a].begin());
                id_bot[c].insert(*id_bot[a].rbegin());
            }
        }

        for (auto& [id, bo] : id_bot) {
            if (bo.size() == 2) {
                unvalued_bot.erase(id);
            }
        }

        for (auto& [id, bo] : id_bot) {
            if (*bo.begin() == 17 && *bo.rbegin() == 61) {
                println("{}", id);
                find = true;
                break;
            }
        }
        if (find) {
            break;
        }
    }
}

int main() {
    part1();
    return 0;
}
