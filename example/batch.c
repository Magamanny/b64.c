#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b64.h"

int
main (void) {
  unsigned char *str = "brian the monkey and bradley the kinkajou are friends";
  char enc[1024];
  b64_encode(str, enc, strlen(str));

  printf("%s\n", enc); // YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=

  char dec[1024];
  b64_decode(enc, dec, strlen(enc));

  printf("%s\n", dec); // brian the monkey and bradley the kinkajou are friends
  return 0;
}