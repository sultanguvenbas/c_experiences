#include "highprecision.h"
#include <stdio.h>
#include <stdbool.h>

int scanHighPrec(high_prec_t* h){
    high_prec_t highPrec;
    highPrec.pos=0;
  
    int extras=0;
    bool foundANumber=false;
    bool foundADot=false;
    int finalPos;
    for(int i=0; i < LIMIT + extras; i++){
      char c;
      scanf("%c", &c);
      if(c=='\n' || c==' '){
        highPrec.arr[i-extras]=-1;
        finalPos=i-extras+1;
        break;
      }      
      if(i==0){
        if(c=='-'){
          extras++;
          highPrec.sign=-1;
          continue;
        }
        else if(c=='+'){
          extras++;
          highPrec.sign=1;
          continue;
        }else{
          highPrec.sign=1;
        }
      }
      int n=c-'0';

      if(!foundANumber && n==0){
          if(foundADot)
            highPrec.pos--;
          extras++;
          continue;
      }
      


      if(c=='.'){
        extras++;
        foundADot=true;
        continue;
      }    

      if(!foundADot)
        highPrec.pos++;

      foundANumber=true;
      highPrec.arr[i-extras]=n;
    }
    for(int i=finalPos; i < LIMIT; i++)
      highPrec.arr[i]=0;
      
    *h=highPrec;
    return 0;
}



void printHighPrec(high_prec_t h){
  if(h.sign==-1)
    printf("-");
  

  int start=0;

  if(h.pos<1){
    printf("0."); 
    for(int i=0; i > h.pos; i--){
      printf("0");
    }
  }else
    for(int i=0; i<h.pos; i++){
      start++;
      printf("%d", h.arr[i]);
    }

  for(int i=start; i < LIMIT; i++){
    if(h.arr[i]==-1)
      break;
    if(i==start && h.pos >0)
      printf(".");

    printf("%d",h.arr[i]);
  }
  printf("\n");
}
