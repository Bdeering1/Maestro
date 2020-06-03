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
  
  Pocket my_pocket = pocket_from_text(argv[1], argv[2]);
  draw_pocket(my_pocket);
  printf("\nMy pocket: ");
  print_pocket(my_pocket);
  printf("\n\n");
  
  /*Board my_board;
  my_board = flop_from_text("5s","6s","8h");
  printf("Board: ");
  print_board(my_board);
  
  Poker_Hand my_hand = create_poker_hand(my_pocket, my_board);
  print_outs(my_hand);
  printf("\n");*/
  
  Range *my_range = create_range();
  relative_range(my_range, 2);
  print_simple_range(my_range);
  
  /*print_pocket_ranks();*/
  
  printf("\nWin percent: %.2f\n", relative_strength(my_pocket, 6));
  
  return 0;
}
