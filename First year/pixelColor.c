#include <math.h>
#define MAX_ITERATION 256

unsigned char stepsToRed (int steps){
    char red;
    if (steps >= 100 && steps <MAX_ITERATION){
        red= 255-steps;
    } else {
        red = 0;
    }
    return red;

}
unsigned char stepsToBlue (int steps){
    char blue;
    if (steps >= MAX_ITERATION){
        blue = 0;
    }else if (steps>25){
        blue = 255*cos(steps);
    }else{
        blue = steps+10;
    }
    return blue;
}


unsigned char stepsToGreen (int steps){
    char green;
    if (steps >= MAX_ITERATION){
        green = 0;
    }else if (steps <= 150 && steps > 25){
        green = steps+30;
    } else{
        green = 0;
    }
    return green;
}

