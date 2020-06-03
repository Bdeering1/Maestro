/*
 Maestro: Probability
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "probability.h"

const float POCKET_RANKS[13][13] = {
/*A*/  {31.0,20.2,18.7,17.5,16.6,14.6,13.9,13.4,13.0,13.4,13.2,13.1,12.7},
/*K*/  {16.7,26.0,18.1,17.1,16.1,14.2,12.8,12.2,11.8,11.6,11.4,11.3,11.3},
/*Q*/  {14.9,14.4,22.0,16.6,15.8,13.8,12.4,11.2,10.9,10.6,10.4,10.4,10.3},
/*J*/  {13.5,13.2,12.9,19.1,15.8,13.8,12.5,11.1,10.1,9.9,9.7,9.6,9.5},
/*T*/  {12.4,12.2,12.0,12.1,16.8,14.1,12.7,11.5,10.3,9.2,9.1,9.1,9.0},
/*9*/  {10.2,9.9,9.8,10.0,10.4,15.3,12.6,11.7,10.7,9.6,8.7,8.5,8.5},
/*8*/  {9.4,8.5,8.3,8.5,8.9,9.0,14.2,12.0,11.2,10.1,9.1,8.2,8.1},
/*7*/  {8.8,7.9,7.0,7.1,7.5,8.0,8.4,13.4,11.5,10.7,9.7,8.8,7.9},
/*6*/  {8.4,7.5,6.6,5.9,6.3,6.8,7.4,7.9,12.8,11.1,10.4,9.5,8.5},
/*5*/  {8.9,7.1,6.3,5.6,5.6,5.6,6.3,7.0,7.6,12.2,10.9,10.2,9.3},
/*4*/  {8.7,7.0,6.1,5.5,5.0,4.7,5.3,6.0,6.8,7.4,11.9,9.8,9.0},
/*3*/  {8.5,6.9,6.1,5.4,5.0,4.5,4.3,4.9,5.7,6.6,6.2,11.9,8.7},
/*2*/  {8.2,6.8,6.0,5.3,4.9,4.5,4.2,4.0,4.7,5.6,5.4,5.0,11.9},
};

const char CARD_VALUES[13] = {'A','K','Q','J','T','9','8','7','6','5','4','3','2'};


/* Utility Functions */

int choose(short a, short b) {
  int c = a;
  for (int i = 1; i < b; i++) {
    a--;
    c *= a;
  }
  
  return c / factorial(b);
}

int factorial(int n)
{
  if (n == 0)
    return 1;
  return n * factorial(n - 1);
}


/* Range Functions */

Range *create_range() {
  Range *range = malloc(sizeof(Range));
  range->size = choose(deck.length, 2);
  range->pockets = malloc(range->size * sizeof(Pocket));
  range->simple_range = malloc(13 * sizeof(short));
  for (int i = 0; i < 13; i++)
    range->simple_range[i] = 0;
  
  return range;
}

void absolute_range(Range *range, float min_strength) {
  Pocket this_pocket;
  int pocket_num = 0;
  
  sort_deck();
  for (int card_1 = 0; card_1 < deck.length; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
      this_pocket = new_pocket(deck.cards[card_1], deck.cards[card_2]);
      if (absolute_strength(this_pocket) >= min_strength) {
        range->pockets[pocket_num] = this_pocket;
        pocket_num++;
      }
    }
  }
  create_simple_range(range);
}

void relative_range(Range *range, float min_strength) {
  Pocket this_pocket;
  int pocket_num = 0;
  
  sort_deck();
  for (int card_1 = 0; card_1 < deck.length; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
      this_pocket = new_pocket(deck.cards[card_1], deck.cards[card_2]);
      if (relative_strength(this_pocket, 9) >= min_strength) {
        range->pockets[pocket_num] = this_pocket;
        pocket_num++;
      }
    }
  }
  create_simple_range(range);
}

void create_simple_range(Range *range) {
  short pos = 0;
  
  for (int pocket = 0; pocket < range->size; pocket++) {
    pos = range_chart_pos(range->pockets[pocket]);
    range->simple_range[pos/13] |= 1 << (pos%13);
  }
}

short range_chart_pos(Pocket pocket) {
  Card big_card, small_card;
  short pos = 0;
  big_card = high_card(pocket.cards[0], pocket.cards[1]);
  small_card = low_card(pocket.cards[0], pocket.cards[1]);
  if (big_card.value == small_card.value) { /* pocket pair */
    pos = 13 * (14 - big_card.value) + (14 - big_card.value);
  } else if (big_card.suit == small_card.suit) { /* suited hand */
    pos = 13 * (14 - big_card.value) + (14 - small_card.value);
  } else { /* unsuited hand */
    pos = 13 * (14 - small_card.value) + (14 - big_card.value);
  }
  return pos;
}

float absolute_strength(Pocket pocket) {
  short pos = range_chart_pos(pocket);
  return POCKET_RANKS[pos/13][pos%13];
}

float relative_strength(Pocket pocket, short players) {
  short pos = range_chart_pos(pocket);
  return (POCKET_RANKS[pos/13][pos%13] * 9) / players - (100 / (float)players);
}

/* sort range function */


/* Print Functions */

void print_range(Range *range) {
  for (int pocket = 0; pocket < range->size; pocket++) {
    printf("%d. ", pocket + 1);
    print_pocket(range->pockets[pocket]);
    printf("\n");
  }
  printf("Range size: %d\n", range->size);
}

void print_simple_range(Range *range) {
  printf("  ");
  for (int i = 0; i < 13; i++) {
    printf("%-2c", CARD_VALUES[i]);
  }
  for (int j = 0; j < 169; j++) {
    if ((j % 13) == 0)
      printf("\n%-2c", CARD_VALUES[j/13]);
    printf("%d ", ((range->simple_range[j/13] & (1 << (j%13) )) != 0));
  }
  printf("\n");
}

void print_pocket_ranks() {
  printf("\n     ");
  for (int i = 0; i < 13; i++) {
    printf("%-5c", CARD_VALUES[i]);
  }
  printf("\n\n");
  for (int pocket_1 = 0; pocket_1 < 13; pocket_1++) {
    printf("%-5c", CARD_VALUES[pocket_1]);
    for (int pocket_2 = 0; pocket_2 < 13; pocket_2++) {
      printf("%-5.1f",POCKET_RANKS[pocket_1][pocket_2]);
    }
    printf("\n\n");
  }
}
