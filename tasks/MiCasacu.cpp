#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"
//#include "../lib/range/rev_range.h"

//#pragma comment(linker, "/STACK:200000000")

class MiCasacu {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        int m = in.readInt();
        vi w, d;
        in.readArrays(n, w, d);
        
        vi answer(m + 1);
        for (int i : Range(n)) {
//            for (int j : RevRange(m + 1, w[i])) {
//                maxim(answer[j], answer[j - w[i]] + d[i]);
//            }
        }
        out.printLine(answer[m]);
	}
};
