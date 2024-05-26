#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>

//define define new color
#define COLOR_PINK 8
#define COLOR_BROWN 9
#define COLOR_BEIGE 10
#define COLOR_BEIGE_LIGHT 11

#define MAX_ROOM 100

typedef struct{
    int x;
    int y;
} Position;

typedef struct {
    char* name;
    int id;
    Position coordinates;
    int weight;
    int single_use;
    int stack;
    int max_stack;
    int augmentation;
    int what_augmentation;
    /*
    0 nothing 
    1 life 
    2 strength
    3 armor
    4 Weapon
    5 score
    */
}Object;

//for Weapon
typedef enum{
    RANGED,
    CC,
}Type;
//
typedef struct {
    char* name;
    int id;
    Position coordinates;
    Type type;
    int range;
    int dmg;
    int weight;
}Weapon;

typedef struct {
    char* name;
    int id;
    Position coordinates;
    int weight;
    int shield;
}Armor;

//for enemy
typedef enum{
    GIGA_ROBOT,
    DRONE,
    ALIEN,
    ROBOT,
    BLOB,
    TURRET,
}Names;

typedef enum{
    ALL_IN,
    FLYING,
    RANGE,
}Behave;
//
typedef struct {
    Names name;
    Position coordinates;
    int life;
    int armor;
    int strength;
    int speed;
    int range;
    int orientation;
    time_t cooldown;
    Behave type;
    int XP;
}Enemy;

typedef struct {
  int x;
  int y;
  int room_num1;
  int room_num2;
  int direction;
} Door;

typedef struct {
  int room_door[4];
  int num_door;
  int x_min;
  int x_max;
  int y_min;
  int y_max;
  int nbr_enemy;
  Enemy* tab_enemy;
  int nbr_object;
  Object* tab_object;
  int nbr_armor;
  Armor* tab_armor;
  int nbr_blade;
  Weapon* tab_blade;
}Room;

typedef struct{
    Position coordinates;
    int room;
    int orientation; //o up 1 right 2 down 3 left
    int life;
    time_t start_hit;
    int max_life;
    int level;
    int XP;
    int score;
    int strength;
    int nbr_object_inventory;
    Object* inventory;
    Weapon blade;
    Armor stuff;
} Hero;

int min(int a,int b);

int absoluteValue(int a);

Weapon searchBlade(int ID, FILE* file);

Armor searchStuff(int ID, FILE* file);

Object searchObject(int ID, FILE* file);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function Hero
Hero buildHero(FILE* blade_file, FILE* stuff_file);
    
void displayGame(int screen_length, int screen_width, Hero player, WINDOW* background, time_t timer, int time_pause, int time_play, int time_to_play, int* end);

void useObject(Hero* player, int position_stuff);

int collectObject(Hero* player, Room* a);

void collectArmor(Hero* player, Room* a, int screen_length, int screen_width, WINDOW* background, time_t timer, int time_pause, int time_play, int time_to_play, int* end);

void collectBlade(Hero* player, Room* a, int screen_length, int screen_width, WINDOW* background, time_t timer, int time_pause, int time_play, int time_to_play, int* end);
 
void displayHit(Hero player, int screen_length, int screen_width);

void youHit(Hero* player, Room* a);

void beHit(Hero* player, Room* a);
    
void winLevel(Hero* player);

void death(Hero* player);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Room function
Room createMainRoom();

void createMainDoor(Door *tab_door);

int searchNearDoor (Door * tab_door, Door test_door, int door_count);

int searchReallyNearDoor (Door possible_door, Door test_door);

int confirmOverlap (Room * room_size_tab, Room new_room, int room_count);

int confirmDoorLock (Door * tabDoor, Door testDoor, int Doorcount, Room * Roomsizetab, int Roomcount);

int confirmDoororientation (Room * Roomsizetab, Room newRoom, int Roomcount,Door prevDoor);

int adaptNextSizeRoomFuse (Room * new_room, int room_count, Door * tab_door, Door test_door, int door_count);


Room generateRoom (int* seed, int *max_room, Room * tab_room, Door * prev_door, int *room_count, Door * tab_door, int *door_count);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//enemy function
double calculateDistance(Position pos1, Position pos2);

int checkRange(Enemy* a, Hero* player);

Enemy defEnemy(Enemy a);

void moveMob(Enemy* a, Hero* player, Room* b);

void enemySpawn(int number, Room* b, int* seed);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//think function
void stuffSpawn(Room* a, FILE* Object, FILE* Blade, FILE* Armor, int* seed);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//display function
void displayMenu(int screen_length, int screen_width, int menu_cursor, WINDOW* background);

void displayNameMenu(int screen_length, int screen_width, WINDOW* background, char* name);

int searchSave(char* name, FILE* file);

void displaySeedMenu(int screen_length, int screen_width, WINDOW* background, int seed, int count);

void displayNameLoadMenu(int screen_length, int screen_width, WINDOW* background, char* name, int load_menu_cursor);

void displayGame(int screen_length, int screen_width, Hero player, WINDOW* background, time_t timer, int time_pause, int time_play, int time_to_play, int* end);

void displayDungeon(int screen_length, int screen_width, Hero player, int door_count, Door* tab_door, int room_count, Room* tab_room, WINDOW* dungeon);

void displayInventoryMenu(int screen_length, int screen_width, Hero player, WINDOW* dungeon, int inventory_cursor);