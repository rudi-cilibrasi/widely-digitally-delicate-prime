#include "Tester54Bit.h"
#include "miller-rabin/miller-rabin.h"
#include "SimpleDDPTest.h"
#include <gmp.h>
#include <iostream>
#include <sstream>

using namespace std;


ResultExplanation is_widely_digitally_delicate(uint64_t x)
{
	ResultExplanation re;
	re.x = x;
	re.is_digitally_delicate = false;
	re.is_widely_digitally_delicate = false;
	if (!isprime(x))
	{
		/*
		ostringstream oss;
		oss << x << " is composite";
		re.reason = oss.str();
*/
		return re;
	}
    uint64_t tenVal = 0;
    if (is_digitally_delicate(x, tenVal)) {
        re.is_digitally_delicate = true;
    } else {
        return re;
    }

	mpz_t mTenVal;
	mpz_init(mTenVal);
	mpz_set_ui(mTenVal, tenVal);
	mpz_t mx;
	mpz_init(mx);
	mpz_set_ui(mx, x);
	if (!mpz_probab_prime_p(mx, 30))
	{
		// earlier is_prime was false positive
		return re;
	}
	for (int j = 0; j < 100; ++j)
	{
		for (int i = 1; i < 10; ++i)
		{
			mpz_t cand;
			mpz_init(cand);
			mpz_set(cand, mx);
			mpz_addmul_ui(cand, mTenVal, i);
			if (mpz_probab_prime_p(cand, 30))
			{
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
