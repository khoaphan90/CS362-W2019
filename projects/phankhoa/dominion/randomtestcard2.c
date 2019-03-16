#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNAMT 10000

int main() {

	//SMITHY CARD

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
		printf("***Testing Smithy Card - TEST #%d\n", j+1);

		// //Copying game state into tester function
		//copy struct source: https://stackoverflow.com/questions/29550609/accessing-struct-members-using-memcpy-in-c
		memcpy(&tester, &state, sizeof(struct gameState));
		cardEffect(smithy, choice1, choice2, choice3, &state, handpos, &bonus);

		//Game state tester - checking amount of cards in players hand
		if(state.hand[player][tester.handCount[player]-1] != -1)
			printf("Passed. Smithy card was added to hand.\n");
		else 
			printf("Failed. Smithy card was not added to hand.\n");

		//Game state tester - check to see if player played a card and drawn the correct amount
		if(tester.playedCardCount+3 == state.playedCardCount)
			printf("Passed. Smithy card was played +3 Cards.\n");
		else
			printf("Failed. Smithy card was not played - No difference in card amount in hand.\n");

		//Game state tester - discarding
		if(tester.discardCount[player] == state.discardCount[player])
			printf("Passed. Village Card was discarded.\n");
		else
			printf("Failed. Village Card was not discarded.\n");

	}
	printf("***Done testing Smithy card.***\n");
	return 0;
}