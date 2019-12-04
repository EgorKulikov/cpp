#include "../lib/io/input.h"
#include "../lib/io/output.h"
#include "../lib/range/range.h"

//#pragma comment(linker, "/STACK:200000000")

class ClassifyingPalindromes {
public:
	void solve(istream& inp, ostream& outp) {
        Input in(inp);
        Output out(outp);

        string s = in.readString();
        auto isPalindrome = [&](int f, int t) -> bool {
            for (int i = f, j = t; i < j; i++, j--) {
                if (s[i] != s[j]) {
                    return false;
                }
            }
            return true;
        };
        if (isPalindrome(0, s.size() - 1)) {
            out.printLine("palindrome");
        } else {
            for (int i : Range(1, s.size())) {
                if (isPalindrome(0, i - 1) && isPalindrome(i, s.size() - 1)) {
                    out.printLine("bi-palindrome");
                    return;
                }
            }
            out.printLine("non-palindrome");
        }
	}
};
