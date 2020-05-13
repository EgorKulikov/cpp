#include "C:/Users/egor/proj/cpp/tasks/F1SlaimIPosledovatelnostiUproshchennayaVersiya.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <io.h>
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
#ifdef LOCAL
    signal(SIGABRT, &signalHandler);
#endif
    std::vector<jhelper::Test> tests = {
		{"2\n", "3 1 \n", true, true},{"3\n", "10 7 1 \n", true, true},{"1\n", "1 \n", true, true},
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
            int fd = dup(fileno(stdout));
		    freopen("jhelperinput.txt", "r", stdin);
		    freopen("jhelperoutput.txt", "w", stdout);
			std::clock_t start = std::clock();
			try {
			    in = Input();
			    F1SlaimIPosledovatelnostiUproshchennayaVersiya solver;
			    solver.solve();
			    fflush(stdout);
			    fclose(stdout);
            } catch (const char* e) {
                std::cerr << e << std::endl;
            }
			if (!in.isExhausted() && in.skipWhitespace() != EOF) {
			    cerr << "Input is not exhausted" << endl;
			}
			fdopen(fd, "w");
            dup2(fd, fileno(stdout));
            std::clock_t finish = std::clock();
			double currentTime = double(finish - start) / CLOCKS_PER_SEC;
			maxTime = std::max(currentTime, maxTime);
            std::ifstream t("jhelperoutput.txt");
            std::stringstream out;
            out << t.rdbuf();
			std::cout << "Actual output: \n" << out.str() << std::endl;
			if (test.has_output) {
				bool result = jhelper::check(test.output, out.str());
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
