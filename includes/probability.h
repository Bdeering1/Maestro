/*
 Maestro: Probability Definitions
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"
#include <stdbool.h>

/* Structures */
struct poker_hand {
  unsigned int rank : 4;
  Card cards[5];
};
typedef struct poker_hand Poker_Hand;

/* Constants */
const short HIGH_CARD = 0;
const short PAIR = 1;
const short TWO_PAIR = 2;
const short TRIPLE = 3;
const short STRAIGHT = 4;
const short FLUSH = 5;
const short FULL_HOUSE = 6;
const short QUADS = 7;
const short STRAIGHT_FLUSH = 8;
const short ROYAL_FLUSH = 9;

/* River Functions */
Poker_Hand create_poker_hand(Community community, Pocket pocket);
bool is_pair(Card card_pool[7]);
bool is_two_pair(Card card_pool[7], Card hand[5]);
bool is_triple(Card card_pool[7]);
bool is_straight(Community community, Pocket pocket);
bool is_flush(Community community, Pocket pocket, Card hand[5]);
bool is_full_house(Card card_pool[7], Card hand[5]);
bool is_quads(Card card_pool[7], Card hand[5]);
bool is_straight_flush(Card hand[5]);
bool is_royal_flush(Card hand[5]);
Card highest_from_pool(Card *card_pool);
