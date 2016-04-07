//palindrome.c
//Unofficial Practice Practical Exam
//Created by Michael Simarta
//Your Name Here
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define FALSE 0
#define TRUE 1
 
void testCase(void);



int palindrome (char *string);


int main (int argc, char *argv[]) {
    testCase();
    return EXIT_SUCCESS;
}
 
int palindrome (char *string) {
    int a = 0;
    int i = 0;
    int test = TRUE;
    int length = 0;
    char pal[sizeof(string)*2]= {0};
    while(string[i]!=0){ //filter spaces and punctuation
        if(string[i] >= 'a' && string[i] <= 'z'){
            pal[a] = string[i];
            a++;
        }
        i++;
    }
    pal[a] = '\0';
    printf("%s\n",pal);
    while(pal[length]!=0){
        length++;
        
    }

    i = 0;
    
    while(pal[i] != 0){
        if(pal[i] != pal[length-1-i]){
            test = FALSE;
        }
        i++;
    }
    printf("%s\n",pal);
    return test;
}
void testCase(void) {
    assert (palindrome("kayak.") == TRUE);
    assert (palindrome("puzzlequest") == FALSE);
    assert (palindrome("is addo odd as i?") == TRUE);
    assert (palindrome("canoe") == FALSE);
    assert (palindrome("eevee") == TRUE);
    assert (palindrome("awesome") == FALSE);
    //ADD MORE TESTS
 
    printf ("All tests passed, you are Awesome!\n");
}
