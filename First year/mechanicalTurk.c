/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define NUM_DISCIPLINES 6
#define CAMP_ONE 1
#define CAMP_TWO 2

int *discScan(discipline);
int buildFrom(int mj[],int player);

action decideAction (Game g) {
    action nextAction;

    int player = getWhoseTurn(g);
    int students[6]={0};
    /*int numTHD = getStudents(g, player, STUDENT_THD);
    int numBPS = getStudents(g, player, STUDENT_BPS);
    int numBQN = getStudents(g, player, STUDENT_BQN);
    int numMJ = getStudents(g, player, STUDENT_MJ);
    int numMTV = getStudents(g, player, STUDENT_MTV);
    int numMMONEY = getStudents(g, player, STUDENT_MMONEY);*/

    int arcs = getARCS(g,player);
    int campuses = getCampuses(g,player);
    int go8s = getGO8s(g,player);
    
    int counter; //multipurpose counter!
    int strlength; //technically another counter, but just for routes

    int buildFromTop; //Top and left
    int buildFromBottom=0; //bottom and right

    //starting campus locations
    int campusOnePath[PATH_LIMIT]={0}; 
    int campusTwoPath[PATH_LIMIT]={0};

    int *mjRegion = discScan(STUDENT_MJ); //find mj spots first
    int sizeMJ=0;

    counter = 1;
    while(mjRegion[counter]!=0){
        sizeMJ++;
    }
    counter = 0;
    while(students[counter]<NUM_DISCIPLINES){ //figure out resources
        students[counter]= getStudents(g,player, counter)
        counter++
    }


    if(students[STUDENT_BQN] >=1 && students[STUDENT_BPS] >= 1){
        //arcs
        counter=0;
        nextAction.actionCode = BUILD_ARC;

        if(player == UNI_A){ 
            strcpy(campusTwoPath,'RLRLRLRLRLL');

            
            counter=0;
            direction = buildFrom(player,mjRegion);



            if(direction == TWO){
                //start from player A bottom campus
                strcpy(nextAction.destination,campusTwoPath);


            }else{
                counter = 0;
                while(mjRegion[counter]<sizeMJ){
                    if(mjRegion[counter] == 12 || mjRegion[counter] == 13){
                        //build towards right side
                        nextAction.destination[0] = 'L';
                    } else{ //go left
                        nextAction.destination[0]='R';
                    }

                }

                while(isLegalAction!=TRUE){
                    if(){
                        //left vacant
                    } else if{
                        //right vacant
                    }else{
                        nextAction.actionCode = PASS;
                    }

                }

            }
            strlength = 0;
            while(nextAction.destination[length]!=0){
                length++;
            }
            if(nextAction.destination[length-1]=='L'){
                nextAction.destination[length]= 'R';

                if(isLegalAction(g,nextAction)==FALSE){
                    nextAction.destination = 'L';
                }


            } else{
                nextAction.destination[length]='L';
            }

        }else if (player == UNI_B){
            strcpy(campusOnePath,'RRLRL');
            strcpy(campusTwoPath,'RLLRLRRLLR');

        }else {

        }
    } else if (numMJ >= 1 && numMTV >= 1 && numMMONEY >=1) {
        //spinoff
        nextAction.actionCode = START_SPINOFF;
    
    }else if{
        //campus
    
    }else if{
        nextAction.actionCode = PASS;
    }


    if(isLegalAction(g,a)=FALSE){
        nextAction.actionCode = PASS;
    }

    return nextAction;
}

action playerA(Game g, action a){



    return a;
}
int buildFrom(int mj[],int player){
    int buildFromTop=0;
    int buildFromBottom=0;
    int counter = 0;
    int side;
    if(player == UNI_A){
        while(mjRegion[counter]<sizeMJ){
            //decides where to build arcs from
            if(mjRegion[counter] == 3 || mjRegion[counter] == 8 || 
                mjRegion[counter] == 12 ){
                buildFromTop+=2;
            } else if(mjRegion[counter]==6 || mjRegion[counter]==10|| 
                mjRegion[counter] == 15){
                buildFromBottom+=2;
            } else if(mjRegion[counter] == 0 ||
                mjRegion[counter] == 4 || mjRegion[counter] == 9 ||
                mjRegion[counter] == 13 || mjRegion[counter] == 16 ||
                mjRegion[counter] == 1){
                buildFromTop++;
            } else{
                buildFromBottom++;
            }
            counter++;
        }
        if(buildFromBottom > buildFromTop){
            side = CAMP_TWO;
        } else{
            side = CAMP_ONE;
        }

    } else if(player == UNI_B){
        while(mjRegion[counter]<sizeMJ){
            //decides where to build arcs from
            if(mjRegion[counter] == 3 || mjRegion[counter] == 4 || 
                mjRegion[counter] == 1 ){
                buildFromTop+=2;
            } else if(mjRegion[counter]==14 || mjRegion[counter]==17|| 
                mjRegion[counter] == 15){
                buildFromBottom+=2;
            } else if(mjRegion[counter] == 2 ||
                mjRegion[counter] == 6 || mjRegion[counter] == 9 ||
                mjRegion[counter] == 5 || mjRegion[counter] == 8 ||
                mjRegion[counter] == 7){
                buildFromTop++;
            } else{
                buildFromBottom++;
            }
            counter++;
        }
        if(buildFromBottom > buildFromTop){
            side = CAMP_TWO;
        } else{
            side = CAMP_ONE;
        }

    }else{
        while(mjRegion[counter]<sizeMJ){
            //decides where to build arcs from
            if(mjRegion[counter] == 13 || mjRegion[counter] == 17 || 
                mjRegion[counter] == 12 ){
                buildFromTop+=2;
            } else if(mjRegion[counter]==6 || mjRegion[counter]==1|| 
                mjRegion[counter] == 5){
                buildFromBottom+=2;
            } else if(mjRegion[counter] == 7 ||
                mjRegion[counter] == 3 || mjRegion[counter] == 9 ||
                mjRegion[counter] == 8 || mjRegion[counter] == 14 ||
                mjRegion[counter] == 18){
                buildFromTop++;
            } else{
                buildFromBottom++;
            }
            counter++;
        }
        if(buildFromBottom > buildFromTop){
            side = CAMP_TWO;
        } else{
            side = CAMP_ONE;
        }
    }


    return side;

}
int *discScan(int discipline){
    int *array = malloc(sizeof(int)*NUM_REGIONS);

    int region = 0;
    int i = 0;
    while(region<NUM_REGIONS){
        if(discipline = getDiscipline(g,region)){
            array[i] = region;
            i++;
        }
        region++;
    }
    array[i] = 0;
    return array;
}
