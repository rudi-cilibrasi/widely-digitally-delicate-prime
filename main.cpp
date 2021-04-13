#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string>
#include "Tester54Bit.h"

#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;

struct Config
{
	bool collectStats;
};

Config config = {false};

void printHelp() {
	cout << "Usage: search [--perfTest]\n";
	cout << "Usage: search [--help] [-h]\n";
	cout << "Searches for a widely digitally delicate prime number starting from a random 54-bit number\n";
}

std::ostream &operator<<(std::ostream &out, const ResultExplanation &re)
{
	out << "RE for " << re.x << "\t:"
		<< "dd" << re.is_digitally_delicate << "   ww" << re.is_widely_digitally_delicate << " " << re.reason;
	return out;
}

void runTest(uint64_t x)
{
	ResultExplanation re = is_digitally_delicate(x);
	//	cout << re << "\n";
	if (re.is_widely_digitally_delicate)
	{
		cout << "FOUND WIDE " << x << "\n";
		exit(0);
	}
}

int main(int argc, char **argv)
{
	if (argc > 1) {
		std::string arg = argv[1];
		if (arg == "-h" || arg == "--help") {
			printHelp();
			exit(0);
		}
		if (arg == "--perfTest") {
			config.collectStats = true;
		}
	}

	FILE *fp = fopen("/dev/urandom", "rb");
	if (!fp)
	{
		cerr << "Cannot open /dev/urandom\n";
		exit(1);
	}
	uint64_t x = 0;
	int rv = fread(&x, 1, sizeof(x), fp);
	if (rv <= 0)
	{
		cerr << "Error: Short read\n";
		exit(1);
	}
	x /= 1000;
	x /= 2;
	x *= 2;
	x += 1;
	fclose(fp);
	//	uint64_t x = 72345145171;
	//	uint64_t x = 293000;
	//  cerr << "Starting with " << x << "\n";
	auto startTime = chrono::steady_clock::now();
	uint64_t trials = 0;
	for (;;)
	{
		runTest(x);
		if (config.collectStats)
		{
			x += 2;
			trials += 2;
			if (trials == 1000000)
			{
				auto endTime = chrono::steady_clock::now();
				auto dur = (endTime - startTime);
				auto rate = 1e9 * trials / dur.count();
				cout << rate << "\n";
			}
		}
	}
}
