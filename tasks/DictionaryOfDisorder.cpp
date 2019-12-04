#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class DictionaryOfDisorder {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        
        unordered_map<string, int> q;
        for (int i : Range(n)) {
            string s = in.readString();
            sort(all(s));
            out.printLine(q[s]++);
        }
	}
};
