#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

#define PATH_NUM 11
#define BOARD_HEIGHT 11
#define BOARD_WIDTH 6

#define VERTEX_PER_REGION 6
#define NUMBER_OF_DIMENSIONS 2

#define DEFAULT_RATE 3

#define INITIAL_Y 0
#define INITIAL_X 2

#define Y_VALUE 0
#define X_VALUE 1
#define DIRECTN 2
#define VERTICAL 0
#define HORIZONTAL 1
typedef struct _pathVectors {
    int y[6];
    int x[6];
} pathVectors;

typedef struct _gameBoard {
    int disciplines[NUM_REGIONS];
    int diceValues[NUM_REGIONS];
	int coord[BOARD_HEIGHT][BOARD_WIDTH];
	int region[NUM_REGIONS][VERTEX_PER_REGION][NUMBER_OF_DIMENSIONS];
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
int getXCoord(Game g, int pathToVertex[]);
int getYCoord(Game g, int pathToVertex[]);
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
    g->playRes.mmoney[1] = 1;
    g->playRes.mmoney[2] = 1;
    
    g->playRes.campuses[0] = 2;
    g->playRes.campuses[1] = 2;
    g->playRes.campuses[2] = 2;

    g->playRes.ARCs[0] = 0;
    g->playRes.ARCs[1] = 0;
    g->playRes.ARCs[2] = 0;

    g->playRes.GO8s[0] = 0;
    g->playRes.GO8s[1] = 0;
    g->playRes.GO8s[2] = 0;

    g->playRes.publications[0] = 0;
    g->playRes.publications[1] = 0;
    g->playRes.publications[2] = 0;

    g->playRes.patents[0] = 0;
    g->playRes.patents[1] = 0;
    g->playRes.patents[2] = 0;

    g->playRes.KPIs[0] = 20;
    g->playRes.KPIs[1] = 20;
    g->playRes.KPIs[2] = 20;

    g->playerID = NO_ONE;
    
    //#define Y_COORDS {1,1,0,-1,-1,0} 
	//#define X_COORDS {0,0,-1,0,0,1} 
    g->vectors.y[0] = 1;
    g->vectors.y[1] = 1; 
    g->vectors.y[2] = 0;
    g->vectors.y[3] = -1; 
    g->vectors.y[4] = -1;
    g->vectors.y[5] = 0; 
    
    g->vectors.x[0] = 0;
    g->vectors.x[1] = 0; 
    g->vectors.x[2] = -1;
    g->vectors.x[3] = 0; 
    g->vectors.x[4] = 0;
    g->vectors.x[5] = 1; 
    
    
    
    
    return g;
}


void makeAction (Game g, action a){
    int pID = g->playerID-1;
    int x = 0;
    int y = 0;
    int dest[PATH_LIMIT+1]={0};
    int i = 0;
    while(a.destination[i] != 0){
        dest[i] = a.destination[i];
        i++;
    }

    if(a.actionCode == BUILD_CAMPUS){ 

        x = getXCoord(g,dest);  
        y = getYCoord(g,dest);  
        g->board.coord[x][y] = g->playerID;
        //change vertex status to occupied
        
        g->playRes.bps[pID]--;
        g->playRes.bqn[pID]--;
        g->playRes.mj[pID]--;
        g->playRes.mtv[pID]--;

        g->playRes.campuses[pID]++;
        g->playRes.KPIs[pID]+=10;

    } else if(a.actionCode==BUILD_GO8){ 
        x = getXCoord(g,dest);  
        y = getYCoord(g,dest);  
        g->board.coord[x][y] = g->playerID + 3;


        g->playRes.mj[pID]-= 2;
        g->playRes.mmoney[pID]-= 3;
        g->playRes.campuses[pID]--;

        g->playRes.KPIs[pID]+=10;
        g->playRes.GO8s[pID]++;        

    } else if(a.actionCode == OBTAIN_ARC){ 

        int mostArcs = getMostARCs(g);
        int *pCoords = getPathCoord(g,a.destination);

        g->board.paths[pCoords[0]][pCoords[1]] = g->playerID;

        g->playRes.bps[pID]--;
        g->playRes.bqn[pID]--;

        g->playRes.ARCs[pID]++;
        g->playRes.KPIs[pID]+=2;

        if(getMostARCs(g)!=mostArcs && mostArcs != 0){
                printf("MOST ARCS %d\n", mostArcs);
                g->playRes.KPIs[mostArcs-1]-=10;
        }
        if(getMostARCs(g) == g->playerID){ 
            g->playRes.KPIs[pID]+=10;
            
        }

        free(pCoords);

        x=0;
        y=0;
        while(y<PATH_NUM){
            x=0;
            while(x<PATH_NUM){
                printf("%d ", g->board.paths[y][x]);
                x++;
            }
            printf("\n");
            y++;
        }

    } else if (a.actionCode==OBTAIN_PUBLICATION){  
        int mostPubs = getMostPublications(g); //find player w most pubs

        
        g->playRes.publications[pID]++; 

        if(getMostPublications(g)!= mostPubs && mostPubs !=0){
            g->playRes.KPIs[mostPubs-1]-=10;
        }
        if(getMostPublications(g) == g->playerID){ 
        //if after pub increase current player has most pubs, add 10 to KPI 
        //and take 10 from previous player w most pubs
            g->playRes.KPIs[pID]+=10;
            
        }

    } else if (a.actionCode == OBTAIN_IP_PATENT){
        g->playRes.patents[pID]++;

        g->playRes.mj[pID]--;
        g->playRes.mtv[pID]--;
        g->playRes.mmoney[pID]--;

        g->playRes.KPIs[pID]+=10;

    } else if (a.actionCode == RETRAIN_STUDENTS){ 
        int rate = getExchangeRate(g,g->playerID,a.disciplineFrom,
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
    
    int xCoord = 0;
    int yCoord = 0;
    
    regionID = 0;

	while (regionID < NUM_REGIONS) {
	// What regions have the same dice value as diceScore?

		if (diceScore == g->board.diceValues[regionID]) {
			vertex = 0;
			// Which vertexes are attached to this region?    	
			while (vertex < VERTEX_PER_REGION) {
			     
                yCoord = g->board.region[regionID][vertex][Y_VALUE];
                xCoord = g->board.region[regionID][vertex][X_VALUE];


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
						g->playRes.mtv[UNI_B-1]++;
						if (g->board.coord[yCoord][xCoord] == GO8_B) {
							g->playRes.mtv[UNI_B-1]++;
						}
					} else if(g->board.coord[yCoord][xCoord] == CAMPUS_C ||g->board.coord[yCoord][xCoord] == GO8_C ) {
						g->playRes.mtv[UNI_C-1]++;
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
			    vertex++;	
			}
			
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

int getMostARCs (Game g){
    int mostArcs = NO_ONE;
    int i = 0;
    int max = 0;
    int maxCount = 0;

    while(i<NUM_UNIS){
        if(g->playRes.ARCs[i]>max){
            max = g->playRes.ARCs[i];
            mostArcs = i+1;
        }
        i++;
    } //find max Arcs first
    i = 0; //reset i to use as counter again
    printf("A  %d\n",g->playRes.ARCs[0]);
    printf("B  %d\n",g->playRes.ARCs[1]);
    printf("C  %d\n",g->playRes.ARCs[2]);
    printf("%d\n",max);

    while(i<NUM_UNIS){
        if(g->playRes.ARCs[i]==max){
            maxCount++;
        }
        i++;
    } //see how many unis have maximum

    if(maxCount > 1){
        mostArcs = NO_ONE;
    } //if more than 1 uni with max, no one has mostArcs
    printf("getmostarcs  %d\n",mostArcs);

    return mostArcs;

}


int getMostPublications ( Game g){
    int mostPubs = NO_ONE;
    int i = 0;
    int max = 0;
    int maxCount = 0;

    while(i<NUM_UNIS){
        if(g->playRes.publications[i]>max){
            max = g->playRes.publications[i];
            mostPubs = i+1;
        }
        i++;
    } //find max Arcs first

    i = 0; //reset i to use as counter again
    while(i<NUM_UNIS){
        if(g->playRes.publications[i]==max){
            maxCount++;
        }
        i++;
    } //see how many unis have maximum

    if(maxCount > 1){
        mostPubs = NO_ONE;
    } //if more than 1 uni with max, no one has mostArcs

    return mostPubs;

}

int getTurnNumber(Game g){
    return g->turnCounter;

}

int getWhoseTurn(Game g){
    g->playerID = g->turnCounter % 3 +1;
    return g->playerID;
}


int getXCoord(Game g, int pathToVertex[]){
    int i=0;
    int x=INITIAL_X;
    int dX=0;
    while(pathToVertex[i]!= 0){
        if(pathToVertex[i]=='R') { 
            //right
            if(dX==5){
                dX = 0;
            } else{
                dX +=1;
            }
        } else if(pathToVertex[i]=='L') { 
            //left
            if(dX==0){
                dX = 5;
            }else {
                dX -=1;
            }
        } else { //back
            if(dX<=2){
                dX+=3;
            } else{
                dX-=3;
            }     
        }
        
        x += g->vectors.x[dX];
        i++;
    }
    return x;
}


int getYCoord(Game g, int pathToVertex[]){
    int i=0;
    int y=INITIAL_Y;
    int dY=0;
    while(pathToVertex[i]!= 0){
        if(pathToVertex[i]=='R') { 
            //right
            if(dY==5){
                dY = 0;
            } else{
                dY +=1;
            }
        } else if(pathToVertex[i]=='L') { 
            //left
            if(dY==0){
                dY = 5;
            }else {
                dY -=1;
            }
        } else { //back
            if(dY<=2){
                dY+=3;
            } else{
                dY-=3;
            }     
        }
        
        y += g->vectors.y[dY];
        i++;
    }
    return y;
}


int *getPathCoord(Game g, path pathToEdge){
    int prevY=0;
    int prevX = 0; 
    int *pathcoords= malloc(sizeof(int)*10);
    //prevY and prevX is second last vertex coordinate
    // --> needed to find path btw last two points
    //pX and pY is coords of paths

    int direction;
    //int path;

    int i=0;
    int y=INITIAL_Y; 
    int x=INITIAL_X;
    int dY=0;
    int dX=0;
    int pX,pY;
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
            if(dX<=2){
                dX+=3;
                dY+=3;
            } else{
                dX-=3;
                dY-=3;
            }     
        }

        prevX = x;
        prevY = y;
        x += g->vectors.x[dX];
        y += g->vectors.y[dY];
        i++;
    }
    printf("x=%d,y=%d\n",x,y );
    direction = pathDirection(prevX, x, prevY, y);
    printf("direction = %d\n", direction);
    if(direction == VERTICAL){
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
        if((x % 2 ==0 && y % 2 == 0) ||
            (x % 2 !=0 && y % 2 != 0)) {
            pX = x*2 + 1; //path right of vertex
            pY = y;
            printf("right\n");
        } else{
            pX = 2*x - 1; //path left of vertex
            pY = y;
            printf("left\n");
        }
    }
    pathcoords[Y_VALUE] = pY;
    pathcoords[X_VALUE] = pX;
    pathcoords[DIRECTN] = direction;

    return pathcoords;
}




int getCampus(Game g, path pathToVertex){
    int campus;
    int dest[PATH_LIMIT+1]={0};
    int i = 0;
    while(pathToVertex[i] != 0){
        dest[i] = pathToVertex[i];
        i++;
    }
    int x = getXCoord(g,dest);
    int y = getYCoord(g,dest);

    campus = g->board.coord[y][x];
    return campus;

}

int testCampus(Game g, int destination[]){
    int campus;
    int x = getXCoord(g,destination);
    int y = getYCoord(g,destination);

    campus = g->board.coord[y][x];
    return campus;

} 
int getARC(Game g, path pathToEdge){
    int path;
	
	int *pCoord = getPathCoord(g, pathToEdge);
	

    path = g->board.paths[pCoord[0]][pCoord[1]];
    free(pCoord);
    
    return path;
}

int pathDirection(int x1, int x, int y1, int y){
    int orientation;
    if(x1 == x){
        //same x-coords; vertical path
        orientation = VERTICAL;
    } else {
        //same y-coords; horizontal path
        orientation = HORIZONTAL;
    }
    return orientation;
}


int isLegalAction (Game g, action a){
    int pID = g->playerID-1;
    int player = g->playerID;
    int isLegal = TRUE;
    int x,y,pX,pY;
    int dest[PATH_LIMIT+1]={0};
    int i = 0;
    while(a.destination[i] != 0){
        dest[i] = a.destination[i];
        i++;
    }
    if(g->turnCounter == -1){ //no actions during terra nullius
        isLegal = FALSE;
    }else {
        if(a.actionCode == BUILD_CAMPUS){ 
            x = getXCoord(g,dest);  
            y = getYCoord(g,dest);  
            
            //no arc path by player connecting to destination vertex
            if((x%2 == 0 && y% 2 ==0 )|| (x%2!=0 && y%2!=0)){
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

            //--------------------------next test:
            //campuses can't be on adjacent vertexes
            i = 0;
            while(a.destination[i] != 0){
                dest[i] = a.destination[i];
                i++;
            }
            dest[i+1] = 0;

            dest[i] = 'R';
            if(testCampus(g,dest)!= VACANT_VERTEX){
                isLegal = FALSE;
            }
            dest[i] = 'L';
            if(testCampus(g,dest)!= VACANT_VERTEX){
                isLegal = FALSE;
            }
            a.destination[i] = 'B';
            if(testCampus(g,dest)!= VACANT_VERTEX){
                isLegal = FALSE;
            } 
            //--------------------------next test:
            //insufficient resources
            if(g->playRes.bps[pID] < 1 || g->playRes.bqn[pID] < 1 ||
                g->playRes.mj[pID] < 1 || g->playRes.mtv[pID] < 1 || 
                g->playRes.KPIs[pID] <1){
                    isLegal = FALSE;
            }

            //--------------------------next test:
            //occupied vertex
            if (getCampus(g,a.destination)!= VACANT_VERTEX){
                isLegal = FALSE;
            }
            if(x<0 || x>5 || y<0 || y > 10){
                //off grid coords
                isLegal = FALSE;
            } 

            //--------------------------next test:
            //vertices in the sea
            if( (y==0 && x==0) || (y==0 && x==1) || (y==0 && x==4) ||
               (y==0 && x==5) || (y==1 && x==0) || (y==1 && x==5) ||
               (y==9 && x==0) || (y==9 && x==5) || (y==10 && x==0) ||
               (y==10 && x==1) || (y==10 && x==4) || (y==10 && x==5) ){

                isLegal = FALSE;
            }

        } else if(a.actionCode == BUILD_GO8){ 

            //--------------------------next test:
            //insufficient resources
            if(g->playRes.mj[pID]< 2 || g->playRes.mmoney[pID]< 3){
                
                isLegal = FALSE;
            }
            //--------------------------next test:
            //occupied vertex by another player

            if (getCampus(g,a.destination)!= getWhoseTurn(g) ){
                isLegal = FALSE;
            }


        } else if(a.actionCode == OBTAIN_ARC){ 
            int *pCoords = getPathCoord(g,a.destination);
            pX = pCoords[X_VALUE];
            pY = pCoords[Y_VALUE];
            x = getXCoord(g,dest);
            y = getYCoord(g,dest);

            printf("pX = %d, pY = %d\n",pX,pY);
            //--------------------------next test:
            //insufficient resources
            if(g->playRes.bps[pID]< 1 || g->playRes.bqn[pID]< 1){
                printf("insufficient resources\n");
                isLegal = FALSE;
            }

            //--------------------------next test:
            //no connecting campus/arcs

            if(g->board.paths[pY][pX+1] != player && g->board.paths[pY][pX-1] != player &&
                g->board.paths[pY+1][pX] != player && g->board.paths[pY-1][pX] != player &&
                g->board.paths[pY+1][pX+1] != player && g->board.paths[pY-1][pX-1] != player &&
                g->board.paths[pY+1][pX-1] != player && g->board.paths[pY-1][pX+1] != player){
                //no paths connecting
                printf("NO PATHS\n");
                if (pCoords[DIRECTN]==VERTICAL){
                    //check vertex above and below for vertical
                    if((g->board.coord[pY][pX/2]!=player && g->board.coord[pY][pX/2]!=(player+3)) && 
                        (g->board.coord[pY+1][pX/2]!=player && g->board.coord[pY+1][pX/2]!=(player+3))){
                        isLegal = FALSE;
                    }
                    
                    printf("BOOM VERT\n");
                } else {
                    if((g->board.coord[pY][(pX-1)/2]!= player && g->board.coord[pY][(pX-1)/2] !=(player+3)) && 
                        (g->board.coord[pY][(pX+1)/2]!=player && g->board.coord[pY][(pX+1)/2] !=(player+3))){
                        isLegal = FALSE;
                    }
                    printf("direct %d, indirect %d\n", g->board.coord[0][2],g->board.coord[pY][(pX-1)/2]);
                    printf("pX %d, pY %d\n",pX,pY);
                    //check vertex left and right for horizontal
                }


            }

            //--------------------------next test:
            //off grid coords
            if(pX<0 || pX>10 || pY<0 || pY > 10){
                printf("off grid\n");
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
            //--------------------------next test:
            //if path in sea
            if( (pY == 0 && (pX== 0 ||pX== 1 ||pX== 2 || pX==3 
                ||pX==7|| pX== 8 ||pX== 9 ||pX== 10 ) ) ||
               (pY==1 && (pX==1 ||pX== 0||pX==9||pX==10)) || 
               (pY==8&&(pX==0||pX==10))|| 
               (pY==9&&(pX==1||pX==2||pX==0|| pX==8 || pX==9 ||pX==10))||
               (pY==10 && pX!=5) ){
                printf("in sea\n");


                isLegal  = FALSE;
            }
            //--------------------------next test:
            //check if spot vacant
            if(g->board.paths[pY][pX] != VACANT_ARC){
                
                printf("occupied by %d\n",g->board.paths[pCoords[0]][pCoords[1]] );
                printf("Y=%d,X=%d\n",pCoords[0],pCoords[1] );



                x=0;
                y=0;
                while(y<PATH_NUM){
                    x=0;
                    while(x<PATH_NUM){
                        printf("%d ", g->board.paths[y][x]);
                        x++;
                    }
                    printf("\n");
                    y++;
                }

                isLegal = FALSE;
            }

        }else if (a.actionCode==OBTAIN_PUBLICATION){ 
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
            int rate = getExchangeRate(g,g->playerID,
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
            
        }else{
            isLegal = TRUE;
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
    int exRate = DEFAULT_RATE;
    
    if (disciplineFrom == STUDENT_BPS){
        if(g->board.coord[9][1] == player || 
            g->board.coord[8][1] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;

        } 
    } else if (disciplineFrom == STUDENT_BQN) {
        if(g->board.coord[5][5] == player || 
            g->board.coord[6][5] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;

        } 
    } else if (disciplineFrom == STUDENT_MJ) {
        if(g->board.coord[9][4] == player || 
            g->board.coord[8][4] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;
        } 
    } else if (disciplineFrom == STUDENT_MTV){
        if(g->board.coord[1][1] == player || 
            g->board.coord[1][2] == player){ //red bqs
            //checks if retraining centre is owned by player
            exRate = 2;
        } 
    } else if (disciplineFrom == STUDENT_MMONEY) {
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
    int vertCount;
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
	int y = 0;
	int x;
    int pX = 0;
    int pY = 0;
	//vertex grid
	while (y < BOARD_HEIGHT) {
		
		x = 0;
		
		while (x < BOARD_WIDTH) {
		
		// The starting players' campuses
		if ( (y == 0 && x == 2) || (y == 10 && x == 3) ) {
			g->board.coord[y][x] = CAMPUS_A;
		} else if ( (y == 3 && x == 0) || (y == 7 && x == 5) ) {
			g->board.coord[y][x] = CAMPUS_B;
		} else if ( (y == 2 && x == 5) || (y == 8 && x == 0) ) {
			g->board.coord[y][x] = CAMPUS_C;
		
		// These are the vertices which are located in the 'Ocean'
		} else if ( (y == 0 && x == 0 ) || (y == 0 && x == 1) || (y == 0 && x == 4)
					|| (y == 0 && x == 5) || (y == 1 && x == 0) || (y == 1 && x == 5)
					|| (y == 9 && x == 0) || (y == 9 && x == 5) || (y == 10&& x == 0)
					|| (y == 10&& x == 1) || (y == 10&& x == 4) || (y == 10&& x == 5) ) {
					
			g->board.coord[y][x] = -1;
					
		
		} else {
			g->board.coord[y][x] = VACANT_VERTEX;
		}
		
		
		x++;
		}
	
	y++;
	}

    //path grid
    while (pY < PATH_NUM) {
        
        pX = 0;
        
        while (pX < PATH_NUM) {
            //paths in ocean
            if ( (pY == 0 && (pX>6 || pX<4)) || 
                (pY==1 &&(pX<2||pX>8)) || (pY==8 && (pX==0||pX==10))||
                (pY==9 &&(pX<3||pX>7)) || (pY==10 && pX!=5) ) {
                    
            g->board.paths[pY][pX] = -1;        
            
            } else {
                g->board.paths[pY][pX] = VACANT_VERTEX;
            }
        
        
        pX++;
        }
    
    pY++;
    }
        x=0;
        y=0;
        while(y<PATH_NUM){
            x=0;
            while(x<PATH_NUM){
                printf("%d ", g->board.paths[y][x]);
                x++;
            }
            printf("\n");
            y++;
        }
}

	
	
void disposeGame (Game g) {
	free(g);
}	
