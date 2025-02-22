#include <fstream>
#include <map>
#include <print>
#include <set>
#include <vector>

using namespace std;

enum class turn { L, R };
enum class direction { N, E, S, W };

vector<pair<int, int>> next_coord(pair<int, int>& curr, direction& dir, turn t, int dist) {
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    static const map<pair<direction, turn>, size_t> delta_inx{
        {{direction::N, turn::R}, 1}, {{direction::E, turn::R}, 2}, {{direction::S, turn::R}, 3}, {{direction::W, turn::R}, 0},
        {{direction::N, turn::L}, 3}, {{direction::E, turn::L}, 0}, {{direction::S, turn::L}, 1}, {{direction::W, turn::L}, 2}};

    static const map<pair<direction, turn>, direction> dir_next{
        {{direction::N, turn::R}, direction::E}, {{direction::E, turn::R}, direction::S}, {{direction::S, turn::R}, direction::W},
        {{direction::W, turn::R}, direction::N}, {{direction::N, turn::L}, direction::W}, {{direction::E, turn::L}, direction::N},
        {{direction::S, turn::L}, direction::E}, {{direction::W, turn::L}, direction::S}};

    auto& [x, y] = curr;
    auto inx     = delta_inx.at({dir, t});

    vector<pair<int, int>> path;

    for (int i = 1; i <= dist; ++i) {
        path.emplace_back(x + deltas[inx][0] * i, y + deltas[inx][1] * i);
    }

    x += deltas[inx][0] * dist;
    y += deltas[inx][1] * dist;
    dir = dir_next.at({dir, t});

    return path;
}

void part1_2() {
    ifstream input("input/input01");
    vector<pair<turn, int>> turn_dist_vec;
    for (char c, d; input; c = input.get()) {
        if (c == 'R' || c == 'L') {
            d     = c;
            c     = input.get();
            int n = 0;
            while (isdigit(c)) {
                n = n * 10 + c - '0';
                c = input.get();
            }

            turn_dist_vec.push_back({d == 'R' ? turn::R : turn::L, n});
        }
    }

    pair<int, int> curr{0, 0};
    direction dir{direction::N};
    for (auto [t, d] : turn_dist_vec) {
        next_coord(curr, dir, t, d);
    }

    println("{}", abs(curr.first) + abs(curr.second));

    curr = {0, 0};
    dir  = direction::N;
    set<pair<int, int>> visited;

    for (auto [t, d] : turn_dist_vec) {
        auto path  = next_coord(curr, dir, t, d);
        bool twice = false;
        for (auto p : path) {
            if (visited.contains(p)) {
                twice = true;
                println("{}", abs(p.first) + abs(p.second));
                break;
            } else {
                visited.insert(p);
            }
        }
        if (twice) {
            break;
        }
    }
}

int main() {
    part1_2();
    return 0;
}
