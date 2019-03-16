#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNAMT 10000

int main() {
	srand(time(NULL));

	//variables for cardEffect
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;

	struct gameState state;
	struct gameState tester;

	int k[10] = {adventurer, smithy, minion, great_hall,
				tribute, copper, silver, council_room, village, mine};

	for(int j=0; j < RUNAMT; j++) {

		int player = whoseTurn(&tester);
		int numPlayers = rand() % 100;
		int seed = rand() % 10000;

		//Initialize original game state
		initializeGame(numPlayers, k, seed, &state);
		printf("***Testing Adventurer Card - TEST #%d\n", j+1);

		//Copying game state into tester function
		//copy struct source: https://stackoverflow.com/questions/29550609/accessing-struct-members-using-memcpy-in-c
		memcpy(&tester, &state, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &state, handpos, &bonus);

		//Game state tester - deck count to check correct amount
		if(tester.deckCount[player]-1 == state.deckCount[player])
			printf("Passed. Deck count.\n");
		else
			printf("Failed. Deck count.\n");

		//Game state tester - checking amount of cards in players hand
		if(state.hand[player][tester.handCount[player]] != -1)
			printf("Passed. Adventurer card was added to hand.\n");
		else 
			printf("Failed. Adventurer card was not added to hand.\n");

		//Game state tester - check to see if player played a card
		if(tester.playedCardCount+2 == state.playedCardCount)
			printf("Passed. Adventurer card was played.\n");
		else
			printf("Failed. Adventurer card was not played.\n");

		//Game state tester - discarding
		if(tester.discardCount[player] == state.discardCount[player])
			printf("Passed. Adventurer Card was discarded.\n");
		else
			printf("Failed. Adventurer Card was not discarded.\n");


		//Game state tester - number of actions
		if(tester.numActions+2 == state.numActions)
			printf("Passed, 2 extra actions were added.\n");
		else
			printf("Failed, no actions were added.\n");
	}
	printf("***Done testing Adventurer card.***\n");
	return 0;
}

//