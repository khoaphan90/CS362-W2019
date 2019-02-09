#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {

	//check next players turn

	struct gameState state;
	int s;
	int k[10] = {1,2,3,4,5,6,7,8,9,10};

	for (int i = 2; i < 5; ++i) {
		s = initializeGame(2, k, 5, &state);
		s = whoseTurn(&state);
		assert(s == state.whoseTurn);
			printf("Next Player Turn Test3 passed\n");
	}

	return 0;

}