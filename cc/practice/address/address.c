#include <stdio.h>
#include <stdlib.h>
#define SIZE 256
#define NUM 3
struct address{
    char ad[SIZE];
    int num;
};

int main(int argc,char **argv){
    FILE *file = fopen("address.txt","r");
    struct address tmp;
    struct address ad[NUM];
    int i;
    for( i = 0; i < NUM; i++){
        ad[i].num = 0;
        strcpy(ad[i].ad,"none\n");
    }
    printf("----start----\n");
    while( fgets(tmp.ad,SIZE,file) != NULL){
        printf("%d %s", ftell(file), tmp.ad);
        tmp.num = 0;
        FILE *file2 = fopen("address.txt","r");
        char buffer2[SIZE];
        while( fgets(buffer2,SIZE,file2) != NULL){
            //printf("\t%d %s", ftell(file2), buffer2);
            if( strcmp( tmp.ad, buffer2 ) == 0 ){
                if( ftell(file) > ftell(file2) ){
                    goto next;
                }
                else
                    tmp.num ++;
            }
        }
        int min=10000000,num;
        for( i=0; i<NUM; i++ ){
            if( min > ad[i].num ){
                min = ad[i].num;
                num = i;
            }
        }
        if( tmp.num > min ){
            ad[num].num = tmp.num;
            strcpy(ad[num].ad, tmp.ad);
        }
next:
        fclose(file2);
    }
    printf("----result----\n");
    for( i=0; i<NUM; i++){
        printf("%d %s", ad[i].num, ad[i].ad);
    }
    fclose(file);
    return 0;
}
