#include "../template/template.hpp"
/*
md5 hash を求める

md5: md5構造を初期化して構築する
md5(a,b,c,d): md5を初期値 a,b,c,d で初期化して構築する

hash(String): 文字列 S の md5 hash を 32bit整数4つで求める
hash(String,len): 文字列 S の md5 hash を 長さ=len と偽装して 32bit整数4つで求める
hash(vector<char>): byte列 S の md5 hash を 32bit整数4つで求める
hash(vector<char>,len): byte列 S の md5 hash を 長さ=len と偽装して 32bit整数4つで求める

hex(): hash() を呼んだ後に呼ぶと、hash値のhex表現を返す

*/

namespace Lib {
struct md5 {
  unsigned a0, b0, c0, d0;
  vector<int> S = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                   5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                   6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
  vector<unsigned> K;
  md5(unsigned a = 0x67452301, unsigned b = 0xefcdab89, unsigned c = 0x98badcfe,
      unsigned d = 0x10325476)
      : a0(a), b0(b), c0(c), d0(d) {
    for (int i = 0; i < 64; i++) {
      K.push_back(floor(pow(2, 32) * abs(sin(i + 1))));
    }
  }

  unsigned LRotate(unsigned x, int c) {
    c %= 32;
    if (c == 0) return x;
    return ((x << c) | (x >> (32 - c))) & ((1ll << 32) - 1);
  }
  array<unsigned, 4> hash(vector<unsigned char> data, size_t len = 0) {
    if (len == 0) {
      len = data.size() * 8;
    }
    data.push_back(0x80);
    while (data.size() % 64 != 56) {
      data.push_back(0);
    }
    for (int i = 0; i < 8; i++) {
      data.push_back(len >> (i * 8) & ((1 << 8) - 1));
    }
    len = data.size();
    for (ull i = 0; i < len; i += 64) {
      unsigned A = a0, B = b0, C = c0, D = d0;
      vector<unsigned> M;
      for (int j = 0; j < 64; j += 4) {
        M.push_back((data[i + j + 0]) | (data[i + j + 1] << 8) |
                    (data[i + j + 2] << 16) | (data[i + j + 3]) << 24);
      }
      for (int j = 0; j < 64; j++) {
        unsigned F, G;
        if (j < 16) {
          F = (B & C) | ((~B) & D);
          G = j;
        } else if (j < 32) {
          F = (D & B) | ((~D) & C);
          G = (5 * j + 1) % 16;
        } else if (j < 48) {
          F = B ^ C ^ D;
          G = (3 * j + 5) % 16;
        } else {
          F = C ^ (B | (~D));
          G = (7 * j) % 16;
        }
        F = F + A + K[j] + M[G];
        A = D;
        D = C;
        C = B;
        B = B + LRotate(F, S[j]);
      }
      a0 += A;
      b0 += B;
      c0 += C;
      d0 += D;
    }
    return array<unsigned, 4>({a0, b0, c0, d0});
  }
  array<unsigned, 4> hash(string S, size_t len = 0) {
    vector<unsigned char> data(S.begin(), S.end());
    return hash(data, len);
  }
  string hex() {
    string ret = "";
    for (int i = 0; i < 32; i += 8)
      ret += format("{:02x}", (a0 >> i) & ((1 << 8) - 1));
    for (int i = 0; i < 32; i += 8)
      ret += format("{:02x}", (b0 >> i) & ((1 << 8) - 1));
    for (int i = 0; i < 32; i += 8)
      ret += format("{:02x}", (c0 >> i) & ((1 << 8) - 1));
    for (int i = 0; i < 32; i += 8)
      ret += format("{:02x}", (d0 >> i) & ((1 << 8) - 1));
    return ret;
  }
};
}  // namespace Lib
