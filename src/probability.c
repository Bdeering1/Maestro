/*
 Maestro: Probability
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "probability.h"


/* Utility Functions */

int choose(short a, short b) {
  int c = a;
  printf("c = %d\n", c);
  for (int i = 1; i < b; i++) {
    a--;
    c *= a;
    printf("c = %d\n", c);
  }
  printf("a = %d, b = %d, c = %d\nfact(b) = %d", a, b, c, factorial(b));
  
  return c / factorial(b);
}

int factorial(int n)
{
  if (n == 0)
    return 1;
  return n * factorial(n - 1);
}


/* Range Functions */

Range *max_range() {
  Range *range = malloc(sizeof(Range));
  range->size = choose(deck.length,2);
  range->hands = malloc(range->size * sizeof(Pocket));
  
  sort_deck();
  
  int hand = 0;
  for (int card_1 = 0; card_1 < deck.length; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
      range->hands[hand] = new_pocket(deck.cards[card_1], deck.cards[card_2]); /*WILL DRAW FROM DECK!!!*/
      hand++;
    }
  }
  return range;
}

void print_range(Range *range) {
  for (int hand = 0; hand < range->size; hand++) {
    printf("%d. ", hand + 1);
    print_pocket(range->hands[hand]);
  }
}


/* Print Functions */

void print_simple_range(Range *range) {
  Card big_card, small_card;
  short bit_array[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
  short pos = 0;
  
  for (int hand = 0; hand < range->size; hand++) {
    big_card = high_card(range->hands[hand].cards[0], range->hands[hand].cards[1]);
    small_card = low_card(range->hands[hand].cards[0], range->hands[hand].cards[1]);
    if (big_card.value == small_card.value) { /* pocket pair */
      pos = 13 * (14 - big_card.value) + (14 - big_card.value);
    } else if (big_card.suit == small_card.suit) { /* suited hand */
      pos = 13 * (14 - big_card.value) + (14 - small_card.value);
    } else { /* unsuited hand */
      pos = 13 * (14 - small_card.value) + (14 - big_card.value);
    }
    bit_array[pos/13] |= 1 << (pos%13);
  }
  for (int i = 0; i < 169; i++) {
    printf("%d ", ((bit_array[i/13] & (1 << (i%13) )) != 0));
    if (((i + 1) % 13) == 0)
      printf("\n");
  }
}
