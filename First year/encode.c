//ng yi yan
//16 march 2015
/*if it is a lower case letter
we encode it
anything else is left alone*/

#include <stdio.h>
#include <assert.h>

#include "encode.h" 
//searches for encode.h in same directory
//copies and pastes code from encode.h here, replacing original line of code


int main(int argc, char * argv[]){
    char plainText;
    char cipherText;

    printf("Enter a plain text character:\n");
    scanf("%c",&plainText); //input saved as variable 'plainText'

    

    printf("Encrypted is %c\n",cipherText);
    return 0;
}

char encode(char plainText){
    char cipherText;
    if(isLowerLetter(plainText)){
        if(plainText == LAST_LETTER){
            cipherText = FIRST_LETTER;
        } else {
            cipherText = plainText + 1;
        //shifts plainText to the next letter eg. 'a' is encrypted as 'b'
        //only works for a single letter / first letter in input
        }
    } else {
        cipherText = plainText;
    }
    return cipherText;

}

//return 0 : false, not letter
//return 1: true, is a lower case letter
int isLowerLetter(char letter){
    return (letter >= FIRST_LETTER && letter <= LAST_LETTER);
}

//tests to run for code automatically
void testEncode(void){
    assert(encode('a') == 'b');
    assert(encode('b') == 'c');
    assert(encode('z') == 'a');
    assert(encode('1') == '1');
    assert(encode('A') == 'A');
    assert(encode('!') == '!');
    assert(encode('$') == '$');

    printf("All test passed\n");
    printf("You are awesome!!!!\n");
}