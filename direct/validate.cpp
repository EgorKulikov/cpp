#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MAXC = 20000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(3, 50, "n");
    inf.readSpace();
    int ax = inf.readInt(-MAXC, MAXC, "xA");
    inf.readSpace();
    int ay = inf.readInt(-MAXC, MAXC, "yA");
    inf.readSpace();
    int bx = inf.readInt(-MAXC, MAXC, "xB");
    inf.readSpace();
    int by = inf.readInt(-MAXC, MAXC, "yB");
    inf.readEoln();
    vector<int> x;
    vector<int> y;
    for (int i = 0; i < n; i++) {
        x.push_back(inf.readInt(-MAXC, MAXC, "x"));
        inf.readSpace();
        y.push_back(inf.readInt(-MAXC, MAXC, "y"));
        inf.readEoln();
    }
    inf.readEof();
    ensuref(ax != bx || ay != by, "A and B should be distinct");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int a = y[j] - y[i];
            int b = x[i] - x[j];
            int c = -x[i] * a - y[i] * b;
            for (int k = 0; k < i; k++) {
                ensuref(a * x[k] + b * y[k] + c < 0, "polygon should be convex and in counter-clockwise order, see points %d, %d and %d", i, j, k);
            }
            for (int k = i + 1; k < j; k++) {
                ensuref(a * x[k] + b * y[k] + c > 0, "polygon should be convex and in counter-clockwise order, see points %d, %d and %d", i, j, k);
            }
            for (int k = j + 1; k < n; k++) {
                ensuref(a * x[k] + b * y[k] + c < 0, "polygon should be convex and in counter-clockwise order, see points %d, %d and %d", i, j, k);
            }
        }
    }
    auto checkInside = [&](int px, int py, const string& label) -> void {
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int a = y[j] - y[i];
            int b = x[i] - x[j];
            int c = -x[i] * a - y[i] * b;
            ensuref(a * px + b * py + c < 0, "%s should be inside the polygon", label.c_str());
        }
    };
    checkInside(ax, ay, "A");
    checkInside(bx, by, "B");
}
