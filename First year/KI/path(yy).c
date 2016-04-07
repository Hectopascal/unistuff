
#define INITIAL_Y 0
#define INITIAL_X 2

typedef struct _board {
    
    int diceScore;
    int disciplines[NUM_REGIONS];
    int diceValues[NUM_REGIONS];
    int vertex [11][12];
	coord direction;
} board;

typedef struct _coord {
    int y[6]= {1,1,0,-1,-1,0};
    int x[6]= {1,-1,-1,-1,1,1};
}coord;


int getCampus(Game g, path pathToVertex){
    i=0;
    y=INITIAL_Y; 
    x=INITIAL_X;
    dY=0;
    dX=0;
    campus=0;
    while(pathtoVertex[i]!= 0){
        if(pathtoVertex[i]=='R') { 
            //right
            if(dX==5){
                dX = 0;
                dY = 0;
            } else{
                dX +=1;
                dY +=1;
            }
        } else if(pathtoVertex[i]=='L') { 
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
        
        x += g->board.directions[dX];
        y += g->board.directions[dY];
        i++;
    }
    campus = vertex[y][x];
    return campus;

}

