#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class UnionOfSets {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        unordered_set<int> s;
        
        for (int i : Range(n)) {
            int sz = in.readInt();
            for (int j : Range(sz)) {
                s.insert(in.readInt());
            }
        }
        out.printLine(s.size());
	}
};
