/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lang_specs/entities.h"
#include "./data_structures/hash_map.h"
#include "./utils/terminal_map.h"
#include "./utils/nonterminal_map.h"
#include "./data_structures/grammar.h"
#include "./utils/grammar_parser.h"
#include "./utils/print.h"
#include "./driver.h"

int main()
{
  hash_map *tmap, *ntmap, *khm;
  grammar *gm;

  char grammar_file[150] = "./grammar.txt";

  while (true)
  {
    printf("\n");
    printf("Options: \n");
    printf("0. Exit\n");
    printf("1. Create Parse Tree\n");
    printf("2. Print Type Errors\n");
    printf("3. Print Parse Tree\n");
    printf("4. Print Type Expression Table\n");

    int input;
    printf("\nSelect option> ");
    scanf("%d", &input);
    printf("\n");

    switch (input)
    {
    case 0:
      printf("Exiting...\n");
      return 0;
      break;

    case 1:
      tmap = generate_t_map(15);
      ntmap = generate_nt_map(15);
      gm = grammar_parser(grammar_file, tmap, ntmap);
      print_grammar(gm);

      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      printf("Please select a valid option.\n\n");
      break;
    }
  }
}