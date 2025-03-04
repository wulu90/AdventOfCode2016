#include <charconv>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void run(array<int, 5> regs, const vector<string>& ins_vec) {
    size_t index = 0;
    while (index < ins_vec.size()) {
        auto& ins = ins_vec[index];
        if (ins.starts_with("cpy")) {
            if (isalpha(ins[4])) {
                regs[ins.back() - 'a'] = regs[ins[4] - 'a'];
            } else {
                auto p1 = ins.find(' ');
                auto p2 = ins.rfind(' ');
                int num = 0;
                from_chars(ins.data() + p1 + 1, ins.data() + p2, num);
                regs[ins.back() - 'a'] = num;
            }
            ++index;
        } else if (ins.starts_with("inc")) {
            ++regs[ins.back() - 'a'];
            ++index;
        } else if (ins.starts_with("dec")) {
            --regs[ins.back() - 'a'];
            ++index;
        } else if (ins.starts_with("jnz")) {
            int awaystep = 0;
            auto p1      = ins.find(' ');
            auto p2      = ins.rfind(' ');
            if (isalpha(ins[p2 + 1])) {
                awaystep = regs[ins[p2 + 1] - 'a'];
            } else {
                from_chars(ins.data() + p2 + 1, ins.data() + ins.size(), awaystep);
            }
            int condition = 0;
            if (isalpha(ins[4])) {
                condition = regs[ins[4] - 'a'];
            } else {
                from_chars(ins.data() + p1 + 1, ins.data() + p2, condition);
            }
            if (condition != 0) {
                index += awaystep;
            } else {
                ++index;
            }
        }
    }

    println("{}", regs[0]);
}

void part1_2() {
    ifstream input("input/input12");
    vector<string> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.push_back(line);
    }

    array<int, 5> regs{0, 0, 0, 0, 0};
    run(regs, ins_vec);
    regs = {0, 0, 1, 0, 0};
    run(regs, ins_vec);
}

int main() {
    part1_2();
    return 0;
}
