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
    int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int dice[NUM_REGIONS] = DEFAULT_DICE;
    Game g = newGame (disciplines, dice);


    disposeGame(g);
    return 0;
}

Game newGame (int discipline[], int dice[]){

}


int getDiscipline (Game g, int regionID){
    int discID;
    discID = g->b.disciplines[regionID];
    
    return discID;
}
void makeAction (Game g, action a){
/*#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_PATENT 6
#define RETRAIN_STUDENTS 7 

typedef struct _action {
   int actionCode;  // see #defines above
   path destination; // if the action operates on a vertex or ARC this
                     // specifies *which* vertex or path.  unused 
                     // otherwise
   int disciplineFrom;  // used for the retrain students action
   int disciplineTo;    // used for the retrain students action
} action;*/
    if(isLegalAction(g,a) == 1){
        if(a == 1){

            action camp;
            camp.destination = getPath();
        } else if()

    }

}


int isLegalAction (Game g, action a){

}

int getExchangeRate (Game g, int player, int discipline From, int disciplineTo){


}
















