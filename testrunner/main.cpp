#include "../tasks/FVkusnayaPechenka.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include "../lib/general.h"

namespace jhelper {

struct Test {
	std::string input;
	std::string output;
	bool active;
	bool has_output;
};

bool check(std::string expected, std::string actual) {
	while(!expected.empty() && isspace(*--expected.end()))
		expected.erase(--expected.end());
	while(!actual.empty() && isspace(*--actual.end()))
		actual.erase(--actual.end());
	return expected == actual;
}

} // namespace jhelper

int main() {
    std::vector<jhelper::Test> tests = {
		{"2\n5 7\n5 7\n", "SMALL\n0\n\n", true, true},{"2\n1 1\n300000 1\n", "BIG\n299999\n", true, true},{"2\n10 1\n13 14\n", "SMALL\n6\nRPPPRP\n", true, true},{"3\n1 2 1\n2 1 2\n", "IMPOSSIBLE\n", true, true},
	};
	bool allOK = true;
	int testID = 0;
	std::cout << std::fixed;
	double maxTime = 0.0;
	for(const jhelper::Test& test: tests ) {
		std::cout << "\x1B[34mTest #" << ++testID << "\033[0m" << std::endl;
		if (!test.active) {
            std::cout << "\x1B[33mSKIPPED\033[0m\n";
            std::cout << std::endl;
            continue;
		}
		std::cout << "\x1B[34mInput:\033[0m \n" << test.input << std::endl;
		if (test.has_output) {
			std::cout << "\x1B[34mExpected output:\033[0m \n" << test.output << std::endl;
		}
		else {
			std::cout << "\x1B[34mExpected output:\033[0m \n" << "\x1B[33mN/A\033[0m" << std::endl;
		}
		if (test.active) {
            std::ofstream inw;
            inw.open("jhelperinput.txt");
            inw << test.input;
            inw.close();
            freopen("jhelperinput.txt", "r", stdin);
            ofstream fout("jhelperoutput.txt");
            std::clock_t start = std::clock();
            try {
                in = Input();
                out.setOut(fout);
                FVkusnayaPechenka solver;
                solver.solve();
                out.flush();
                fout.close();
            } catch (const char* e) {
                std::cerr << e << std::endl;
            }
            if (!in.isExhausted() && in.skipWhitespace() != EOF) {
                cout << "\x1B[31mInput is not exhausted\033[0m" << endl;
            }
            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);
            std::ifstream t("jhelperoutput.txt");
            std::stringstream output;
            output << t.rdbuf();
            std::cout << "\x1B[34mActual output:\033[0m \n" << output.str() << std::endl;
            if (test.has_output) {
                bool result = jhelper::check(test.output, output.str());
                allOK = allOK && result;
                std::cout << "\x1B[34mResult:\033[0m " << (result ? "\x1B[32mOK\033[0m" : "\x1B[31mWrong answer\033[0m") << std::endl;
            }
            std::cout << "\x1B[34mTime: " << int(currentTime) << "." << (int(currentTime * 10) % 10) << (int(currentTime * 100) % 10) << (int(currentTime * 1000) % 10) << "s\033[0m" << std::endl;
            t.close();
		}

		std::cout << std::endl;
	}
	if (allOK) {
		std::cout << "\x1B[32mAll OK\033[0m" << std::endl;
	} else {
		std::cout << "\x1B[31mSome cases failed\033[0m" << std::endl;
	}
	std::cout << "\x1B[34mMaximal time: " << int(maxTime) << "." << (int(maxTime * 10) % 10) << (int(maxTime * 100) % 10) << (int(maxTime * 1000) % 10) << "s.\033[0m" << std::endl;
	return 0;
}
