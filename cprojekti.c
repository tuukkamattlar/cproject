#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// First create DB for all data in the game
// A following struct will do

struct avatar {
	char *name;			// name of the avatar
	int hp; 			// health points
	int ep;				// experience points
	char *weapon;		// the weapon of choise
	int weaponForce;	// the level of damage the weapon can maximally produce
};


//create dynamic list for avatars
struct avatar *listOfAvatars; 				//this will be reallocated at every new add case, even first

//Also add index that tells us the maximum index we're running at
int indexOfList=-1;

//a tool used for reallocating the list
int resizeArr() {
	indexOfList++;
	unsigned int a = indexOfList * sizeof(struct avatar);
	unsigned int b = sizeof(struct avatar); 					//for new size of the alloc
	unsigned int c = a + b;									// just making sure all fine here
	listOfAvatars = realloc(listOfAvatars, c + 1 );				//realloc the thing
	if(listOfAvatars != NULL && sizeof(listOfAvatars) != a) {	//handle realloc errors
		return 1;
		} 
	else {return 0;}
}


// #############################################

//function for listing the commands 

 void listCommands() {
	 printf("Use following commands to run the game: \n");
	 printf("A - add a player. This requires parameters name, hp, weapon and weaponPower^tm. \n");
	 printf("H - attack! Attack another player by giving your name and another players name.\n");
	 printf("L - list all players.\n");
	 printf("W - write current game status into a file you name as parameter.\n");
	 printf("O - load game from file you name as a parameter.\n");
	 printf("Q - the most important command. This shuts the whole game down. \n    No more suffering from bad gaming experience after this.\n");
	 printf("\nThat's about it. How would you like to proceed?\n");
 }


/**
 * A - create a new avatar
 * input: A _name_ _HP_ _gun _gunpower_
 * this adds a new avatar. New block will be allocated in the avatar struct pointer array.
 * this will be freed in quit-function
 */
 int addPlayer(char *fname, int fhp, char *fgun, int fguneff) {

	if (fhp <= 0) {
		printf("Dead players can't be added!\n");
		return 2;
	} else {

	if(resizeArr() == 1) {			//check if the realloc is sucecesfull
	listOfAvatars[indexOfList].name = malloc(sizeof(char)*40); 		//malloc, space for input
	listOfAvatars[indexOfList].weapon = malloc(sizeof(char)*40);	//same
	strcpy(listOfAvatars[indexOfList].name, fname);					//set values
	strcpy(listOfAvatars[indexOfList].weapon, fgun);
	listOfAvatars[indexOfList].hp = fhp;
	listOfAvatars[indexOfList].ep = 0;
	listOfAvatars[indexOfList].weaponForce = fguneff;
							//generate some random ints for different prints
	printf("\nNew player %s succesfully added.\n", fname);
		
	//next just some fancy cases for randomly generated print. Also includes the instructions.	
		

		return 1; //finally telling all was fine
	
	} 
	else {
		printf("New player was not added, better luck next time\n");
		return 0; //telling we didn't succeed
	}
	} // major else end
 } //function end

//this is for the attacks
 
 void omgAttack(char *fattacker, char *fattacked) {
	
	int ate=-1; //attacker index in our list
	int atc=-2; //attacked index in our list
	 
	 for(int i=0; i<=indexOfList; i++) {
		 
		 if(strcmp(fattacker, listOfAvatars[i].name) == 0) 
			{ate=i;}
		 else if(strcmp(fattacked, listOfAvatars[i].name) == 0)
			{atc=i;}
	 }
	 
	 if(ate == atc) 
		{printf("You can't fight yourself, can you?\n");}
	else if (ate == -1) {
		printf("There's no such player as %s. Try again! \n", fattacker);
	}
	else if (atc == -2) {
		printf("There's no such playes as %s. Try again!\n", fattacked);
	}
	 else if(listOfAvatars[ate].hp == 0) {
		 printf("%s is already dead. Cannot fight.\n", listOfAvatars[ate].name);
		 }
	 else if(listOfAvatars[atc].hp == 0) {
		 printf("%s is already dead. Cannot fight.\n", listOfAvatars[atc].name);
		 }
	 else {
		 if(listOfAvatars[ate].ep < 95) {
			 listOfAvatars[ate].ep = listOfAvatars[ate].ep + 5;
			 }
		 else 
			{listOfAvatars[ate].ep=100; printf("Woah, %s just scored full EP. It's their time to move to pension.\n", listOfAvatars[ate].name);
			}
	 int wf = rand() & listOfAvatars[ate].weaponForce; //random force generated, max is the given stuff.
	 
	 listOfAvatars[atc].hp = listOfAvatars[atc].hp - wf; //update hp
	 
	 if (listOfAvatars[atc].hp <= 0) { 
		printf("Shit, %s just died. RIP.\n", listOfAvatars[atc].name);
		listOfAvatars[atc].hp =0; //this is the set min
		printf("At least %s has now %d EP!\n", listOfAvatars[ate].name, listOfAvatars[ate].ep);
		}
	 else {
		printf("Woah. That was bad, lucklily nobody died.\n");
		printf("%s hit %s full blast causing %d HP units of damage..\n",listOfAvatars[ate].name, listOfAvatars[atc].name, wf );
		printf("%s has now %d EP and %s's HP left is %d\n",listOfAvatars[ate].name, listOfAvatars[ate].ep, listOfAvatars[atc].name, listOfAvatars[atc].hp);
	 } 
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

	 if(indexOfList==-1) {
		printf("There are no players yet!\n"); return 0;}
	 else {
		printf("The current players are listed here:\n\n");
	
	int t =100; //not the fastest way to run through the list but will do for now
	
	while(t >= 0) {
		
		for(int i=0; i<= indexOfList; i++) {
			if(t == listOfAvatars[i].ep && listOfAvatars[i].hp != 0){
				
			printf("%s ", listOfAvatars[i].name);
			printf("fights with: %s", listOfAvatars[i].weapon);
			printf(", harm: %d ", listOfAvatars[i].weaponForce);
			printf("EP: %d and ", listOfAvatars[i].ep);
			printf("HP left %d", listOfAvatars[i].hp);
			printf("\n");

			}
		}
		
		t--;
	}
	for(int i=0; i<= indexOfList; i++) {
		if(listOfAvatars[i].hp == 0){
			
			printf("%s ", listOfAvatars[i].name);
			printf("fighted with: %s", listOfAvatars[i].weapon);
			printf(", harmed: %d ", listOfAvatars[i].weaponForce);
			printf("EP: %d but is dead now. RIP.", listOfAvatars[i].ep);
			printf("\n");
		}
	}
	printf("\nCool, that's everyone\n");
	 }
	return 1;

 }
 
 
 /**
 * W - save current players in a file called input
 */
 
 int saveFile( char *nimi) {

	 FILE *f = fopen(nimi, "w");
	 if(f != 0 && indexOfList != -1) {
		 for(int i=0; i <=indexOfList; i++) {
			 fprintf(f, "%s %d %d %s %d\n", 
			 listOfAvatars[i].name, 
			 listOfAvatars[i].ep, 
			 listOfAvatars[i].hp,
			 listOfAvatars[i].weapon, 
			 listOfAvatars[i].weaponForce);
		 }
		 fclose(f);
		 return 1;
 } else if (indexOfList == -1) {
	 printf("Hmm. There are no players. Creating a file now would be pretty useless.\n");
	 return 0;
 }
	else {
	 fprintf(f, "Whoops, the file was not succesfully processed.\n");
	 fclose(f);
	 return 0;
	}
 }
 

  /**
 * Q - quit program and free all memory
 */
 
 void clearAll() {

	 
	for(int i=0; i <= indexOfList; i++ )	{ 
		free(listOfAvatars[i].name);
		free(listOfAvatars[i].weapon);
}
		free(listOfAvatars);
		indexOfList = -1;
 }
 


 
  /**
 * O - load players from file called tiedosto.
 */
 
 int loadFile( char *nimi) {
	clearAll();
	FILE *f = fopen(nimi, "r");
	
	if(f) {
		char fname[40];
		int fep;
		int fhp;
		char fweapon[40];
		int fwf;
		int count;
		//that's the right order in the file
		//there are 5 inputs thus;
		while( (count = fscanf(f, "%s %d %d %s %d", 
		fname, 
		&fep, 
		&fhp, 
		fweapon, 
		&fwf)) == 5 ) {
			addPlayer(fname, fhp, fweapon, fwf);
			listOfAvatars[indexOfList].ep = fep; //indexOfList is updated at each time!
		} //end of while stuff
		
		
		
	} else {
		printf("Uhm, the file could not be opened.\nU sure u gave the right file name?\n");
		return 0;
	}
	
 }
 


 
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
			scanf("%s %d %s %d", str1, &int1, str2, &int2); // like  A Bilbo 25 Dagger 8
			
			if(addPlayer(str1, int1, str2, int2) !=1) {
				
				printf("Shit happens, better luck next time.\n"); 
				
				} 
			else {
				int rann = rand() & 3;		
					if (indexOfList == 0) {
							printf("%s is still a bit too safe because they has no fighting mates. \nPlease add them by creating another avatar.\n\n", listOfAvatars[0].name);
							}
					else if (indexOfList == 1) {
							printf("Cool! %s is now accompanied by %s.\n\nYou may now start doing more stuff! Here are the commands once more:\n\n", listOfAvatars[0].name, listOfAvatars[1].name); listCommands();
							}  		
					else if (rann == 1) {
							printf("%s is keen to start playing! Go ahead!\n", listOfAvatars[indexOfList].name);
							}  
					else if (rann == 2) {
							printf("%s has no experience yet.\nPlease help them by starting a fight. \n", listOfAvatars[indexOfList].name);
							} 
					else {
							printf("%s is however feeling a bit lonely. Please help them by starting a fight. \n", listOfAvatars[indexOfList].name);
					}
				}
			break;
			
		case 'H' :
			scanf("%s %s", str1, str2); // H Bilbo Smaug
			omgAttack(str1, str2);
			break;
			
		case 'L' :
			if(printList()==1) {
				printf("That was successful \n");} 
			else {
				printf("That wasn't successful \n");}
			break;
			
		case 'W' :
			scanf("%s", str1); //esim: W game
			if(saveFile(str1)) {
				printf("Nice, the file %s has now been created.\n", str1);
			}
			break;
			
		case 'O' :
			scanf("%s", str1);
			loadFile(str1); //TODO
			break;
			
		case 'Q' :
			clearAll();
			break;
			
		case '\n':
		case ' ':
			break;	//because spaces and \n created problems in the past
			
		default:
			printf("Command %c is not defined. \n Please use the ones on the following list \n", cmd); 
			//the case when given commang is not known
			listCommands();
			return 'N'; //for futher error print, maybe
			break;
		}
		return cmd;
	}
	
	int main(void) {
		
		printf("\nWelcome to my game 1.0.1\n\n");
		printf("Happy to see you there.\n\n");
		listCommands();
		printf("I'd recommend you to create some players to start the mayhem with.\n");
		printf("So go ahead and type A and then the parameters you wish, obvioustly following the rules.\n\n");
		char inp = 'Y';
		while(inp != 'Q') {
			inp = readCmd();
		}
		printf("Cool and good, see ya!\n");
		return 0;
	}


