#include "../tasks/ERandomPawn.cpp"

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
		{"5\n4 2 6 3 5\n1 1 1 1 1\n", "4.700000000000\n", true, true},{"4\n100 0 100 0\n0 100 0 100\n", "50.000000000000\n", true, true},{"14\n4839 5400 6231 5800 6001 5200 6350 7133 7986 8012 7537 7013 6477 5912\n34 54 61 32 52 61 21 43 65 12 45 21 1 4\n", "7047.142857142857\n", true, true},{"10\n470606482521 533212137322 116718867454 746976621474 457112271419 815899162072 641324977314 88281100571 9231169966 455007126951\n26 83 30 59 100 88 84 91 54 61\n", "815899161079.400024414062\n", true, true},
	};
	bool allOK = true;
	int testID = 0;
	std::cout << std::fixed;
	double maxTime = 0.0;
	for(const jhelper::Test& test: tests ) {
		std::cout << "Test #" << ++testID << std::endl;
		if (!test.active) {
            std::cout << "SKIPPED\n";
            std::cout << std::endl;
            continue;
		}
		std::cout << "Input: \n" << test.input << std::endl;
		if (test.has_output) {
			std::cout << "Expected output: \n" << test.output << std::endl;
		}
		else {
			std::cout << "Expected output: \n" << "N/A" << std::endl;
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
                ERandomPawn solver;
                solver.solve();
                out.flush();
                fout.close();
            } catch (const char* e) {
                std::cerr << e << std::endl;
            }
            if (!in.isExhausted() && in.skipWhitespace() != EOF) {
                cerr << "Input is not exhausted" << endl;
            }
            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);
            std::ifstream t("jhelperoutput.txt");
            std::stringstream output;
            output << t.rdbuf();
            std::cout << "Actual output: \n" << output.str() << std::endl;
            if (test.has_output) {
                bool result = jhelper::check(test.output, output.str());
                allOK = allOK && result;
                std::cout << "Result: " << (result ? "OK" : "Wrong answer") << std::endl;
            }
            std::cout << "Time: " << int(currentTime) << "." << (int(currentTime * 10) % 10) << (int(currentTime * 100) % 10) << (int(currentTime * 1000) % 10) << "s" << std::endl;
            t.close();
		}
		else {
			std::cout << "SKIPPED\n";
		}

		std::cout << std::endl;
	}
	if (allOK) {
		std::cout << "All OK" << std::endl;
	} else {
		std::cout << "Some cases failed" << std::endl;
	}
	std::cout << "Maximal time: " << int(maxTime) << "." << (int(maxTime * 10) % 10) << (int(maxTime * 100) % 10) << (int(maxTime * 1000) % 10) << "s." << std::endl;
	return 0;
}
