/*
 Maestro
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#include "card_manager.h"
#include "hand_manager.h"

int main (int argc, char *argv[]) {
  create_deck();
  
  /*Range my_range;
  my_range.size = 2;
  my_range.hands = malloc(my_range.size * sizeof(Pocket));
  my_range.hands[0] = pocket_from_text("Ah", "Kh");
  my_range.hands[1] = pocket_from_text("Td", "9d");

  printf("My range: \n");
  print_range(&my_range);
  print_simple_range(&my_range);*/
  
  Pocket my_pocket = pocket_from_text("3s", "4d");
  printf("My pocket: ");
  print_pocket(my_pocket);
  
  Board my_board;
  my_board = flop_from_text("As","Tc","Ts");
  burn_and_turn(card_from_text("2s"), &my_board);
  burn_and_turn(card_from_text("6s"), &my_board);
  printf("\n");
  
  Poker_Hand my_hand;
  my_hand = create_poker_hand(my_pocket, my_board);
  
  return 0;
}
