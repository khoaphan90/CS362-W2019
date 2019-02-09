#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {

	// check getCost function

	assert(getCost(smithy) == 4);
	assert(getCost(village) == 3);
	assert(getCost(mine) == 5);
	assert(getCost(province) == 8);
	assert(getCost(silver) == 3);
	assert(getCost(feast) == 4);
	assert(getCost(tribute) == 5);

	printf("function getCost test passed");

	return 0;

}