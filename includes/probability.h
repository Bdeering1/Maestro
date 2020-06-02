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

/* Utility Functions */
int choose(short a, short b);
int factorial(int n);

/* Range Functions */
Range *create_max_range();
void create_simple_range(Range *range);
short range_chart_pos(Pocket pocket);

/* Print Functions */
void print_range(Range *range);
void print_simple_range(Range *range);
void print_pocket_ranks();

#endif
