/*
ID: angelqu1
LANG: C
TASK: milk
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
  size_t price;
  size_t units;
} farmer;

int main() {
  FILE * fin = fopen("milk.in", "r");
  if (fin == NULL) {
    perror("Error opening file :P");
    exit(1);
  }
  FILE * fout = fopen("milk.out", "w");
  if (fout == NULL) {
    perror("Error opening file :P");
    exit(1);
  }

  size_t wanted_milk = 0;
  size_t amnt_farmers = 0;

  // daily quote of milk and how many farmers they may buy from
  fscanf(fin, "%lu %lu", &wanted_milk, &amnt_farmers);

  farmer farmers[amnt_farmers];
  for (int i = 0; fscanf(fin, "%lu %lu", &farmers[i].price, &farmers[i].units) != EOF; i++)
    ;

  // buble sort farmers based on price
  for (int i = 0; i < amnt_farmers; i++) {
    for (int j = i+1; j < amnt_farmers; j++) {
      if (farmers[i].price > farmers[j].price) {
        // pass the price
        farmers[j].price += farmers[i].price; // j + i
        farmers[i].price = farmers[j].price - farmers[i].price; // j + i - i = j
        farmers[j].price = farmers[j].price - farmers[i].price; // j + i - j = i
        // pass the units
        farmers[j].units += farmers[i].units; // j + i
        farmers[i].units = farmers[j].units - farmers[i].units; // j + i - i = j
        farmers[j].units = farmers[j].units - farmers[i].units; // j + i - j = i
      }
    }
  }

  // check results
  // for (int i = 0; i < amnt_farmers; i++) {
  //   printf("\t%lu\t%lu\n", farmers[i].price, farmers[i].units);
  // }
  // printf("************************\n");

  // greedy algorithm
  size_t total_price = 0;
  for (int i = 0; i < amnt_farmers; i++) {
    if (0 == wanted_milk)
      break;
    if (wanted_milk >= farmers[i].units) {
      wanted_milk = wanted_milk - farmers[i].units;
      total_price += farmers[i].price * farmers[i].units;
    } else {
      total_price += wanted_milk * farmers[i].price;
      wanted_milk = 0;
    }
  }

  // print out results
  fprintf(fout, "%lu\n", total_price);
  fclose(fin);
  fclose(fout);

  return 0;
}
