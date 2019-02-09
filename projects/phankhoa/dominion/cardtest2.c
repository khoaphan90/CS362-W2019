#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//test smithy card

int main(int argc, char** argv) {

	//Initialize variables and game
	struct gameState state;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int k[10] = {adventurer, smithy, minion, great_hall, 
		tribute, copper, silver, council_room, village, mine};
	initializeGame(2, k, 4, &state);
	int s;

	//test smithy card effect
	cardEffect(smithy, choice1, choice2, choice3, &state, 0, NULL);

	//test number of cards in hand to check for validity
	s = numHandCards(&state);
	assert(numHandCards(&state)==(s+2));
	printf("Smithy card has passed test.\n");

	return 0;
}
