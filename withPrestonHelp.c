// *** TEXT ADVENTURE *** //
// Donnie Coughlin

// include libraries
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// set up the structure for the room
typedef struct room {
    char *name;
    char *description;
    int near[2];
    int *bag;
    char **commands;
	//TODO add in locationitem int
	//TODO add in locationEvent

} room;

// rooms, inventory and cmnds
room locations[6];
char bag[6];

// function that creates a room from args
void init_room(int roomNumber, char* locationName, char* locationDesc, int near[2]) {
    // set fields for room struct
    locations[roomNumber].name = locationName;
    locations[roomNumber].description = locationDesc;
    memcpy(locations[roomNumber].near, near, sizeof locations[0].near);
    locations[roomNumber].bag = malloc(11 * sizeof(int));
    locations[roomNumber].bag[0] = 0;
}

// the main function
int main() {

	// room descriptions:
	char *winDesc = "You push open the doors of the ruin, inside you find "
        "Mother, but alas she is dead. You cry because you are sad.";
    char *roomDesc0 = "You stand near the charred remains of your campfire. "
        "Over behind you lies your canoe, which you could use to travel to a "
        "nearby island where an OLDMAN lives. Your other option is to head the "
        "other way through a nearby SANDBAR toward the forest.";
	char *roomDesc1 = "You are in the canoe, its a nice canoe, you see some "
        "FISH in the water (to catch one you'd need to USE SPEAR). From here "
        "you can head back to the CAMPFIRE or toward the OLDMAN.";
	char *roomDesc2 = "You arrive at a shallow sandbar, not much here, but "
        "you see some FISH in the water (to catch one you'd need to USE SPEAR). "
        "From here you can go to the FOREST, or head back to the CAMPFIRE.";
	char *roomDesc3 = "You see an old man, he looks hungry, if you have a FISH, "
        "you could USE FISH here to help him out. Other options are to go back "
        "to the CANOE or press onward to the RUINS you see in the distance.";
	char *roomDesc4 = "You see a set of footprints leading off into the forest, "
        "on the ground you see a SPEAR. You could always head back to the SANDBAR,"
        "or you could press onward to the RUINS.";
	char *roomDesc5 = "You see an aged ruin, with a massive set of stone doors,"
        "youd need an OLDKEY to enter though. You see a road leading down the"
        "cliff to the OLDMAN that lives on the nearby island, and you could"
        "always head back to the FOREST.";

    // initialize the room data
    init_room(0, "campfire", roomDesc0, (int[]) {1,2});
	init_room(1, "canoe", roomDesc1, (int[]) {0,3});
    init_room(2, "sandbar", roomDesc2, (int[]) {0,4});
	init_room(3, "old_man", roomDesc3, (int[]) {1,5});
	init_room(4, "forest", roomDesc4, (int[]) {2,5});
	init_room(5, "ruin", roomDesc5, (int[]){3,4});	
    
    //initialize commands
    for (int i = 0; i< 6; i++) {
        locations[i].commands = (char*[]) {
            locations[locations[i].near[0]].name,
            locations[locations[i].near[1]].name
        };
    }

    // set default values
    int current_room = 0;
    bool quit = false;
    bool wonGame = false;
    char command[20];

    // init bag to empty
    bool haveSpear = false;
    bool haveFish = false;
    bool haveOldKey = false;

    // the starting prompt
    printf("The sound of the seagulls wakes you. You're on a tiny island, the "
        "charred remains of a campfire are right behind you.\n\nWhat is your "
        "name?\n\n Thats funny... It doesn't come to you.\n\nIn fact, there is "
        "only one thing you know, and that is that you need to go find mother, "
        "ASAP!\n\n");
    printf("%s\n", roomDesc0);


    // the game and such
    while (quit == false) {
                
    	// the prompt
        printf("\nYou are next to the %s. What do you do?\n\n>> ", locations[current_room].name);
        fflush(stdout);
        scanf("%s", command);

        // quit the game
        if (strcmp(command, "quit") == 0) {
            quit = true;
        }

        // getItem function TODO add in locationItem arg for struct
        // useItem function TODO add in locationEvent arg for struct

        // show description
        else if (strcmp(command, "look") == 0) {
            printf("\n%s\n\n", locations[current_room].description);
        }

		// go to room option 1
        else if (strcmp(command, (char*)locations[current_room].commands[0]) == 0) {
            current_room = locations[current_room].near[0];
        }
        
        // go to room option 2
        else if (strcmp(command, (char*)locations[current_room].commands[1]) == 0) {
            current_room = locations[current_room].near[1];
        }

        // instantly win the game
        else if(strcmp(command, "win") ==0) {
            wonGame = true;
            printf("\n%s\n\n -- THE END -- \n\n", winDesc);
            quit = true;
        }

        // endgame method that sets wingame to true
        else if (wonGame == true) {
            printf("\n%s\n\n  -- THE END --\n\n",winDesc);
            quit = true;
        } 
    }
    return 0; 
}

