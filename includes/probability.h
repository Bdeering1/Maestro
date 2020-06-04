/*
 Maestro: Probability Definitions
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"
#include "hand_manager.h"
#include <stdlib.h>

#ifndef probability_h
#define probability_h

/* Structures */
struct range {
  Pocket *pockets;
  short *simple_range;
  int size;
};
typedef struct range Range;

/* Equity Functions */
float hand_equity(Poker_Hand hand, Board board);
short best_hand_rank(Board board);

/* Range Functions */
Range *create_range();
void absolute_range(Range *range, float min_strength);
void relative_range(Range *range, float min_strength, short players);
void create_simple_range(Range *range);
short range_chart_pos(Pocket pocket);
float absolute_strength(Pocket pocket);
float relative_strength(Pocket pocket, short players);

/* Print Functions */
void print_range(Range *range);
void print_simple_range(Range *range);
void print_pocket_ranks();

/* Utility Functions */
int choose(short a, short b);
int factorial(int n);

#endif
