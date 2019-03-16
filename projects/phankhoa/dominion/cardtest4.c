#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//test minion card

int main(int argc, char** argv) {

	//Initialize variables and game
	struct gameState state;
	int choice1 = 1;
	int choice2 = 0;
	int choice3 = 0;
	int k[10] = {adventurer, smithy, minion, great_hall, 
		tribute, copper, silver, council_room, village, mine};
	initializeGame(2, k, 4, &state);

	//test minion card effect
	choice1 = 1;
	int actions = state.numActions;
	int numCoins = state.coins;
	int numCards = numHandsCards(&state);
	cardEffect(minion, choice1, choice2, choice3, &state, 0, NULL);
	assert((state.numActions==actions+1) && (numHandsCards(state)==numCards-1));
	assert(state.coins==numCoins+2);

	printf("Minion card has passed test.\n");
	return 0;
}