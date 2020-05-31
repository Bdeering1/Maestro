/*
 Maestro: Card Manager Definitions
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#ifndef card_manager_h
#define card_manager_h

#include <stdio.h>

/* Structures */
struct card {
  unsigned int value : 4;
  unsigned int suit : 2;
};
typedef struct card Card;

struct pocket {
  Card cards[2];
};
typedef struct pocket Pocket;

struct board {
  Card cards[5];
  int state;
};
typedef struct board Board;

struct deck {
  Card cards[52];
  int length;
};
typedef struct deck Deck;

/* Global Structures */
Deck deck;


/* Utility Functions */
void create_deck();
void sort_deck();
Card draw_card(Card card);
Card high_card(Card card_a, Card card_b);
Card low_card(Card card_a, Card card_b);
Board new_flop(Card first_card, Card second_card, Card third_card);
void burn_and_turn(Card card, Board *board);
Pocket new_pocket(Card first_card, Card second_card);

/* Interfacing Functions */
Card card_from_text(char *card_string);
Pocket pocket_from_text(char *card_string_1, char *card_string_2);
Board flop_from_text(char *first_card, char *second_card, char *third_card);

/* Print Functions */
void print_deck();
void print_card(Card card);
void print_pocket(Pocket pocket);
void print_board(Board board);

#endif
