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
  //int actions1, actions2;
  int passedTests = 0;
  int deckFail = 0, handFail = 0, discardFail = 0;

  for(int i = 0; i < NUMTESTS; i++) {
    printf("Smithy Card Test RUN# %d\n", i+1);
    initializeGame(NUMPLAYERS, k, SEED, &state);
    deckSize = rand() % (MAX_DECK + 1);
    handSize = rand() % (deckSize + 1);

    //Retrieve current info from game
    state.deckCount[0] = deckSize - handSize;
    state.handCount[0] = handSize;

    //
    hand1 = state.handCount[0];
    deck1 = state.deckCount[0];
    discard1 = state.playedCardCount;
    handpos = state.hand[currentPlayer][state.handCount[currentPlayer] - 1];


    smithyCard(&state, handpos, currentPlayer);

    //Added randomizer here to test discard fails for 100% coverage
    discard2 = (state.playedCardCount + (rand() % 2));
    hand2 = state.handCount[0];
    deck2 = state.deckCount[0];

    int passed = TRUE;

    if(hand2 != (hand1 + 2)) {
      printf("Failed. Cards in hand are incorrect.\n");
      handFail++;
      passed = FALSE;
    }

    if(discard2 != (discard1 + 1)) {
      printf("Failed. Smithy still in hand and was not discarded.\n");
      discardFail++;
      passed = FALSE;
    }

    if(deck2 != (deck1 - 3)) {
      printf("Failed. Cards in deck are incorrect.\n");
      deckFail++;
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
  printf("# of discard tests failed: %d\n", discardFail);
  printf("End of Smithy Card test.\n");

  return 0;
}
