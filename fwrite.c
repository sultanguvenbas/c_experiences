#include<stdio.h>


int main(){

    FILE *binaryp,*binary2p;

    int scores[5]={5,6,7,8,9};

    binaryp=fopen("nums.bin","wb");

    for(int i=2; i<=500; i+=2){
        fwrite(&i,sizeof(int),1,binaryp);
    }

    binary2p=fopen("arraysnums.bin","wb");
    fwrite(scores,sizeof(int),5,binary2p);

    fclose(binaryp);
    
}
