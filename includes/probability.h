/*
 Maestro: Probability Definitions
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"
#include "hand_manager.h"
#include <stdlib.h>
#include <stdbool.h>

struct range {
  Pocket *hands;
  int size;
};
typedef struct range Range;

/* River Functions */
float get_outs(Pocket pocket, Board board);
bool is_river_out(Pocket pocket, Board board, Poker_Hand current_hand, short card);

/* Utility Functions */
int choose(short a, short b);
int permutations(short a, short b);
int factorial(int n);

/* Range Functions */
Range *max_range();

/* Print Functions */
void print_range(Range *range);
void print_simple_range(Range *range);
