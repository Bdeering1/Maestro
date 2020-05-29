/*
 Maestro: Hand Manager Definitions
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#ifndef probability_h
#define probability_h

#include "card_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Constants */
#define HIGH_CARD 0;
#define PAIR 1;
#define TWO_PAIR 2;
#define TRIPLE 3;
#define STRAIGHT 4;
#define FLUSH 5;
#define FULL_HOUSE 6;
#define QUADS 7;
#define STRAIGHT_FLUSH 8;
#define ROYAL_FLUSH 9;

/* Structures */
struct poker_hand {
  unsigned int rank : 4;
  short tie_breakers[2];
};
typedef struct poker_hand Poker_Hand;

/* Hand Finding Functions */
Poker_Hand create_poker_hand(Pocket pocket, Board board);
bool is_pair(Card pool[7], short tie_breakers[2]);
bool is_two_pair(Card pool[7], short tie_breakers[2]);
bool is_triple(Card pool[7], short tie_breakers[2]);
bool is_straight(Card pool[7], Card straight[5], short tie_breakers[2]);
bool is_flush(Card pool[7], short tie_breakers[2]);
bool is_full_house(Card pool[7], short tie_breakers[2]);
bool is_quads(Card pool[7]);
bool is_straight_flush(Card straight[5], short tie_breakers[2]);

#endif
