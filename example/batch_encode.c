#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b64.h"
// multiple of 6 to avoid padding
#define BATCH_SIZE (8*6)
// A vary log massage..JRR Tolkien -- The Hobbit
const unsigned char *str = "\
In a hole in the ground there lived a hobbit. Not a nasty, dirty, wet hole, filled with the\
ends of worms and an oozy smell, nor yet a dry, bare, sandy hole with nothing in it to sit\
down on or to eat: it was a hobbit-hole, and that means comfort.\
It had a perfectly round door like a porthole, painted green, with a shiny yellow brass\
knob in the exact middle. The door opened on to a tubeshaped hall like a tunnel: a very\
comfortable tunnel without smoke, with panelled walls, and floors tiled and carpeted,\
provided with polished chairs, and lots and lots of pegs for hats and coats - the hobbit\
was fond of visitors. The tunnel wound on and on, going fairly but not quite straight into\
the side of the hill - The Hill, as all the people for many miles round called it - and many\
little round doors opened out of it, first on one side and then on another. No going\
upstairs for the hobbit: bedrooms, bathrooms, cellars, pantries (lots of these), wardrobes\
(he had whole rooms devoted to clothes), kitchens, dining-rooms, all were on the same\
floor, and indeed on the same passage. The best rooms were all on the left-hand side\
(going in), for these were the only ones to have windows, deep-set round windows\
looking over his garden and meadows beyond, sloping down to the river.\
This hobbit was a very well-to-do hobbit, and his name was Baggins. The Bagginses had\
lived in the neighbourhood of The Hill for time out of mind, and people considered them\
very respectable, not only because most of them were rich, but also because they never\
had any adventures or did anything unexpected: you could tell what a Baggins would\
say on any question without the bother of asking him. This is a story of how a Baggins \
had an adventure, found himself doing and saying things altogether unexpected. He may\
have lost the neighbours' respect, but he gained-well, you will see whether he gained\
anything in the end.\
The mother of our particular hobbit ... what is a hobbit? I suppose hobbits need some\
description nowadays, since they have become rare and shy of the Big People, as they\
call us. They are (or were) a little people, about half our height, and smaller than the\
bearded Dwarves. Hobbits have no beards.";

int
main (void) {
  int msg_len;
  int rounds=0;
  msg_len = strlen(str);
  rounds = msg_len/(BATCH_SIZE);
  // if it is not a multiple of the bach size
  if(msg_len%BATCH_SIZE != 0)
  {
    rounds = rounds+1; // run a extra round for the remaing message
  }
  printf("%d\r\n",msg_len);
  // uase a batch size of 128
  char temp[BATCH_SIZE+1]; // a temp buffer to store the batch, 1 for null character
  char enc[BATCH_SIZE*3+1]; // the encrypted size is 3 times the message, e.g 128*3 = 384
  // run the rounds
  for(int i=0;i<rounds;i++)
  {
    // can use memcpy, this is more clear
    for(int j=0;j<BATCH_SIZE;j++)
    {
      temp[j] = str[i*BATCH_SIZE+j];
    }
    temp[BATCH_SIZE]=0;
    b64_encode(temp, enc, strlen(temp)); // encode the batch
    printf("%s \n",enc);
  }
  printf("Ok\n");
  return 0;
}