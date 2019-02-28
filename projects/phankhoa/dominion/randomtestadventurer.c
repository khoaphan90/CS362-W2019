#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

#define NUMPLAYERS 2
#define SEED 2000
#define NUMTESTS 100000
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
  int handSize, deckSize, randomCard, cardPile;
  int coinCount1, coinCount2;
  int dCopper, dSilver, dGold;
  int passedTests = 0;
  int drawFail = 0, discardFail = 0;

  for(int i = 0; i < NUMTESTS; i++) {
    printf("Adventurer Card Test RUN# %d\n", i+1);
    initializeGame(NUMPLAYERS, k, SEED, &state);
    coinCount1 = rand() % 4;
    deckSize = rand() % (MAX_DECK + 1);
    handSize = rand() % (deckSize + 1);

    //Retrieve current info from game
    state.deckCount[0] = deckSize - handSize;
    state.handCount[0] = handSize;

    for(int j = 0; j < NUMPLAYERS; j++) {
      for(int p = 0; p < state.deckCount[j]; p++) {
        randomCard = rand() % 50;
        cardPile = rand() % 10;

        //
        if(randomCard == 1)
          state.deck[j][p] = copper;
        else if(randomCard == 2)
          state.deck[j][p] = silver;
        else if(randomCard == 3)
          state.deck[j][p] = gold;
        else
          state.deck[j][p] = k[cardPile];

      }
    }

    for(int m = 0; m < state.handCount[currentPlayer]; m++) {
      if(state.hand[currentPlayer][m] == copper || state.hand[currentPlayer][m] == silver 
        || state.hand[currentPlayer][m] == gold){
        coinCount1++;
      }
    }

    adventurerCard(&state);

    // Generate random # of coins for testing coverages
    coinCount2 = rand() % 2;

    //Count amount of each coin in hand
    for(int m = 0; m < state.handCount[currentPlayer]; m++) {
      if(state.hand[currentPlayer][m] == copper || state.hand[currentPlayer][m] == silver 
        || state.hand[currentPlayer][m] == gold){
        coinCount2++;
      }
    }

    // Generate random # of coins for testing coverages
    dCopper = rand() % 2;
    dSilver = rand() % 2; 
    dGold = rand() % 2;

    //Checks discarded cards
    for(int a = 0; a < state.discardCount[currentPlayer]; a++){

      if(state.discard[currentPlayer][a] == copper)
        dCopper++;
      else if(state.discard[currentPlayer][a] == silver)
        dSilver++;
      else if(state.discard[currentPlayer][a] == gold)
        dGold++;

    }

    int passed = TRUE;

    //Tests to count failures in differences in hand and types
    //of cards
    if(coinCount2 > (coinCount1 + 2)) {
      printf("Failed. Too many cards drawn.\n");
      drawFail++;
      passed = FALSE;
    }

    if(coinCount2 < coinCount1) {
      printf("Failed. Cards were discards.\n");
      drawFail++;
      passed = FALSE;
    }

    if(dCopper != 0) {
      printf("Failed. Copper was discarded.\n");
      discardFail++;
      passed = FALSE;
    }

    if(dSilver != 0) {
      printf("Failed. Silver was discarded.\n");
      discardFail++;
      passed = FALSE;
    }

    if(dGold != 0) {
      printf("Failed. Gold was discarded.\n");
      discardFail++;
      passed = FALSE;
    }

    if(passed == TRUE){
      printf("Passed. No Failures.\n");
      passedTests++;
    }
  } 

  //Display counter of the results of tests
  printf("# of passed tests: %d\n", passedTests);
  printf("# of drawn tests failed: %d\n", drawFail);
  printf("# of discard tests failed: %d\n", discardFail);
  printf("End of Adventurer Card test.\n");

  return 0;
}
