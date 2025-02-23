#include <bit>
#include <print>
#include <queue>
#include <set>

using namespace std;

bool is_open(pair<int64_t, int64_t> coord) {
    static set<pair<int64_t, int64_t>> walls;
    static set<pair<int64_t, int64_t>> opens;

    if (walls.contains(coord) || opens.contains(coord)) {
        return opens.contains(coord);
    } else {
        auto [y, x] = coord;
        auto tmp    = x * x + 3 * x + 2 * x * y + y + y * y + 1358;
        auto ones   = popcount(static_cast<u_int64_t>(tmp));
        if (ones % 2 == 0) {
            opens.insert(coord);
        } else {
            walls.insert(coord);
        }
        return ones % 2 == 0;
    }
}

vector<pair<int64_t, int64_t>> next_coord(pair<int64_t, int64_t> curr) {
    static const array<array<int64_t, 2>, 4> deltas{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
    vector<pair<int64_t, int64_t>> vec;
    for (auto [dr, dc] : deltas) {
        auto r = curr.first + dr;
        auto c = curr.second + dc;

        if (r >= 0 && c >= 0 && is_open({r, c})) {
            vec.push_back({r, c});
        }
    }
    return vec;
}

void part1() {
    using node = pair<int, pair<int64_t, int64_t>>;    // step, coord(row,col)
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, {1, 1}});
    set<node> visited;

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        if (visited.contains(curr)) {
            continue;
        }

        if (curr.second == make_pair(39, 31)) {
            println("{}", curr.first);
            break;
        }

        auto [step, coord] = curr;

        for (auto nextcoord : next_coord(coord)) {
            pq.push({step + 1, nextcoord});
        }

        visited.insert(curr);
    }
}

int main() {
    part1();
    return 0;
}
