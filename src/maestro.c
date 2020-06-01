/*
 Maestro
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#include "card_manager.h"
#include "hand_manager.h"
#include "probability.h"

int main (int argc, char *argv[]) {
  create_deck();
  
  Pocket my_pocket = pocket_from_text("3s", "4s");
  draw_pocket(my_pocket);
  printf("\nMy pocket: ");
  print_pocket(my_pocket);
  
  Board my_board;
  my_board = flop_from_text("5s","6s","8h");
  /*burn_and_turn(card_from_text("8d"), &my_board);*/
  printf("Board: ");
  print_board(my_board);
  
  printf("Outs: ");
  printf("\n%.02f outs\n\n", get_outs(my_pocket, my_board));
  
  /*burn_and_turn(card_from_text("9d"), &my_board);
  printf("\n");
  
  Poker_Hand my_hand;
  my_hand = create_poker_hand(my_pocket, my_board, 5);
  printf("Rank: %d\n", my_hand.rank);*/
  
  return 0;
}
