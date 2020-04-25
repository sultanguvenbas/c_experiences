#include <stdio.h>
#include "highprecision.h"

int main(void) {
  high_prec_t h;
  scanHighPrec(&h);
  // printf("sign: %d\npos: %d\n",h.sign, h.pos);
  // for(int i=0; i<20; i++)
  //   printf("%d,",h.arr[i]);
  // printf("\n\n");
  printHighPrec(h);

  return 0;
}