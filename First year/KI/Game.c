#include <stdlib.h>
#include <stdio.h>
#include "Game-1.07.h"

#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

#define NUM_DISC 6
#define NUM_REGIONS 19

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

//Struct containing board arrangement
//Example: disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES
//		   diceValues[NUM_REGIONS] = DEFAULT_DICE
//refers to the default arrangement of Knowledge Island
typedef struct _board {
    
    int diceScore;
    int disciplines[NUM_REGIONS];
    int diceValues[NUM_REGIONS];
    int vertex [11][12];
	
    int direction[0][0] = {{0,1},{1,1},{1,-1},{0,-1},{-1,-1},{-1,1}};
     
} board;


//Struct containing all resources that each player currently has.
typedef struct _playerResources {
    //Arrays containing each player's students currently in hand
    //int disPlayer[NUM_DISC];
    
    int thd [NUM_UNIS];
    int bps[NUM_UNIS];
    int bqn[NUM_UNIS];
    int mj[NUM_UNIS];
    int mtv[NUM_UNIS];
    int mmoney[NUM_UNIS];

    //Arrays containing each player's capital
    int campuses[NUM_UNIS];
    int ARCs[NUM_UNIS];
    int G08sP[NUM_UNIS];
    int publications[NUM_UNIS];
    int patents[NUM_UNIS];
    int KPIs[NUM_UNIS];
} playerResources;

typedef struct _game {
    board b;
    int turnCounter; 
    int resourceCount;
    int playerID; 
    //total resources dispensed, incl. initial and used/exchanged resources
    int totalActions; //counts actions made in game
    playerResources playRes;
    board defaultBoard;
	

} game;


/* ++++++ LET THE HUNGER GAMES BEGIN ++++++ */

int main(int argc, char  *argv[]) {
    // something????
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game g = newGame (disciplines, dice);


    disposeGame(g);
    return 0;
}

Game newGame (int discipline[], int dice[]){

}



void throwDice (Game g, int diceScore){
    gb.diceScore = diceScore;
    g->turnCounter++;		
}

int getDiscipline (Game g, int regionID){
    int discID;

    while()
    
    return discID;
}

int getDiceValue (Game g, int regionID){


}

int getMostArcs (Game g){
    int mostArcs = NO_ONE;
    int i = 0;
    int max = 0;
    int maxCount = 0;

    while(i<NUM_UNIS){
        if(g->playRes.ARCs[i+1]>max){
            max = g->playRes.ARCs[i+1];
            mostArcs = i+1
        }
        i++;
    } //find max Arcs first

    i = 0; //reset i to use as counter again
    while(i<NUM_UNIS){
        if(g->playRes.ARCs[i+1]==max){
            maxCount++;
        }
        i++;
    } //see how many unis have maximum

    if(maxCount > 1){
        mostArcs = NO_ONE
    } //if more than 1 uni with max, no one has mostArcs

    return mostArcs;

}



int getMostPublications ( Game g){


}

int getTurnNumber(Game g){
    return g.turnCounter;

}

int getWhoseTurn(Game g){
    g.playerID = g.turnCounter % 3 +1;
    return g.playerID;
}

int getCampus(Game g, path pathToVertex){
}

int getARC(Game g, path pathToEdge){

}


int isLegalAction (Game g, action a);


int getKPIpoints (Game g, int player);

int getARCs (Game g, int player);


int getGO8s (Game g, int player);

int getCampuses (Game g, int player);

int getIPs (Game g, int player);
int getPublications (Game g, int player){
}
int getStudents (Game g, int player, int discipline){
    if()

}
int getExchangeRate (Game g, int player, int discipline From, int disciplineTo){


}
















