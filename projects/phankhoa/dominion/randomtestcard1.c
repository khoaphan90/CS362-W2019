#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNAMT 10000

int main() {

	//VILLAGE CARD

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
		printf("***Testing Village Card -  TEST #%d\n", j+1);

		//Copying game state into tester function
		//copy struct source: https://stackoverflow.com/questions/29550609/accessing-struct-members-using-memcpy-in-c
		memcpy(&tester, &state, sizeof(struct gameState));
		cardEffect(village, choice1, choice2, choice3, &state, handpos, &bonus);


		//Game state tester - checking amount of cards in players hard
		if(state.hand[player][tester.handCount[player]-1] != -1)
			printf("Passed, Village card was added to hand.\n");
		else 
			printf("Failed, Village card was not added to hand.\n");

		//Game state tester - check to see if player played a card
		if(tester.playedCardCount+1 == state.playedCardCount)
			printf("Passed, Village card was played.\n");
		else
			printf("Failed, Village card was not played.\n");

		//Game state tester - discarding
		if(tester.discardCount[player] == state.discardCount[player])
			printf("Passed. Village Card was discarded.\n");
		else
			printf("Failed. Village Card was not discarded.\n");

		//Game state tester - actions added
		if(tester.numActions+2 == state.numActions)
			printf("Passed, +2 actions\n");
		else
			printf("Failed, +0 actions.\n");
	}
	printf("***Done testing Village card.***\n");
	return 0;
}