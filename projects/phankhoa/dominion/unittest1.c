#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"

int main() {

	// isGameOverFunction test

	struct gameState state;
	int s;
	int k[10] = {1,2,3,4,5,6,7,8,9,10};

	initializeGame(2, k, 2, &state);


	// force 3 piles to have 0 cards - ending the game
	state.supplyCount[1]=0;
	state.supplyCount[2]=0;
	state.supplyCount[3]=0;

	s = isGameOver(&state);

	assert(s == 1);
	printf("function isGameOver Test1 passed\n");


	// check province remaining to 0 to see if it ends game
	state.supplyCount[province] = 0;
	s = isGameOver(&state);

	assert(s == 1);
	printf("function isGameOver Test2 passed\n");

	return 0;

}