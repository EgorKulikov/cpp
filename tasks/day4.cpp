#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class day4 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        auto check = [](int i) -> bool {
            bool same = false;
            int last = 10;
            int len = 0;
            while (i) {
                int d = i % 10;
                i /= 10;
                if (d > last) {
                    return false;
                }
                if (d == last) {
                    len++;
                } else {
                    if (len == 2) {
                        same = true;
                    }
                    len = 1;
                }
                last = d;
            }
            return same || len == 2;
        };

        out.printLine(check(112233));
        out.printLine(check(123444));
        out.printLine(check(111122));

        int answer = 0;
        for (int i : Range(256310, 732737)) {
            answer += check(i) ? 1 : 0;
        }

        out.printLine(answer);
	}
};
