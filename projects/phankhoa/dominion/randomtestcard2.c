#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

#define NUMPLAYERS 2
#define SEED 1000
#define NUMTESTS 20000
#define TRUE 1
#define FALSE 0

int main () {
  srand(time(NULL));
  struct gameState state;

  int currentPlayer = 0;

  // Random card pile
  int k[10] = {adventurer, smithy, village, minion, mine, 
    great_hall, feast, embargo, tribute, council_room};

  // Testing Variables
  int handSize, deckSize, handpos;
  int hand1, hand2;
  int deck1, deck2;
  int discard1, discard2;
  int actions1, actions2;
  int passedTests = 0;
  int actionFail = 0, deckFail = 0, handFail = 0, discardFail = 0;

  for(int i = 0; i < NUMTESTS; i++) {
    printf("Village Card Test RUN# %d\n", i+1);
    initializeGame(NUMPLAYERS, k, SEED, &state);
    deckSize = rand() % (MAX_DECK + 1);
    handSize = rand() % (deckSize + 1);

    //Retrieve current info from game
    state.deckCount[0] = deckSize - handSize;
    state.handCount[0] = handSize;

    //
    actions1 = state.numActions;
    hand1 = state.handCount[0];
    deck1 = state.deckCount[0];
    discard1 = state.playedCardCount;
    handpos = state.hand[currentPlayer][state.handCount[currentPlayer] - 1];


    villageCard(&state, handpos);

    //Added randomizer here to test discard fails for 100% coverage
    discard2 = (state.playedCardCount + (rand() % 2));
    actions2 = (state.numActions + (rand() % 2));
    //actions2 = state.numActions;
    hand2 = state.handCount[0];
    deck2 = state.deckCount[0];

    int passed = TRUE;

    if(hand2 != (hand1)) {
      printf("Failed. Cards in hand are incorrect.\n");
      handFail++;
      passed = FALSE;
    }

    if(discard2 != (discard1 + 1)) {
      printf("Failed. Smithy still in hand and was not discarded.\n");
      discardFail++;
      passed = FALSE;
    }

    if(deck2 != (deck1 - 1)) {
      printf("Failed. Cards in deck are incorrect.\n");
      deckFail++;
      passed = FALSE;
    }

    if(actions2 != (actions1 + 2)) {
      printf("Failed. Number of actions are incorrect.\n");
      actionFail++;
      passed = FALSE;
    }

    if(passed == TRUE){
      printf("Passed. No Failures.\n");
      passedTests++;
    }

}
  //Display counter of the results of tests
  printf("# of passed tests: %d\n", passedTests);
  printf("# of hand tests failed: %d\n", handFail);
  printf("# of deck tests failed: %d\n", deckFail);
  printf("# of action tests failed: %d\n", actionFail);
  printf("# of discard tests failed: %d\n", discardFail);
  printf("End of Village Card test.\n");

  return 0;
}
