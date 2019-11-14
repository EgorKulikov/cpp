#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/string/suffix_automaton.h"

class GajjoIsBackAgain {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string s = in.readString();
        auto head = new SuffixAutomaton(nullptr, 0, 26);
        auto tail = head;
        ll answer = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            tail = tail->addLetter(head, s[i] - 'a', 26);
            answer += tail->length - tail->link->length;
            out.printLine(answer);
        }
	}
};
