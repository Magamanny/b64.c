
/**
 * `decode.c' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "b64.h"
int
b64_decode (const char *src,unsigned char *dec, size_t len) {
  return b64_decode_ex(src, dec, len, NULL);
}

int
b64_decode_ex (const char *src,unsigned char *dec, size_t len, size_t *decsize) {
  int i = 0;
  int j = 0;
  int l = 0;
  size_t size = 0;
  unsigned char buf[3];
  unsigned char tmp[4];

  if (NULL == dec) { return 1; }

  // parse until end of source
  while (len--) {
    // break if char is `=' or not base64 char
    if ('=' == src[j]) { break; }
    if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

    // read up to 4 bytes at a time into `tmp'
    tmp[i++] = src[j++];

    // if 4 bytes read then decode into `buf'
    if (4 == i) {
      // translate values in `tmp' from table
      for (i = 0; i < 4; ++i) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[i] == b64_table[l]) {
            tmp[i] = l;
            break;
          }
        }
      }

      // decode
      buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
      buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
      buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

      // write decoded buffer to `dec'
      if (dec != NULL){
        for (i = 0; i < 3; ++i) {
          dec[size++] = buf[i];
        }
      } else {
        return 1;
      }

      // reset
      i = 0;
    }
  }

  // remainder
  if (i > 0) {
    // fill `tmp' with `\0' at most 4 times
    for (j = i; j < 4; ++j) {
      tmp[j] = '\0';
    }

    // translate remainder
    for (j = 0; j < 4; ++j) {
        // find translation char in `b64_table'
        for (l = 0; l < 64; ++l) {
          if (tmp[j] == b64_table[l]) {
            tmp[j] = l;
            break;
          }
        }
    }

    // decode remainder
    buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

    // write remainer decoded buffer to `dec'
    if (dec != NULL){
      for (j = 0; (j < i - 1); ++j) {
        dec[size++] = buf[j];
      }
    } else {
      return 1;
    }
  }

  // Make sure we have enough space to add '\0' character at end.
  if (dec != NULL){
    dec[size] = '\0';
  } else {
    return 1;
  }

  // Return back the size of decoded string if demanded.
  if (decsize != NULL) {
    *decsize = size;
  }

  return 0;
}
