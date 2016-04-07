#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(int argc, char *argv[]) {
    int first, second, third; 
    scanf ("%d %d %d", &first, &second, &third);

    if(first >= second){

        swap(&first, &second);

    } 
    if(second >= third){
        swap(&second, &third);
    }

    if(first >= second){
        swap(&first, &second);
    }         

    printf("%d\n%d\n%d\n", first, second, third);
    return 0;
}


void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
