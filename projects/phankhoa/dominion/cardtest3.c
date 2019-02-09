#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//test village card

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
	int action;

	//test village card effect
	action = state.numActions;
	s =	cardEffect(village, choice1, choice2, choice3, &state, 0, NULL);

	//test number of actions left in turn to check for validity
	assert(state.numActions==action+2);
	assert(s==0);
	
	printf("Village card has passed test.\n");
	return 0;
}