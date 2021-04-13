#ifndef __RESULTEXPLANATION_H
#define __RESULTEXPLANATION_H

#include <stdint.h>
#include <string>

struct ResultExplanation {
	uint64_t x;
	bool is_digitally_delicate;
	bool is_widely_digitally_delicate;
	std::string reason;
};

#endif