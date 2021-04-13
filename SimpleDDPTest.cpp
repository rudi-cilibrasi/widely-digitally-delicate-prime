#include "SimpleDDPTest.h"
#include "miller-rabin/miller-rabin.h"


bool is_digitally_delicate(uint64_t x, uint64_t& tenVal) {
	uint64_t tenPow = 0;
	tenVal = 1;
	uint64_t theRest = 0;
	uint64_t v = x;

	while (v > 0)
	{
		auto lastDigit = v % 10;
		v /= 10;
		for (uint32_t i = 0; i < 10; ++i)
		{
			if (i == lastDigit)
			{
				continue;
			}
			uint64_t q = v * 10 + i;
			uint64_t cand = q * tenVal + theRest;
			if (isprime(cand))
			{
				/*
				ostringstream oss;
				oss << cand << " is prime";
				re.reason = oss.str();
*/
				return false;
			}
		}
		theRest += tenVal * lastDigit;
		tenPow += 1;
		tenVal *= 10;
	}
    return true;
}