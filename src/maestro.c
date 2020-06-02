/*
 Maestro
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#include "card_manager.h"
/*#include "hand_manager.h"*/
#include "probability.h"

int main (int argc, char *argv[]) {
  create_deck();
  
  Pocket my_pocket = pocket_from_text("3s", "4s");
  draw_pocket(my_pocket);
  printf("\nMy pocket: ");
  print_pocket(my_pocket);
  
  Board my_board;
  my_board = flop_from_text("5s","6s","8h");
  printf("Board: ");
  print_board(my_board);
  
  Poker_Hand my_hand = create_poker_hand(my_pocket, my_board);
  print_outs(my_hand);
  printf("\n");
  
  return 0;
}
