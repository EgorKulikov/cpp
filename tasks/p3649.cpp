#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class p3649 {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int k = in.readInt();
        auto s = in.readIntArray(n);
        sort(all(s));
        int at = 0;
        int answer = 0;
        
        for (int i : Range(n)) {
            while (s[i] - s[at] > k) {
                at++;
            }
            maxim(answer, i - at + 1);
        }
        out.printLine(answer);
	}
};
