#include <array>
#include <cstdint>
#include <cstring>
#include <map>
#include <print>
#include <string>

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

size_t triple(const string& str) {
    size_t pos = string::npos;
    for (size_t i = 0; i < str.size() - 2; ++i) {
        if (str[i] == str[i + 1] && str[i] == str[i + 2]) {
            pos = i;
            break;
        }
    }
    return pos;
}

bool fivekind(const string& str, char c) {
    bool res = false;
    for (size_t i = 0; i < str.size() - 4; ++i) {
        if (c == str[i] && c == str[i + 1] && c == str[i + 2] && c == str[i + 3] && c == str[i + 4]) {
            res = true;
            break;
        }
    }
    return res;
}

string hash_bytes_to_str(const array<byte, 16>& hb) {
    string str;
    for (auto b : hb) {
        format_to(back_inserter(str), "{:02x}", to_integer<uint8_t>(b));
    }
    return str;
}

void part1() {
    int i    = 0;
    int ii64 = 0;

    while (true) {
        auto str1 = hash_bytes_to_str(md5(format("jlmsuwbz{}", i)));

        auto pos = triple(str1);
        if (pos != string::npos) {
            for (int n = i + 1; n < i + 1001; ++n) {
                auto str2 = hash_bytes_to_str(md5(format("jlmsuwbz{}", n)));
                if (fivekind(str2, str1[pos])) {
                    ++ii64;
                    break;
                }
            }
        }

        if (ii64 == 64) {
            println("{}", i);
            break;
        }
        ++i;
    }
}

string hash_bytes_to_str_2(const array<byte, 16>& hb) {
    string str(32, ' ');
    static const string hexstr = "0123456789abcdef";
    for (size_t i = 0; i < 16; ++i) {
        auto tmp       = to_integer<uint8_t>(hb[i]);
        str[i * 2]     = hexstr[(tmp & 0xf0) >> 4];
        str[i * 2 + 1] = hexstr[tmp & 0x0f];
    }
    return str;
}

string hash2016(const string& str) {
    auto hash = hash_bytes_to_str_2(md5(str));
    for (int i = 0; i < 2016; ++i) {
        hash = hash_bytes_to_str_2(md5(hash));
    }
    return hash;
}

string inx_hash(int i) {
    static map<int, string> hash_map;
    string str;
    if (!hash_map.contains(i)) {
        str = hash2016(format("jlmsuwbz{}", i));
        hash_map.insert({i, str});
    } else {
        str = hash_map[i];
    }
    return str;
}

void part2() {
    int i    = 0;
    int ii64 = 0;
    map<int, string> hash_map;
    while (true) {
        string str1 = inx_hash(i);

        auto pos = triple(str1);
        if (pos != string::npos) {
            for (int n = i + 1; n < i + 1001; ++n) {
                auto str2 = inx_hash(n);
                if (fivekind(str2, str1[pos])) {
                    ++ii64;
                    break;
                }
            }
        }

        if (ii64 == 64) {
            println("{}", i);
            break;
        }
        ++i;
    }
}

int main() {
    // part1();
    part2();
    return 0;
}
