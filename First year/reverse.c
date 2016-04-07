
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *reverse (char *message);
void swap(char *a, char *b);

int main (int argc, char *argv[]) {
    
    char *stringOne = "uwotm8";
    char *final = reverse(stringOne);
    printf("%s\n", final);

    free(final);
    return 0;


}

char *reverse (char *message){
    //create memory
    char *stringTwo = malloc (sizeof(message)*1000);
    int i =0;
    int pos=0;

    while(message[i] != 0){ 
        //copy string and count length
        stringTwo[i]=message[i];
        i++;
    } 

    while(pos < i/2){
        //swap characters 
        swap(&stringTwo[pos],&stringTwo[i-1-pos]);
        pos++;

    }
    stringTwo[i]='\0'; //null terminator
    return stringTwo;
    free(stringTwo);
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}
