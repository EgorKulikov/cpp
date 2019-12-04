#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class PenaltyCalculation {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        int n = in.readInt();
        auto submissions = in.readArray<int, string>(n);
        
        sort(all(submissions));
        int answer = 0;
        for (const auto& p : submissions) {
            if (p.second == "AC") {
                answer += p.first;
                out.printLine(answer);
                return;
            }
            answer += 20;
        }
        out.printLine(0);
	}
};
