// extract.c
// funtions and types used to extract x,y,z values from a
// string containing a url of the form
// "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp"
// initially by richard buckland
// 13 April 2014
// your name here:
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "extract.h"

static int k = 0; 
 
int main (int argc, char *argv[]) {
    
    char * message = "http://almondbread.cse.unsw.edu.au:7191/tile_x-9999999_y-0.141_z-99999.bmp";
 
    triordinate dat = extract (message);
 
    printf ("dat is (%f, %f, %d)\n", dat.x, dat.y, dat.z);
 
    //assert (dat.x == 3.14);
    //assert (dat.y == -0.141);
    //assert (dat.z == 5);
 
    return EXIT_SUCCESS;
}



triordinate extract (char *message){
    triordinate value;
        
    
    value.x = myAtoD(message + 46);
    value.y = myAtoD(message + 46 + k);
    value.z = myAtoL(message + 46 + k);
    
    return value;
}
 
double myAtoD (char *message) {
    int i = 0; 
    int dec = 0;
    double num = 0;
    int counter = 0;
    int negative;

    if(message[0]=='-'){
        negative = 1;
        i++;
    } else {
        negative = 0;
    }
    
    while((message[i]>= '0' && message[i] <= '9') || message[i] == '.'){
        
        if(message[i] == '.'){
            dec = i;
        } else {
            num *= 10;
            num += message[i] - '0';
        }   
        i++;
    }   

    
    if(dec!=0){
        while(counter < (i-dec)-1){
            num = num/10;
            counter++;
        }
    }
    if(negative == 1){
        num = num*(-1);
    }
   
    k= i+2+k;
    return num;
    
}
 
long myAtoL (char *message){
    int i = 0;
    int num = 0;
    int negative;

    if(message[0]=='-'){
        negative = 1;
        i++;
    } else {
        negative = 0;
    }
    while(message[i]>= '0' && message[i] <= '9'){
        num *= 10;
        num += message[i] - '0';
        i++;

    }   
    if(negative == 1){
        num = num*(-1);
    }
    return num;
}
