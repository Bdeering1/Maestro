/*
 Maestro: Probability
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "probability.h"
#include "hand_manager.h"
#include "card_manager.h"


/* Outs */

float get_outs(Pocket pocket, Board board) {
  Poker_Hand current_hand;
  float outs = 0;
  sort_deck(); /* TEMPORARY (to print outs nicely) */
  current_hand = create_poker_hand(pocket, board, board.state);
  if (board.state == 3) { /* after flop */
    for (int card = 0; card < deck.length; card++) {
      peek_next(deck.cards[card], &board);
      Poker_Hand hand = create_poker_hand(pocket, board, 4);
      if ((hand.rank > current_hand.rank || (hand.rank == current_hand.rank && hand.tie_breakers[0] > current_hand.tie_breakers[0])) && hand.tie_breakers[2] == 0) {
        print_card(deck.cards[card]);
        outs++;
      }
    }
    /*for (int card_1 = 0; card_1 < deck.length; card_1++) {
      burn_and_turn(deck.cards[card_1], &board);
      for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
        if (is_river_out(pocket, board, current_hand, card_2)) {
          outs++;
        }
      }
      board.state = 3;
      replace_card();
    }
    outs  = outs / 46;*/
  } else { /* after turn */
    for (int card = 0; card < deck.length; card++) {
      if (is_river_out(pocket, board, current_hand, card)) {
        print_card(deck.cards[card]);
        outs++;
      }
    }
  }
  return outs;
}

bool is_river_out(Pocket pocket, Board board, Poker_Hand current_hand, short card) {
  peek_next(deck.cards[card], &board);
  Poker_Hand hand = create_poker_hand(pocket, board, 5);
  if ((hand.rank > current_hand.rank || (hand.rank == current_hand.rank && hand.tie_breakers[0] > current_hand.tie_breakers[0])) && hand.tie_breakers[2] == 0) {
    return true;
  }
  return false;
}


/* Utility Functions */

int choose(short a, short b) {
  int c = a;
  for (int i = 1; i < b; i++) {
    a--;
    c *= a;
  }
  
  return c / factorial(b);
}

int permutations(short a, short b) {
  int c = a;
  for (int i = 1; i < b; i++) {
    a--;
    c *= a;
  }
  
  return c;
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
  range->size = choose(deck.length, 2);
  range->hands = malloc(range->size * sizeof(Pocket));
  
  sort_deck();
  
  int hand = 0;
  for (int card_1 = 0; card_1 < deck.length; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
      range->hands[hand] = new_pocket(deck.cards[card_1], deck.cards[card_2]);
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
  printf("Range size: %d\n", range->size);
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
