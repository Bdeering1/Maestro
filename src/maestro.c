/*
 Maestro
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#include "card_manager.h"
#include "probability.h"
#include <ctype.h>

void help() {
  printf("\nHow to use:\n\n");
  printf("Enter the letter for the function you want to use, then any additional input if required.\n\n");
  printf("O = Calculate outs           ->  o [my card 1] [my card 2] [flop 1] [flop 2] [flop 3]\n");
  printf("E = Evalutate hand strength  ->  e [card 1] [card 2] [num players] <- optional, def=9\n");
  printf("R = Opening range            ->  r [min hand strength] [num players]\n");
  printf("A = Winning percentage of ALL starting hands (9 players)\n");
  printf("H = Get help menu (this)\n");
  printf("Q = Quit\n\n");
  printf("*nothing is case sensitive, each card should be two letters (ten = 'T')\n");
  printf(" eg. Ah, Kd, Ts, 5c\n\n\n");
}

int main (int argc, char *argv[]) {
  create_deck();
  
  help();
  
  char user_input[50];
  char *token;
  short first = 1;
  while (true) {
    printf("->");
    fgets(user_input, 50, stdin);
    token = strtok(user_input, " ");
    token[0] = tolower(token[0]);
    
    if (token[0] == 'o') { /* not finding straight draw with A in outs??? */
      Pocket my_pocket = pocket_from_text(strtok(NULL, " "), strtok(NULL, " "));
      draw_pocket(my_pocket);
      Board my_board = flop_from_text(strtok(NULL, " "), strtok(NULL, " "), strtok(NULL, " "));
      Poker_Hand my_hand = create_poker_hand(my_pocket, my_board);
      printf("\n");
      print_outs(my_hand);
      printf("\n");
      printf("Chance of improving hand: %.2f %%\n\n\n", hand_equity(my_hand, my_board));
      replace_cards(5);
    } else if (token[0] == 'e') {
      Pocket my_pocket = pocket_from_text(strtok(NULL, " "), strtok(NULL, " "));
      draw_pocket(my_pocket);
      token = strtok(NULL, " ");
      if (token == NULL) {
        printf("\nHand strength: %.2f\n", relative_strength(my_pocket, 9));
      } else {
        printf("\nHand strength: %.2f\n", relative_strength(my_pocket, atoi(token)));
      }
      if (first) {
        printf("*generally >2 is good, and >5 is really good\n\n\n");
      } else {
        printf("\n\n");
      }
      replace_cards(2);
    } else if (token[0] == 'r') {
      Range *my_range = create_range();
      printf("\n");
      relative_range(my_range, atoi(strtok(NULL, " ")), atoi(strtok(NULL, " ")));
      print_simple_range(my_range);
      printf("\n\n");
    } else if (token[0] == 'a') {
      print_pocket_ranks();
    } else if (token[0] == 'h') {
      help();
    } else if (token[0] == 'q'){
      break;
    } else {
      printf("\nYour entry was not a valid command\n\n");
    }
    first = 0;
  }
  
  
  return 0;
}
