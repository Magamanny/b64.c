
/**
 * `test.c' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "b64.h"

#define S(x) #x
#define t(m, a, b) (                                 \
    {                                                \
      char tmp[1024];                                \
      char r[1024];                                  \
      sprintf(tmp, "%s(%s) = %s", S(m), S(a), S(b)); \
      m(a, r, strlen((char *)a));                    \
      assert(0 == strcmp(b, r));                     \
    })

int main(void)
{
  // encode
  {
    t(b64_encode, (const unsigned char *)"bradley", "YnJhZGxleQ==");
    t(b64_encode, (const unsigned char *)"kinkajou", "a2lua2Fqb3U=");
    t(b64_encode, (const unsigned char *)"vino", "dmlubw==");
    t(b64_encode,
      (const unsigned char *)"brian the monkey and bradley the kinkajou are friends",
      "YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=");
  }

  // decode
  {
    t(b64_decode, "Y2FzaWxsZXJv", "casillero");
    t(b64_decode, "aGF4", "hax");
    t(b64_decode, "bW9ua2V5cyBhbmQgZG9ncw==", "monkeys and dogs");
    t(b64_decode,
      "dGhlIGtpbmtham91IGFuZCBtb25rZXkgZm91Z2h0IG92ZXIgdGhlIGJhbmFuYQ==",
      "the kinkajou and monkey fought over the banana");
  }

  printf("Ok done");
  return 0;
}
