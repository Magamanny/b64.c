#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b64.h"
// multiple of 3 for proper
#define BATCH_SIZE (8*3)
// A vary log massage..JRR Tolkien -- The Hobbit
const unsigned char *str = "\
SW4gYSBob2xlIGluIHRoZSBncm91bmQgdGhlcmUgbGl2ZWQgYSBob2JiaXQuIE5v\
dCBhIG5hc3R5LCBkaXJ0eSwgd2V0IGhvbGUsIGZpbGxlZCB3aXRoIHRoZWVuZHMg\
b2Ygd29ybXMgYW5kIGFuIG9venkgc21lbGwsIG5vciB5ZXQgYSBkcnksIGJhcmUs\
IHNhbmR5IGhvbGUgd2l0aCBub3RoaW5nIGluIGl0IHRvIHNpdGRvd24gb24gb3Ig\
dG8gZWF0OiBpdCB3YXMgYSBob2JiaXQtaG9sZSwgYW5kIHRoYXQgbWVhbnMgY29t\
Zm9ydC5JdCBoYWQgYSBwZXJmZWN0bHkgcm91bmQgZG9vciBsaWtlIGEgcG9ydGhv\
bGUsIHBhaW50ZWQgZ3JlZW4sIHdpdGggYSBzaGlueSB5ZWxsb3cgYnJhc3Nrbm9i\
IGluIHRoZSBleGFjdCBtaWRkbGUuIFRoZSBkb29yIG9wZW5lZCBvbiB0byBhIHR1\
YmVzaGFwZWQgaGFsbCBsaWtlIGEgdHVubmVsOiBhIHZlcnljb21mb3J0YWJsZSB0\
dW5uZWwgd2l0aG91dCBzbW9rZSwgd2l0aCBwYW5lbGxlZCB3YWxscywgYW5kIGZs\
b29ycyB0aWxlZCBhbmQgY2FycGV0ZWQscHJvdmlkZWQgd2l0aCBwb2xpc2hlZCBj\
aGFpcnMsIGFuZCBsb3RzIGFuZCBsb3RzIG9mIHBlZ3MgZm9yIGhhdHMgYW5kIGNv\
YXRzIC0gdGhlIGhvYmJpdHdhcyBmb25kIG9mIHZpc2l0b3JzLiBUaGUgdHVubmVs\
IHdvdW5kIG9uIGFuZCBvbiwgZ29pbmcgZmFpcmx5IGJ1dCBub3QgcXVpdGUgc3Ry\
YWlnaHQgaW50b3RoZSBzaWRlIG9mIHRoZSBoaWxsIC0gVGhlIEhpbGwsIGFzIGFs\
bCB0aGUgcGVvcGxlIGZvciBtYW55IG1pbGVzIHJvdW5kIGNhbGxlZCBpdCAtIGFu\
ZCBtYW55bGl0dGxlIHJvdW5kIGRvb3JzIG9wZW5lZCBvdXQgb2YgaXQsIGZpcnN0\
IG9uIG9uZSBzaWRlIGFuZCB0aGVuIG9uIGFub3RoZXIuIE5vIGdvaW5ndXBzdGFp\
cnMgZm9yIHRoZSBob2JiaXQ6IGJlZHJvb21zLCBiYXRocm9vbXMsIGNlbGxhcnMs\
IHBhbnRyaWVzIChsb3RzIG9mIHRoZXNlKSwgd2FyZHJvYmVzKGhlIGhhZCB3aG9s\
ZSByb29tcyBkZXZvdGVkIHRvIGNsb3RoZXMpLCBraXRjaGVucywgZGluaW5nLXJv\
b21zLCBhbGwgd2VyZSBvbiB0aGUgc2FtZWZsb29yLCBhbmQgaW5kZWVkIG9uIHRo\
ZSBzYW1lIHBhc3NhZ2UuIFRoZSBiZXN0IHJvb21zIHdlcmUgYWxsIG9uIHRoZSBs\
ZWZ0LWhhbmQgc2lkZShnb2luZyBpbiksIGZvciB0aGVzZSB3ZXJlIHRoZSBvbmx5\
IG9uZXMgdG8gaGF2ZSB3aW5kb3dzLCBkZWVwLXNldCByb3VuZCB3aW5kb3dzbG9v\
a2luZyBvdmVyIGhpcyBnYXJkZW4gYW5kIG1lYWRvd3MgYmV5b25kLCBzbG9waW5n\
IGRvd24gdG8gdGhlIHJpdmVyLlRoaXMgaG9iYml0IHdhcyBhIHZlcnkgd2VsbC10\
by1kbyBob2JiaXQsIGFuZCBoaXMgbmFtZSB3YXMgQmFnZ2lucy4gVGhlIEJhZ2dp\
bnNlcyBoYWRsaXZlZCBpbiB0aGUgbmVpZ2hib3VyaG9vZCBvZiBUaGUgSGlsbCBm\
b3IgdGltZSBvdXQgb2YgbWluZCwgYW5kIHBlb3BsZSBjb25zaWRlcmVkIHRoZW12\
ZXJ5IHJlc3BlY3RhYmxlLCBub3Qgb25seSBiZWNhdXNlIG1vc3Qgb2YgdGhlbSB3\
ZXJlIHJpY2gsIGJ1dCBhbHNvIGJlY2F1c2UgdGhleSBuZXZlcmhhZCBhbnkgYWR2\
ZW50dXJlcyBvciBkaWQgYW55dGhpbmcgdW5leHBlY3RlZDogeW91IGNvdWxkIHRl\
bGwgd2hhdCBhIEJhZ2dpbnMgd291bGRzYXkgb24gYW55IHF1ZXN0aW9uIHdpdGhv\
dXQgdGhlIGJvdGhlciBvZiBhc2tpbmcgaGltLiBUaGlzIGlzIGEgc3Rvcnkgb2Yg\
aG93IGEgQmFnZ2lucyBoYWQgYW4gYWR2ZW50dXJlLCBmb3VuZCBoaW1zZWxmIGRv\
aW5nIGFuZCBzYXlpbmcgdGhpbmdzIGFsdG9nZXRoZXIgdW5leHBlY3RlZC4gSGUg\
bWF5aGF2ZSBsb3N0IHRoZSBuZWlnaGJvdXJzJyByZXNwZWN0LCBidXQgaGUgZ2Fp\
bmVkLXdlbGwsIHlvdSB3aWxsIHNlZSB3aGV0aGVyIGhlIGdhaW5lZGFueXRoaW5n\
IGluIHRoZSBlbmQuVGhlIG1vdGhlciBvZiBvdXIgcGFydGljdWxhciBob2JiaXQg\
Li4uIHdoYXQgaXMgYSBob2JiaXQ/IEkgc3VwcG9zZSBob2JiaXRzIG5lZWQgc29t\
ZWRlc2NyaXB0aW9uIG5vd2FkYXlzLCBzaW5jZSB0aGV5IGhhdmUgYmVjb21lIHJh\
cmUgYW5kIHNoeSBvZiB0aGUgQmlnIFBlb3BsZSwgYXMgdGhleWNhbGwgdXMuIFRo\
ZXkgYXJlIChvciB3ZXJlKSBhIGxpdHRsZSBwZW9wbGUsIGFib3V0IGhhbGYgb3Vy\
IGhlaWdodCwgYW5kIHNtYWxsZXIgdGhhbiB0aGViZWFyZGVkIER3YXJ2ZXMuIEhv\
YmJpdHMgaGF2ZSBubyBiZWFyZHMu";

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
  char temp[BATCH_SIZE+1]; // a temp buffer to store the batch, 1 for null character
  char dec[BATCH_SIZE*3+1]; // the encrypted size is 3 times the message, e.g 128*3 = 384
  // run the rounds
  for(int i=0;i<rounds;i++)
  {
    // can use memcpy, this is more clear
    for(int j=0;j<BATCH_SIZE;j++)
    {
      temp[j] = str[i*BATCH_SIZE+j];
    }
    temp[BATCH_SIZE]=0;
    b64_decode(temp, dec, strlen(temp)); // encode the batch
    printf("%s",dec);
  }
  printf("\nOk\n");
  return 0;
}