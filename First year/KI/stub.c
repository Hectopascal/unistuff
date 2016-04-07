int getKPIpoints (Game g, int player){
    int kpi;
    kpi = g->playRes.KPIs[player-1];

    return kpi;
}

int getARCs (Game g, int player){
    int arc;
    arc = g->playRes.ARCs[player-1];

    return arc;
}


int getGO8s (Game g, int player){
    int grpEights;
    grphEights = g->playRes.GO8s[player-1];

    return grpEights;

}

int getCampuses (Game g, int player){
    int camps;
    camps = g->playRes.campuses[player-1];

    return camps;
}

int getIPs (Game g, int player){
    int patents;
    patents = g->playRes.patents[player-1];

    return patents;
}
int getPublications (Game g, int player){
    int pubs;
    pubs = g->playRes.publications[player-1];

    return pubs;
}
int getStudents (Game g, int player, int discipline){
    int students;
    
    if(discipline == 0){
        students = g->playRes.thd[player-1];
    }else if(discipline == 1){
        students = g->playRes.bps[player-1];    
    } else if(discipline == 2){
        students = g->playRes.bqn[player-1];    
    } else if(discipline == 3){
        students = g->playRes.mj[player-1];    
    } else if(discipline == 4){
        students = g->playRes.mty[player-1];    
    } else if(discipline == 5){
        students = g->playRes.mmoney[player-1];    
    }
    
    return students;
}















