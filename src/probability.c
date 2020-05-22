/*
 Maestro: Probability
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "probability.h"
#include <stdio.h>

/* River Functions */
Poker_Hand create_poker_hand(Community community, Pocket pocket) {
  Poker_Hand poker_hand;
  
  poker_hand.rank = 0;
  return poker_hand;
}

bool is_pair(Card card_pool[7]) {
  return false;
}
bool is_two_pair(Card card_pool[7], Card hand[5]) {
  return false;
}
bool is_triple(Card card_pool[7]) {
  return false;
}
bool is_straight(Community community, Pocket pocket) {
  return false;
}
bool is_flush(Community community, Pocket pocket, Card hand[5]) {
  return false;
}
bool is_full_house(Card card_pool[7], Card hand[5]) {
  return false;
}
bool is_quads(Card card_pool[7], Card hand[5]) {
  return false;
}
bool is_straight_flush(Card hand[5]) {
  return false;
}
bool is_royal_flush(Card hand[5]) {
  return false;
}

Card highest_from_pool(Card *card_pool) {
  return card_pool[0];
}
