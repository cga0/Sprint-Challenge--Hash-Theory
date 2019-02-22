#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  // Build hash table
  for (int i = 0; i < length; i++)
  {
    char *source = tickets[i]->source;
    char *destination = tickets[i]->destination;
    hash_table_insert(ht, source, destination);
  }

  // Find the key of NONE (this is the starting point)
  char *point = hash_table_retrieve(ht, "NONE");

  for (int x = 0; x < length; x++)
  {
    // Set route[x] to the value of the current point
    // i.e "NONE" evaluates to "LAX"
    route[x] = strdup(point);

    // Update the current point to the value of the current key
    // i.e. "LAX" evaluates to "SFO"
    point = hash_table_retrieve(ht, point);
  }

  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
