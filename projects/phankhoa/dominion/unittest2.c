#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {

	//check buyCard function

	struct gameState state;
	int testBuy;
	int k[10] = {1,2,3,4,5,6,7,8,9,10};

	initializeGame(2, k, 2, &state);

	state.numBuys = 2;
	state.coins = 2;

	// test amount of coins in hand
	testBuy = buyCard(2, &state);
	if(testBuy == -1)
		printf("function buyCard Test1 passed\n");
	else
		printf("function buyCard Test1 failed\n");

	// test amount of buys left in turn
	state.numBuys = 0;

	testBuy = buyCard(2, &state);
	if(testBuy == -1)
		printf("function buyCard Test2 passed\n");
	else
		printf("function buyCard Test2 failed\n");

	return 0;

}