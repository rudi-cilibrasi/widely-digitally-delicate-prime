#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string>
#include "miller-rabin/miller-rabin.h"
#include <iostream>
#include <sstream>

using namespace std;

struct ResultExplanation {
	uint64_t x;
	bool is_digitally_delicate;
	bool is_widely_digitally_delicate;
	std::string reason;
};

std::ostream& operator<<(std::ostream& out, const ResultExplanation& re) {
	out << "RE for " << re.x << "\t:" << "dd" << re.is_digitally_delicate << "   ww" << re.is_widely_digitally_delicate << " " << re.reason;
	return out;
}

ResultExplanation is_digitally_delicate(uint64_t x) {
	ResultExplanation re;
	re.x = x;
	re.is_digitally_delicate = false;
	re.is_widely_digitally_delicate = false;
	if (!isprime(x)) {
/*
		ostringstream oss;
		oss << x << " is composite";
		re.reason = oss.str();
*/
		return re;
	}
	uint64_t tenPow = 0;
	uint64_t tenVal = 1;
	uint64_t theRest = 0;
	uint64_t v = x;

	while (v > 0) {
		auto lastDigit = v % 10;
		v /= 10;
		for (uint32_t i = 0; i < 10; ++i) {
			if (i == lastDigit) {
				continue;
			}
			uint64_t q = v * 10 + i;
			uint64_t cand = q * tenVal + theRest;
			if (isprime(cand)) {
/*
				ostringstream oss;
				oss << cand << " is prime";
				re.reason = oss.str();
*/
				return re;
			}
		}
		theRest += tenVal * lastDigit;
		tenPow += 1;
		tenVal *= 10;
	}
	re.is_digitally_delicate = true;

	mpz_t mTenVal;
	mpz_init(mTenVal);
	mpz_set_ui(mTenVal, tenVal);
	mpz_t mx;
	mpz_init(mx);
	mpz_set_ui(mx, x);
  if (!mpz_probab_prime_p(mx, 30)) {
      // earlier is_prime was false positive
      return re;
  }
	for (int j = 0; j < 100; ++j) {
		for (int i = 1; i < 10; ++i) {
			mpz_t cand;
			mpz_init(cand);
			mpz_set(cand, mx);
			mpz_addmul_ui(cand, mTenVal, i);
			if (mpz_probab_prime_p(cand, 30)) {
				ostringstream oss;
				char ubuf[1024];
				mpz_get_str(ubuf, 10, cand);
				oss << ubuf << " is prime";
				re.reason = oss.str();
				mpz_clear(mTenVal);
				mpz_clear(mx);
				mpz_clear(cand);
				return re;
			}
			mpz_clear(cand);
		}
		mpz_mul_ui(mTenVal, mTenVal, 10);
	}
	re.is_widely_digitally_delicate = true;
	mpz_clear(mTenVal);
	mpz_clear(mx);
	return re;
}

void runTest(uint64_t x) {
	ResultExplanation re = is_digitally_delicate(x);
//	cout << re << "\n";
	if (re.is_widely_digitally_delicate) {
		cout << "FOUND WIDE " << x << "\n";
		exit(0);
	}
}

int main(int argc, char **argv) {
  FILE *fp = fopen("/dev/urandom", "rb");
  if (!fp) {
    cerr << "Cannot open /dev/urandom\n";
    exit(1);
  }
  uint64_t x = 0;
  fread(&x, 1, sizeof(x), fp);
  x /= 1000;
  fclose(fp);
//	uint64_t x = 72345145171;
//	uint64_t x = 293000;
//  cerr << "Starting with " << x << "\n";
	for (;;) {
		runTest(x);
		++x;
	}
}
