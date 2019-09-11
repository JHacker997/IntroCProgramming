/*
John Hacker
11/17/16
COP 3223, Section 203
Final Project

A monster fighting/capture game on a confined 2-dimensional map.
*/
  
//Include statements
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  
//Define constants
  #define MAX_MONSTERS 100
  #define MAX_ATTACKS 400
  #define MAX_MONSTER_ATTACKS 4
  #define MIN_MONSTER_ATTACKS 1
  #define MAX_NAME 100
  #define MAX_MONSTER_STAT 20
  #define MAX_ATTACK_STAT 50
  #define MIN_MONSTER_STAT 1
  #define MIN_ATTACK_STAT 10
  #define DEFAULT_MONSTERS 10
  #define DEFAULT_ATTACKS 20
  #define QUIT 6
  #define MAP_SIZE 9
  #define EMPTY 0
  #define OCCUPIED 1
  #define PLAYER 2
  #define STARTING_MONSTERS 20
  #define ON 1
  #define OFF 0
  #define MAX_STAT_INCREASE 5
  #define WIN 1
  #define LOSE 0
  #define NEITHER 2
  #define MAX_STAT_BONUS 30
  #define EXP_GAIN 5
  #define LEVEL_UP 50
  #define MAX_EXP_MULTIPLIER 5
  #define CRITICAL_HIT_THRESHOLD 40
  #define HEALTH_BOOST 7
  
//Declare structures
//Attack for monsters to use
  struct Attack
  {
    char name[MAX_NAME];
    int power;
    int speed;
    int accuracy;
  };
//Monster for the character to use
  struct Monster
  {
    char name[MAX_NAME];
    int power;
    int defense;
    int speed;
    int healthAvail;
    int healthMax;
    int accuracy;
    int ellusiveness;
    struct Attack mAttacks[MAX_MONSTER_ATTACKS];
    int experience;
    int experienceFull;
    int level;
  };
//Character to the user to control
  struct Character
  {
    struct Monster monster;
    int experience;
    int experienceFull;
    int level;
  };
  
//Declare functions
  int randomMonster(struct Monster monsters[], int numMonsters);
  int createMonster(struct Monster monsters[], int numMonsters, struct Attack attacks[], int *numAttacks);
  int randomAttack(struct Attack attacks[], int numAttacks);
  int createAttack(struct Attack attacks[], int numAttacks);
  int removeMonster(struct Monster monsters[], int numMonsters, int choose, char deleteName[]);
  int options(void);
  int showDefaults(struct Monster monsters[]);
  int startGame(struct Monster monsters[], int defaultsT, int monsterT, int numMonsters, int *highMonster, int *highPlayer);
  int randomSpawn(int map[][MAP_SIZE]);
  int move(int map[][MAP_SIZE], struct Character player, struct Monster monsters[], int moves, int numMonsters, int *highMonster, int *highPlayer);
  int displayMonster(struct Character player);
  int characterStats(struct Character player);
  int highScore(int *highMonster, int *highPlayer);
  int battle(struct Character player, struct Monster monsters[], int moves, int numMonsters, int *monsterHigh, int *highPlayer);
  int actionScene(struct Monster battler, struct Monster enemy);
  int monsterLevelUp(struct Monster monster, int *highMonster);
  int playerLevelUp(struct Character player, int *highPlayer);
  
//Main function
  int main(void){
  
  //Declare variables
    int choice = 0;
    int numMonsters = 0;
    int numAttacks = 0;
    int confirm = 0;
    int c = 0;
    int i = 0;
    int r = 0;
    int togMonsters = ON;
    int togBegin = OFF;
    int togMonsters1 = 0;
    int togBegin1 = 0;
    int togMTemp = 0;
    int togBTemp = 0;
    int togOption = 0;
    int count = 2;
    int highMonster = 1;
    int highPlayer = 1;
    char index[1];
    struct Monster monsters[MAX_MONSTERS];
    struct Attack attacks[MAX_ATTACKS];
    
  //Seed the random-number generating algorithm
    srand(time(NULL));
    
  //Loop to create default monsters
    for (c = 0; c < DEFAULT_MONSTERS; c++){
    count = 2;
    sprintf(index, "%d", count);
    randomMonster(monsters, numMonsters);
    //Loop to create all attacks for monster
      for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
        randomAttack(attacks, numAttacks);
        monsters[numMonsters].mAttacks[i] = attacks[numAttacks];
        for (r = i - 1; r >= 0 ; r--){
          if (strcmp(monsters[numMonsters].mAttacks[i].name, monsters[numMonsters].mAttacks[r].name) == 0){
            strcat(monsters[numMonsters].mAttacks[i].name, index);
            count++;
            sprintf(index, "%d", count);
          }
        }
        numAttacks++;
      }
    numMonsters++;
    }
    
  //Loop through Selection Screen
    while (choice != QUIT){
        
    //Selection Screen
      printf("\nMONSTER MASTER\n===========================================\n");
      printf("Please select one:\n");
      printf("  [1]  Start a New Game!\n");
      printf("  [2]  Import a Monster\n");
      printf("  [3]  Remove a Monster\n");
      printf("  [4]  Toggles\n");
      printf("  [5]  Show default monsters\n");
      printf("  [%d]  Quit\n\n", QUIT);
      scanf("%d", &choice);
      printf("\n");
      
    //Implement user selection
      if (choice == 1){
      //Start the game
        startGame(monsters, togMonsters, togBegin, numMonsters, &highMonster, &highPlayer);
        
      //Show the current high score
        highScore(&highMonster, &highPlayer);
        
        do{
      //Prompt asking user to play again
          printf("Would you like to play again?\n");
          printf("  [0]  NO, I do NOT want to play another game.\n");
          printf("  [1]  YES, I do want to play another game!\n\n");
          scanf("%d", &choice);
          if (choice == 1){
            printf("\nAll previously applied toggles and imported monsters are in effect.\n");
            printf("If you started a previous game without default monsters,\nthey will not be available for future games, no matter the toggle.\n\n");
          }
          else if (choice == 0){
            choice = QUIT;
            printf("\nGoodbye!\n\n");
          }
          else 
            printf("\nInvalid selection!\n\n");
        } while (choice != 1 && choice != QUIT);
      }
      
      else if (choice == 2){
      //Fill monster name with end-characters
        for (i = 0; i < MAX_NAME; i++){
          monsters[numMonsters].name[i] = '\0';
        }
      
          confirm = createMonster(monsters, numMonsters, attacks, &numAttacks);
      //Fill attack names with end-characters
        for (c = 0; c < MAX_MONSTER_ATTACKS; c++){
          for (i = 0; i < MAX_NAME; i++){
            monsters[numMonsters].mAttacks[c].name[i] = '\0';
          }
        }
      //Loop to create all attacks for monster
        for (c = 0; c < confirm; c++)
        {
        //Say which # attack the user is creating
          printf("Attack #%d\n", c + 1);
        //Create a new attack for the new monster
          createAttack(attacks, numAttacks);
        //Set the new attack into the monster structure
          monsters[numMonsters].mAttacks[c] = attacks[numAttacks];
        //Add to total for amount of attacks made
          numAttacks++;
          printf("\n");
        }
        if (confirm > 0){
        //Add to total for amount of monsters made
          numMonsters++;
          printf("Successfully added a customized monster!\n");
          }
        else
          printf("Monster creation ERROR\n");
      }
      
      else if (choice == 3){
      //Delete a monster
        confirm = removeMonster(monsters, numMonsters, ON, " ");
        if (confirm == 1)
          printf("\nSuccessfully removed a monster\n");
        else
          printf("\nError in removing a monster\n");
      }
      
      else if (choice == 4){
        togOption = options();
      //Check for what option was chosen
        if (togOption == 1)
          togMonsters1++;
        if (togOption == 2)
          togBegin1++;
      //Fulfill goal of the chosen option
        if (togMonsters1 > togMTemp && togMonsters1 % 2 == 1){
          printf("\nToggle for default monsters is turned OFF\n");
          togMTemp++;
          togMonsters = OFF;
        }
        if (togMonsters1 > togMTemp && togMonsters1 % 2 == 0){
          printf("\nToggle for default monsters is turned ON\n");
          togMTemp++;
          togMonsters = ON;
        }
        if (togBegin1 > togBTemp && togBegin1 % 2 == 1){
          printf("\nToggle for setting your own beginning monster is turned ON\n");
          togBTemp++;
          togBegin = ON;
        }
        if (togBegin1 > togBTemp && togBegin1 % 2 == 0){
          printf("\nToggle for setting your own beginning monsters is turned OFF\n");
          togBTemp++;
          togBegin = OFF;
        }
      }
    
    //Print summaries of default monsters
      else if (choice == 5){
      //Start the game
        showDefaults(monsters);
      }
      
    //Bid farewell
      else if (choice == QUIT){
        printf("Goodbye!\n\n");
      }
      
    //Anything else is not valid
      else
        printf("Invalid selection!\n");
    
    }
    
  //Complete Program
    return 0;
  }


  
/*
Precondition: monsters array, amountof monsters
Postcondition: integer
Actions:
Creates a monster with random stats that will be new every time the program is ran
*/
  int randomMonster(struct Monster monsters[], int numMonsters){
    
  //Declare variables
    int c = 0;
    int r = 0;
    
  //Fill monster name with end-characters
    for (r = 0; r < MAX_NAME; r++){
      monsters[numMonsters].name[r] = '\0';
    }
    
  //Name the generated monster, unique to each default monster
    if (numMonsters == 1)
      strcpy(monsters[numMonsters].name, "Giant");
    else  if (numMonsters == 2)
      strcpy(monsters[numMonsters].name, "Goliath");
    else  if (numMonsters == 3)
      strcpy(monsters[numMonsters].name, "Cyclops");
    else  if (numMonsters == 4)
      strcpy(monsters[numMonsters].name, "Dragon");
    else  if (numMonsters == 5)
      strcpy(monsters[numMonsters].name, "Witch");
    else  if (numMonsters == 6)
      strcpy(monsters[numMonsters].name, "Zombie");
    else  if (numMonsters == 7)
      strcpy(monsters[numMonsters].name, "Vampire");
    else  if (numMonsters == 8)
      strcpy(monsters[numMonsters].name, "Werewolf");
    else  if (numMonsters == 9)
      strcpy(monsters[numMonsters].name, "Dinosaur");
    else  if (numMonsters == 0)
      strcpy(monsters[numMonsters].name, "BigFoot");
    else
      printf("Monster-naming ERROR");
    
  //Set random numbers to every stat
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].power = r;
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].defense = r;
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].speed = r;
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].healthMax = r;
    monsters[numMonsters].healthAvail = monsters[numMonsters].healthMax;
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].accuracy = r;
    r = rand() / (RAND_MAX / MAX_MONSTER_STAT) + 1;
    monsters[numMonsters].ellusiveness = r;
    
  //Set experience and level stats
    monsters[numMonsters].experience = 0;
    monsters[numMonsters].experienceFull = LEVEL_UP;
    monsters[numMonsters].level = 1;
    
  //Confirm completion
    return 0;
  }  
  

  
/*
Precondition: monsters array, ammount of monsters, array of attacks, pointer to amount of attacks
Postcondition: integer
Actions:
Opens a file from the user to create a new monster based to their specificationsand add it to the monsters array
*/
  int createMonster(struct Monster monsters[], int numMonsters, struct Attack attacks[], int *numAttacks){
    
  //Declare variables
    FILE *ifp;
    char fileName[MAX_NAME];
    int c = 0;
    int amountAttacks = 0;
    
  //Fill monster name with end-characters
    for (c = 0; c > MAX_NAME; c++){
      monsters[numMonsters].name[c] = '\0';
    }
    
  //Set parameters of monster file
    printf("Create a .txt file in the following form (do not include titles):\n");
    printf("<Name>\n");
    printf("<Power>\n");
    printf("<Defense>\n");
    printf("<Speed>\n");
    printf("<Health>\n");
    printf("<Accuracy>\n");
    printf("<Ellusiveness>\n");
    printf("<Number of Attacks>\n\n");
    printf("Every base stat can be any number 1-20.\nThe number of attacks should be 1-4.\n");
    printf("The health stat will automatically increase for your personal monster.\n\n");
    printf("What is the full name of your monster file?\n");
    scanf("%s", fileName);
    
  //Open monster's file
    ifp = fopen(fileName, "r");
    
  //Scan to complete an Monster structure
    fscanf(ifp, "%s %d %d %d %d %d %d %d", monsters[numMonsters].name, &monsters[numMonsters].power, &monsters[numMonsters].defense, &monsters[numMonsters].speed, &monsters[numMonsters].healthMax, &monsters[numMonsters].accuracy, &monsters[numMonsters].ellusiveness, &amountAttacks);

  //Close monster's file
    fclose(ifp);
    
  //Check for stat limitations
    if (monsters[numMonsters].name[0] == '\0' || monsters[numMonsters].power > MAX_MONSTER_STAT || monsters[numMonsters].defense > MAX_MONSTER_STAT || monsters[numMonsters].speed > MAX_MONSTER_STAT || monsters[numMonsters].healthMax > MAX_MONSTER_STAT || monsters[numMonsters].accuracy > MAX_MONSTER_STAT || monsters[numMonsters].ellusiveness > MAX_MONSTER_STAT || amountAttacks > MAX_MONSTER_ATTACKS || monsters[numMonsters].power < MIN_MONSTER_STAT || monsters[numMonsters].defense < MIN_MONSTER_STAT || monsters[numMonsters].speed < MIN_MONSTER_STAT || monsters[numMonsters].healthMax < MIN_MONSTER_STAT || monsters[numMonsters].accuracy < MIN_MONSTER_STAT || monsters[numMonsters].ellusiveness < MIN_MONSTER_STAT || amountAttacks < MIN_MONSTER_ATTACKS){
      printf("Oops, invalid enrty!\n");
    for (c = 0; c > MAX_NAME; c++){
      monsters[numMonsters].name[c] = '\0';
    }
    monsters[numMonsters].power = (int) NULL;
    monsters[numMonsters].defense = (int) NULL;
    monsters[numMonsters].speed = (int) NULL;
    monsters[numMonsters].healthMax = (int) NULL;
    monsters[numMonsters].accuracy = (int) NULL;
    monsters[numMonsters].ellusiveness = (int) NULL;
    return 0;
    }
    
  //Make maximum and available health the same
    monsters[numMonsters].healthAvail = monsters[numMonsters].healthMax;
    
  //Set experience and level stats
    monsters[numMonsters].experience = 0;
    monsters[numMonsters].experienceFull = LEVEL_UP;
    monsters[numMonsters].level = 1;
    
  //Let the userknow to create new attacks for new user
    printf("\nNow set the attack(s) for %s!\n\n", monsters[numMonsters].name);
    
  //Confirm completion
    return amountAttacks;
  }
  


/*
Precondition: array of attacks and amount of attacks that already existed
Postcondition: integer
Actions:
Creates an attack with random stats that will change every time the program is run
*/
  int randomAttack(struct Attack attacks[], int numAttacks){
    
  //Declare variables
    int c = 0;
    int r = 0;
    
  //Fill attack name with end-characters
    for (r = 0; r < MAX_NAME; r++){
      attacks[numAttacks].name[r] = '\0';
    }
    
  //Set default names
    r = rand() / (RAND_MAX / (DEFAULT_ATTACKS - 1)) + 1;
    if (r == 1)
      strcpy(attacks[numAttacks].name, "Charge");
    if (r == 2)
      strcpy(attacks[numAttacks].name, "Stab");
    if (r == 3)
      strcpy(attacks[numAttacks].name, "Slap");
    if (r == 4)
      strcpy(attacks[numAttacks].name, "Kick");
    if (r == 5)
      strcpy(attacks[numAttacks].name, "Punch");
    if (r == 6)
      strcpy(attacks[numAttacks].name, "Chop");
    if (r == 7)
      strcpy(attacks[numAttacks].name, "Bite");
    if (r == 8)
      strcpy(attacks[numAttacks].name, "Headbutt");
    if (r == 9)
      strcpy(attacks[numAttacks].name, "Shoot");
    if (r == 10)
      strcpy(attacks[numAttacks].name, "Blast");
    if (r == 11)
      strcpy(attacks[numAttacks].name, "Tackle");
    if (r == 12)
      strcpy(attacks[numAttacks].name, "Headlock");
    if (r == 13)
      strcpy(attacks[numAttacks].name, "Trip");
    if (r == 14)
      strcpy(attacks[numAttacks].name, "Stomp");
    if (r == 15)
      strcpy(attacks[numAttacks].name, "Scratch");
    if (r == 16)
      strcpy(attacks[numAttacks].name, "Jab");
    if (r == 17)
      strcpy(attacks[numAttacks].name, "Grapple");
    if (r == 18)
      strcpy(attacks[numAttacks].name, "KnockDown");
    if (r == 19)
      strcpy(attacks[numAttacks].name, "Ignite");
    if (r == 0)
      strcpy(attacks[numAttacks].name, "Swing");
    
  //Set random numbers to every stat
    r = rand() / (RAND_MAX / MAX_ATTACK_STAT) + 1;
    attacks[numAttacks].power = r;
    r = rand() / (RAND_MAX / MAX_ATTACK_STAT) + 1;
    attacks[numAttacks].speed = r;
    r = rand() / (RAND_MAX / MAX_ATTACK_STAT) + 1;
    attacks[numAttacks].accuracy = r;
    
  //Confirm completion
    return 0;
  }
  
  
  
/*
Precondition: array of attacks and amount of attacks that already exist
Postcondition: integer
Actions:
Opens a file from the user to create an attack to their specifications
*/
  int createAttack(struct Attack attacks[], int numAttacks){
    
  //Declare variables
    FILE *ifp1;
    char fileName[MAX_NAME];
    int c;
    
  //Fill attack name with end-characters
    for (c = 0; c < MAX_NAME; c++){
      attacks[numAttacks].name[c] = '\0';
    }
    
  //Set parameters of attack file
    printf("Create a .txt file in the following form (do not include titles):\n");
    printf("<Name>\n");
    printf("<Power>\n");
    printf("<Speed>\n");
    printf("<Accuracy>\n\n");
    printf("Every stat can be any number 10-50.\n\n");
    printf("What is the full name of your attack file?\n");
    scanf("%s", fileName);
    
  //Open the attack file
    ifp1 = fopen(fileName, "r");
    
  //Scan to complete an Attack structure
    fscanf(ifp1, "%s %d %d %d", attacks[numAttacks].name, &attacks[numAttacks].power, &attacks[numAttacks].speed, &attacks[numAttacks].accuracy);
    
  //Close the attack's file
    fclose(ifp1);
    
  //Check for stat limitations
    if (attacks[numAttacks].name[0] == '\0' || attacks[numAttacks].power > MAX_ATTACK_STAT || attacks[numAttacks].speed > MAX_ATTACK_STAT || attacks[numAttacks].accuracy > MAX_ATTACK_STAT || attacks[numAttacks].power < MIN_ATTACK_STAT || attacks[numAttacks].speed < MIN_ATTACK_STAT || attacks[numAttacks].accuracy < MIN_ATTACK_STAT){
      printf("Oops, invalid entry!\n");
    for (c = 0; c > MAX_NAME; c++){
      attacks[numAttacks].name[c] = '\0';
    }
    attacks[numAttacks].power = (int) NULL;
    attacks[numAttacks].speed = (int) NULL;
    attacks[numAttacks].accuracy = (int) NULL;
    return 1;
    }
    
  //Confirm completion
    return 0;
  }
  
  
  
/*
Precondition: monster array, amount of monsters, integer, name of monster being removed
Postcondition: integer
Actions:
Clears the name of a monster that the user does not want in the game from the monsters array
*/
  int removeMonster(struct Monster monsters[], int numMonsters, int choose, char deleteName[]){
    
  //Declare variables
    int c;
    int i;
    int boolV = 0;
    char dName[MAX_NAME];
    
    if (choose == ON){
    
    //Fill deleteing monster's name with end-characters
      for (c = 0; c > MAX_NAME; c++){
        dName[c] = '\0';
      }
      
    //Ask for name of monster being deleted
      printf("What is the name of the monster being removed?\n");
      scanf("%s", dName);
    //Loop to find monster with matching name
      for (c = 0; c < numMonsters; c++){
        if (strcmp(dName, monsters[c].name) == 0){
          for (i = 0; i < MAX_NAME; i++){
            monsters[c].name[i] = '\0';
          }
         boolV = 1;
        }
      }
    }
    
    else{
    //Loop to find monster with matching name
      for (c = 0; c < numMonsters; c++){
        if (strcmp(deleteName, monsters[c].name) == 0){
          for (i = 0; i < MAX_NAME; i++){
            monsters[c].name[i] = '\0';
          }
          boolV = 1;
        }
      }
    }
    
  //Report if the removal was succussful
    if (boolV == 1)
      return 1;
    else
      return 0;
    
    return 0;
  }
  

  
/*
Precondition: none
Postcondition: integer
Actions:
Prints a menu with toggle options
*/
  int options(void){
    
  //Declare variable
    int choice;
    
  //Present the options
    printf("Select one:\n");
    printf("  [1]  Toggle: Use default monsters\n");
    printf("  [2]  Toggle: Select monster to begin with\n");
    printf("  [3]  Leave options menu\n\n");
    scanf("%d", &choice);
    
  //Complete toggles
    if (choice == 1)
      return 1;
    else if (choice == 2)
      return 2;
    else if (choice == 3)
      return 0;
    else
      printf("Invalid selection\n");
    
  //Confirm completion
    return 0;
  }
  
  
  
/*
Precondition: array of monsters
Postcondition: integer
Actions:
Prints summaries of all the deafault monsters
*/
  int showDefaults(struct Monster monsters[]){
  
  //Declare variables
    int c = 0;
    int i = 0;
    
  //Loop to print a summary of every monster
    printf("Summaries of default monsters display in the following form:\n");
    printf("MonsterName: Power, Defense, Speed, Health, Accuracy, Ellusiveness\n");
    printf("  AttackName: Power, Speed, Accuracy\n");
    printf("  AttackName: Power, Speed, Accuracy\n");
    printf("  AttackName: Power, Speed, Accuracy\n");
    printf("  AttackName: Power, Speed, Accuracy\n\n");
    for (c = 0; c < DEFAULT_MONSTERS; c++){
      if (monsters[c].name[0] != '\0'){
        printf("%11s: %3d, %3d, %3d, %3d, %3d, %3d\n", monsters[c].name, monsters[c].power, monsters[c].defense, monsters[c].speed, monsters[c].healthMax, monsters[c].accuracy, monsters[c].ellusiveness);
        for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
          printf("%11s: %3d, %3d, %3d\n", monsters[c].mAttacks[i].name, monsters[c].mAttacks[i].power, monsters[c].mAttacks[i].speed, monsters[c].mAttacks[i].accuracy);
        }
        printf("\n");
      }
    }
    
  //Confirm completion
    return 0;
  }


  
/*
Precondition: monsters array, integer toggles for options, amount of monsters, and pointers to the high scores of the hghest level achieved by both the player and his monster
Postcondition: integer
Actions:
Prints map with player on it, creates the player, displays many choices for userto pickfrom while playing
*/
  int startGame(struct Monster monsters[], int defaultsT, int monsterT, int numMonsters, int *highMonster, int *highPlayer){
    
  //Declare variables
    struct Character player;
    int map[MAP_SIZE][MAP_SIZE];
    int r = 0;
    int c = 0;
    int i = 0;
    int moves = 0;
    int choice = 0;
    int confirm = 0;
    char monster[MAX_NAME];
    
  //Fill player statistics
    player.experience = 0;
    player.experienceFull = LEVEL_UP;
    player.level = 1;
    
  //Delete default characters if requested 
    if (defaultsT == OFF){
      if (numMonsters == 10){
        printf("ERROR: Please import a monster!\n\n");
        return 0;
      }
      for (i = 0; i < DEFAULT_MONSTERS; i++){
        removeMonster(monsters, DEFAULT_MONSTERS, OFF, monsters[i].name);
      }
    }
    
  //Fill the monster's name with end-characters
    for (c = 0; c < MAX_NAME; c++){
      player.monster.name[c] = '\0';
    }  
    
  //Make a monster monster
    if (monsterT == OFF){
      do{
      //Generate a random index for the starting monster
        r = rand() / (RAND_MAX / (numMonsters));
      //Check to make sure selected monster was not removed
        if (monsters[r].name[0] != '\0'){
        //Set monster as the randomly selected monster
          player.monster = monsters[r];
          player.monster.experience = 0;
          player.monster.experienceFull = LEVEL_UP;
          player.monster.level = 1;
          player.monster.healthMax *= HEALTH_BOOST;
          player.monster.healthAvail *= HEALTH_BOOST;
        //Print summary of starting monster
          printf("Starting Monster:\n");
          printf("MonsterName: Power, Defense, Speed, Health, Accuracy, Ellusiveness\n");
          printf("%11s:  %2d,  %2d,  %2d,  %2d,  %2d,  %2d\n", player.monster.name, player.monster.power, player.monster.defense, player.monster.speed, player.monster.healthMax, player.monster.accuracy, player.monster.ellusiveness);
          printf("\nAttackName: Power, Speed, Accuracy\n");
          for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
            if (player.monster.mAttacks[i].name[0] != '\0'){
              printf(" %9s:  %2d,  %2d,  %2d\n", player.monster.mAttacks[i].name, player.monster.mAttacks[i].power, player.monster.mAttacks[i].speed, player.monster.mAttacks[i].accuracy);
            }
          }
          printf("\n");
        }
      } while (monsters[r].name[0] == '\0');
    }
    
  //Allow the user to choose their own starting monster
    else if (monsterT == ON){
    //Fill monster choice name with end-characters
      for (i = 0; i < MAX_NAME; i++){
        monster[i] = '\0';
      }
      do{
      //Ask for name of starting monster
        printf("What is the name of monster you would like to start with?\n");
        scanf("%s", monster);
        for (c = 0; c < numMonsters; c++){
          if (strcmp(monster, monsters[c].name) == 0){
          //Set the monster as the randomly selected monster
            player.monster = monsters[c];
            player.monster.experience = 0;
            player.monster.experienceFull = LEVEL_UP;
            player.monster.level = 1;
            player.monster.healthMax *= HEALTH_BOOST;
            player.monster.healthAvail *= HEALTH_BOOST;
          //Print summary of starting monster
            printf("\nStarting Monster:\n");
            printf("MonsterName: Power, Defense, Speed, Health, Accuracy, Ellusiveness\n");
            printf("%11s:  %2d,  %2d,  %2d,  %2d,  %2d,  %2d\n", player.monster.name, player.monster.power, player.monster.defense, player.monster.speed, player.monster.healthMax, player.monster.accuracy, player.monster.ellusiveness);
            printf("\nAttackName: Power, Speed, Accuracy\n");
            for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
              if (player.monster.mAttacks[i].name[0] != '\0'){
                printf(" %9s:  %2d,  %2d,  %2d\n", player.monster.mAttacks[i].name, player.monster.mAttacks[i].power, player.monster.mAttacks[i].speed, player.monster.mAttacks[i].accuracy);
              }
            }
            printf("\n");
          }
        }
        if (player.monster.name[0] == '\0'){
          printf("\nInvalid monster name. Try again!\n\n");
        }
      } while (player.monster.name[0] == '\0');
    }
    
  //Initialize the map to be empty
    for (r = 0; r < MAP_SIZE; r++){
      for (c = 0; c < MAP_SIZE; c++){
        map[r][c] = EMPTY;
      }
    }
    
  //Randomly enter 20 monsters on to the map
    for (i = 0; i < STARTING_MONSTERS; i++){
      confirm = randomSpawn(map);
      if (confirm != 1)
        i--;
    }
    
  //Place the player on a random spot of the map
    r = rand() / (RAND_MAX / (MAP_SIZE));
    c = rand() / (RAND_MAX / (MAP_SIZE));
    map[r][c] = PLAYER;
    
  //Loop to play the game
    do{
  //Print a blank map, excpept for the location of the player
    printf("Monster Master Map:\n");
    for (r = 0; r < MAP_SIZE; r++){
      printf(" _ ");
    }
    printf("\n");
    for (r = 0; r < MAP_SIZE; r++){
      for (c = 0; c < MAP_SIZE; c++){
        if (map[r][c] == PLAYER)
          printf("|X|");
        else 
          printf("|_|");
      }
      printf("\n");
    }

    //Print menu for gameplay
      printf("\nPlease select one:\n");
      printf("  [1]  Move\n");
      printf("  [2]  Look at Monster\n");
      printf("  [3]  Show Character Statistics\n");
      printf("  [4]  Look at High Score\n");
      printf("  [5]  Quit\n\n");
      scanf("%d", &choice);
      printf("\n");
      
      if (choice == 1){
        confirm = move(map, player, monsters, moves, numMonsters, highMonster, highPlayer);
        if (confirm == WIN){
        //User's monster gains experience
          r = rand() / (RAND_MAX / MAX_EXP_MULTIPLIER);
          player.monster.experience += EXP_GAIN * r;
          if (player.monster.experience >= player.monster.experienceFull)
        //Monster levels up if reaches full experience
          monsterLevelUp(player.monster, highMonster);
        //The character gainsexperience for winning
          r = rand() / (RAND_MAX / MAX_EXP_MULTIPLIER);
          player.experience += EXP_GAIN * r;
          if (player.experience >= player.experienceFull)
        //The playerlevels up if his experience if full
          playerLevelUp(player, highPlayer);
          moves++;
        }
        else if (confirm == NEITHER)
          moves++;
        else if (confirm == LOSE){
          printf("\n~~~~~~~~~~ GAME OVER ~~~~~~~~~~\n\n");
          return 0;
        }
        
      }
      
      else if (choice == 2){
        displayMonster(player);
      }
      
      else if (choice == 3){
        characterStats(player);
      }
      
      else if (choice == 4){
        highScore(highMonster, highPlayer);
      }
      
      else if (choice == 5){
        return 0;
      }
      
      else{
        printf("Invalid selection!\n");
      }
      
    } while (choice != QUIT);
            
  //Confirm completion
    return 0;
  }
  

  
/*
Precondition: 2-dimensional array of integers that represent a map
Postcondition: integer
Actions:
Finds a random spot on the 2D array that has not already been marked full and marks it full
*/
  int randomSpawn(int map[][MAP_SIZE]){
  
  //Declare variables
    int r = 0;
    int c = 0;
    
  //Make a random row and collumn
    r = rand() / (RAND_MAX / (MAP_SIZE));
    c = rand() / (RAND_MAX / (MAP_SIZE));
  //Check if random spot is already occupied
    if (map[r][c] != OCCUPIED){
    //Change empty spot to an occupied spot
      map[r][c] = OCCUPIED;
    //Confirm completion
      return 1;
    }

  //Report failure
    return 0;
  }


  
/*
Precondition: 2D array ofintegers, character structure, monstersarray, amount of moves, amount of monsters, and pointers to the high scores for the highest player and monster levels reached
Postcondition: integer
Actions:
Changes the position of the player on the 2D map and initiates battle with a monster if encountered
*/
  int move(int map[][MAP_SIZE], struct Character player, struct Monster monsters[], int moves, int numMonsters, int *highMonster, int *highPlayer){
  
  //Declare variables
    int direction = 0;
    int i = 0;
    int r = 0;
    int c = 0;
    int confirm = 0;
    int outcome = NEITHER;
    
  //Ask which direction to move in
    printf("Please select a direction:\n");
    printf("  [1]  Up\n");
    printf("  [2]  Down\n");
    printf("  [3]  Left\n");
    printf("  [4]  Right\n\n");
    scanf("%d", &direction);
    
  //Find where the player is on the map already
    for (r = 0; r < MAP_SIZE; r++){
      for (c = 0; c < MAP_SIZE; c++){
        if (map[r][c] == PLAYER){
        
        //Make appropriate movement
          if (direction == 1 && r != 0){
          //Check for monster on new spot
            if (map[r-1][c] == OCCUPIED){
            //Enter battle scene with monster on new spot
              outcome = battle(player, monsters, moves, numMonsters, highMonster, highPlayer);
            //In case the players wins the battle
              if (outcome == WIN){
              //Spawn a new monster in a spot that is currently empty
                while (confirm == 0)
                  confirm = randomSpawn(map);
                printf("\nMoved up!\n");
              }
            }
          //Move player on to empty spot
            map[r-1][c] = PLAYER;
            map[r][c] = EMPTY;
            return outcome;
          }
          
          else if (direction == 2 && r != MAP_SIZE - 1){
          //Check for monster on new spot
            if (map[r+1][c] == OCCUPIED){
            //Enter battle scene with monster on new spot
              outcome = battle(player, monsters, moves, numMonsters, highMonster, highPlayer);
            //In case the players wins the battle
              if (outcome == WIN){
              //Spawn a new monster in a spot that is currently empty
                while (confirm == 0)
                  confirm = randomSpawn(map);
                printf("\nMoved down!\n");
              }
            }
          //Move player on to empty spot
            map[r+1][c] = PLAYER;
            map[r][c] = EMPTY;
            return outcome;
            
          }
          
          else if (direction == 3 && c != 0){
          //Check for monster on new spot
            if (map[r][c-1] == OCCUPIED){
            //Enter battle scene with monster on new spot
              outcome = battle(player, monsters, moves, numMonsters, highMonster, highPlayer);
            //In case the players wins the battle
              if (outcome == WIN){
              //Spawn a new monster in a spot that is currently empty
                while (confirm == 0)
                  confirm = randomSpawn(map);
                printf("\nMoved left!\n");
              }
            }
          //Move player on to empty spot
            map[r][c-1] = PLAYER;
            map[r][c] = EMPTY;
            return outcome;
          }
          
          else if (direction == 4 && c != MAP_SIZE - 1){
          //Check for monster on new spot
            if (map[r][c+1] == OCCUPIED){
            //Enter battle scene with monster on new spot
              outcome = battle(player, monsters, moves, numMonsters, highMonster, highPlayer);
            //In case the players wins the battle
              if (outcome == WIN){
              //Spawn a new monster in a spot that is currently empty
                while (confirm == 0)
                  confirm = randomSpawn(map);
                printf("\nMoved right!\n");
              }
            }
          //Move player on to empty spot
            map[r][c+1] = PLAYER;
            map[r][c] = EMPTY;
            return outcome;
          }
        //Do not allow to pick out of the range given
          else
            printf("Invalid selection\n\n");
        }
      }
    }
  //Report failure to move
    return -1;
  }
  

  
/*
Precondition: Character structure
Postcondition: integer
Actions:
Prints a summary of the statistics about the monsterused by the player
*/
  int displayMonster(struct Character player){
  
  //Declare variables
    int c = 0;
    int i = 0;
    
  //Introduce monster to user
    printf("Your Monster:\n\n");
  //Print a summary of the monster
    printf("MonsterName: Power, Defense, Speed, Health, Accuracy, Ellusiveness\n");
    printf("%11s:  %2d,  %2d,  %2d,  %2d,  %2d,  %2d\n\n", player.monster.name, player.monster.power, player.monster.defense, player.monster.speed, player.monster.healthMax, player.monster.accuracy, player.monster.ellusiveness);
    printf("AttackName: Power, Speed, Accuracy\n");
    for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
      printf(" %9s:  %2d,  %2d,  %2d\n", player.monster.mAttacks[i].name, player.monster.mAttacks[i].power, player.monster.mAttacks[i].speed, player.monster.mAttacks[i].accuracy);
    }
    printf("\nExperince: %d/%d\n",player.monster.experience, player.monster.experienceFull);
        printf("Level: %d\n\n", player.monster.level);

  //Confirm completion
    return 0;
  }


  
/*
Precondition: character structure
Postcondition: integer
Actions:
Prints a summary of the charcter's experience
*/
  int characterStats(struct Character player){
    
  //Declare variables
    int i = 0;
    
  //Print summary of the player's statistics
    printf("Player Summary:\n\n");
    printf("Experience: %d/%d\n", player.experience, player.experienceFull);
    printf("Level: %d\n\n", player.level);
    
  //Confirm completion
    return 0;
  }
   
 
  
/*
Precondition: pointers to the high score for the highest levels achieved by the player and monster
Postcondition: 
Actions:

*/
  int highScore(int *highMonster, int *highPlayer){
  
  //Print the highest levels achieved since running the game
    printf("Highest monster level: %d\n", *highMonster);
    printf("Highest player level: %d\n\n", *highPlayer);
  
  //Confirm completion
    return 0;
  }
  
  

/*
Precondition: character strucutre, monsters array, amount of moves and monsters, pointers to the high scores of highest level achieved by the player and his monster
Postcondition: integer
Actions:
Carries out the math of the battle and presents the options for the playerto choose from when battling with their monster
*/
  int battle(struct Character player, struct Monster monsters[], int moves, int numMonsters, int *monsterHigh, int *highPlayer){
  
  //Declared variables
    struct Monster enemy;
    struct Attack playerAttack;
    struct Attack enemyAttack;
    int i = 0;
    int r = 0;
    int rE = 0;
    int rD = 0;
    int c = 0;
    int t = 0;
    int battleIndex = 0;
    int choice = OFF;
    int boolV = OFF;
    char attack[MAX_NAME];
  
  //Create enemy monster
    do{
    //Generate a random index for the starting monster
      r = rand() / (RAND_MAX / (numMonsters));
    //Check to make sure selected monster was not removed
      if (monsters[r].name[0] != '\0'){
      //Set enemy as the randomly selected monster
        enemy = monsters[r];
      }
    } while (monsters[r].name[0] == '\0');
  
  //Increase all stats of enemy by amount of moves made by player
    enemy.power += moves;
    enemy.defense += moves;
    enemy.speed += moves;
    enemy.healthMax += moves;
    enemy.healthAvail += moves;
    enemy.accuracy += moves;
    enemy.ellusiveness += moves;
  
  //Loop through battle scene until one of the monsters run out of health
    do{
    //Fill attack with end-characters
      for (i = 0; i < MAX_NAME; i++){
        attack[i] = '\0';
      }
    
    //Display the action scene
      actionScene(player.monster, enemy);
    
    //Prompt user to choose an attack
      printf("Make a selection:\n");
      c = 0;
      for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
        if (player.monster.mAttacks[i].name[0] != '\0'){
          printf("  [%d]  %s\n", i, player.monster.mAttacks[i].name);
          c++;
        }
      }
      scanf("%d", &choice);
    
      if (choice >= 0 && choice <= c){
      //Set the attack that the user wants to use
          for (i = 0; i < MAX_MONSTER_ATTACKS; i++){
            if (strcmp(player.monster.mAttacks[i].name, player.monster.mAttacks[choice].name) == 0){
              playerAttack = player.monster.mAttacks[i];
              boolV = ON;
            }
          }
          if (boolV != ON){
            printf("Invalid selection\n");
            continue;
          }
      
      //Enemy chooses random attacks
        r = rand() / (RAND_MAX / (MAX_MONSTER_ATTACKS));
        enemyAttack = enemy.mAttacks[r];
      
      //Determine the faster attack/monster combination (enemy wins tie-breaker)
        if (playerAttack.speed + player.monster.speed > enemyAttack.speed + enemy.speed){
        //Random bonus to ellusiveness
          rE = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          printf("YOU: %s used %s!\n", player.monster.name, playerAttack.name);
        //Determine hit rate
          if (playerAttack.accuracy + player.monster.accuracy >= enemy.ellusiveness + rE){
          //Random bonus to defense
            rD = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          //Player's monster attacks firt
            if ((playerAttack.power + player.monster.power - (enemy.defense + rD)) <= 0)
            //One damage point is done if defense is stronger than power
              enemy.healthAvail -= 1;
            else
              enemy.healthAvail -= (playerAttack.power + player.monster.power - (enemy.defense + rD));
          //Determine if critical hit
            if (rE + player.monster.accuracy >= CRITICAL_HIT_THRESHOLD){
              //Critical hit causes double damage
              if ((playerAttack.power + player.monster.power - (enemy.defense + rD)) <= 0)
               enemy.healthAvail -= 1;
              else
               enemy.healthAvail -= (playerAttack.power + player.monster.power - (enemy.defense + rD));
              printf("A critical hit!!\n");
            }
          }
        //Attack misses if accuracy is outweighed by ellusiveness
          else
            printf("%s missed!", player.monster.name);
          actionScene(player.monster, enemy);
          
        //Battle is won if the enemy dies
          if (enemy.healthAvail <= 0){
            printf("\nYou defeated the %s!\n", enemy.name);
            return WIN;
          }            
      
          rE = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          printf("Enemy: %s used %s!\n", enemy.name, enemyAttack.name);
        //Determine hit rate
          if (enemyAttack.accuracy + enemy.accuracy >= player.monster.ellusiveness + rE){
            rD = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          //Enemy attacks second
            if((enemyAttack.power + enemy.power - (player.monster.defense + rD)) <= 0)
              player.monster.healthAvail -= 1;
            else
              player.monster.healthAvail -= (enemyAttack.power + enemy.power - (player.monster.defense + rD));
          //Determine critical hit
            if (rE + enemy.accuracy >= CRITICAL_HIT_THRESHOLD){
              if((enemyAttack.power + enemy.power - (player.monster.defense + rD)) <= 0)
                player.monster.healthAvail -= 1;
              else
                player.monster.healthAvail -= (enemyAttack.power + enemy.power - (player.monster.defense + rD));
              printf("A critical hit!!\n");
            }
          }
          else
            printf("%s missed!", enemy.name);
          actionScene(player.monster, enemy);
          
        //Battle is lost if your monster is dead
          if (player.monster.healthAvail <= 0){
            printf("\nYou were defeated by the %s....\n", enemy.name);
            return LOSE;
          }
        }
      
        else{
          rE = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          printf("Enemy: %s used %s!\n", enemy.name, enemyAttack.name);
        //Determine hit rate
          if (enemyAttack.accuracy + enemy.accuracy >= player.monster.ellusiveness + rE){
            rD = rand() / (RAND_MAX / (MAX_STAT_BONUS));
        //Enemy attacks first
          if((enemyAttack.power + enemy.power - (player.monster.defense + rD)) <= 0)
            player.monster.healthAvail -= 1;
          else
            player.monster.healthAvail -= (enemyAttack.power + enemy.power - (player.monster.defense + rD));
          //Determine critical hit
            if (rE + enemy.accuracy >= CRITICAL_HIT_THRESHOLD){
              if((enemyAttack.power + enemy.power - (player.monster.defense + rD)) <= 0)
                player.monster.healthAvail -= 1;
              else
                player.monster.healthAvail -= (enemyAttack.power + enemy.power - (player.monster.defense + rD));
              printf("A critical hit!!\n");
            }
          }
          else
            printf("%s missed!", enemy.name);
          actionScene(player.monster, enemy);
      
        //Battle is lost if you monster is dead
          if (player.monster.healthAvail <= 0){
            printf("\nYou were defeated by the %s....\n", enemy.name);
            return LOSE;
          }
      
          rE = rand() / (RAND_MAX / (MAX_STAT_BONUS));
          printf("YOU: %s used %s!\n", player.monster.name, playerAttack.name);
        //Determine hit rate
          if (playerAttack.accuracy + player.monster.accuracy >= enemy.ellusiveness + rE){
            rD = rand() / (RAND_MAX / (MAX_STAT_BONUS));
        //Player's monster attacks second
          if ((playerAttack.power + player.monster.power - (enemy.defense + rD)) <= 0)
            enemy.healthAvail -= 1;
          else
            enemy.healthAvail -= (playerAttack.power + player.monster.power - (enemy.defense + rD));
        //Determine critical hit
          if (rE + player.monster.accuracy >= CRITICAL_HIT_THRESHOLD){
            if ((playerAttack.power + player.monster.power - (enemy.defense + rD)) <= 0)
              enemy.healthAvail -= 1;
            else
              enemy.healthAvail -= (playerAttack.power + player.monster.power - (enemy.defense + rD));
            printf("A critical hit!!\n");
            }
          }
          else
            printf("%s missed!", player.monster.name);
          actionScene(player.monster, enemy);
      
        //Battle is won if the enemy dies
          if (enemy.healthAvail <= 0){
            printf("\nYou defeated the %s!\n", enemy.name);
            return WIN;
          }
        }          
      }           
      else        
      printf("Invalid selection\n"); 
      
      printf("=================================\n");
      
    } while (r != -1);
    
  return -1;
  }

  
  
/*
Precondition: two monster structures that are in a battle
Postcondition: integer
Actions:
Prints a text-made picture of twobeings and avisual representation of their health points
*/
  int actionScene(struct Monster battler, struct Monster enemy){
    
  //Declare variables
    double i = 0;
    double battlerRatio = (double)battler.healthAvail / (double)battler.healthMax;
    double enemyRatio = (double)enemy.healthAvail / (double)enemy.healthMax;
    
  //Many print statements
    printf("\n   0            0    \n");
    printf("  \\|/          \\|/ \n");
    printf("   |     vs     |    \n");
    printf("  / \\          / \\ \n");
    printf("_______      _______ \n");
    printf("|");
    if (battlerRatio > 0){
      for (i = 0; i < battlerRatio * 5.0; i++){
          printf("X");
      }
      for (i = 4; i >= battlerRatio * 5.0; i--){
          printf(" ");
      }
    }
    else
      printf("     ");
    printf("|      |");
    if (enemyRatio > 0){
      for (i = 4; i >= enemyRatio * 5.0; i--){
          printf(" ");
      }
      for (i = 0; i < enemyRatio * 5.0; i++){
          printf("X");
      }
    }
    else
      printf("     ");
    printf("|\n");
    printf(" -----        -----\n");
    printf("%-8s    %8s\n", battler.name, enemy.name);
    if (battler.healthAvail < 0)
      battler.healthAvail = 0;
    if (enemy.healthAvail < 0)
      enemy.healthAvail = 0;
    printf("HP:%3d        HP:%3d\n\n", battler.healthAvail, enemy.healthAvail);
    
  //Confirm completion
    return 0;
  }



/*
Precondition: monster structure and high score for monster level
Postcondition: integer
Actions:
Increasethe level of a monster and apporpriately increase its stats for its accomplishment
*/
  int monsterLevelUp(struct Monster monster, int *highMonster){
  
  //Declare variables
    int r = 0;
    
  //Print message announcing new level
    printf("\nYour %s has leveled up!\n\n", monster.name);
    
  //Say what monster leveled up
    printf("%s level up!\n", monster.name);
    
  //Increase stats of monster
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.power += r;
    printf("Power +%d\n", r);
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.defense += r;
    printf("Defense +%d\n", r);
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.speed += r;
    printf("Speed +%d\n", r);
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.healthMax += r;
    monster.healthAvail = r;
    printf("Health +%d\n", r);
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.accuracy += r;
    printf("Accuracy +%d\n", r);
    r = rand() / (RAND_MAX / MAX_STAT_INCREASE) + 1;
    monster.ellusiveness += r;
    printf("Ellusiveness +%d\n\n", r);
    
  //Increase the level stat and start over on experience
    monster.level += 1;
    monster.experience -= monster.experienceFull;
    
  //Increase amount of experience needed to level up
    monster.experienceFull += 10;
    
    
  //Set new highest monster level achieved
    if (monster.level > *highMonster){
      *highMonster = monster.level;
    }
    
  //Confirm Completion
    return 0;
  }
  
  
  
/*
Precondition: character structure and high score for high player level reached
Postcondition: integer
Actions:
Increase the level of the player for the sole purpose of keeping a running high score
*/
  int playerLevelUp(struct Character player, int *highPlayer){
  
  //Print message announcing new level
    printf("\nYour player has leveled up!\n\n");
  
  //Increase the level stat and start over on experience
    player.level += 1;
    player.experience -= player.experienceFull;
    
  //Increase amount of experience needed to level up
    player.experienceFull += 10;
    
  //Set new highest player level achieved
    if (player.level > *highPlayer){
      *highPlayer = player.level;
    }
    
  //Confirm Completion
    return 0;
  }
