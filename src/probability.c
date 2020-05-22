/*
 Maestro: Probability
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "probability.h"

/* Hand Finding Functions */
Poker_Hand create_poker_hand(Pocket pocket, Community community) {
  Poker_Hand poker_hand;
  poker_hand.tie_breakers[0] = 0;
  poker_hand.tie_breakers[1] = 0;
  Card card_pool[7];
  memcpy (card_pool, pocket.cards, 2 * sizeof(Card));
  memcpy (card_pool + 2, community.cards, 5 * sizeof(Card));
  
  /*TEMPORARY PRINT*/
  for (int i = 0; i < sizeof(card_pool) / sizeof(Card); i++) {
    print_card(card_pool[i]);
    printf("\n");
  }
  
  if (is_straight(card_pool, poker_hand.tie_breakers)) {
    if (is_flush(card_pool, poker_hand.tie_breakers)) {
      if (is_straight_flush(card_pool, poker_hand.tie_breakers)) {
        if (is_royal_flush(poker_hand.tie_breakers)) {
          poker_hand.rank = ROYAL_FLUSH;
        } else {
          poker_hand.rank = STRAIGHT_FLUSH;
        }
      } else {
        poker_hand.rank = FLUSH;
      }
    } else {
      poker_hand.rank = STRAIGHT;
    }
  } else if (is_flush(card_pool, poker_hand.tie_breakers)) {
    poker_hand.rank = FLUSH;
  } else if (is_pair(card_pool)) {
    if (is_triple(card_pool)) {
      if (is_quads(card_pool, poker_hand.tie_breakers)) {
        poker_hand.rank = QUADS;
      } else if (is_full_house(card_pool, poker_hand.tie_breakers)) {
        poker_hand.rank = FULL_HOUSE;
      } else {
        poker_hand.rank = TRIPLE;
        /*complete tie_breakers*/
      }
    } else if (is_two_pair(card_pool, poker_hand.tie_breakers)) {
      poker_hand.rank = TWO_PAIR;
    } else {
      poker_hand.rank = PAIR;
      /*complete tie_breakers*/
    }
  } else {
    poker_hand.rank = HIGH_CARD;
    /*complete tie_breakers*/
  }
  
  /*TEMPORARY PRINT*/
  printf("Hand rank: %d\n", poker_hand.rank);
  return poker_hand;
}

bool is_pair(Card card_pool[7]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (card_pool[card_1].value == card_pool[card_2].value)
        return true;
    }
  }
  return false;
}
bool is_two_pair(Card card_pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (card_pool[card_1].value == card_pool[card_2].value) {
        for (int card_3 = card_1 + 1; card_3 < 7; card_3++) {
          for (int card_4 = card_3 + 1; card_4 < 7; card_4++) {
            if (card_pool[card_3].value == card_pool[card_4].value) {
              /*create_two_pair_hand();*/
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
bool is_triple(Card card_pool[7]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (card_pool[card_1].value == card_pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (card_pool[card_2].value == card_pool[card_3].value)
            return true;
        }
      }
    }
  }
  return false;
}
bool is_straight(Card card_pool[7], short tie_breakers[2]) {
  return false;
}
bool is_flush(Card card_pool[7], short tie_breakers[2]) {
  short suits[4] = {0,0,0,0};
  for (int card = 0; card < 7; card++)
    suits[card_pool[card].suit]++;
  for (int suit = 0; suit < 4; suit++) {
    if (suits[suit] == 5) {
      /*create_flush_hand*/
      return true;
    }
  }
  return false;
}
bool is_full_house(Card card_pool[7], short tie_breakers[2]) { /***DOES NOT CURRENTLY WORK*****/
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (card_pool[card_1].value == card_pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (card_pool[card_2].value == card_pool[card_3].value) {
            /*triple*/
            for (int test_card = card_1 + 1; test_card < 7; test_card++) {
              if (card_pool[test_card].value != card_pool[card_1].value)
                break;
            }
            for (int card_4 = test_card; card_4 < 7; card_4++) {
              for (int card_5 = card_4 + 1; card_5 < 7; card_5++) {
                if (card_pool[card_4].value == card_pool[card_5].value) {
                  /*create_full_house_hand() //maybe not necessary??*/
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
bool is_quads(Card card_pool[7], short tie_breakers[2]) {
  for (int card_1 = 0; card_1 < 7; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < 7; card_2++) {
      if (card_pool[card_1].value == card_pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < 7; card_3++) {
          if (card_pool[card_2].value == card_pool[card_3].value) {
            for (int card_4 = card_3 + 1; card_4 < 7; card_4++) {
              if (card_pool[card_3].value == card_pool[card_4].value) {
                /*create_quads_hand()*/
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
bool is_straight_flush(Card card_pool[7], short tie_breakers[2]) {
  return false;
}
bool is_royal_flush(short tie_breakers[2]) {
  return false;
}

Card highest_from_pool(Card *card_pool) {
  return card_pool[0];
}
