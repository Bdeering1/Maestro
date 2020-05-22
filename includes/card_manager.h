/*
 Maestro: Card Manager Definitions
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

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

struct community {
  Card cards[5];
  short state;
};
typedef struct community Community;

struct deck {
  Card cards[52];
};
typedef struct deck Deck;

struct range {
  Pocket *hands;
  short size;
};
typedef struct range Range;

/* Global Structures */
Deck deck;


/* Range Functions */
Range *max_range();

/* Utility Functions */
Community new_flop(Card first_card, Card second_card, Card third_card);
void burn_and_turn(Card card, Community *community);
void create_deck();
Pocket new_pocket(Card first_card, Card second_card);
Card high_card(Card card_a, Card card_b);
Card low_card(Card card_a, Card card_b);

/* Interfacing Functions */
Community flop_from_text(char *first_card, char *second_card, char *third_card);
Pocket pocket_from_text(char *card_string_1, char *card_string_2);
Card card_from_text(char *card_string);

/* Print Functions */
void print_range(Range *range);
void print_simple_range(Range *range);
void print_community(Community community);
void print_deck();
void print_community();
void print_pocket(Pocket pocket);
void print_card(Card card);
