#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Game-1.07.h"

/* TO DO LIST:
test LegalAction (e.g. no legal actions on turn -1)
test amount of resources are correct
exchange rate
idk lol what is computing
*/

void testKPIpoints(Game g);
void testBoardState(Game g, int*dispArray, int*diceArray);
void testTurnf(Game g, int turnNum);
void testInitial(Game g);

int main (int argc, char *argv[]) {
	
	int turnNum = -1;
	

	int dispArray[NUM_REGIONS] = DEFAULT_DISCIPLINES;
	int diceArray[DEFAULT_DICE] = DEFAULT_DICE;

	Game g = newGame(dispArray, diceArray);

	testBoardState(g, dispArray, diceArray);
	testKPIpoints(g);
	testTurnf(g, turnNum);
	testInitial(g);
	assert(getKPIpoints == 20);
	
	//
	int diceScore = 1;
	throwDice(g, diceScore);
	turnNum++;
	
	testBoardState
	testKPIpoints
	testTurnf(g, turnNum);
	testInitial(g);
	assert(getKPIpoints == 20);
	
	return EXIT_SUCCESS;
}
	
void testTurnf(Game g, int turnNum) {
	int currentPlayer = (turnNumber%NUM_UNIS + 1);
	assert(getWhoseTurn(g) = currentPlayer);
	assert(getTurnNumber(g) = turnNum);
}


void testKPIpoints(Game g) {
	
	printf ("Testing KPIpoints...\n");
	
	int player = UNI_A;
	
	while(player <= NUM_UNIS){
		
		int total = 0;
		int numARCs = getARCs(g, player);
		int numG08s = getG08s(g, player);
		int numCampuses = getCampuses (g, player);
		int numIPs = getIPs (g, player);
		int mostARC = FALSE;
		int mostPUB = FALSE;
	
		if (player == getMostARCS(g)) {
			mostARC = TRUE;
		}
	
		if (player == getMostPub(g)) {
			mostPub = TRUE;
		}
	
		total = 2*numARCs + 20*G08s + 2*numCampuses + 
				10*numIPs + 10*mostARC + 10*mostPub;
			
		assert (getKPIpoints (g, player) == total);
		player++;
		
		printf("Player %d: %d points.\n", player, total);
		
	}
			
}
	

void testBoardState(Game g, int *dispArray, int *diceArray) {
	
	printf ("Testing board state... ");
	
	int regionID = 0;
	while (regionID < NUM_REGIONS) {
		assert (getDiscipline(g, regionID) == dispArray[regionID]);
		assert (getDiceValue(g, regionID) == diceArray[regionID]);
		regionID++;
	}
	
	printf ("Passed\n");
}

void testInitial(Game g){
    int disc = STUDENT_THD;
    int player = UNI_A;
    int initial[6] = {0, 3, 3, 1, 1, 1};
    while(player<=NUM_UNIS){
        while(disc<= STUDENT_MMONEY){
        assert(getStudents(g, player, disc) == initial[disc]);
        disc++;
        }
        player++;
    }
}
    
    
void testExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {
    if(normaltrainingcenter){
        if (bps >= 3) {
        assert((ExchangeRate (g, player,  bps, mj) == TRUE)); 
        assert((ExchangeRate (g, player,  bps, bqn) == TRUE)); 
        assert((ExchangeRate (g, player,  bps, mtv) == TRUE));
        assert((ExchangeRate (g, player,  bps, mmoney) == TRUE)); 
        }
        if (bqn >= 3) {
        assert((ExchangeRate (g, player,  bqn, mj) == TRUE));
        assert((ExchangeRate (g, player,  bqn, bps) == TRUE)); 
        assert((ExchangeRate (g, player,  bqn, mtv) == TRUE));
        assert((ExchangeRate (g, player,  bqn, mmoney) == TRUE));
        }
        if (mj >= 3) {
        assert((ExchangeRate (g, player,  mj, bps) == TRUE)); 
        assert((ExchangeRate (g, player,  mj, bqn) == TRUE)); 
        assert((ExchangeRate (g, player,  mj, mtv) == TRUE)); 
        assert((ExchangeRate (g, player,  mj, mmoney) == TRUE)); 
        }
        if (mtv >= 3) {
        assert((ExchangeRate (g, player,  mtv, bps) == TRUE)); 
        assert((ExchangeRate (g, player,  mtv, bqn) == TRUE)); 
        assert((ExchangeRate (g, player,  mtv, mj) == TRUE)); 
        assert((ExchangeRate (g, player,  mtv, mmoney) == TRUE)); 
        }
        if (mmoney >= 3) {
        assert((ExchangeRate (g, player,  mmoney, mj) == TRUE)); 
        assert((ExchangeRate (g, player,  mmoney, bqn) == TRUE)); 
        assert((ExchangeRate (g, player,  mmoney, mtv) == TRUE)); 
        assert((ExchangeRate (g, player,  mmoney, bps) == TRUE)); 
        }
        player++;
    }
    
    // if (disciplineFrom >= 3 && disciplineTo != thd) {
    // assert((ExchangeRate (g, player,  disciplineFrom, disciplineTo) == TRUE)); } 
                            
}                     
                     
                     
void testStudents (Game g, int player, int discipline){
    if (discipline == 3){
        assert ((Students (g, player, discipline) == 3));
    }                     
}
    
void testPublications (Game g, int player){

}     
    
void testIPs (Game g, int player){
}
void testCampuses (Game g, int player){    
}
    
void testGO8s (Game g, int player){ 
}

void testARCs (Game g, int player){
}
void testARC(Game g, path pathToEdge){
}
void testCampus(Game g, path pathToVertex) {
}
void testWhoseTurn (Game g){
}
void testMostARCs (Game g){
}                     


