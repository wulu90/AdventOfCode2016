#include <array>
#include <cstdint>
#include <cstring>
#include <print>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

inline void FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
    a += ((b & c) | ((~b) & d)) + x + ac;
    a = (a << s) | (a >> (32 - s));
    a += b;
}

inline void GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint64_t ac) {
    a += ((b & d) | (c & (~d))) + x + ac;
    a = (a << s) | (a >> (32 - s));
    a += b;
}

inline void HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint64_t ac) {
    a += (b ^ c ^ d) + x + ac;
    a = (a << s) | (a >> (32 - s));
    a += b;
}

inline void II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint64_t ac) {
    a += (c ^ (b | (~d))) + x + ac;
    a = (a << s) | (a >> (32 - s));
    a += b;
}

void MD5Transform(array<uint32_t, 4>& state, const array<byte, 64>& block) {
    auto [a, b, c, d] = state;

    array<uint32_t, 16> x;
    memcpy(x.data(), block.data(), 64);

    FF(a, b, c, d, x[0], 7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);

    /* Round 2 */
    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

    /* Round 3 */
    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);

    /* Round 4 */
    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

/// only for string len < 56
array<byte, 16> md5(const string& str) {
    array<byte, 64> padding;
    padding.fill(byte{0});
    padding[0] = byte{0x80};

    array<uint32_t, 4> state{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

    array<byte, 64> block;
    memcpy(block.data(), str.data(), str.size());
    memcpy(block.data() + str.size(), padding.data(), 56 - str.size());
    uint64_t len = str.size() * 8;
    memcpy(block.data() + 56, &len, 8);

    MD5Transform(state, block);

    array<byte, 16> op;
    memcpy(op.data(), state.data(), 16);

    return op;
}

vector<tuple<char, int, int>> next_coord(const string& path, const pair<int, int> coord) {
    static const array<array<int, 2>, 4> deltas{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
    static const string input{"bwnlcvfs"};
    static const string hexchars{"0123456789abcdef"};
    static const string dirs{"UDLR"};
    auto hashbytes = md5(input + path);
    string doorstr{hexchars[(to_integer<uint8_t>(hashbytes[0]) & 0xf0) >> 4], hexchars[to_integer<uint8_t>(hashbytes[0]) & 0x0f],
                   hexchars[(to_integer<uint8_t>(hashbytes[1]) & 0xf0) >> 4], hexchars[to_integer<uint8_t>(hashbytes[1]) & 0x0f]};

    vector<tuple<char, int, int>> res;
    for (size_t i = 0; i < 4; ++i) {
        if (doorstr[i] == 'b' || doorstr[i] == 'c' || doorstr[i] == 'd' || doorstr[i] == 'e' || doorstr[i] == 'f') {
            auto r = coord.first + deltas[i][0];
            auto c = coord.second + deltas[i][1];

            if (r >= 0 && r < 4 && c >= 0 && c < 4) {
                res.push_back({dirs[i], r, c});
            }
        }
    }
    return res;
}

void part1() {
    using node = tuple<uint, string, int, int>;    // step num,path string,row,col;
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, {}, 0, 0});
    set<node> visited;

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        if (visited.contains(curr)) {
            continue;
        }

        auto [step, path, row, col] = curr;

        if (row == 3 && col == 3) {    // destination
            println("{}", path);
            break;
        }

        for (auto [ch, r, c] : next_coord(path, {row, col})) {
            pq.push({step + 1, path + ch, r, c});
        }

        visited.insert(curr);
    }
}

int main() {
    part1();
    return 0;
}
