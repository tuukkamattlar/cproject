#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// First create DB for all data in the game
// A following struct will do

struct avatar {
	char *name;		// name of the avatar
	int hp; 		// health points
	int ep;			// experience points
	char *weapon;	// the weapon of choise
	int weaponForce;	// the level of damage the weapon can maximally produce
};


//create dynamic list for avatars
struct avatar *listOfAvatars; //realloc at every new add case, even first
int indexOfList=-1;


int resizeArr() {
	indexOfList++;
	unsigned int a = indexOfList * sizeof(struct avatar);
	unsigned int b = sizeof(struct avatar); //for new size of the alloc
	unsigned int c = a + b;
	//indexOfList++;
	listOfAvatars = realloc(listOfAvatars, c + 1 );	//realloc the thing
	if(listOfAvatars != NULL && sizeof(listOfAvatars) != a) {return 1;} 		//handle realloc errors
	else {return 0;}
}

// ata base created. Cool. Let's continue


// #############################################

 
 void listCommands() {
	 printf("Use following commands to run the game: \n");
	 printf("A - add player. This requires parameters name, hp, weapon and weaponPower^tm. \n");
	 printf("H - attack! Attack another player by giving your name and another players name.\n");
	 printf("L - list all players.\n");
	 printf("W - write current game status into a file you name as parameter.\n");
	 printf("O - load game from file you name as a parameter.\n");
	 printf("Q - the most important command. This shuts the whole game down. \n    No more suffering from bad gaming experience after this.\n");
	 printf("\nThat's about it. How would you like to proceed?\n");
 }


/**
 * A - create a new avatar
 * syote A _nimi_ _HP_ _ase _asevahinkoyksikko_
 * ei palautusta
 */
 int addPlayer(char *fname, int fhp, char *fgun, int fguneff) {

	//struct avatar *newAvatar; // = malloc();
	//int oldsize = sizeof(listOfAvatars)/sizeof(struct avatar);
	//newAvatar = malloc(sizeof(struct avatar));


	//check if the realloc is sucecesfull
	if(resizeArr() == 1) {	
	//realloc is done here every tiem
	listOfAvatars[indexOfList].name = malloc(sizeof(char)*40);
	//listOfAvatars[oldsize].name = fname;
	listOfAvatars[indexOfList].weapon = malloc(sizeof(char)*40);
	//listOfAvatars[oldsize].weapon = fgun;
	strcpy(listOfAvatars[indexOfList].name, fname);
	strcpy(listOfAvatars[indexOfList].weapon, fgun);
	listOfAvatars[indexOfList].hp = fhp;
	listOfAvatars[indexOfList].ep = 0;
	listOfAvatars[indexOfList].weaponForce = fguneff;
	int rann = rand() & 3;
	//	listOfAvatars[ - 1] = newAvatar;
		printf("\nNew player %s succesfully added.\n", fname);
		
		if (indexOfList == 0) {printf("%s is still a bit too safe because they has no fighting mates. \nPlease add them by creating another avatar.\n", fname);}
		else if (indexOfList == 1) {printf("Cool! %s is now accompanied by %s.\n\nYou may now start doing more stuff! Here are the commands once more:\n\n", listOfAvatars[0].name, fname); listCommands();}  		
		else if (rann == 1) {printf("%s is keen to start playing! Go ahead!\n", fname);}  
		else if (rann == 2) {printf("%s has no experience yet.\nPlease help them by starting a fight. \n", fname);} 
		//else if (rann == 2) {printf("%s is reversed %s. Think about that for a while.\n", fname , strrev(fname));} 
		else {printf("%s is however feeling a bit lonely. Please help them by starting a fight. \n", fname);}
		//free(fname);	// these might cause problems
		//free(fgun);		// also this one
		return 1;
	} else {
		printf("New player was not added, better luck next time\n");
		return 0; //kys
	}
	 
 }


 
 void omgAttack(char *fattacker, char *fattacked) {
	 int ate=0;
	 int atc=0;
	 for(int i=0; i<=indexOfList; i++) {
		 if(strcmp(fattacker, listOfAvatars[i].name) == 0) {ate=i;}
		 else if(strcmp(fattacked, listOfAvatars[i].name) == 0){atc=i;}
	 }
	 if(ate == atc) {printf("You can't fight yourself, can you?\n");}
	 else if(listOfAvatars[ate].hp == 0) {printf("%s is already dead. Cannot fight.\n", listOfAvatars[ate].name);}
	 else if(listOfAvatars[atc].hp == 0) {printf("%s is already dead. Cannot fight.\n", listOfAvatars[atc].name);}
	 else {
		 if (listOfAvatars[ate].ep < 95) {listOfAvatars[ate].ep =+5;}
		 else {listOfAvatars[ate].ep=100; printf("Woah, %s just scored full EP. It's their time to move to pension.\n", listOfAvatars[ate].name);}
	 
	 
	 listOfAvatars[atc].hp = listOfAvatars[atc].hp - listOfAvatars[ate].weaponForce;
	 
	 if (listOfAvatars[atc].hp <= 0) { printf("Shit, %s just died. RIP.\n", listOfAvatars[atc].name);listOfAvatars[atc].hp =0;}
	 else (printf("Woah. That was bad, lucklily nobody died.\n"));
	 
	 }
 }
	 



// #############################################
// #############################################

/**
 * L - tulosta hahmot. kukin omalla rivilla, ilmoita kaikki ominaisuudet, 
 * sort by expP. Kuolleet hahmot lopussa jossain jarkassa
 * tulosta edeltavan mukaan
 */
 
 
 int printList() {
	 if(indexOfList==-1) {printf("There are no players yet!\n"); return 0;}
	 else {
	printf("The current players are listed here:\n\n");
	
	int t =100;
	
	while(t >= 0) {
		for(int i=0; i<= indexOfList; i++) {
			if(t == listOfAvatars[i].ep){
			printf("Name: %s. ", listOfAvatars[i].name);
			printf("Fights with: %s ", listOfAvatars[i].weapon);
			printf("that makes %d much of damage. ", listOfAvatars[i].weaponForce);
			printf("\nEP: %d and ", listOfAvatars[i].ep);
			printf("HP left %d", listOfAvatars[i].hp);
			if(listOfAvatars[i].hp == 0){printf("\nI'm afraid this means we've lost %s. RIP.\n\n", listOfAvatars[i].name );}
			else {printf("\n\n");}

			}
		}
		
		t--;
	}
	printf("\nCool, that's everyone\n");
	 }
	return 1;

 }
 
// #############################################
// #############################################
 
 /**
 * W - save current players in a file called input
 */
 
 void saveFile( char *nimi) {
	 printf("kys \n");	 
 }
 
 
// #############################################
// #############################################
 
  /**
 * O - load players from file called tiedosto.
 */
 
 void loadFile( char *nimi) {
	 printf("kys \n");	 
 }
 
 
// #############################################
// #############################################
 
  /**
 * Q - quit program and free all memory
 */
 
 void clearAll() {
//	 int sizeOfArr;
	 printf("kys \n");
for(int i=0; i <= indexOfList; i++ )	{ 
	 free(listOfAvatars[i].name);
	 free(listOfAvatars[i].weapon);
	// free(listOfAvatars[i]);
}
	free(listOfAvatars);
 }
 
 
// #############################################
// #############################################
 
 
 
  /**
 * This function allows scanning the feed
 */

char readCmd() {
	//introduce all possible inputs
	char cmd;
	char str1[40]; 	//used primarily for names and other strings
	char str2[40]; 	//second for names&other strings
	int int1;		//primary int
	int int2;		//sec int

	//continue to reading
	scanf("%c", &cmd); //scanning given command starter
	
	// now continue to check the command and select sophisticated function
	// also include default case for a command not defined here
	
	switch(cmd) {
		
		case 'A' :
			scanf("%s %d %s %d", str1, &int1, str2, &int2); // A Bilbo 25 Dagger 8
			if(addPlayer(str1, int1, str2, int2) !=1) {
				printf("Shit happens, better luck next time.\n"); 
				} 
		//printf("\n");
		break;
			
		case 'H' :
			scanf("%s %s", str1, str2); // H Bilbo Smaug
			omgAttack(str1, str2);
			break;
			
		case 'L' :
			if(printList()==1){printf("That was successful \n");} else {printf("That wasn't successful \n");}
			break;
			
		case 'W' :
			scanf("%s", str1); //esim: W game
			saveFile(str1);
			break;
			
		case 'O' :
			scanf("%s", str1);
			loadFile(str1);
			break;
			
		case 'Q' :
			clearAll();
			break;
			
		case '\n':
		case ' ':
			break;
			
		default:
			printf("Command %c is not defined. \n Please use the ones on the following list \n", cmd); 
			//the case when given commang is not known
			listCommands();
			return 'N'; //for futher error print
			break;
		}
		return cmd;
	}
	
	int main(void) {
		printf("\nWelcome to my game 1.0.1\n\n");
		printf("Happy to see you there.\n\n");
		listCommands();
		printf("I'd recommend you to create some players to start the mayhem with.\n");
		printf("So go ahead and type A and then the parameters you wish, obvioustly following the rules.\n");
		char inp = 'Y';
		while(inp != 'Q') {
			inp = readCmd();
		}
		printf("kys, see ya\n");
		return 0;
	}


