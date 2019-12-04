#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class CAT {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string s = in.readString();
        
        int answer = 0;
        for (int i : Range(s.size())) {
            if (s[i] != 'T') {
                continue;
            }
            for (int j : Range(i)) {
                if (s[j] != 'A') {
                    continue;
                }
                for (int k : Range(j)) {
                    if (s[k] == 'C') {
                        answer++;
                    }
                }
            }
        }
        out.printLine(answer);
	}
};
