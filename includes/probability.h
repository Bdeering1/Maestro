/*
 Maestro: Probability Definitions
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"
#include "hand_manager.h"
#include <stdlib.h>
#include <stdbool.h>

/* Structures */
struct range {
  Pocket *hands;
  int size;
};
typedef struct range Range;

/* Utility Functions */
int choose(short a, short b);
int permutations(short a, short b);
int factorial(int n);

/* Range Functions */
Range *max_range();

/* Print Functions */
void print_range(Range *range);
void print_simple_range(Range *range);
