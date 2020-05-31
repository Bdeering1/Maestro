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

  /*draw_card(card_from_text("Ah"));
  print_deck();*/
  
  /*Pocket my_pocket = pocket_from_text("Ts", "Js");
  printf("My pocket: ");
  print_pocket(my_pocket);
  
  Board my_board;
  my_board = flop_from_text("As","Qs","Ks");
  burn_and_turn(card_from_text("5d"), &my_board);
  burn_and_turn(card_from_text("7c"), &my_board);
  printf("\n");
  
  Poker_Hand my_hand;
  my_hand = create_poker_hand(my_pocket, my_board);*/
  
  printf("\n%d\n", choose(52,5));
  
  return 0;
}
