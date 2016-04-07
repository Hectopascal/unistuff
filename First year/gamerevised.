


#include <stdio.h>
#include <stdlib.h>
#include "Game.h"


#define PATH_NUM 11
#define BOARD_HEIGHT 11
#define BOARD_WIDTH 6
#define Y_COORDS {1,1,0,-1,-1,0} \
#define X_COORDS {0,0,-1,0,0,1} \
#define VERTEX_PER_REGION 6
#define NUMBER_OF_DIMENSIONS 2

#define DEFAULT_RATE 3


#define INITIAL_Y 0
#define INITIAL_X 2


/* YY: I combined this with gameBoard struct
typedef struct _regionID {
    int disciplines[NUM_REGIONS];
    int diceValues[NUM_REGIONS];
} regionID;
*/
typedef struct _pathVectors {
    int y[6];
    int x[6];
} pathVectors;

typedef struct _gameBoard {
    int disciplines[NUM_REGIONS];
    int diceValues[NUM_REGIONS];
    int coord[BOARD_HEIGHT][BOARD_WIDTH];
    int region[BOARD_HEIGHT][BOARD_WIDTH];
    int paths[PATH_NUM][PATH_NUM];
} gameBoard;

typedef struct _playerResources {
    int thd[NUM_UNIS];
    int bps[NUM_UNIS];
    int bqn[NUM_UNIS];
    int mj[NUM_UNIS];
    int mtv[NUM_UNIS];
    int mmoney[NUM_UNIS];
    
    int campuses[NUM_UNIS];
    int ARCs[NUM_UNIS];
    int GO8s[NUM_UNIS];
    int publications[NUM_UNIS];
    int patents[NUM_UNIS];
    int KPIs[NUM_UNIS];
} playerResources;


typedef struct _game {
    gameBoard board;
    int turnCounter;
    playerResources playRes;
    pathVectors vectors;
    int playerID;
} game;


// Function Declarations
int getXCoord(Game g, path pathToVertex);
int getYCoord(Game g, path pathtoVertex);
int pathDirection(int x1, int x, int y1, int y);
int *getPathCoord(Game g, path pathToEdge);
void populateMap(Game g);
void populateCoords(Game g);

Game newGame (int discipline[], int dice[]){
    Game g = malloc (sizeof (game));
    
    // Populates the arrays corresponding to the regionID.
    int regionID = 0;
    while (regionID < NUM_REGIONS) {
        g->board.disciplines[regionID] = discipline[regionID];
        g->board.diceValues[regionID]  = dice[regionID];
        regionID++;
    }
    // Populates coord array
    populateCoords(g);
    
    // Populates the region array
    populateMap(g);
    
    
    g->turnCounter = -1;
    
    g->playRes.thd[0] = 0;
    g->playRes.thd[1] = 0;
    g->playRes.thd[2] = 0;

    g->playRes.bps[0] = 3;
    g->playRes.bps[1] = 3;
    g->playRes.bps[2] = 3;

    g->playRes.bqn[0] = 3;
    g->playRes.bqn[1] = 3;
    g->playRes.bqn[2] = 3;

    g->playRes.mj[0] = 1;
    g->playRes.mj[1] = 1;
    g->playRes.mj[2] = 1;

    g->playRes.mtv[0] = 1;
    g->playRes.mtv[1] = 1;
    g->playRes.mtv[2] = 1;

    g->playRes.mmoney[0] = 1;
    g->playRes.mmoney[0] = 1;
    g->playRes.mmoney[0] = 1;
    
    g->playRes.campuses = {2};
    g->playRes.ARCs = {0};
    g->playRes.GO8 = {0};
    g->playRes.publications = {0};
    g->playRes.patents = {0};
    g->playRes.KPIs = {20, 20, 20};
    
    g->playerID = NO_ONE;
    
    g->vectors.y = Y_COORDS;
    g->vectors.x = X_COORDS;
    
    
    
    
    return g;
}





void makeAction (Game g, action a){
    pID = g->playerID-1;

    if(a.actionCode == BUILD_CAMPUS){ //***COMPLETE

        x = getXCoord(g,a.destination);  
        y = getYCoord(g,a.destination);  
        g->board.coord[x][y] = g->playerID;
        //change vertex status to occupied
        
        g->playRes.bps[pID]--;
        g->playRes.bqn[pID]--;
        g->playRes.mj[pID]--;
        g->playRes.mtv[pID]--;

        g->playRes.campuses[pID]++;
        g->playRes.KPIs[pID]+=10;

    } else if(a.actionCode==BUILD_GO8){ //***COMPLETE
        x = getXCoord(g,a.destination);  
        y = getYCoord(g,a.destination);  
        g->board.coord[x][y] = g->playerID + 3;


        g->playRes.mj[pID]-= 2;
        g->playRes.mmoney[pID]-= 3;
        g->playRes.campuses[pID]--;

        g->playRes.KPIs[pID]+=10;
        g->playRes.GO8s[pID]++;        

    } else if(a.actionCode == OBTAIN_ARC){ //***COMPLETE BUT UGLY
        int mostArcs = getMostARCs(g);
        


        int pCoords[2] =getPathCoord(g,a.destination);

        g->board.paths[pCoords[0]][pCoords[1]] = g->playerID;

        g->playRes.bps[pID]--;
        g->playRes.bqn[pID]--;

        g->playRes.ARCs[pID]++;
        g->playRes.KPIs[pID]+=2;

        if(getMostARCs(g) == g->playerID){ 
            g->playRes.KPIs[pID]+=10;
            g->playRes.KPIs[mostArcs-1]-=10;
        }
        free(pCoords);

    } else if (a.actionCode==OBTAIN_PUBLICATION){  //***COMPLETE
        int mostPubs = getMostPublications(g); //find player w most pubs

        
        g->playRes.publications[pID]++; 

        if(getMostPublications(g) == g->playerID){ 
        //if after pub increase current player has most pubs, add 10 to KPI 
        //and take 10 from previous player w most pubs
            g->playRes.KPIs[pID]+=10;
            g->playRes.KPIs[mostPubs-1]-=10;
        }

    } else if (a.actionCode == OBTAIN_IP_PATENT){//***COMPLETE
        g->playRes.patents[pID]++;

        g->playRes.mj[pID]--;
        g->playRes.mtv[pID]--;
        g->playRes.mmoney[pID]--;

        g->playRes.KPIs[pID]+=10;

    } else if (a.actionCode == RETRAIN_STUDENTS){ //***COMPLETE
        rate = getExchangeRate(g,g->playerID,a.disciplineFrom,
                                a.disciplineTo);

        if (a.disciplineFrom == STUDENT_BPS){
            g->playRes.bps[pID]-= rate;
        } else if (a.disciplineFrom == STUDENT_BQN) {
            g->playRes.bqn[pID]-= rate;
        } else if (a.disciplineFrom == STUDENT_MJ) {
            g->playRes.mj[pID]-= rate;
        } else if (a.disciplineFrom == STUDENT_MTV){
            g->playRes.mtv[pID]-= rate;
        } else if (a.disciplineFrom == STUDENT_MMONEY) {
            g->playRes.mmoney[pID]-= rate;
        }


        if (a.disciplineTo == STUDENT_BPS){
            g->playRes.bps[pID]++;
        } else if (a.disciplineTo == STUDENT_BQN) {
            g->playRes.bqn[pID]++;
        } else if (a.disciplineTo == STUDENT_MJ) {
            g->playRes.mj[pID]++;
        } else if (a.disciplineTo == STUDENT_MTV){
            g->playRes.mtv[pID]++;
        } else if (a.disciplineTo == STUDENT_MMONEY) {
            g->playRes.mmoney[pID]++;
        }

    }



}



void throwDice (Game g, int diceScore){
    g->turnCounter++;
    int regionID;
    int vertex;
    int dimension;
    // Dimension refers to which 'dimension' we're looking at for the coordinates
    // i.e. If we have an (A,B) coordinate system, A is the first dimension and B is the second.
    
    
    
    int xCoord = 0;
    int yCoord = 0;
    
    regionID = 0;
    
    

    
    while (regionID < NUM_REGIONS) {
        // What regions have the same dice value as diceScore?
        if (diceScore == g->board.diceValues[regionID]) {
        
            vertex = 0;
        
            // Which vertexes are attached to this region?      
            while (vertex < VERTEX_PER_REGION) {
                dimension = 0;
            
                
                while (dimension < NUMBER_OF_DIMENSIONS) {
                    
                    //What are the coordinates of the vertexes that have the same corresponding
                    //dice value as diceScore?
                    if (dimension%2 == 0) {
                        yCoord = g->board.region[regionID][vertex][dimension];
                    } else {
                        xCoord = g->board.region[regionID][vertex][dimension];
                    }
                    
                    
                    dimension++;
                }
                
                
                // vvvvvvvvvvv
                // Checks to see which resources need to be updated, and to which player.
                if(g->board.disciplines[regionID] == STUDENT_THD) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.thd[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.thd[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.thd[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.thd[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.thd[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.thd[UNI_C-1]++;
                        }
                    }
            
                } else if(g->board.disciplines[regionID] == STUDENT_BPS) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.bps[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.bps[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.bps[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.bps[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.bps[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.bps[UNI_C-1]++;
                        }
                    }
                
                } else if(g->board.disciplines[regionID] == STUDENT_BQN) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.bqn[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.bqn[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.bqn[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.bqn[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.bqn[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.bqn[UNI_C-1]++;
                        }
                    }
                
                } else if(g->board.disciplines[regionID] == STUDENT_MJ) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.mj[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.mj[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.mj[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.mj[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.mj[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.mj[UNI_C-1]++;
                        }
                    }
                
                } else if(g->board.disciplines[regionID] == STUDENT_MTV) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.mtv[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.mtv[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.mtb[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.mtv[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.mtb[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.mtv[UNI_C-1]++;
                        }
                    }
                
                } else if(g->board.disciplines[regionID] == STUDENT_MMONEY) {
                    if(g->board.coord[yCoord][xCoord] == CAMPUS_A ||g->board.coord[yCoord][xCoord] == GO8_A ) {
                        g->playRes.mmoney[UNI_A-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_A) {
                            g->playRes.mmoney[UNI_A-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_B ||g->board.coord[yCoord][xCoord] == GO8_B ) {
                        g->playRes.mmoney[UNI_B-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_B) {
                            g->playRes.mmoney[UNI_B-1]++;
                        }
                    } else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
                        g->playRes.mmoney[UNI_C-1]++;
                        if (g->board.coord[yCoord][xCoord] == GO8_C) {
                            g->playRes.mmoney[UNI_C-1]++;
                        }
                    }
                }
                // ^^^^^^^^^^^^
                // End of updating resources.
                
            }
            
                vertex++;
        }
        regionID++;
    }
    
    int player = UNI_A;
    
    // On a dice roll of 7, all MTV and MMONEY students switch to THD.
    if (diceScore == 7) {
        while(player <= NUM_UNIS) {
            g->playRes.thd[player-1] += g->playRes.mtv[player-1];
            g->playRes.thd[player-1] += g->playRes.mmoney[player-1];
            g->playRes.mtv[player-1] = 0;       
            g->playRes.mmoney[player-1] = 0;
            player++;
        }
    }
}
    

int getDiscipline (Game g, int regionID){
    
    return g->board.disciplines[regionID];
}

int getDiceValue (Game g, int regionID){

    return g->board.diceValues[regionID];
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
    int mostPubs = NO_ONE;
    int i = 0;
    int max = 0;
    int maxCount = 0;

    while(i<NUM_UNIS){
        if(g->playRes.publications[i+1]>max){
            max = g->playRes.publications[i+1];
            mostPubss = i+1
        }
        i++;
    } //find max Arcs first

    i = 0; //reset i to use as counter again
    while(i<NUM_UNIS){
        if(g->playRes.publications[i+1]==max){
            maxCount++;
        }
        i++;
    } //see how many unis have maximum

    if(maxCount > 1){
        mostPubs = NO_ONE
    } //if more than 1 uni with max, no one has mostArcs

    return mostPubs;

}

int getTurnNumber(Game g){
    return g->turnCounter;

}

int getWhoseTurn(Game g){
    g.playerID = g.turnCounter % 3 +1;
    return g->playerID;
}







int getXCoord(Game g, path pathToVertex){
    int i=0;
    int x=INITIAL_X;
    int dX=0;
    while(pathtoVertex[i]!= 0){
        if(pathtoVertex[i]=='R') { 
            //right
            if(dX==5){
                dX = 0;
            } else{
                dX +=1;
            }
        } else if(pathtoVertex[i]=='L') { 
            //left
            if(dX==0){
                dX = 5;
            }else {
                dX -=1;
            }
        } else { //back
            if(dx<=2){
                dX+=3;
            } else{
                dX-=3;
            }     
        }
        
        x += g->vectors[dX];
        i++;
    }
    return x;
}


int *getPathCoord(Game g, path pathToEdge){
    int prevY, prevX, pX, pY; 
    int pathcoords[2]= malloc(sizeof(int)*10);
    //prevY and prevX is second last vertex coordinate
    // --> needed to find path btw last two points
    //pX and pY is coords of paths

    int direction;
    int path;

    int i=0;
    int y=INITIAL_Y; 
    int x=INITIAL_X;
    int dY=0;
    int dX=0;

    while(pathToEdge[i]!= 0){
        if(pathToEdge[i]=='R') { 
            //right
            if(dX==5){
                dX = 0;
                dY = 0;
            } else{
                dX +=1;
                dY +=1;
            }
        } else if(pathToEdge[i]=='L') { 
            //left
            if(dX==0){
                dX = 5;
                dY = 5;
            }else {
                dX -=1;
                dY -=1;
            }
        } else { //back
            if(dx<=2){
                dX+=3;
                dY+=3;
            } else{
                dX-=3;
                dY-=3;
            }     
        }

        prevX = x;
        prevY = y;
        x += g->vectors[dX];
        y += g->vectors[dY];
        i++;
    }
    direction = pathDirection(prevX, x, prevY, y);

    if(direction == 0){
        //vertical
        if(y > prevY){
            //vert path above point
            pX = x*2;
            pY = y-1;
        } else {
            //vert path below point
            pX = x*2;
            pY = y;
        }
    } else{
        //horizontal, direction == 1
        if(x % 2 ==0 && y % 2 == 0 ||
            x % 2 !=0 && y % 2 != 0) {
            pX = x*2 + 1; //path right of vertex
            pY = y;

        } else if{
            pX = x*2 - 1; //path left of vertex
            pY = y;
        }
    }
    pathcoords = {y,x};

    return pathcoords;
}




int getCampus(Game g, path pathToVertex){
    int campus;
    int x = getXCoord(g,pathtoVertex);
    int y = getYCoord(g,pathtoVertex);

    campus = vertex[y][x];
    return campus;

}

int getARC(Game g, path pathToEdge){
    int prevY, prevX, pX, pY; 
    //prevY and prevX is second last vertex coordinate
    // --> needed to find path btw last two points
    //pX and pY is coords of paths

    int direction;
    int path;

    int i=0;
    int y=INITIAL_Y; 
    int x=INITIAL_X;
    int dY=0;
    int dX=0;
    
    int *pCoord = getPathCoord(g, pathToEdge);
    

    path = g->board.paths[pCoord[0]][pCoord[1]];
    free(pCoord);
    
    return path;
}

int pathDirection(int x1, int x, int y1, int y){
    int orientation;
    if(x1 == x){
        //same x-coords; vertical path
        orientation = 0;
    } else if(y1 == y){
        //same y-coords; horizontal path
        orientation = 1;
    } else{
        // error if neither x nor y equal??? 
    }

    return orientation;
}


int isLegalAction (Game g, action a){
    pID = g->playerID-1;
    int isLegal = TRUE;

    if(g->turnCounter == -1){ //no actions during terra nullius
        isLegal == FALSE;
    }else {
        if(a.actionCode == BUILD_CAMPUS){ //***COMPLETE

            x = getXCoord(g,a.destination);  
            y = getYCoord(g,a.destination);  
             
            //no arc path by player connecting to destination vertex
            
            if(x%2 == 0 && y% 2 ==0 || x%2!=0 && y%2!=0){
                //test horizontal paths
                pX = x*2+1;
                pY = y;
            }else{
                pX = x*2-1;
                pY = y;
            }
            if(g->board.paths[pY][pX] != g->playerID){
                isLegal = FALSE;
            }
            pX = x*2;
            if(g->board.paths[pY][pX] != g->playerID){
                isLegal = FALSE;
            }
            pY = y-1;
            if(g->board.paths[pY][pX] != g->playerID){
                isLegal = FALSE;
            }
            if(g->playRes.bps[pID] < 1 || g->playRes.bqn[pID] < 1 ||
                g->playRes.mj[pID] < 1 || g->playRes.mtv[pID] < 1 || 
                g->playRes.KPIs[pID] <1){
                    //insufficient resources
                    isLegal = FALSE;
            }
            if (getCampus(g,a.destination)!= VACANT_VERTEX){
                //occupied vertex
                isLegal = FALSE;
            }
            if(x<0 || x>5 || y<0 || y > 10){
                //off grid coords
                isLegal = FALSE;
            } 
            if( (y==0 && x==0) || (y==0 && x==1) || (y==0 && x==4) ||
               (y==0 && x==5) || (y==1 && x==0) || (y==1 && x==5) ||
               (y==9 && x==0) || (y==9 && x==5) || (y==10 && x==0) ||
               (y==10 && x==1) || (y==10 && x==4) || (y==10 && x==5) ){
                //vertices in the sea
                isLegal = FALSE;
            }

        } else if(a.actionCode == BUILD_GO8){ //***COMPLETE

            if(g->playRes.mj[pID]< 2 || g->playRes.mmoney[pID]< 3){
                //insufficient resources
                isLegal = FALSE;
            }

            if (getCampus(g,a.destination)!= getWhoseTurn(g) ){
                //occupied vertex by another player
                isLegal = FALSE;
            }


        } else if(a.actionCode == OBTAIN_ARC){ //***COMPLETE
            int pCoords = getPathCoord(g,a.destination);
            int pX = pCoords[1];
            int pY = pCoords[0]
            if(g->playRes.bps[pID]< 1 || g->playRes.bqn[pID]< 1){
                //insufficient resources
                isLegal = FALSE;
            }

            if(pX<0 || pX>10 || pY<0 || pY > 10){
                //off grid coords
                isLegal = FALSE;
            } 
            if(pX==1 || pX == 5 || pX == 9){ //horizontal path checking
                if(pY%2!=0){
                    isLegal = FALSE;
                }
            } else if(pX == 3 || pX == 7){
                if(pY%2==0){
                    isLegal = FALSE;
                }
            }

            if( (y == (0||9) && (x== (0 || 1 || 2 || 8 || 9 || 10) ) ) ||
                ( y==(1||8) && (x== (0||10))) || (y==10 && x!=5) ){
                //if path in sea
                isLegal  = FALSE;
            }

            if(g->board.paths[pCoords[0]][pCoords[1]] != VACANT_ARC){
                //check if spot vacant
                isLegal = FALSE;
            }

        }else if (a.actionCode==OBTAIN_PUBLICATION){ //***COMPLETE
            if(g->playRes.mj[pID]<1 || g->playRes.mtv[pID]<1 || 
                g->playRes.mmoney[pID]<1){

                isLegal = FALSE;

            }
           
        }else if (a.actionCode == OBTAIN_IP_PATENT){ //***COMPLETE
            if(g->playRes.mj[pID]<1 || g->playRes.mtv[pID]<1 || 
                g->playRes.mmoney[pID]<1){
                
                isLegal = FALSE;
            }


        } else if (a.actionCode == RETRAIN_STUDENTS){ //***COMPLETE
            rate = getExchangeRate(g,g->playerID,
                                    a.disciplineFrom,a.disciplineTo);
            //insufficient resources
            if (a.disciplineFrom == STUDENT_BPS){
                if(g->playRes.bps[pID]< rate){
                    isLegal = FALSE;
                }
            } else if (a.disciplineFrom == STUDENT_BQN) {
                if(g->playRes.bqn[pID]< rate){
                    isLegal = FALSE;
                }
            } else if (a.disciplineFrom == STUDENT_MJ) {
                if(g->playRes.mj[pID]< rate){
                    isLegal = FALSE;
                }
            } else if (a.disciplineFrom == STUDENT_MTV){
                if(g->playRes.mtv[pID]< rate){
                    isLegal = FALSE;
                }
            } else if (a.disciplineFrom == STUDENT_MMONEY) {
                if(g->playRes.mmoney[pID]< rate){
                    isLegal = FALSE;
                }
            } else if(a.disciplineFrom == STUDENT_THD){
                isLegal = FALSE; //thd can't be retrained
            }     
            
        }
    }

    return isLegal;
}


int getKPIpoints (Game g, int player){
    return g->playRes.KPIs[player-1];
}

int getARCs (Game g, int player){
    return g->playRes.ARCs[player-1];
}

int getGO8s (Game g, int player){
    return g->playRes.GO8s[player-1];
}

int getCampuses (Game g, int player){
    return g->playRes.campuses[player-1];
}

int getIPs (Game g, int player){
    return g->playRes.patents[player-1];
}

int getPublications (Game g, int player){
    return g->playRes.publications[player-1];
}


int getStudents (Game g, int player, int discipline){
        int value = 0;
        if (discipline == 0){
            value = g->playRes.thd[player-1];
        }else if (discipline == 1){
            value = g->playRes.bps[player-1];
        }else if (discipline == 2){
            value = g->playRes.bqn[player-1];
        }else if (discipline == 3){
            value = g->playRes.mj[player-1];
        }else if (discipline == 4){
            value = g->playRes.mtv[player-1];
        }else if (discipline == 5){
            value = g->playRes.mmoney[player-1];
        }
        return value;

}

int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo){
    pID = player -1;
    int exRate = DEFAULT_RATE;
    
    if (a.disciplineFrom == STUDENT_BPS){
        if(g->board.coord[9][1] == player || 
            g->board.coord[8][1] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;

        } 
    } else if (a.disciplineFrom == STUDENT_BQN) {
        if(g->board.coord[5][5] == player || 
            g->board.coord[6][5] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;

        } 
    } else if (a.disciplineFrom == STUDENT_MJ) {
        if(g->board.coord[9][4] == player || 
            g->board.coord[8][4] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;
        } 
    } else if (a.disciplineFrom == STUDENT_MTV){
        if(g->board.coord[1][1] == player || 
            g->board.coord[1][2] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;
        } 
    } else if (a.disciplineFrom == STUDENT_MMONEY) {
        if(g->board.coord[1][3] == player || 
            g->board.coord[1][4] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;
        } 
    }


    return exRate;
}

void populateMap(Game g){
    int y, x;
    int regCount =0;
    int vertCount = 0;
    y=2;  
    x=0;
    vertCount = 0;
    while(regCount<3){ //first column
        
        while(vertCount<6){ //populate y coords
                g->board.region[regCount][vertCount][0]=y;
                g->board.region[regCount][vertCount+1][0]=y;
                vertCount+=2;
                y++; 
        }
        y--; 
            //y increments by 3 after the loop, but 
            // next g->board.region's vertex is an increment by 2 only
            // therefore decrease y by 1
        vertCount = 0;
            while(vertCount<6){ //populate x coords
            g->board.region[regCount][vertCount][1]=x;
            g->board.region[regCount][vertCount+1][1]=x+1;
            vertCount+=2;

        }
        vertCount = 0;
         //move to next g->board.region below it
        regCount++;
    }

    y=1;
    x=1;
    vertCount = 0;
    while(regCount<7){ //second column
        while(vertCount<6){
                g->board.region[regCount][vertCount][0]=y;
                g->board.region[regCount][vertCount+1][0]=y;
                y++; 
                vertCount+=2;
        }
        y--;

        vertCount = 0;
            while(vertCount<6){
            g->board.region[regCount][vertCount][1]=x;
            g->board.region[regCount][vertCount+1][1]=x+1;
            vertCount+=2;
        }
        vertCount = 0;
        regCount++;
    }

    y=0;
    x=2;
    vertCount = 0;
    while(regCount<12){ //third column
        while(vertCount<6){
                g->board.region[regCount][vertCount][0]=y;
                g->board.region[regCount][vertCount+1][0]=y;
                y++; 
                vertCount+=2;
        }
        y--;

        vertCount = 0;
            while(vertCount<6){
            g->board.region[regCount][vertCount][1]=x;
            g->board.region[regCount][vertCount+1][1]=x+1;
            vertCount+=2;
        }
        vertCount = 0;
        regCount++;
    }

    y=1;
    x=3;
    vertCount = 0;
    while(regCount<16){ //fourth column
        while(vertCount<6){
                g->board.region[regCount][vertCount][0]=y;
                g->board.region[regCount][vertCount+1][0]=y;
                y++; 
                vertCount+=2;
        }
        y--;

        vertCount = 0;
            while(vertCount<6){
            g->board.region[regCount][vertCount][1]=x;
            g->board.region[regCount][vertCount+1][1]=x+1;
            vertCount+=2;
        }
        vertCount = 0;

        regCount++;
    }

    y=2;
    x=4;
    vertCount = 0;
    while(regCount<19){ //second column
        while(vertCount<6){
                g->board.region[regCount][vertCount][0]=y;
                g->board.region[regCount][vertCount+1][0]=y;
                y++; 
                vertCount+=2;
        }

        y--;

        vertCount = 0;
            while(vertCount<6){
            g->board.region[regCount][vertCount][1]=x;
            g->board.region[regCount][vertCount+1][1]=x+1;
            vertCount+=2;
        }
        vertCount = 0;
        regCount++;
    }

}

void populateCoords (Game g) {
    int y;
    int x;
    
    while (y < BOARD_HEIGHT) {
        while (x < BOARD_WIDTH) {
        
        // The starting players' campuses
        if ( (y == 0 && x == 2) || (y == 10 && x == 3) ) {
            g->board.coord[y][x] = CAMPUS_A;
        } else if ( (y == 0 && x == 3) || (y == 8 && x == 5) ) {
            g->board.coord[y][x] = CAMPUS_B;
        } else if ( (y == 2 && x == 5) || (y == 8 && x == 0) ) {
            g->board.coord[y][x] = CAMPUS_C;
        
        // These are the vertices which are located in the 'Ocean'
        } else if ( (y == 0 && x == 0 ) || (y == 0 && x == 1) || (y == 0 && x == 4)
                    || (y == 0 && x == 5) || (y == 1 && x == 0) || (y == 1 && x == 5)
                    || (y == 9 && x == 0) || (y == 9 && x == 5) || (y == 10&& x == 0)
                    || (y == 10&& x == 1) || (y == 10&& x == 4) || (y == 10&& x == 5) {
                    
            g->board.coord[y][x] = -1;
                    
        
        } else {
            g->board.coord[y][x] = VACANT;
        }
        
        
        x++;
        }
    
    y++;
    }
}
    
    
void disposeGame (Game g) {
    free(g);
}   
