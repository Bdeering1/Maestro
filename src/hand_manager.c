/*
 Maestro: Hand Manager
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "hand_manager.h"

/* Hand Finding Functions */
Poker_Hand create_poker_hand(Pocket pocket, Board board) {
  Poker_Hand hand;
  hand.tie_breakers[0] = 0;
  hand.tie_breakers[1] = 0;
  
  Card pool[7];
  memcpy (pool, pocket.cards, 2 * sizeof(Card));
  memcpy (pool + 2, board.cards, 5 * sizeof(Card));
  
  Card straight[5];
  
  /*TEMPORARY PRINT*/
  for (int i = 0; i < sizeof(pool) / sizeof(Card); i++) {
    print_card(pool[i]);
    printf("\n");
  }
  
  if (is_straight(pool, straight, hand.tie_breakers)) {
    if (is_flush(pool, hand.tie_breakers)) {
      if (is_straight_flush(straight, hand.tie_breakers)) {
        if (hand.tie_breakers[0] == 10) {
          hand.rank = ROYAL_FLUSH;
        } else {
          hand.rank = STRAIGHT_FLUSH;
        }
      } else {
        hand.rank = FLUSH;
      }
    } else {
      hand.rank = STRAIGHT;
    }
  } else if (is_flush(pool, hand.tie_breakers)) {
    hand.rank = FLUSH;
  } else if (is_pair(pool, hand.tie_breakers)) {
    if (is_triple(pool, hand.tie_breakers)) {
      if (is_quads(pool)) {
        hand.rank = QUADS;
      } else if (is_full_house(pool, hand.tie_breakers)) {
        hand.rank = FULL_HOUSE;
      } else {
        hand.rank = TRIPLE;
      }
    } else if (is_two_pair(pool, hand.tie_breakers)) {
      hand.rank = TWO_PAIR;
    } else {
      hand.rank = PAIR;
    }
  } else {
    hand.rank = HIGH_CARD;
    hand.tie_breakers[0] = high_card(pool[0], pool[1]).value;
    hand.tie_breakers[1] = low_card(pool[0], pool[1]).value;
  }
  
  /*TEMPORARY PRINT*/
  printf("Hand rank: %d\n", hand.rank);
  printf("Tie breakers: %d %d\n", hand.tie_breakers[0], hand.tie_breakers[1]);
  return hand;
}

bool is_pair(Card pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        if (card_1 > 1) {
        /* CASE 1 */
          tie_breakers[0] = high_card(pool[0], pool[1]).value;
          tie_breakers[1] = low_card(pool[0], pool[1]).value;
        } else {
        /* CASE 2 */
          tie_breakers[0] = pool[card_1].value;
          tie_breakers[1] = (card_1 == 0) ? pool[1].value : pool[0].value;
        }
        return true;
      }
    }
  }
  return false;
}
bool is_two_pair(Card pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_1 + 1; card_3 < 7; card_3++) {
          for (int card_4 = card_3 + 1; card_4 < 7; card_4++) {
            if (pool[card_3].value == pool[card_4].value) {
              if ((card_1 > 1 && card_3 > 1) || (card_1 <= 1 && card_3 <= 1)) {
                /* CASE 1 */
                tie_breakers[0] = high_card(pool[0], pool[1]).value;
                tie_breakers[1] = low_card(pool[0], pool[1]).value;
              } else {
                /* CASE 2 */
                if (card_1 <= 1) {
                  tie_breakers[0] = pool[card_1].value;
                  tie_breakers[1] = (card_1 == 0) ? pool[1].value : pool[0].value;
                } else {
                  tie_breakers[0] = pool[card_3].value;
                  tie_breakers[1] = (card_3 == 0) ? pool[1].value : pool[0].value;
                }
              }
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
bool is_triple(Card pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            if (card_1 > 1) {
              /* CASE 1 */
              tie_breakers[0] = high_card(pool[0], pool[1]).value;
              tie_breakers[1] = low_card(pool[0], pool[1]).value;
            } else {
              /* CASE 2 */
              tie_breakers[0] = pool[card_1].value;
              tie_breakers[1] = (card_1 == 0) ? pool[1].value : pool[0].value;
            }
            return true;
          }
        }
      }
    }
  }
  return false;
}
bool is_straight(Card pool[7], Card straight[5], short tie_breakers[2]) {
  return false;
}
bool is_flush(Card pool[7], short tie_breakers[2]) {
  short suits[4] = {0,0,0,0};
  for (int card = 0; card < 7; card++) {
    suits[pool[card].suit]++;
  }
  for (int suit = 0; suit < 4; suit++) {
    if (suits[suit] == 5) {
      if (pool[0].suit == suit && pool[1].suit == suit) {
        /* CASE 1 */
        tie_breakers[0] = high_card(pool[0], pool[1]).value;
        tie_breakers[1] = low_card(pool[0], pool[1]).value;
      } else {
        /* CASE 2 */
        if (pool[0].suit == suit) {
          tie_breakers[0] = pool[0].value;
        } else {
          tie_breakers[0] = pool[1].value;
        }
      }
      return true;
    }
  }
  return false;
}
bool is_full_house(Card pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            /*triple*/
            for (int card_4 = 0; card_4 < 7; card_4++) {
              if (pool[card_4].value == pool[card_1].value)
                continue;
              for (int card_5 = card_4 + 1; card_5 < 7; card_5++) {
                if (pool[card_4].value == pool[card_5].value) {
                  tie_breakers[0] = pool[card_1].value;
                  tie_breakers[1] = pool[card_4].value;
                  return true;
                }
              }
            }
          }
        }
      }
    }
  }
  return false;
}
bool is_quads(Card pool[7]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            for (int card_4 = card_3 + 1; card_4 < 7; card_4++) {
              if (pool[card_3].value == pool[card_4].value) {
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}
bool is_straight_flush(Card straight[5], short tie_breakers[2]) {
  short suits[4] = {0,0,0,0};
  for (int card = 0; card < 5; card++) {
    suits[straight[card].suit]++;
  }
  for (int suit = 0; suit < 4; suit++) {
    if (suits[suit] == 5) {
      /* tie_breakers[0] = (lowest card) */
      return true;
    }
  }
  return false;
}

Card highest_from_pool(Card *pool) {
  return pool[0];
}
