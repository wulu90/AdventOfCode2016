#include <fstream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <vector>

using namespace std;

uint32_t interest_to_interest_shortest(const vector<string>& inputmap, char i0, char i1,
                                       const map<char, pair<uint32_t, uint32_t>>& interests_location) {
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    uint row_count = inputmap.size();
    uint col_count = inputmap.front().size();

    queue<pair<uint32_t, uint32_t>> q;
    q.push(interests_location.at(i0));

    set<pair<uint32_t, uint32_t>> visited;
    visited.insert(interests_location.at(i0));

    uint32_t res  = 0;
    uint32_t step = 0;
    while (!q.empty()) {
        auto n = q.size();
        for (size_t i = 0; i < n; ++i) {
            auto curr = q.front();
            q.pop();

            if (curr == interests_location.at(i1)) {
                res = step;
                break;
            }

            for (auto [dr, dc] : deltas) {
                auto r = curr.first + dr;
                auto c = curr.second + dc;
                if (r < row_count && c < col_count && !visited.contains({r, c}) && inputmap[r][c] != '#') {
                    q.push({r, c});
                    visited.insert({r, c});
                }
            }
        }
        ++step;
    }

    return res;
}

void part1() {
    ifstream input("input/input24");
    vector<string> inputmap;
    for (string line; getline(input, line);) {
        inputmap.push_back(line);
    }

    map<char, pair<uint32_t, uint32_t>> interests_location;
    for (size_t i = 0; i < inputmap.size(); ++i) {
        for (size_t j = 0; j < inputmap.front().size(); ++j) {
            if (isdigit(inputmap[i][j])) {
                interests_location.insert({inputmap[i][j], {i, j}});
            }
        }
    }

    auto interests = views::keys(interests_location) | ranges::to<vector>();
    map<pair<char, char>, uint32_t> ii_dists;
    for (size_t i = 0; i < interests.size() - 1; ++i) {
        for (size_t j = i + 1; j < interests.size(); ++j) {
            auto dist = interest_to_interest_shortest(inputmap, interests[i], interests[j], interests_location);

            if (dist > 0) {
                ii_dists.insert({{interests[i], interests[j]}, dist});
                ii_dists.insert({{interests[j], interests[i]}, dist});
            }
        }
    }

    using node = tuple<uint32_t, char, set<char>>;    // steps,current interest point, visited interest points;
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, '0', {'0'}});
    set<node> visited;

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        if (visited.contains(curr)) {
            continue;
        }

        auto [step, ch, path] = curr;
        if (path.size() == interests.size()) {    // all interest point visite at least once
            println("{}", step);
            break;
        }

        for (auto c : interests) {
            if (ch == c) {
                continue;
            }

            if (ii_dists.contains({ch, c})) {
                auto tmp_path = path;
                tmp_path.insert(c);
                pq.push({step + ii_dists[{ch, c}], c, tmp_path});
            }
        }

        visited.insert(curr);
    }

    while (!pq.empty()) {
        pq.pop();
    }
    pq.push({0, '0', {'0'}});
    visited.clear();

    map<char, uint32_t> non_zero_steps;

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        if (visited.contains(curr)) {
            continue;
        }

        auto [step, ch, path] = curr;
        if (path.size() == interests.size()) {    // all interest point visite at least once

            if (non_zero_steps.contains(ch)) {
                non_zero_steps[ch] = min(non_zero_steps[ch], step);
            } else {
                non_zero_steps[ch] = step;
            }

            if (non_zero_steps.size() == interests.size() - 1) {
                break;
            }
        }

        for (auto c : interests) {
            if (ch == c || c == '0') {
                continue;
            }

            if (ii_dists.contains({ch, c})) {
                auto tmp_path = path;
                tmp_path.insert(c);
                pq.push({step + ii_dists[{ch, c}], c, tmp_path});
            }
        }

        visited.insert(curr);
    }

    uint32_t min_non_zero = UINT32_MAX;
    for (auto [c, step] : non_zero_steps) {
        min_non_zero = min(min_non_zero, step + ii_dists[{c, '0'}]);
    }

    println("{}", min_non_zero);
}

int main() {
    part1();
    return 0;
}
