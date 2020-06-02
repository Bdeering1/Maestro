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
  unsigned short rank : 4;
  short tie_breakers[3];
  Card outs[21];
  short num_outs;
};
typedef struct poker_hand Poker_Hand;

/* Outs Functions */
Poker_Hand create_poker_hand(Pocket pocket, Board board);
bool is_out(Pocket pocket, Board board, Poker_Hand current_hand, Poker_Hand hand);

/* Hand Value Functions */
Poker_Hand hand_with_value(Pocket pocket, Board board, short state);
bool is_pair(Card *pool, short pool_size, short tie_breakers[3]);
bool is_two_pair(Card *pool, short pool_size, short tie_breakers[3]);
bool is_triple(Card *pool, short pool_size, short tie_breakers[3]);
bool is_straight(Card *pool, short pool_size, Card straight[5], short tie_breakers[3]);
bool is_flush(Card *pool, short pool_size, short tie_breakers[3]);
bool is_full_house(Card *pool, short pool_size, short tie_breakers[3]);
bool is_quads(Card *pool, short pool_size, short tie_breakers[3]);
bool is_straight_flush(Card straight[5], short tie_breakers[3]);

/* Print Functions */
void print_outs(Poker_Hand hand);

#endif
