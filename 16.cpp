#include <print>
#include <ranges>
#include <string>

using namespace std;

string dragon_curve(string str, size_t len) {
    if (str.length() >= len) {
        return str;
    } else {
        auto tmp = str;
        tmp.reserve(str.length() * 2 + 1);
        tmp.push_back('0');
        for (auto c : str | views::reverse) {
            tmp.push_back(c == '1' ? '0' : '1');
        }
        return dragon_curve(tmp, len);
    }
}

string check_sum(string str) {
    if (str.length() % 2 != 0) {
        return str;
    } else {
        string tmp;
        tmp.reserve(str.size() / 2);
        for (size_t i = 0; i < str.size(); i += 2) {
            tmp.push_back(str[i] == str[i + 1] ? '1' : '0');
        }
        return check_sum(tmp);
    }
}

void part1() {
    string input{"00111101111101000"};
    size_t len = 272;
    auto data  = dragon_curve(input, len);
    data.resize(len);
    println("{}", check_sum(data));
}

int main() {
    part1();
    return 0;
}
