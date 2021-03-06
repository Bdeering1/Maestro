/*
 Maestro: Hand Manager
 Created by Bryn Deering on 2020-05-21.
 
 bdeering@uoguelph.ca
 */

#include "hand_manager.h"


/* Outs Functions */

Poker_Hand create_poker_hand(Pocket pocket, Board board) {
  short pool_size = 2 + board.state;
  Card *pool = malloc(sizeof(Card) * 7); /* default 7, regardless of size */
  memcpy (pool, pocket.cards, 2 * sizeof(Card));
  memcpy (pool + 2, board.cards, board.state * sizeof(Card));
  
  Poker_Hand hand, possible_hand;
  hand = pool_value(pool, pool_size);
  pool_size++;
  hand.num_outs = 0;
  
  sort_deck();
  for (int card = 0; card < deck.length; card++) {
    peek_next(deck.cards[card], &board);
    pool[2 + board.state] = board.cards[board.state];
    if (board.state != 5) {
      possible_hand = pool_value(pool, pool_size);
    } else {
      printf("Board is full!");
      hand.num_outs = -1;
      return hand;
    }
    if (is_out(pocket, board, hand, possible_hand)) {
      hand.outs[hand.num_outs] = deck.cards[card];
      hand.num_outs++;
    }
  }
  
  return hand;
}

bool is_out(Pocket pocket, Board board, Poker_Hand hand, Poker_Hand possible_hand) {
  if ((possible_hand.rank > hand.rank || (possible_hand.rank == hand.rank && possible_hand.tie_breakers[0] > hand.tie_breakers[0])) && possible_hand.tie_breakers[2] == 0)
    return true;
  return false;
}


/* Hand Value Functions */

Poker_Hand pool_value(Card *pool, short pool_size) {
  Poker_Hand hand;
  hand.tie_breakers[0] = 0;
  hand.tie_breakers[1] = 0;
  hand.tie_breakers[2] = 0;
  
  Card straight[5];
  
  /*TEMPORARY PRINT*/
  /*for (int i = 0; i < pool_size; i++) {
    print_card(pool[i]);
    printf(" ");
  }
  printf("\n");*/
  
  if (is_straight(pool, pool_size, straight, hand.tie_breakers)) {
    if (is_flush(pool, pool_size, hand.tie_breakers)) {
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
  } else if (is_flush(pool, pool_size, hand.tie_breakers)) {
    hand.rank = FLUSH;
  } else if (is_pair(pool, pool_size, hand.tie_breakers)) {
    if (is_triple(pool, pool_size, hand.tie_breakers)) {
      if (is_quads(pool, pool_size, hand.tie_breakers)) {
        hand.rank = QUADS;
      } else if (is_full_house(pool, pool_size, hand.tie_breakers)) {
        hand.rank = FULL_HOUSE;
      } else {
        hand.rank = TRIPLE;
      }
    } else if (is_two_pair(pool, pool_size, hand.tie_breakers)) {
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
  /*printf("Hand rank: %d\n", hand.rank);
  printf("Tie breakers: %d %d\n\n", hand.tie_breakers[0], hand.tie_breakers[1]);*/
  return hand;
}

bool is_pair(Card *pool, short pool_size, short tie_breakers[3]) {
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        if (card_1 > 1) {
          /* CASE 1 */
          tie_breakers[0] = high_card(pool[0], pool[1]).value;
          tie_breakers[1] = low_card(pool[0], pool[1]).value;
          tie_breakers[2] = 1;
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
bool is_two_pair(Card *pool, short pool_size, short tie_breakers[3]) {
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        /* first pair found */
        for (int card_3 = card_1 + 1; card_3 < pool_size; card_3++) {
          for (int card_4 = card_3 + 1; card_4 < pool_size; card_4++) {
            if (pool[card_3].value == pool[card_4].value) {
              /* second pair found */
              if ((card_1 > 1 && card_3 > 1)) {
                /* CASE 1 */
                tie_breakers[0] = high_card(pool[0], pool[1]).value;
                tie_breakers[1] = low_card(pool[0], pool[1]).value;
                tie_breakers[2] = 1;
              } else if (card_1 <= 1 && card_3 <= 1) {
                /* CASE 3 */
                tie_breakers[0] = high_card(pool[0], pool[1]).value;
                tie_breakers[1] = low_card(pool[0], pool[1]).value;
                tie_breakers[2] = 0;
              } else {
                /* CASE 2 */
                tie_breakers[0] = pool[card_1].value;
                tie_breakers[1] = (card_1 == 0) ? pool[1].value : pool[0].value;
                if (card_4 == pool_size - 1) {
                  tie_breakers[2] = 1;
                } else {
                  tie_breakers[2] = 0;
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
bool is_triple(Card *pool, short pool_size, short tie_breakers[3]) {
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < pool_size; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            if (card_1 > 1) {
              /* CASE 1 */
              tie_breakers[0] = high_card(pool[0], pool[1]).value;
              tie_breakers[1] = low_card(pool[0], pool[1]).value;
              tie_breakers[2] = 1;
            } else {
              /* CASE 2 */
              tie_breakers[0] = pool[card_1].value;
              tie_breakers[1] = (card_1 == 0) ? pool[1].value : pool[0].value;
              tie_breakers[2] = 0;
            }
            return true;
          }
        }
      }
    }
  }
  return false;
}
bool is_straight(Card *pool, short pool_size, Card straight[5], short tie_breakers[3]) {
  /* sort elements */
  Card sort_array[pool_size];
  for (int i = 0; i < pool_size; i++) {
    sort_array[i] = pool[i];
  }
  Card temp;
  
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (sort_array[card_1].value > sort_array[card_2].value) {
        temp = sort_array[card_1];
        sort_array[card_1] = sort_array[card_2];
        sort_array[card_2] = temp;
      }
    }
  }
  
  /* scan elements */
  short straight_count = 1;
  short straight_start = -1;
  for (int card = 0; card < pool_size; card++) {
    if (sort_array[card].value + 1 == sort_array[card + 1].value) {
      /* consecutive cards */
      straight_count++;
      if (straight_count == 4 && sort_array[pool_size - 1].value == 14 && sort_array[card].value == 4) { /* ace lowest card in straight */
        tie_breakers[0] = 1;
        straight_start = 0;
      } else if (straight_count >= 5) {
        straight_start = card - 3;
      }
    } else if (sort_array[card].value == sort_array[card + 1].value) {
      /* matching cards (so that straight_count doesn't reset) */
      /* if this is part of a straight, check to make sure that flush version of straight is used */
      continue;
    } else if (card > 2) {
      /* no straight found */
      break;
    } else {
      straight_count = 1;
    }
  }
  
  if (straight_start != -1) {
    if (tie_breakers[0] == 1) {
      memcpy(straight + 1, sort_array + straight_start, 4 * sizeof(Card));
      straight[0] = sort_array[pool_size - 1];
    } else {
      tie_breakers[0] = sort_array[straight_start].value;
      memcpy(straight, sort_array + straight_start, 5 * sizeof(Card));
    }
    return true;
  }

  return false;
}
bool is_flush(Card *pool, short pool_size, short tie_breakers[3]) {
  short suits[4] = {0,0,0,0};
  for (int card = 0; card < pool_size; card++) {
    suits[pool[card].suit]++;
  }
  for (int suit = 0; suit < 4; suit++) {
    if (suits[suit] >= 5) {
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
bool is_full_house(Card *pool, short pool_size, short tie_breakers[3]) {
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < pool_size; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            /* triple found */
            for (int card_4 = 0; card_4 < pool_size; card_4++) {
              if (pool[card_4].value == pool[card_1].value)
                continue;
              for (int card_5 = card_4 + 1; card_5 < pool_size; card_5++) {
                if (pool[card_4].value == pool[card_5].value && (card_1 <= 1 || card_4 <= 1)) {
                  tie_breakers[0] = pool[card_1].value;
                  tie_breakers[1] = pool[card_4].value;
                  tie_breakers[2] = 0;
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
bool is_quads(Card *pool, short pool_size, short tie_breakers[3]) {
  for (int card_1 = 0; card_1 < pool_size; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < pool_size; card_2++) {
      if (pool[card_1].value == pool[card_2].value) {
        for (int card_3 = card_2 + 1; card_3 < pool_size; card_3++) {
          if (pool[card_2].value == pool[card_3].value) {
            for (int card_4 = card_3 + 1; card_4 < pool_size; card_4++) {
              if (pool[card_3].value == pool[card_4].value) {
                if (card_1 >= 2) {
                  /* CASE 1 */
                  tie_breakers[0] = high_card(pool[0], pool[1]).value;
                  tie_breakers[2] = 1;
                } else {
                  /* CASE 2 */
                  tie_breakers[2] = 0;
                }
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
bool is_straight_flush(Card straight[5], short tie_breakers[3]) {
  short suit = straight[0].suit;
  for (int card = 0; card < 5; card++) {
    if (straight[card].suit != suit)
      return false;
  }
  tie_breakers[0] = straight[0].value;
  return true;
}


/* Print Functions */

void print_outs(Poker_Hand hand) {
  printf("Outs: ");
  if (hand.num_outs == -1) {
    printf("none (full board)\n");
  } else if (hand.num_outs == 0) {
    printf("none\n");
  } else {
    for (int i = 0; i < hand.num_outs; i++) {
      print_card(hand.outs[i]);
    }
  }
  if (hand.num_outs > 0)
    printf("\n%d outs\n", hand.num_outs);
}
