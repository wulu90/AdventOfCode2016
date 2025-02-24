#include <algorithm>
#include <fstream>
#include <string>
#include <string_view>

using namespace std;

string next_row(const string& str) {
    string row(str.size() - 2, ' ');

    for (size_t i = 1; i < str.size() - 1; ++i) {
        string_view sv{str.data() + i - 1, str.data() + i + 2};
        if (sv == "^^."sv || sv == ".^^"sv || sv == "^.."sv || sv == "..^"sv) {
            row[i - 1] = '^';
        } else {
            row[i - 1] = '.';
        }
    }
    return row;
}

void part1() {
    ifstream input("input/input18");
    string line;
    getline(input, line);

    auto safe_tiles = count_if(line.begin(), line.end(), [](auto& c) { return c == '.'; });
    for (int i = 0; i < 39; ++i) {
        line     = '.' + line + '.';
        auto row = next_row(line);
        safe_tiles += count_if(row.begin(), row.end(), [](auto& c) { return c == '.'; });
        line = std::move(row);
    }

    println("{}", safe_tiles);
}

int main() {
    part1();
    return 0;
}
