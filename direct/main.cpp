#include "../lib/collections/mdarr.h"
#include "../lib/io/output.h"
#include "../lib/io/input.h"

//#include "solution.hpp"
using namespace std;


class Solution {
  public:
  int solve(string s) {
    vector<string> n(3);
    int at = 0;
    for (int i = 0; i < s.size(); i++) {
      if (isdigit(s[i])) {
        n[at] += s[i];
      } else {
        at++;
      }
    }
    vector<vector<vector<vector<int>>>> res(8, vector<vector<vector<int>>>(n[0].size() + 1, vector<vector<int>>(n[1].size() + 1, vector<int>(n[2].size() + 1, -1))));
      vector<vector<vector<vector<vector<string>>>>> vals(8, vector<vector<vector<vector<string>>>>(n[0].size() + 1, vector<vector<vector<string>>>(n[1].size() + 1, vector<vector<string>>(n[2].size() + 1, vector<string>(3)))));
    res[0][0][0][0] = 0;
    res[1][0][0][0] = 1;
      res[2][0][0][0] = 0;
      res[3][0][0][0] = 1;
      res[4][0][0][0] = 0;
      res[5][0][0][0] = 1;
      res[6][0][0][0] = 0;
      res[7][0][0][0] = 1;
    function<int(int, int, int, int)> go = [&](int mask, int xd, int yd, int zd) -> int {
      int& ans = res[mask][xd][yd][zd];
      if (ans != -1) {
        return ans;
      }
      ans = 1000;
      if (xd == 0 && (mask & 2) == 0) {
          int cand = go(mask + 2, xd, yd, zd);
          if (ans > cand) {
              ans = cand;
              vals[mask][xd][yd][zd][0] = vals[mask + 2][xd][yd][zd][0];
              vals[mask][xd][yd][zd][1] = vals[mask + 2][xd][yd][zd][1];
              vals[mask][xd][yd][zd][2] = vals[mask + 2][xd][yd][zd][2];
          }
      }
      if (yd == 0 && (mask & 4) == 0) {
          int cand = go(mask + 4, xd, yd, zd);
          if (ans > cand) {
              ans = cand;
              vals[mask][xd][yd][zd][0] = vals[mask + 4][xd][yd][zd][0];
              vals[mask][xd][yd][zd][1] = vals[mask + 4][xd][yd][zd][1];
              vals[mask][xd][yd][zd][2] = vals[mask + 4][xd][yd][zd][2];
          }
      }
      int bc = 3;
      if ((mask & 2) == 2) {
          bc--;
      }
        if ((mask & 4) == 4) {
            bc--;
        }
      for (int i = 0; i < 10; i++) {
        if (i > 0 && (mask & 2) == 2) {
            break;
        }
        for (int j = 0; j < 10; j++) {
          if (j > 0 && (mask & 4) == 4) {
              break;
          }
          int k = (i + j + (mask & 1)) % 10;
          int nxd = xd > 0 && n[0][xd - 1] == '0' + i ? xd - 1 : xd;
          int nyd = yd > 0 && n[1][yd - 1] == '0' + j ? yd - 1 : yd;
          int nzd = zd > 0 && n[2][zd - 1] == '0' + k ? zd - 1 : zd;
          if (nxd != xd || nyd != yd || nzd != zd) {
              int nm = (i + j + (mask & 1)) / 10 + (mask & 6);
              int cand = go(nm, nxd, nyd, nzd) + bc - (xd - nxd) - (yd - nyd) - (zd - nzd);
              if (ans > cand) {
                  ans = cand;
                  vals[mask][xd][yd][zd][0] = vals[nm][nxd][nyd][nzd][0] + (((mask & 2) == 2) ? "" : to_string(i));
                  vals[mask][xd][yd][zd][1] = vals[nm][nxd][nyd][nzd][1] + (((mask & 4) == 4) ? "" : to_string(j));
                  vals[mask][xd][yd][zd][2] = vals[nm][nxd][nyd][nzd][2] + to_string(k);
              }
          }
        }
      }
      return ans;
    };
      int r = go(0, n[0].size(), n[1].size(), n[2].size());
      out.printLine(vals[0][n[0].size()][n[1].size()][n[2].size()]);
      return r;
  }
};

int main() {
    freopen("input.txt", "r", stdin);
    int len = in.readInt();
    arr<char> op;
    arri left;
    arri right;
    arri res;
    in.readArrays(len, op, left, right, res);
    arr<ll> vals(200000);
    for (int a : range(11)) {
        for (int b : range(11)) {
            err.printLine(a, b);
            fill(all(vals), 0);
            vals[0] = a;
            vals[1] = b;
            for (int i : range(len)) {
                if (op[i] == '<') {
                    vals[res[i]] = vals[left[i]] < vals[right[i]] ? 1 : 0;
                } else {
                    vals[res[i]] = vals[left[i]] + vals[right[i]];
                }
            }
            if (vals[2] != a * b) {
                throw "Jopa";
            }
        }
    }
}
