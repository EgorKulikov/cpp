#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class BirthdayStatistics {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        vi answer(12);

        for (int i : Range(n)) {
            in.readInt();
            string date = in.readString();
            int month = 0;
            bool slash = false;
            for (char c : date) {
                if (c == '/') {
                    if (slash) {
                        break;
                    }
                    slash = true;
                } else if (slash) {
                    month *= 10;
                    month += c - '0';
                }
            }
            answer[month - 1]++;
        }
        for (int i : Range(12)) {
            out.printLine(i + 1, answer[i]);
        }
	}
};
