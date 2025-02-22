#include <fstream>
#include <map>
#include <print>
#include <string>

using namespace std;

struct room {
    string name;
    uint id;
    string check;
};

room parse(const string& str) {
    auto last_dash      = str.rfind('-');
    auto square_bracket = str.find('[', last_dash);
    room r;
    r.name  = string{str.begin(), str.begin() + last_dash};
    r.id    = stoi(string{str.begin() + last_dash + 1, str.begin() + square_bracket});
    r.check = string{str.begin() + square_bracket + 1, str.end() - 1};
    return r;
}

bool room_real(const room& r) {
    map<char, uint> char_count;
    for (auto c : r.name) {
        if (c != '-') {
            ++char_count[c];
        }
    }

    string str;
    for (auto [c, n] : char_count) {
        str.push_back(c);
    }

    sort(str.begin(), str.end(),
         [&char_count](auto& c1, auto& c2) { return char_count[c1] == char_count[c2] ? c1 < c2 : char_count[c1] > char_count[c2]; });

    return str.starts_with(r.check);
}

void part1() {
    ifstream input("input/input04");
    uint sum = 0;
    for (string line; getline(input, line);) {
        auto r = parse(line);
        if (room_real(r)) {
            sum += r.id;
        }
    }

    println("{}", sum);
}

int main() {
    part1();
    return 0;
}
