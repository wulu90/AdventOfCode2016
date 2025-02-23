#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

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
        } else if (!line.contains("output")) {
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

tuple<string, string, string> parse2(const string& str) {
    auto [a, b, c] = parse_num(str);
    string sa, sb, sc;
    if (str.contains("low to bot")) {
        sb = format("b{}", b);
    }
    if (str.contains("low to output")) {
        sb = format("o{}", b);
    }

    if (str.contains("high to bot")) {
        sc = format("b{}", c);
    }
    if (str.contains("high to output")) {
        sc = format("o{}", c);
    }
    sa = format("b{}", a);
    return {sa, sb, sc};
}

void part2() {
    ifstream input("input/input10");
    map<string, set<uint>> id_bot;
    vector<tuple<string, string, string>> bot_give_vec;
    set<string> unvalued_bot;
    for (string line; getline(input, line);) {
        if (line.starts_with("value")) {
            auto [a, b, c] = parse_num(line);
            auto botname   = format("b{}", b);
            id_bot[botname].insert(a);
            unvalued_bot.insert(botname);
        } else {
            auto [sa, sb, sc] = parse2(line);
            bot_give_vec.push_back({sa, sb, sc});
            unvalued_bot.insert(sa);
            unvalued_bot.insert(sb);
            unvalued_bot.insert(sc);
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
            if ((id.starts_with("b") && bo.size() == 2) || (id.starts_with("o") && bo.size() == 1)) {
                unvalued_bot.erase(id);
            }
        }

        if ((!id_bot["o0"].empty()) && (!id_bot["o1"].empty()) && (!id_bot["o2"].empty())) {
            println("{},{},{},{}", id_bot["o0"], id_bot["o1"], id_bot["o2"],
                    *id_bot["o0"].begin() * *id_bot["o1"].begin() * *id_bot["o2"].begin());
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
