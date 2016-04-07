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