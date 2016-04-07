#include <stdio.h>
#include <stdlib.h>

#define LOWER 1
#define UPPER 2
#define OTHER 3
#define LFEED 4
#define SPACE 5

int lowerCase (char text);
void frequency(char text , unsigned long long *low, 
               unsigned long long *up, unsigned long long *lf);
void tallyLower (unsigned long long *array, unsigned long long sumCharacters);
void tallyUpper (unsigned long long *array, unsigned long long sumCharacters);



int main (int argc, char * argv[]) {
    unsigned long long lowCount[27] = {0} ;
    unsigned long long upCount[26] = {0} ;
    char text = getchar();
    unsigned long long sumCharacters = 0;
    unsigned long long vowels = 0;
    unsigned long long special[2] = {0};


    while (text != EOF) {
    frequency (text, lowCount, upCount, special);
    text = getchar();
    sumCharacters++;
    }

    printf("The number of characters is %llu!\n", sumCharacters);
    printf("The number of line feeds is %llu!\n", special[0]);
    printf("The number of line feeds is %llu!\n", special[1]);
    vowels = lowCount[0] + lowCount[4] + lowCount[8] + lowCount[14] + lowCount[20] +
             upCount[0] + upCount[4] + upCount[8]+ upCount[14] + upCount[20];
    printf("The number of vowels is %llu!\n", vowels); 


    tallyLower(lowCount, sumCharacters);
    tallyUpper(upCount, sumCharacters);
    
    return EXIT_SUCCESS;
}



int lowercase (char text) {
    int result;
    if (text >= 'a' && text <= 'z') {
        result = LOWER;
    } else if (text >= 'A' && text <= 'Z') {
        result = UPPER;
    } else if(text == 10){
        result = LFEED;
    } else if(text == 32){
        result = SPACE;
    } else {
        result = OTHER;
    }
    return result;
}




void frequency(char text , unsigned long long *low, 
               unsigned long long *up, unsigned long long *lf) {

    if (lowercase(text) == LOWER) {
        low[text - 'a']++;
    } else if (lowercase(text) == UPPER) {
        up[text - 'A']++;
    } else if (lowercase(text) == LFEED){
        lf[0]++;
    } else if (lowercase(text) == SPACE){
        lf[1]++;
    } else if (lowercase(text) == OTHER) {
        low[26]++;
    }
    
}


void tallyLower (unsigned long long *array, unsigned long long sumCharacters) {
    int i = 0;
    unsigned long long sumLetters = 0;

    char letter = 'a';
    double proportion = 0;
    
    while (i <= 25) {
        sumLetters += array[i];
        proportion = ((double) array[i]/sumCharacters);
        printf("The frequency of %c is %llu! ( %.5f%%)\n", letter, array[i], proportion*100);
        letter++;
        i++;
    }
    i = 0;
    
    printf("The number of lowercase letters is %llu!\n", sumLetters);

        
}


void tallyUpper (unsigned long long *array, unsigned long long sumCharacters) {
    int i = 0;
    unsigned long long sumLetters = 0;

    char letter = 'a';
    double proportion = 0;
    
    while (i <= 25) {
        sumLetters += array[i];
        proportion = ((double) array[i]/sumCharacters);
        printf("The frequency of %c is %llu! ( %.5f%%)\n", letter, array[i], proportion*100);
        letter++;
        i++;
    }
    i = 0;
    
    printf("The number of uppercase letters is %llu!\n", sumLetters);

        
}
