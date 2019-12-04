#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class MusicNotesI {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int q = in.readInt();
        auto b = in.readIntArray(n);
        
        vi s(n + 1);
        for (int i : Range(n)) {
            s[i + 1] = s[i] + b[i];
        }
        for (int i : Range(q)) {
            out.printLine(upper_bound(all(s), in.readInt()) - s.begin());
        }
	}
};
