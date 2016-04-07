#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Game.h"
 
 
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,\
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV,\
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN,\
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ,\
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
 
int main (int argc, char *argv[]) {
     
    int dispArray[NUM_REGIONS] = DEFAULT_DISCIPLINES;
    int diceArray[NUM_REGIONS] = DEFAULT_DICE;
 
    Game g = newGame(dispArray, diceArray);
	
    assert(getTurnNumber(g)==-1);
    assert(getWhoseTurn(g)==NO_ONE);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 0);
    assert(getARCs(g, UNI_B) == 0);
    assert(getARCs(g, UNI_C) == 0);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 20);
    assert(getKPIpoints(g, UNI_B) == 20);
    assert(getKPIpoints(g, UNI_C) == 20);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
     

    throwDice(g, 11);
     
    assert(getTurnNumber(g)==0);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 0);
    assert(getARCs(g, UNI_B) == 0);
    assert(getARCs(g, UNI_C) == 0);
    assert(getMostARCs(g)==NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 20);
    assert(getKPIpoints(g, UNI_B) == 20);
    assert(getKPIpoints(g, UNI_C) == 20);
		
	assert(getStudents(g, UNI_A, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0); 
		
	assert(getStudents(g, UNI_B, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);

	action a;
    a.actionCode = OBTAIN_ARC;
    a.destination[0] = 'L';
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 2);
	assert(getARCs(g, UNI_A) == 1);
	assert(getKPIpoints(g, UNI_A) == 32);
	assert(getMostARCs(g) == UNI_A);


    throwDice(g, 8);

    assert(getTurnNumber(g)==1);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 1);
    assert(getARCs(g, UNI_B) == 0);
    assert(getARCs(g, UNI_C) == 0);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 32);
    assert(getKPIpoints(g, UNI_B) == 20);
    assert(getKPIpoints(g, UNI_C) == 20);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
   
	
    a.actionCode = OBTAIN_ARC;
    a.destination[0] = 'R'; 
    a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	a.destination[3] = 'R'; 
	a.destination[4] = 'L'; 
    a.destination[5] = 0;

	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 2);
	assert(getARCs(g, UNI_B) == 1);
	assert(getKPIpoints(g, UNI_B) == 22);
    assert(getMostARCs(g) == NO_ONE);
    
	
	throwDice(g, 9);
     
     
    assert(getTurnNumber(g)==2);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 1);
    assert(getARCs(g, UNI_B) == 1);
    assert(getARCs(g, UNI_C) == 0);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 22);
    assert(getKPIpoints(g, UNI_B) == 22);
    assert(getKPIpoints(g, UNI_C) == 20);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
     
    
    a.actionCode = OBTAIN_ARC;
    a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	a.destination[3] = 'R'; 
    a.destination[4] = 'L';
    a.destination[5] = 0;
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
	assert(getARCs(g, UNI_C) == 1);
	assert(getKPIpoints(g, UNI_C) == 22);

	
	
	throwDice(g, 5);
     
	 
    assert(getTurnNumber(g)==3);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 1);
    assert(getARCs(g, UNI_B) == 1);
    assert(getARCs(g, UNI_C) == 1);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 22);
    assert(getKPIpoints(g, UNI_B) == 22);
    assert(getKPIpoints(g, UNI_C) == 22);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 3);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
     
	
    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'L'; 
    a.destination[1] = 'L'; 
    a.destination[2] = 0; 
	assert(isLegalAction (g, a) == FALSE);
	a.destination[0] = 'L'; 
    a.destination[1] = 'R'; 
    a.destination[2] = 0; 
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 1);
	assert(getARCs(g, UNI_A) == 2);
    assert(getMostARCs(g) == UNI_A);

	assert(getKPIpoints(g, UNI_A) == 34);


	
	throwDice(g, 5);
     
	 
    assert(getTurnNumber(g)==4);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 2);
    assert(getARCs(g, UNI_B) == 1);
    assert(getARCs(g, UNI_C) == 1);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 34);
    assert(getKPIpoints(g, UNI_B) == 22);
    assert(getKPIpoints(g, UNI_C) == 22);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 4);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 3);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
     
	
    a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_BPS;
    a.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
	
	
    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'R'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
    a.destination[3] = 'R'; 
    a.destination[4] = 0; 
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
	assert(getARCs(g, UNI_B) == 2);
	assert(getKPIpoints(g, UNI_B) == 24);
	
	
	
	throwDice(g, 5);
     
	 
    assert(getTurnNumber(g)==5);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 2);
    assert(getARCs(g, UNI_B) == 2);
    assert(getARCs(g, UNI_C) == 1);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 24);
    assert(getKPIpoints(g, UNI_B) == 24);
    assert(getKPIpoints(g, UNI_C) == 22);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
     
	
    a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_BPS;
    a.disciplineTo = STUDENT_MMONEY;
	assert(isLegalAction (g, a) == FALSE);

    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
    a.destination[3] = 'R'; 
    a.destination[4] = 0; 
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_C, STUDENT_BQN)== 1);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
	assert(getARCs(g, UNI_C) == 2);
	assert(getKPIpoints(g, UNI_C) == 24);

	
	
	throwDice(g, 8);
     
	 
    assert(getTurnNumber(g)==6);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 2);
    assert(getARCs(g, UNI_B) == 2);
    assert(getARCs(g, UNI_C) == 2);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
    
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 24);
    assert(getKPIpoints(g, UNI_B) == 24);
    assert(getKPIpoints(g, UNI_C) == 24);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
    a.destination[2] = 'R'; 
    a.destination[3] = 0; 
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_A, STUDENT_BQN)== 0);
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
	assert(getARCs(g, UNI_A) == 3);
	assert(getKPIpoints(g, UNI_A) == 36);
	assert(getMostARCs(g) == UNI_A);
	
	
	throwDice(g, 5);
     
	 
    assert(getTurnNumber(g)==7);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 3);
    assert(getARCs(g, UNI_B) == 2);
    assert(getARCs(g, UNI_C) == 2);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 36);
    assert(getKPIpoints(g, UNI_B) == 24);
    assert(getKPIpoints(g, UNI_C) == 24);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 2);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'R'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	a.destination[3] = 'L'; 
	assert(isLegalAction (g, a) == TRUE);    
	makeAction(g, a);	
    assert(getStudents(g, UNI_B, STUDENT_BQN)== 1);
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
	assert(getARCs(g, UNI_B) == 3);
	assert(getKPIpoints(g, UNI_B) == 26);
	assert(getMostARCs(g) == NO_ONE);
	
	
	throwDice(g, 4);
     
	 
    assert(getTurnNumber(g)==8);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 3);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 2);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 26);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 24);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	
	a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_MTV;
    a.disciplineTo = STUDENT_BPS;
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g,a);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 0);

    a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	a.destination[3] = 0; 
 
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_C, STUDENT_BQN)== 0);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
	assert(getARCs(g, UNI_C) == 3);
	assert(getKPIpoints(g, UNI_C) == 26);
	assert(getMostARCs(g) == NO_ONE);
	
	
	
	throwDice(g, 4);
     
	 
    assert(getTurnNumber(g)==9);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 2);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 3);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == NO_ONE);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 26);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 26);
     
    assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	a.actionCode = OBTAIN_ARC;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'R'; 
	a.destination[3] = 'L'; 
    a.destination[4] = 0; 

	assert(isLegalAction (g, a) == FALSE);


	a.actionCode = BUILD_CAMPUS;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'R'; 
	a.destination[3] = 'L'; 
    makeAction(g, a);
	assert(isLegalAction (g, a) == FALSE);

	
	/*
	throwDice(g, 8);
     
	 
    assert(getTurnNumber(g)==11);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 26);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 5);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
		
	a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_MJ;
    a.disciplineTo = STUDENT_MMONEY;
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
	
	
	throwDice(g, 8);
     
	 
    assert(getTurnNumber(g)==12);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 26);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	
	throwDice(g, 8);
     
	 
    assert(getTurnNumber(g)==13);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 26);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 4);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	
	
	throwDice(g, 4);
     
	 
    assert(getTurnNumber(g)==14);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 2);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 26);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 4);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	
	
	a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_MJ;
    a.disciplineTo = STUDENT_BPS;
    makeAction(g, a);
	assert(isLegalAction (g, a) == TRUE);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 1);
	
	
	a.actionCode = BUILD_CAMPUS;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	a.destination[3] = 'R'; 
	a.destination[4] = 'R'; 
	assert(isLegalAction (g, a) == FALSE);
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'L'; 
	assert(isLegalAction (g, a) == TRUE);

    makeAction(g, a);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
	assert(getCampuses(g, UNI_C) == 3);
	assert(getKPIpoints(g, UNI_C) == 36);
	
	
	throwDice(g, 6);
     
	 
    assert(getTurnNumber(g)==15);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	throwDice(g, 6);
     
	 
    assert(getTurnNumber(g)==16);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	

	throwDice(g, 6);
     
	 
    assert(getTurnNumber(g)==17);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 3);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	

	throwDice(g, 6);
     
	 
    assert(getTurnNumber(g)==18);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 4);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	

	a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_MJ;
    a.disciplineTo = STUDENT_MMONEY;
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 2);


	throwDice(g, 6);
     
	 
    assert(getTurnNumber(g)==19);
    assert(getWhoseTurn(g)==UNI_B);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);
	
	

	throwDice(g, 11);
     
	 
    assert(getTurnNumber(g)==20);
    assert(getWhoseTurn(g)==UNI_C);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);



	throwDice(g, 11);
     
	 
    assert(getTurnNumber(g)==21);
    assert(getWhoseTurn(g)==UNI_A);
     
    assert(getCampuses(g, UNI_A) == 3);
    assert(getCampuses(g, UNI_B) == 2);
    assert(getCampuses(g, UNI_C) == 3);
     
    assert(getARCs(g, UNI_A) == 4);
    assert(getARCs(g, UNI_B) == 3);
    assert(getARCs(g, UNI_C) == 3);
	assert(getMostARCs(g) == UNI_A);
     
    assert(getGO8s(g, UNI_A) == 0);
    assert(getGO8s(g, UNI_B) == 0);
    assert(getGO8s(g, UNI_C) == 0);
     
    assert(getIPs(g, UNI_A) == 0);
    assert(getIPs(g, UNI_B) == 0);
    assert(getIPs(g, UNI_C) == 0);
     
    assert(getPublications(g, UNI_A) == 0);
    assert(getPublications(g, UNI_B) == 0);
    assert(getPublications(g, UNI_C) == 0);
	assert(getMostPublications(g) == NO_ONE); 
     
    assert(getKPIpoints(g, UNI_A) == 38);
    assert(getKPIpoints(g, UNI_B) == 26);
    assert(getKPIpoints(g, UNI_C) == 36);
     
   	assert(getStudents(g, UNI_A, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_A, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 3);
    assert(getStudents(g, UNI_A, STUDENT_MJ) == 2);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_A, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_B, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_B, STUDENT_BQN) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MTV) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MJ) == 1);
    assert(getStudents(g, UNI_B, STUDENT_MMONEY) == 1);
    assert(getStudents(g, UNI_B, STUDENT_THD) == 0);
     
    assert(getStudents(g, UNI_C, STUDENT_BPS) == 0);
    assert(getStudents(g, UNI_C, STUDENT_BQN) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MTV) == 2);
    assert(getStudents(g, UNI_C, STUDENT_MJ) == 0);
    assert(getStudents(g, UNI_C, STUDENT_MMONEY) == 2);
    assert(getStudents(g, UNI_C, STUDENT_THD) == 0);


	a.actionCode = RETRAIN_STUDENTS;
    a.disciplineFrom = STUDENT_MTV;
    a.disciplineTo = STUDENT_MMONEY;
	assert(isLegalAction (g, a) == TRUE);
    makeAction(g, a);
    assert(getStudents(g, UNI_A, STUDENT_MTV) == 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 3);



    a.actionCode = BUILD_GO8;
	a.destination[0] = 'L'; 
	a.destination[1] = 'R'; 
	a.destination[2] = 'R'; 
	a.destination[3] = 'L'; 
    makeAction(g, a);
	assert(isLegalAction (g, a) == TRUE);
    assert(getStudents(g, UNI_A, STUDENT_MJ)== 0);
    assert(getStudents(g, UNI_A, STUDENT_MMONEY) == 0);
	assert(getGO8s(g, UNI_A) == 1);
	assert(getCampuses(g, UNI_A) == 2);
	assert(getKPIpoints(g, UNI_A) == 38);

	printf("All tests passed, you are awesome! Go hug a cat =^.^="); */
	
return EXIT_SUCCESS;
}
/*
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
            
} */

	
