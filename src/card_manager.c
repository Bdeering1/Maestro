/*
 Maestro: Card Manager
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"

/* Range Functions */
Range *max_range() {
  Range *range = malloc(sizeof(Range));
  range->size = 1326;
  range->hands = malloc(range->size * sizeof(Pocket));
  
  int hand = 0;
  short deck_size = sizeof(deck.cards) / sizeof(Card);
  for (int card_1 = 0; card_1 < deck_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck_size; card_2++) {
      range->hands[hand] = new_pocket(deck.cards[card_1], deck.cards[card_2]);
      hand++;
    }
  }
  return range;
}

/* Utility Functions */
Board new_flop(Card first_card, Card second_card, Card third_card) {
  Board board;
  board.state = 0;
  board.cards[0] = first_card;
  board.cards[1] = second_card;
  board.cards[2] = third_card;
  return board;
}

void burn_and_turn(Card card, Board *board) {
  if (board->state == 2)
    return;
  board->cards[3 + board->state] = card;
  board->state++;
}

void create_deck() {
  Card card;
  int card_count = 0;
  for (int val = 14; val > 1; val--) {
    for (int suit = 0; suit < 4; suit++) {
      card.value = val;
      card.suit = suit;
      deck.cards[card_count] = card;
      card_count++;
    }
  }
}

Pocket new_pocket(Card first_card, Card second_card) {
  Pocket pocket;
  pocket.cards[0] = first_card;
  pocket.cards[1] = second_card;
  return pocket;
}

Card high_card(Card card_a, Card card_b) {
  return (card_a.value >= card_b.value) ? card_a : card_b;
}
Card low_card(Card card_a, Card card_b) {
  return (card_a.value >= card_b.value) ? card_b : card_a;
}

/* Interfacing Functions */

/*Range range_from_text (finish)*/

Board flop_from_text(char *first_card, char *second_card, char *third_card) {
  return new_flop(card_from_text(first_card), card_from_text(second_card), card_from_text(third_card));
}

Pocket pocket_from_text(char *first_card, char *second_card) {
  return new_pocket(card_from_text(first_card), card_from_text(second_card));
}
Card card_from_text(char *card_string) {
  Card card;
  switch (card_string[0]) {
    case 'A':
      card.value = 14;
      break;
    case 'K':
      card.value = 13;
      break;
    case 'Q':
      card.value = 12;
      break;
    case 'J':
      card.value = 11;
      break;
    case 'T':
      card.value = 10;
      break;
    default:
      card.value = (int)card_string[0];
  }
  switch (card_string[1]) {
    case 's':
      card.suit = 0;
      break;
    case 'c':
      card.suit = 1;
      break;
    case 'd':
      card.suit = 2;
      break;
    case 'h':
      card.suit = 3;
      break;
  }
  return card;
}

/* Print Functions */
void print_range(Range *range) {
  for (int hand = 0; hand < range->size; hand++) {
    printf("%d. ", hand + 1);
    print_pocket(range->hands[hand]);
  }
}

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

void print_board(Board board) {
  print_card(board.cards[0]);
  print_card(board.cards[1]);
  print_card(board.cards[2]);
  if (board.state == 1) {
    print_card(board.cards[3]);
  } else if (board.state == 2) {
    print_card(board.cards[3]);
    print_card(board.cards[4]);
  }
  printf("\n");
}

void print_deck() {
  short deck_size = sizeof(deck.cards) / sizeof(Card);
  for (int card = 0; card < deck_size; card++) {
    printf("%d.", card + 1);
    print_card(deck.cards[card]);
  }
}

void print_pocket(Pocket pocket) {
  print_card(pocket.cards[0]);
  print_card(pocket.cards[1]);
  printf("\n");
}

void print_card(Card card) {
  switch (card.value) {
    case 14:
      printf("A");
      break;
    case 13:
      printf("K");
      break;
    case 12:
      printf("Q");
      break;
    case 11:
      printf("J");
      break;
    case 10:
       printf("T");
       break;
    default:
      printf("%u", card.value);
  }
  switch (card.suit) {
    case 0:
      printf("s ");
      break;
    case 1:
      printf("c ");
      break;
    case 2:
      printf("d ");
      break;
    case 3:
      printf("h ");
      break;
  }
}
