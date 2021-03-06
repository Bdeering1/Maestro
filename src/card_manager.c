/*
 Maestro: Card Manager
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
 */

#include "card_manager.h"


/* Utility Functions */

void create_deck() {
  deck.length = 52;
  Card card;
  int card_count = 0;
  for (int val = 14; val > 1; val--) {
    for (int suit = 3; suit >= 0; suit--) {
      card.value = val;
      card.suit = suit;
      deck.cards[card_count] = card;
      card_count++;
    }
  }
}

void sort_deck() {
  Card temp;
  for (int card_1 = 0; card_1 < deck.length; card_1++) {
    for (int card_2 = card_1 + 1; card_2 < deck.length; card_2++) {
      if (deck.cards[card_1].value * 4 + deck.cards[card_1].suit < deck.cards[card_2].value * 4 + deck.cards[card_2].suit) {
        temp = deck.cards[card_1];
        deck.cards[card_1] = deck.cards[card_2];
        deck.cards[card_2] = temp;
      }
    }
  }
}

Card draw_card(Card card) {
  Card temp;
  for (int i = 0; i < deck.length; i++) {
    if (cards_are_equal(deck.cards[i], card)) {
      temp = deck.cards[i];
      deck.cards[i] = deck.cards[deck.length - 1];
      deck.cards[deck.length - 1] = temp;
      break;
    }
  }
  if (i == deck.length) {
    printf("\nError: Trying to draw a duplicate card - (");
    print_card(card);
    printf(")\n");
  }
  deck.length--;
  return card;
}

void replace_card() {
  if (deck.length != 52) {
    deck.length++;
  } else {
    printf("\nError: Trying to add card to full deck!");
  }
}

void replace_cards(short num_cards) {
  for (int card = 0; card < num_cards; card++)
    replace_card();
}

Card high_card(Card card_a, Card card_b) {
  return (card_a.value >= card_b.value) ? card_a : card_b;
}
Card low_card(Card card_a, Card card_b) {
  return (card_a.value >= card_b.value) ? card_b : card_a;
}

bool cards_are_equal(Card card_1, Card card_2) {
  if (card_1.value == card_2.value && card_1.suit == card_2.suit)
    return true;
  return false;
}

Pocket new_pocket(Card first_card, Card second_card) {
  Pocket pocket;
  pocket.cards[0] = first_card;
  pocket.cards[1] = second_card;
  return pocket;
}

void draw_pocket(Pocket pocket) {
  draw_card(pocket.cards[0]);
  draw_card(pocket.cards[1]);
}

Board new_flop(Card first_card, Card second_card, Card third_card) {
  Board board;
  board.state = 3;
  board.cards[0] = draw_card(first_card);
  board.cards[1] = draw_card(second_card);
  board.cards[2] = draw_card(third_card);
  return board;
}

void burn_and_turn(Card card, Board *board) {
  if (board->state == 5)
    return;
  board->cards[board->state] = draw_card(card);
  board->state++;
}

void peek_next(Card card, Board *board) {
  if (board->state == 3) {
    board->cards[3] = card;
  } else {
    board->cards[4] = card;
  }
}


/* Interfacing Functions */

Card card_from_text(char *card_string) {
  Card card;
  switch (toupper(card_string[0])) {
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
  switch (tolower(card_string[1])) {
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

Pocket pocket_from_text(char *first_card, char *second_card) {
  return new_pocket(card_from_text(first_card), card_from_text(second_card));
}

Board flop_from_text(char *first_card, char *second_card, char *third_card) {
  return new_flop(card_from_text(first_card), card_from_text(second_card), card_from_text(third_card));
}


/* Print Functions */

void print_deck() {
  sort_deck();
  printf("\n");
  for (int card = 0; card < deck.length; card++) {
    printf("%d.", card + 1);
    print_card(deck.cards[card]);
  }
  printf("\n\n");
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

void print_pocket(Pocket pocket) {
  print_card(pocket.cards[0]);
  print_card(pocket.cards[1]);
}

void print_board(Board board) {
  print_card(board.cards[0]);
  print_card(board.cards[1]);
  print_card(board.cards[2]);
  if (board.state == 4) {
    print_card(board.cards[3]);
  } else if (board.state == 5) {
    print_card(board.cards[3]);
    print_card(board.cards[4]);
  }
  printf("\n");
}
