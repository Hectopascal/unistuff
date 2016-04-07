#include <stdlib.h>
#include <stdio.h>

void showDanish (void);

int main(int argc, char const *argv[])
{
    showDanish();
    return 0;
}

void showDanish (void){
    int horizontal;
    int vertical;
    horizontal = 0;
    vertical = 0;
    while(vertical < 5){

        if(vertical == 2){
            printf("\n");
        } else {

            while(horizontal < 13){
                if(horizontal == 2){
                    printf(" ");
                    horizontal++;
                } else {
                    printf("*");
                }
                horizontal++;
            }
            horizontal = 0;
            printf("\n");
  

        }  
    vertical++;
    }

}