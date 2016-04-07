
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

    g->playRes.GO8[0] = 0;
    g->playRes.GO8[1] = 0;
    g->playRes.GO8[2] = 0;

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
    
    g->vectors.y = Y_COORDS;
    g->vectors.x = X_COORDS;
    
    
    
    
    return g;
}
