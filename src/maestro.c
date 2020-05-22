/*
 Maestro
 Created by Bryn Deering on 2020-05-20.
 
 bdeering@uoguelph.ca
*/

#include "card_manager.h"
#include "probability.h"
#include <stdio.h>
#include <stdlib.h>

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
  
  Community my_com;
  my_com = flop_from_text("Ah","Kd","Ts");
  printf("Flop: ");
  print_community(my_com);
  burn_and_turn(card_from_text("7c"), &my_com);
  printf("Turn: ");
  print_community(my_com);
  burn_and_turn(card_from_text("2s"), &my_com);
  printf("River: ");
  print_community(my_com);
  
  return 0;
}
