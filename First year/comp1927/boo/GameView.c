// GameView.c ... GameView ADT implementation

// Coded by :
//      Cameron Lonsdale
//      Charlotte Han
//      Joshua Merrit
//      Ng Yi Yan

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Map.h" // Using the Map ADT


// =======================
//        Structs
// =======================
    
// Used for intuitive access for the location "queue"
#define NEWEST_LOC 0
#define OLDEST_LOC TRAIL_SIZE

typedef struct player {
    int health;
    LocationID locations[TRAIL_SIZE]; // Acts as a queue
} Player;

struct gameView {
    // Simple status info
    Round current_round;
    PlayerID current_player;
    int score;

    // Player info
    Player players[NUM_PLAYERS]; // Index also their player ID

    // Map info
    Map map;
};
     
// =======================
//         Setters
// =======================

// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    GameView gameView = malloc(sizeof(struct gameView));

    gameView -> current_round = 1;
    gameView -> current_player = 0;
    gameView -> score = GAME_START_SCORE;

    int player_id;
    int loc_id;
    for (player_id = 0; player_id < NUM_PLAYERS; player_id++) {
        // Health
        if (player_id == PLAYER_DRACULA) {
            gameView -> players[player_id].health = GAME_START_BLOOD_POINTS;
        } else {
            gameView -> players[player_id].health = GAME_START_HUNTER_LIFE_POINTS;
        }
        // Location history
        for (loc_id = 0; loc_id < TRAIL_SIZE; loc_id++) {
            gameView -> players[player_id].locations[loc_id] = UNKNOWN_LOCATION;
        }
    }
    // Map
    gameView -> map = newMap();

    return gameView;
}
     
     
// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    disposeMap(toBeDeleted -> map); 
    free(toBeDeleted);
}

// =======================
//         Getters
// =======================

//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return currentView -> current_round;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return currentView -> current_player;
}

// Get the current score
int getScore(GameView currentView)
{
    return currentView -> score;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    return currentView -> players[player].health;
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{
    return currentView -> players[player].locations[NEWEST_LOC];
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    int index;
    // Copies across our queue into their trail array
    for (index = 0; index < TRAIL_SIZE; index++) {
        trail[index] = currentView -> players[player].locations[index];
    }
}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

// +++++ pasted from gameview.h ++++++

// road, rail and sea are connections should only be considered
//   if the road, rail, sea parameters are TRUE.
// The array can be in any order but must contain unique entries

//COMPLETED parts
// connectedLocations() returns an array of LocationID that represent
//   all locations that are connected to the given LocationID.
// The size of the array is stored in the variable pointed to by numLocations
// Your function must take into account the round and player id for rail travel
// Your function must take into account that Dracula can't move to
//   the hospital or travel by rail but need not take into account Dracula's trail
// The destination 'from' should be included in the array
LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
   assert(currentView != NULL);
   int dice = 0;
   int size = *numLocations;

   LocationID to[size]={0};
   to[0] = from; 

   if(player == PLAYER_DRACULA){rail = 0;} //no rail for drac
   else if (rail == 1){ dice = (round+player) % 4;} //determine rail travel options

   if(road == 1 || rail == 1 || sea ==1){
      printf("before\n");
      to[] = connections(GameView->map, from, size, to[], road, rail, sea, dice);
      
   }

   return to[]; 
}
