#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include <locale.h>

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

int min(int a,int b){
    if(a<=b){
        return a;
        }
    return b;
}

int absoluteValue(int a){
    if(a<0){
        return -a;
        }
    return a;
}

Weapon searchBlade(int ID, FILE* file){
    int verify, test, temp;
    Weapon blade;
	rewind(file);
    char c = getc(file);
	while(c != EOF){
		if(c == '@'){
            verify = fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
            }
            if(ID==test){
                blade.id = ID;
                blade.name = calloc(21,sizeof(char));
                if(blade.name == NULL){
                    printf("error calloc");
                    exit(3);
                }
                verify = fscanf(file, "%s", blade.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &temp);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                switch(temp){
                    case 1:
                        blade.type = RANGED;
                        break;
                    case 2:
                        blade.type = CC;
                        break;
                }
                verify = fscanf(file, "%d", &blade.range);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &blade.dmg);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &blade.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                return blade;
            }
        }
        c = getc(file);
    }
    printf("formatting error blade.txt");
    exit(12);
}

Armor searchStuff(int ID, FILE* file){
    int verify, test;
    char* verify_name = NULL;
    Armor stuff;
	rewind(file);
    char c = getc(file);
	while(c != EOF){
		if(c == '@'){
            verify = fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
            }
            if(ID==test){
                stuff.id = ID;
                stuff.name = calloc(21,sizeof(char));
                if(stuff.name == NULL){
                    printf("error calloc");
                    exit(3);
                }
                verify = fscanf(file, "%s", stuff.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &stuff.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &stuff.shield);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                return stuff;
            }
        }
        c = getc(file);
    }
    printf("formatting error stuff.txt");
    exit(12);
}

Object searchObject(int ID, FILE* file){
    int verify, test;
    Object think;
	rewind(file);
    char c = getc(file);
	while(c != EOF){
		if(c == '@'){
            verify = fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
            }
            if(ID == test){
                think.id = ID;
                think.name = calloc(21,sizeof(char));
                if(think.name == NULL){
                    printf("error calloc");
                    exit(3);
                }
                verify = fscanf(file, "%s", think.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &think.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &think.single_use);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &think.max_stack);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }

                verify = fscanf(file, "%d", &think.augmentation);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                verify = fscanf(file, "%d", &think.what_augmentation);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                }
                return think;
            }
        }
        c = getc(file);
    }
    printf("formatting error Object.txt");
    exit(12);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function Hero
Hero buildHero(FILE* blade_file, FILE* stuff_file){
    Hero player;
    player.coordinates.x = 0;
    player.coordinates.y = 0;
    player.room = 0;
    player.orientation = 0;
    player.life = 100;
    player.start_hit = 0;
    player.max_life = 100;
    player.level = 0;
    player.XP = 0;
    player.score = 0;
    player.strength = 10;
    player.nbr_object_inventory = 0;
    player.inventory=calloc(15,sizeof(Object));
    if(player.inventory == NULL){
        printf("error calloc inventory");
        exit(2);
    }
    player.blade = searchBlade(0, blade_file);
    player.stuff = searchStuff(0, stuff_file);
    return player;
}
    
void displayGame(int screen_length, int screen_width, Hero player, WINDOW* background, time_t timer, int time_pause,
                 int time_play, int time_to_play, int* end);

void useObject(Hero* player, int position_stuff){
    //effect
    switch (player->inventory[position_stuff].what_augmentation){
        case 1:
            //life
            player->life += player->inventory[position_stuff].augmentation;
            if(player->life > player->max_life){
                player->life = player->max_life;
            }
            break;
        case 2:
            //strength
            player->strength += player->inventory[position_stuff].augmentation;
            break;
        case 3:
            //armor
            player->stuff.shield += player->inventory[position_stuff].augmentation;
            break;
        case 4:
            //armor
            player->blade.dmg += player->inventory[position_stuff].augmentation;
            break;
        case 5:
            //score
            player->score += player->inventory[position_stuff].augmentation;
            break;
    }
    if (player->inventory[position_stuff].single_use){
        player->inventory[position_stuff].stack--;
    }
    if(player->inventory[position_stuff].stack == 0){
        //delete stuff
        player->inventory[position_stuff] = player->inventory[player->nbr_object_inventory-1];
        player->inventory[player->nbr_object_inventory-1].id=0;
        player->nbr_object_inventory--;
    }
}

int collectObject(Hero* player, Room* a){
    Room* tab = a + player->room;
    
    for(int i=0;i<tab->nbr_object;i++){
        if(player->coordinates.x == tab->tab_object[i].coordinates.x &&
        player->coordinates.y == tab->tab_object[i].coordinates.y){
            for(int j=0;j<15;j++){
                if(player->inventory[j].id == tab->tab_object[i].id &&
                player->inventory[j].stack < player->inventory[j].max_stack){
                    player->inventory[j].stack++;
                    tab->tab_object[i] = tab->tab_object[tab->nbr_object];
                    tab->tab_object[tab->nbr_object].id = 0;
                    tab->nbr_object--;
                    return 1;
                }
                if(player->inventory[j].id == 0){
                    player->inventory[j] = tab->tab_object[i];

                    player->inventory[j].stack=1;
                    player->nbr_object_inventory++;

                    tab->tab_object[i] = tab->tab_object[tab->nbr_object];
                    tab->tab_object[tab->nbr_object].id = 0;
                    tab->nbr_object--;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void collectArmor(Hero* player, Room* a, int screen_length, int screen_width, WINDOW* background, time_t timer,
                  int time_pause, int time_play, int time_to_play, int* end){
    Room* tab = a + player->room;
    
    for(int i=0;i<tab->nbr_armor;i++){
        if(player->coordinates.x == tab->tab_armor[i].coordinates.x &&
        player->coordinates.y == tab->tab_armor[i].coordinates.y){
            int test1 = getch();
            do{
                //refresh the timer
                //display game
                displayGame(screen_length, screen_width, *player, background, timer, time_pause, time_play,
                            time_to_play, end);
                //verification
                attron(COLOR_PAIR(8));
                mvprintw(7, 4, "are you sure you want to change your stuff?");
                mvprintw(8, 4, "y/n");
                //name objet use
                mvprintw(9, 6, "name: %s           ",player->stuff.name);
                mvprintw(11, 6, "shield: %d        ",player->stuff.shield);
                mvprintw(13, 6, "weight: %d        ",player->stuff.weight);
                //name objet
                mvprintw(9, 20, "name:%s",tab->tab_armor[i].name);
                mvprintw(11, 20, "shield: %d",tab->tab_armor[i].shield);
                mvprintw(13, 20, "weight: %d",tab->tab_armor[i].weight);
                refresh();

                test1 = getch();
                //yes
                if(test1 == 121){
                    player->stuff = tab->tab_armor[i];
                    tab->tab_armor[i] = tab->tab_armor[tab->nbr_armor-1];
                    tab->nbr_armor--;
                }
                //no
                else if(test1 == 110){
                    tab->tab_armor[i] = tab->tab_armor[tab->nbr_armor-1];
                    tab->nbr_armor--;
                }
            }while(test1!=121 && test1!=110);
            attron(COLOR_PAIR(3));
        }
    }
}

void collectBlade(Hero* player, Room* a, int screen_length, int screen_width, WINDOW* background, time_t timer,
                  int time_pause, int time_play, int time_to_play, int* end){
    Room* tab = a + player->room;
    for(int i=0;i<tab->nbr_blade;i++){
        if(player->coordinates.x == tab->tab_blade[i].coordinates.x &&
        player->coordinates.y == tab->tab_blade[i].coordinates.y){
            int test1 = getch();
            do{
                //refresh the timer
                //display game
                displayGame(screen_length, screen_width, *player, background, timer, time_pause, time_play,
                            time_to_play, end);
                //verification
                attron(COLOR_PAIR(8));
                mvprintw(7, 4, "are you sure you want to change your blade?");
                mvprintw(8, 4, "y/n");
                refresh();
                //name objet use
                mvprintw(9, 6, "name: %s         ", player->blade.name);
                mvprintw(11, 6, "range: %d       ", player->blade.range);
                mvprintw(13, 6, "damage: %d      ", player->blade.dmg);
                mvprintw(15, 6, "weight: %d      ", player->blade.weight);
                //name objet
                mvprintw(9, 20, "name: %s", tab->tab_blade[i].name);
                mvprintw(11, 20, "range: %d", tab->tab_blade[i].range);
                mvprintw(13, 20, "damage: %d", tab->tab_blade[i].dmg);
                mvprintw(15, 20, "weight: %d", tab->tab_blade[i].weight);
                test1 = getch();
                //yes
                if(test1==121){
                    player->blade = tab->tab_blade[i];
                    tab->tab_blade[i] = tab->tab_blade[tab->nbr_blade-1];
                    tab->nbr_blade--;
                }
                //no
                else if(test1==110){
                    tab->tab_blade[i] = tab->tab_blade[tab->nbr_blade-1];
                    tab->nbr_blade--;
                }
            }while(test1 != 121 && test1 != 110);
            attron(COLOR_PAIR(3));
        }
    }
}
 
void displayHit(Hero player, int screen_length, int screen_width){
    attron(COLOR_PAIR(15));
    if(time(NULL)-player.start_hit>0 && time(NULL)-player.start_hit<=1){
        for(int i=0;i<=player.blade.range;i++){
            switch(player.orientation){
                case 0:
                    mvprintw(6+(screen_width-8)/2-i, 3+(screen_length-6)/2, "a");
                    break;
                case 1:
                    mvprintw(6+(screen_width-8)/2, 3+(screen_length-6)/2+i, "a");
                    break;
                case 2:
                    mvprintw(6+(screen_width-8)/2+i, 3+(screen_length-6)/2, "a");
                    break;
                case 3:
                    mvprintw(6+(screen_width-8)/2, 3+(screen_length-6)/2-i, "a");
                    break;
            }
        }
        refresh();
    }
}

void youHit(Hero* player, Room* a){
    Room* tab = a + player->room;

    switch (player->blade.type){
        case CC:
            for(int i=0;i<tab->nbr_enemy;i++){
                //search if there is an enemy in front of the player
                switch(player->orientation){
                    //up
                    case 0:
                        if(player->coordinates.x == tab->tab_enemy[i].coordinates.x &&
                        player->coordinates.y+player->blade.range >= tab->tab_enemy[i].coordinates.y){
                            tab->tab_enemy[i].life -= player->strength+player->blade.dmg;
                        }
                        break;
                    //right
                    case 1:
                        if(player->coordinates.y == tab->tab_enemy[i].coordinates.y &&
                        player->coordinates.x+player->blade.range >= tab->tab_enemy[i].coordinates.x){
                            tab->tab_enemy[i].life -= player->strength+player->blade.dmg;
                        }
                        break;
                    //down
                    case 2:
                        if(player->coordinates.x == tab->tab_enemy[i].coordinates.x &&
                        player->coordinates.y-player->blade.range <= tab->tab_enemy[i].coordinates.y){
                            tab->tab_enemy[i].life -= player->strength+player->blade.dmg;
                        }
                        break;
                    //left
                    case 3:
                        if(player->coordinates.y == tab->tab_enemy[i].coordinates.y &&
                        player->coordinates.x-player->blade.range <= tab->tab_enemy[i].coordinates.x){
                            tab->tab_enemy[i].life-=player->strength+player->blade.dmg;
                        }
                        break;
                }
                //Enemy dead
                if(tab->tab_enemy[i].life<=0){
                    //win xp
                    player->XP += tab->tab_enemy[i].XP;
                    player->score+=2;
                    //sup Enemy
                    tab->tab_enemy[i] = tab->tab_enemy[tab->nbr_enemy];
                    tab->nbr_enemy--;
                }
            }
            break;
        
        case RANGED:
            if(tab->nbr_enemy>0){
                tab->tab_enemy[0].life -= player->strength+player->blade.dmg;
            }
            //Enemy dead
            if(tab->tab_enemy[0].life==0){
                //win xp
                player->XP += tab->tab_enemy[0].XP;
                player->score+=2;
                //sup Enemy
                tab->tab_enemy[0] = tab->tab_enemy[tab->nbr_enemy];
                tab->nbr_enemy--;
            }
            break;
    }
}

void beHit(Hero* player, Room* a){
    Room* tab = a + player->room;

    for(int i=0;i<tab->nbr_enemy;i++){
        if(player->coordinates.y == tab->tab_enemy[i].coordinates.y
        && (player->coordinates.x-tab->tab_enemy[i].coordinates.x <= tab->tab_enemy[i].range
        || player->coordinates.x-tab->tab_enemy[i].coordinates.x <= -tab->tab_enemy[i].range)){
            int total_damage = tab->tab_enemy[i].strength-player->stuff.shield;
            if(total_damage>0){
                player->life-=total_damage;
            }
        }
        else if(player->coordinates.x==tab->tab_enemy[i].coordinates.x
        && (player->coordinates.y-tab->tab_enemy[i].coordinates.y <= tab->tab_enemy[i].range
        || player->coordinates.y-tab->tab_enemy[i].coordinates.y <= -tab->tab_enemy[i].range)){
            int total_damage = tab->tab_enemy[i].strength-player->stuff.shield;
            if(total_damage>0){
                player->life -= total_damage;
                }
            }
        }
    }

void winLevel(Hero* player){
    while(player->XP >= 1000){
        player->XP -= 1000;
        player->level++;
        //buff for XP
         player->strength++;
         player->max_life+=2;
         player->life+=2;       
    }
}

void death(Hero* player){
    player->coordinates.x = 0;
    player->coordinates.y = 0;
    player->room = 0;
    player->life = 100;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Room function
Room createMainRoom() {
  Room f_room;
  for (int j = 0; j < 4; j++) {
      f_room.room_door[j] = 1;
  }
    f_room.num_door = 4;
    f_room.x_min = 1 * -4;
    f_room.x_max = 1 * 5;
    f_room.y_min = 1 * -4;
    f_room.y_max = 1 * 5;
    f_room.nbr_enemy = 0;
    f_room.nbr_object = 0;
    f_room.nbr_armor = 0;
    f_room.nbr_blade = 0;
  return f_room;
}
  
void createMainDoor(Door *tab_door) {
    tab_door[0].x = 0;
    tab_door[0].y = 6;
    tab_door[0].room_num1 = 0;
    tab_door[0].room_num2 = -1;
    tab_door[0].direction = 0;
    tab_door[1].x = 6;
    tab_door[1].y = 0;
    tab_door[1].room_num1 = 0;
    tab_door[1].room_num2 = -1;
    tab_door[1].direction = 1;
    tab_door[2].x = 0;
    tab_door[2].y = -5;
    tab_door[2].room_num1 = 0;
    tab_door[2].room_num2 = -1;
    tab_door[2].direction = 2;
    tab_door[3].x = -5;
    tab_door[3].y = 0;
    tab_door[3].room_num1 = 0;
    tab_door[3].room_num2 = -1;
    tab_door[3].direction = 3;
}

int searchNearDoor (Door * tab_door, Door test_door, int door_count){
	for (int i = 0; i < door_count; i++){
        switch (test_door.direction){
            case 0:
                if (tab_door[i].x >= (test_door.x) - 8 && tab_door[i].x <= (test_door.x) + 8
                && tab_door[i].y >= (test_door.y) + 1 && tab_door[i].y <= (test_door.y) + 13){
                    return 1;
                }
                break;
            case 1:
                if (tab_door[i].y >= (test_door.y) - 8 && tab_door[i].y <= (test_door.y) + 8
                && tab_door[i].x >= (test_door.x) + 1 && tab_door[i].x <= (test_door.x) + 13){
                    return 1;
                }
                break;
			case 2:
                if (tab_door[i].x >= (test_door.x) - 8 && tab_door[i].x <= (test_door.x) + 8
                && tab_door[i].y <= (test_door.y) - 1 && tab_door[i].y >= (test_door.y) - 13){
                    return 1;
                }
                break;
			case 3:
                if (tab_door[i].y >= (test_door.y) - 8 && tab_door[i].y <= (test_door.y) + 8
                && tab_door[i].x <= (test_door.x) - 1 && tab_door[i].x >= (test_door.x) - 13){
                    return 1;
                }
                break;
        }
    }
	return 0;
}


int searchReallyNearDoor (Door possible_door, Door test_door){
	switch (test_door.direction){
		case 0:
			if (possible_door.x >= (test_door.x) - 4 && possible_door.x <= (test_door.x) + 4
            && possible_door.y >= (test_door.y) + 1 && possible_door.y <= (test_door.y) + 7){
                if(possible_door.room_num1 != test_door.room_num1 && possible_door.room_num2 != test_door.room_num1
                && possible_door.direction != test_door.direction){
                    return 1;
                }
            }
		case 1:
			if (possible_door.y >= (test_door.y) - 4 && possible_door.y <= (test_door.y) + 4
            && possible_door.x >= (test_door.x) + 1 && possible_door.x <= (test_door.x) + 7){
                if(possible_door.room_num1 != test_door.room_num1 && possible_door.room_num2 != test_door.room_num1
                && possible_door.direction != test_door.direction){
                    return 1;
                }
            }
		case 2:
			if (possible_door.x >= (test_door.x) - 4 && possible_door.x <= (test_door.x) + 4
            && possible_door.y <= (test_door.y) - 1 && possible_door.y >= (test_door.y) - 7){
                if(possible_door.room_num1 != test_door.room_num1 && possible_door.room_num2 != test_door.room_num1
                && possible_door.direction != test_door.direction){
                    return 1;
                }
            }
		case 3:
			if (possible_door.y >= (test_door.y) - 4 && possible_door.y <= (test_door.y) + 4
                && possible_door.x <= (test_door.x) - 1 && possible_door.x >= (test_door.x) - 7){
                if(possible_door.room_num1 != test_door.room_num1 && possible_door.room_num2 != test_door.room_num1
                && possible_door.direction != test_door.direction){
                    return 1;
                }
            }
    }
	return 0;
}

int confirmOverlap (Room * room_size_tab, Room new_room, int room_count){
	for (int i = 0; i < room_count; i++){
        if (((new_room.y_min >= room_size_tab[i].y_min && new_room.y_min <= room_size_tab[i].y_max)
        || (new_room.y_max >= room_size_tab[i].y_min && new_room.y_max <= room_size_tab[i].y_max))
        && ((new_room.x_min >= room_size_tab[i].x_min && new_room.x_min <= room_size_tab[i].x_max)
        || (new_room.x_max >= room_size_tab[i].x_min && new_room.x_max <= room_size_tab[i].x_max))){
            return 0;							//overlap
        }
    }
	return 1;											//no overlap
}

int confirmDoorLock (Door * tab_door, Door test_door, int door_count){
	for (int i = 0; i < door_count; i++){
        if ((test_door.x <= tab_door[i].x + 4 && test_door.x >= tab_door[i].x - 4
        && test_door.y <= tab_door[i].y + 4 && test_door.y >= tab_door[i].y - 4)
        && tab_door[i].direction == test_door.direction){
            return 0;							//not allowed
        }
    }
	return 1;											//allowed
}

int adaptNextSizeRoomFuse (Room * new_room, int room_count, Door * tab_door, Door test_door, int door_count){
	int count_door = 0;
	for (int i = 0; i <= door_count; i++){
        if (tab_door[i].direction != test_door.direction
        && searchReallyNearDoor(tab_door[i], test_door) > 0){
            switch (test_door.direction){
                case 0:
                    switch (tab_door[i].direction){
                        case 1:
                            new_room->x_min = tab_door[i].x + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
                        case 2:
                            new_room->y_max = tab_door[i].y - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 3:
                            new_room->x_max = tab_door[i].x - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
                    }
                    break;
				case 1:
                    switch (tab_door[i].direction){
                        case 0:
                            new_room->y_min = tab_door[i].y + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 2:
                            new_room->y_max = tab_door[i].y - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 3:
                            new_room->x_max = tab_door[i].x - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
                    }
                    break;
				case 2:
                    switch (tab_door[i].direction){
                        case 0:
                            new_room->y_min = tab_door[i].y + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 1:
                            new_room->x_min = tab_door[i].x + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
							break;
						case 3:
                            new_room->x_max = tab_door[i].x - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
                    }
                    break;
				case 3:
                    switch (tab_door[i].direction){
                        case 0:
                            new_room->y_min = tab_door[i].y + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 1:
                            new_room->x_min = tab_door[i].x + 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
						case 2:
                            new_room->y_max = tab_door[i].y - 1;
                            tab_door[i].room_num2 = room_count;
                            count_door++;
                            new_room->room_door[((tab_door[i].direction) + 2) % 4] = 1;
                            break;
                    }
                    break;
            }
        }
    }
	return count_door;
}


Room generateRoom (int* seed, int *max_room, Room * tab_room, Door * prev_door,
                   int *room_count, Door * tab_door, int *door_count){
	Room new_room;
	int door_pull, rand_tamp, door_num = *door_count, direction_index, rand_tamp2;
    prev_door->room_num2 = *room_count;
	for (int i = 0; i < 4; i++){
            new_room.room_door[i] = -1;
    }
    new_room.room_door[(prev_door->direction + 2) % 4] = 1;
    new_room.num_door = 1;
	for (int i = 0; i < *door_count; i++){
        if (searchReallyNearDoor(tab_door[i], *prev_door) > 0){
            new_room.num_door++;
        }
    }
	if (new_room.num_door > 1){
        new_room.x_max = 0;
        new_room.x_min = 0;
        new_room.y_max = 0;
        new_room.y_min = 0;
        adaptNextSizeRoomFuse(&new_room, *room_count, tab_door, *prev_door, *door_count);
        do{
            switch (prev_door->direction){
                case 0:
                    new_room.y_min = prev_door->y + 1;
                    if (new_room.x_min == 0){
                        new_room.x_min = prev_door->x - 2 + (rand() % 4);
                    }
                    if (new_room.x_max == 0){
                        new_room.x_max = new_room.x_min + 4 + (rand() % 5);
                    }
                    if (new_room.y_max == 0){
                        new_room.y_max = new_room.y_min + 4 + (rand() % 5);
                    }
                    break;
                case 1:
                    new_room.x_min = prev_door->x + 1;
                    if (new_room.x_max == 0){
                        new_room.x_max = new_room.x_min + 4 + (rand() % 5);
                    }
                    if (new_room.y_min == 0){
                        new_room.y_min = prev_door->y - 2 + (rand()% 4);
                    }
                    if (new_room.y_max == 0){
                        new_room.y_max = new_room.y_min + 4 + (rand()% 5);
                    }
                    break;
				case 2:
                    new_room.y_max = prev_door->y - 1;
                    if (new_room.x_min == 0){
                        new_room.x_min = prev_door->x - 2 + (rand() % 4);
                    }
                    if (new_room.x_max == 0){
                        new_room.x_max = new_room.x_min + 4 + (rand() % 5);
                    }
                    if (new_room.y_min == 0){
                        new_room.y_min = new_room.y_max - 4 - (rand() % 5);
                    }
                    break;
				case 3:
                    new_room.x_max = prev_door->x - 1;
                    if (new_room.x_min == 0){
                        new_room.x_min = new_room.x_max - 4 - (rand() % 5);
                    }
                    if (new_room.y_min == 0){
                        new_room.y_min = prev_door->y - 2 + (rand() % 4);
                    }
                    if (new_room.y_max == 0){
                        new_room.y_max = new_room.y_min + 4 + (rand() % 5);
                    }
                    break;
            }
                        *seed++;
        }while (confirmOverlap(tab_room, new_room, *room_count) == 0);
    }														//connecting rooms
	else if (searchNearDoor(tab_door, *prev_door, *door_count) > 0){
        new_room.num_door = rand() % 3 + 1;
        *seed ++;
        while (new_room.num_door > MAX_ROOM - *room_count){
            new_room.num_door--;
        }
        direction_index = 0;
        switch (new_room.num_door)
        {
            case 2:
                rand_tamp = rand() % 4;
                if (rand_tamp == (prev_door->direction + 2) % 4){
                    rand_tamp = (rand_tamp + 1) % 4;
                }
                new_room.room_door[rand_tamp] = 1;
                break;
			case 3:
                rand_tamp = rand() % 4;
                if (rand_tamp == (prev_door->direction + 2) % 4){
                    rand_tamp = (rand_tamp + 1) % 4;
                }
                new_room.room_door[rand_tamp] = 1;
                rand_tamp2 = rand() % 4;
                do{
                    rand_tamp2 = (rand_tamp2 + 1) % 4;
                }while (rand_tamp2 != (prev_door->direction + 2) % 4 && rand_tamp2 != rand_tamp);
                new_room.room_door[rand_tamp2] = 1;
                break;
        }
        *seed++;
        do{
            switch (prev_door->direction){
                case 0:
                    new_room.x_min = prev_door->x - 1 + (rand() % 3);
                    new_room.x_max = new_room.x_min + 3 + (rand() % 4);
                    new_room.y_min = prev_door->y + 1;
                    new_room.y_max = new_room.y_min + 3 + (rand() % 4);
                    break;
                case 1:
                    new_room.x_min = prev_door->x + 1;
                    new_room.x_max = new_room.x_min + 3 + (rand() % 4);
                    new_room.y_min = prev_door->y - 1 + (rand() % 3);
                    new_room.y_max = new_room.y_min + 3 + (rand() % 4);
                    break;
				case 2:
                    new_room.x_min = prev_door->x - 1 + (rand() % 3);
                    new_room.x_min = new_room.x_max + 3 + (rand() % 4);
                    new_room.y_max = prev_door->y - 1;
                    new_room.y_min = new_room.y_max - 3 - (rand() % 4);
                    break;
				case 3:
                    new_room.x_max = prev_door->x - 1;
                    new_room.x_min = new_room.x_max - 3 - (rand() % 4);
                    new_room.y_min = prev_door->y - 1 + (rand() % 3);
                    new_room.y_max = new_room.y_min + 3 + (rand() % 4);
                    break;
            }
            *seed+=3;
        }while (confirmOverlap(tab_room, new_room, *room_count) == 0);
        for (int i = door_num; i < door_num + new_room.num_door - 1; i++){
            while (new_room.room_door[direction_index] != 1 || direction_index == ((prev_door->direction) + 2) % 4){
                direction_index = (direction_index + 1) % 4;
            }
            tab_door[i].direction = direction_index;
            do{
                switch (tab_door[i].direction){
                    case 0:
                        tab_door[i].x = new_room.x_min + (rand() % (new_room.x_max - new_room.x_min + 1));
                        tab_door[i].y = new_room.y_max + 1;
                        break;
                    case 1:
                        tab_door[i].x = new_room.x_max + 1;
                        tab_door[i].y = new_room.y_min + (rand() % (new_room.y_max - new_room.y_min + 1));
                        break;
                    case 2:
                        tab_door[i].x = new_room.x_min + (rand() % (new_room.x_max - new_room.x_min + 1));
                        tab_door[i].y = new_room.y_min - 1;
                        break;
                    case 3:
                        tab_door[i].x = new_room.x_min + 1;
                        tab_door[i].y = new_room.y_min + (rand() % (new_room.y_max - new_room.y_min + 1));
                        break;
                }
                *seed++;
            }
            while (confirmDoorLock(tab_door, tab_door[i], *door_count) == 0);
            (*door_count)++;
        }
    }														//near rooms
	else{
        new_room.num_door = rand() % 3 + 2;
        *seed++;
        while (new_room.num_door > MAX_ROOM - *room_count){
            new_room.num_door--;
        }
        direction_index = 0;
        door_pull = new_room.num_door;
        switch (new_room.num_door){
            case 2:
                rand_tamp = rand() % 4;
                *seed++;
                if (rand_tamp == (prev_door->direction + 2) % 4){
                    rand_tamp = (rand_tamp + 1) % 4;
                }
                new_room.room_door[rand_tamp] = 1;
                break;
			case 3:
                rand_tamp = rand() % 4;
                if (rand_tamp == (prev_door->direction + 2) % 4){
                    rand_tamp = (rand_tamp + 1) % 4;
                }
                new_room.room_door[rand_tamp] = 1;
                rand_tamp2 = rand() % 4;
                *seed+=2;
                do{
                    rand_tamp2 = (rand_tamp2 + 1) % 4;
                }
                while (rand_tamp2 == (prev_door->direction + 2) % 4 || rand_tamp2 == rand_tamp);
                new_room.room_door[rand_tamp2] = 1;
                break;
			case 4:
                for (int i = 0; i < 4; i++){
                    new_room.room_door[i] = 1;
                }
        }
        switch (prev_door->direction)
        {
            case 0:
                new_room.x_min = prev_door->x - 2 + (rand() % 4);
                new_room.x_max = new_room.x_min + 4 + (rand() % 5);
                new_room.y_min = prev_door->y + 1;
                new_room.y_max = new_room.y_min + 4 + (rand() % 5);
                break;
			case 1:
                new_room.x_min = prev_door->x + 1;
                new_room.x_max = new_room.x_min + 4 + (rand() % 5);
                new_room.y_min = prev_door->y - 2 + (rand() % 4);
                new_room.y_max = new_room.y_min + 4 + (rand() % 5);
                break;
			case 2:
                new_room.x_min = prev_door->x - 2 + (rand() % 4);
                new_room.x_min = new_room.x_max + 4 + (rand() % 5);
                new_room.y_max = prev_door->y - 1;
                new_room.y_min = new_room.y_max - 4 - (rand() % 5);
                break;
			case 3:
                new_room.x_max = prev_door->x - 1;
                new_room.x_min = new_room.x_max - 4 - (rand() % 5);
                new_room.y_min = prev_door->y - 2 + (rand() % 4);
                new_room.y_max = new_room.y_min + 4 + (rand() % 5);
                break;
        }
        *seed+=3;
        while (confirmOverlap(tab_room, new_room, *room_count) == 0);
        for (int i = door_num; i < door_num + new_room.num_door - 1; i++){
            while (new_room.room_door[direction_index] != 1 || direction_index == ((prev_door->direction) + 2) % 4){
                direction_index = (direction_index + 1) % 4;
            }
            tab_door[i].direction = direction_index;
            do{
                switch (tab_door[i].direction){
                    case 0:
                        tab_door[i].x = new_room.x_min + (rand() % (new_room.x_max - new_room.x_min + 1));
                        tab_door[i].y = new_room.y_max + 1;
                        break;
					case 1:
                        tab_door[i].x = new_room.x_max + 1;
                        tab_door[i].y = new_room.y_min + (rand() % (new_room.y_max - new_room.y_min + 1));
                        break;
					case 2:
                        tab_door[i].x = new_room.x_min + (rand() % (new_room.x_max - new_room.x_min + 1));
                        tab_door[i].y = new_room.y_min - 1;
                        break;
                    case 3:
                        tab_door[i].x = new_room.x_min + 1;
                        tab_door[i].y = new_room.y_min + (rand() % (new_room.y_max - new_room.y_min + 1));
                        break;
                }
                *seed++;
            }
            while (confirmDoorLock(tab_door, tab_door[i], *door_count) == 0);
            (*door_count)++;
            direction_index++;
        }
    }														// rooms
	(*room_count)++;
	return new_room;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//enemy function
double calculateDistance(Position pos1, Position pos2) {
    int dx = pos2.x - pos1.x;
    int dy = pos2.y - pos1.y;
    return sqrt(dx*dx + dy*dy);
}

int checkRange(Enemy* a, Hero* player){
    double distance = calculateDistance(a->coordinates, player->coordinates);
    printf("Distance : %f\n", distance);
    switch (a->type) {
        case ALL_IN:
            if (distance >= a->range){
                return 1;
            }
            else {
                return 0;
            }
        case RANGE:
            if (distance >= a->range){
                return 1;
            }
            else {
                return 0;
            }
        case FLYING:
            if (distance != a->range){
                return 0;
            }
            else {
                return 1;
            }
    }
}

Enemy defEnemy(Enemy a){
    switch (a.name){
        case GIGA_ROBOT:
            a.type = ALL_IN;
            a.life = 300;
            a.armor = 25;
            a.strength = 50;
            a.speed = 5;
            a.range = 3;
            a.XP = 10000;
            return a;
        case DRONE:
            a.type = FLYING;
            a.life = 1;
            a.armor = 1;
            a.strength = 15;
            a.speed = 30;
            a.range = 8;
            a.XP = 200;
            return a;
        case ALIEN:
            a.type = ALL_IN;
            a.life = 80;
            a.armor = 10;
            a.strength = 15;
            a.speed = 20;
            a.range = 2;
            a.XP = 1000;
            return a;
        case ROBOT:
            a.type = ALL_IN;
            a.life = 10;
            a.armor = 5;
            a.strength = 25;
            a.speed = 15;
            a.range = 2;
            a.XP = 100;
            return a;
        case TURRET:
            a.type = RANGE;
            a.life = 30;
            a.armor = 5;
            a.strength = 15;
            a.speed = 0;
            a.range = 8;
            a.XP = 300;
            return a;
        case BLOB:
            a.type = ALL_IN;
            a.life = 20;
            a.armor = 1;
            a.strength = 10;
            a.speed = 10;
            a.range = 1;
            a.XP = 100;
            return a;
        default:
            exit(404);
    }
    a.orientation = 0;
}

void moveMob(Enemy* a, Hero* player, Room* b){
    int x = 0;
    int y = 0;
    printf("Hero Position : %d %d\n", player->coordinates.x, player->coordinates.y);
    switch (a->type) {
        case ALL_IN:
            while (checkRange(a, player)) {
                if (player->coordinates.x + 1 > (a->coordinates.x + a->range)) {
                    if (a->coordinates.x < b->x_max){
                        a->coordinates.x += 1;
                    }
                } else if (player->coordinates.x + 1 < (a->coordinates.x - a->range)) {
                    if (a->coordinates.x > b->x_min){
                        a->coordinates.x -= 1;
                    }
                }
                if (player->coordinates.y + 1 > (a->coordinates.y + a->range)) {
                    if (a->coordinates.y < b->y_max){
                        a->coordinates.y += 1;
                    }
                } else if (player->coordinates.y + 1 < (a->coordinates.y - a->range)) {
                    if (a->coordinates.y > b->y_min){
                        a->coordinates.y -= 1;
                    }
                }
                printf("enemy Position : %d %d\n", a->coordinates.x, a->coordinates.y);
            }
        case FLYING:
            while (checkRange(a, player)) {
                if ((a->coordinates.x + a->range) < player->coordinates.x + 1 && a->coordinates.x < b->x_max) {
                    a->coordinates.x += 1;
                } else if ((a->coordinates.x - a->range) > player->coordinates.x + 1 && a->coordinates.x > b->x_min) {
                    a->coordinates.x -= 1;
                }
                if ((a->coordinates.y + a->range) < player->coordinates.y + 1 && a->coordinates.y < b->y_max) {
                    a->coordinates.y += 1;
                } else if ((a->coordinates.y - a->range) > player->coordinates.y + 1 && a->coordinates.y > b->y_min) {
                    a->coordinates.y -= 1;
                }
                printf("enemy Position : %d %d\n", a->coordinates.x, a->coordinates.y);
            }
        case RANGE:
            break;
    }
}

void enemySpawn(int number, Room* b, int* seed){
    int x;
    if (b->tab_enemy == NULL){
        exit(1);
    }
    for (int i=0;i<number;i++){
        Enemy a;

        x = rand()%6+1;
        *seed++;
        switch (x){
            case 1:
                a.name = GIGA_ROBOT;
                break;
            case 2:
                a.name = DRONE;
                break;
            case 3:
                a.name = ALIEN;
                break;
            case 4:
                a.name = ROBOT;
                break;
            case 5:
                a.name = TURRET;
                break;
            case 6:
                a.name = BLOB;
                break;
            default:
                exit(5);
        }
        b->tab_enemy[i] = defEnemy(a);
        b->tab_enemy[i].coordinates.x =  rand() % (b->x_max - b->x_min) + b->x_min;
        b->tab_enemy[i].coordinates.y =  rand() % (b->y_max - b->y_min) + b->y_min;
        *seed+=2;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//think function
void stuffSpawn(Room* a, FILE* Object, FILE* Blade, FILE* Armor, int* seed){
    for (int i=0; i<a->nbr_object ; i++){
        a->tab_object[i] = searchObject(rand() % 14, Object);
        a->tab_object[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_object[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
        }

    for (int i=0; i<a->nbr_blade ; i++){
        a->tab_blade[i] = searchBlade(rand() % 7, Blade);
        a->tab_blade[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_blade[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
        }

    for (int i=0; i<a->nbr_armor ; i++){
        a->tab_armor[i] = searchStuff(rand() % 6, Armor);
        a->tab_armor[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_armor[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
        }
    *seed+=3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//display function
void displayMenu(int screen_length, int screen_width, int menu_cursor, WINDOW* background){
    clear();
    refresh();
    background=newwin(screen_width,screen_length,0,0);
    wbkgd(background,COLOR_PAIR(1));  
    wrefresh(background);

    attron(COLOR_PAIR(1));
    mvprintw(2,screen_length/2-6,"   in menu   ");

    mvprintw(4,screen_length/2-6,"    start    ");
    mvprintw(6,screen_length/2-6,"continue game");
    mvprintw(8,screen_length/2-6,"   setting   ");
    mvprintw(screen_width-2,3,"exit");

    attron(COLOR_PAIR(2));
    switch(menu_cursor){
        case 0:
            mvprintw(4,screen_length/2-6,"    start    ");
            break;
        case 1:
            mvprintw(6,screen_length/2-6,"continue game");
            break;
        case 2:
            mvprintw(8,screen_length/2-6,"  do nothing ");
            break;
        case 3:
            mvprintw(screen_width-2,3,"exit");
            break;
    }
    attron(COLOR_PAIR(1));
    move(screen_width+10,screen_length+10);
    refresh();
}

void displayNameMenu(int screen_length, int screen_width, WINDOW* background, char* name){
    refresh();
    background=newwin(screen_width-4,screen_length,4,0);
    wbkgd(background,COLOR_PAIR(1));  
    wrefresh(background);

    mvprintw(4,screen_length/2-11,"enter your initials");
    move(6,screen_length/2-11);
    for(int i=0;i<3;i++){
        if (name[i]==0){
            printw("_");
        }
        else{
            printw("%c",name[i]);
        }
        printw(" ");
    }
    attron(COLOR_PAIR(1));
    move(screen_width+10,screen_length+10);
    refresh();
}

int searchSave(char* name, FILE* file){
	rewind(file);
    char c=getc(file);
	while(c != EOF){
		if(c=='@'){
            int identical_name=1;
            for(int i=0;i<3;i++){
                c=getc(file);
                if(c != name[i]){
                    i=3;
                    identical_name=0;
                }
            }
            if(identical_name){
                return 1;
            }
        }
		c=getc(file);
    }
    return 0;
}

void displaySeedMenu(int screen_length, int screen_width, WINDOW* background, int seed, int count){
    mvprintw(10+2*count,10,"%d",seed);
    refresh();
}

void displayNameLoadMenu(int screen_length, int screen_width, WINDOW* background, char* name, int load_menu_cursor){
    displayNameMenu(screen_length, screen_width, background, name);

    //browse the different backups and display their names
    /*
    
    */
}

void displayGame(int screen_length, int screen_width, Hero player, WINDOW* background, time_t timer, int time_pause,
                 int time_play, int time_to_play, int* end){
    clear();
    refresh();
    background=newwin(screen_width,screen_length,0,0);
    wbkgd(background,COLOR_PAIR(3));  
    wrefresh(background);

    time_t time_now=time(NULL);
    int time_total= time_now - timer - time_pause + time_play;

    attron(COLOR_PAIR(3));
    mvprintw(2,1,"Life: %03d   ",player.life);
    mvprintw(4,1,"Time: %02d:%02d ",time_to_play-(time_total/60)-1,59-(time_total%60));

    if(screen_length>25){
        //life 
        attron(COLOR_PAIR(4));
        move(2,13);

        for(int i=0;i<screen_length-14 && i<50;i++){
            if(i>(player.life/(player.max_life*1.0) * min(screen_length-14,50))){
                attron(COLOR_PAIR(6));
            }
            printw(" ");
        }

        //time
        if(time_total+2>time_to_play*60){
            *end=1;
            attron(COLOR_PAIR(7));
            mvprintw(4,7,"00:00");
        }

        attron(COLOR_PAIR(5));
        move(4,13);

        for(int i=0;i<screen_length-14 && i<50;i++){
            if(i>(1-time_total/(time_to_play*60.0))*min(screen_length-14,50)-1){
                attron(COLOR_PAIR(6));
            }
            printw(" ");
        }
    }

    attron(COLOR_PAIR(3));
    mvprintw(1,screen_length-66,"materiel: %04d     level: %03d     XP: %04d     inventory: %02d/15",
             player.score,player.level,player.XP, player.nbr_object_inventory);
    mvprintw(3,screen_length-66,"Weapon: %s  %d damage  %d range",player.blade.name, player.blade.dmg,
             player.blade.range);
    mvprintw(5,screen_length-66,"Stuff: %s  %d armor",player.stuff.name, player.stuff.shield);
    move(screen_width+10,screen_length+10);
    refresh();
}

void displayDungeon(int screen_length, int screen_width, Hero player, int door_count, Door* tab_door, int room_count,
                    Room* tab_room, WINDOW* dungeon){
    //refresh();
    dungeon=newwin(screen_width - 8, screen_length - 6, 6, 3);
    wbkgd(dungeon, COLOR_PAIR(6));
    wrefresh(dungeon);

    int local_x;
    int local_y;
    //display Room
    for(int i=0; i < room_count; i++){
        //display Room background
        for(int j=0; j <= absoluteValue(tab_room[i].y_max - tab_room[i].y_min); j++){
            for(int k=0; k <= absoluteValue(tab_room[i].x_max - tab_room[i].x_min); k++){
                local_x= player.coordinates.x - tab_room[i].x_max + k;
                local_y=-(player.coordinates.y - tab_room[i].y_max + j);
                if(absoluteValue(local_x)<=(screen_length - 6)/2 && absoluteValue(local_y)<=(screen_width - 8)/2){
                    attron(COLOR_PAIR(10));
                    mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x," ");
                    refresh();
                }
            }
        }
        //display enemy
        for(int l=0; l < tab_room[i].nbr_enemy; l++){
            local_x= player.coordinates.x - tab_room[i].tab_enemy[l].coordinates.x;
            local_y=-(player.coordinates.y - tab_room[i].tab_enemy[l].coordinates.y);
            if(absoluteValue(local_x) <= (screen_length - 6)/2 && absoluteValue(local_y) <= (screen_width - 8)/2){
                attron(COLOR_PAIR(11));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"E");
                refresh();
            }
        }
        //display object
        for(int l=0; l < tab_room[i].nbr_object; l++){
            local_x= player.coordinates.x - tab_room[i].tab_object[l].coordinates.x;
            local_y=-(player.coordinates.y - tab_room[i].tab_object[l].coordinates.y);
            if(absoluteValue(local_x) <= (screen_length - 6)/2 && absoluteValue(local_y) <= (screen_width - 8)/2){
                attron(COLOR_PAIR(12));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"O");
                refresh();
            }
        }
        //display armor
        for(int l=0; l < tab_room[i].nbr_armor; l++){
            local_x= player.coordinates.x - tab_room[i].tab_armor[l].coordinates.x;
            local_y=-(player.coordinates.y - tab_room[i].tab_armor[l].coordinates.y);
            if(absoluteValue(local_x) <= (screen_length - 6)/2 && absoluteValue(local_y) <= (screen_width - 8)/2){
                attron(COLOR_PAIR(13));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"A");
            }
        }
        //display blade
        for(int l=0; l < tab_room[i].nbr_blade; l++){
            local_x= player.coordinates.x - tab_room[i].tab_blade[l].coordinates.x;
            local_y=-(player.coordinates.y - tab_room[i].tab_blade[l].coordinates.y);
            if(absoluteValue(local_x) <= (screen_length - 6)/2 && absoluteValue(local_y) <= (screen_width - 8)/2){
                attron(COLOR_PAIR(14));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"W");
                refresh();
            }
        }
    }
    //display Door
    for(int i=0; i < door_count; i++){
        local_x= player.coordinates.x - tab_door[i].x;
        local_y=-(player.coordinates.y - tab_door[i].y);
        if(absoluteValue(local_x) <= (screen_length - 6) / 2 && absoluteValue(local_y) <= (screen_width - 8) / 2){
            attron(COLOR_PAIR(6));
            mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"P");
            refresh();
        }
    }
    displayHit(player, screen_length, screen_width);
    //display Hero
    attron(COLOR_PAIR(10));
    mvprintw(6+(screen_width-8)/2,3+(screen_length-6)/2,"&");
    refresh();
}

void displayInventoryMenu(int screen_length, int screen_width, Hero player, WINDOW* dungeon, int inventory_cursor){
    //window start in 6 3
    dungeon=newwin(screen_width - 8, screen_length - 6, 6, 3);
    wbkgd(dungeon, COLOR_PAIR(8));
    wrefresh(dungeon);
    attron(COLOR_PAIR(8));
    mvprintw(7,4,"inventory");
    for (int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            for(int k=0;k<7;k++){
                if(inventory_cursor==j+5*i){
                    attron(COLOR_PAIR(9));
                }
                else if(player.nbr_object_inventory>j+5*i){
                    attron(COLOR_PAIR(3));
                }
                else{
                    attron(COLOR_PAIR(6));
                }
                //x=start_window+2+nbr_object_raw*length_object
                //y=start_window+2+nbr_object_col*width_object
                mvprintw(9+k+(i*9),6+(22*j),"                    ");
                attron(COLOR_PAIR(8));
                printw("  ");
            }
            if(player.nbr_object_inventory>j+5*i){
                if(inventory_cursor==j+5*i){
                    attron(COLOR_PAIR(9));
                }
                else{
                    attron(COLOR_PAIR(3));
                }
                //name object
                mvprintw(9+0+(i*9),6+(22*j),"  %s",player.inventory[j+5*i].name);
                mvprintw(9+2+(i*9),6+(22*j),"  %d / %d",player.inventory[j+5*i].stack,player.inventory[j+5*i].max_stack);
                switch (player.inventory[j+5*i].what_augmentation){
                    case 0:
                        mvprintw(9+4+(i*9),6+(22*j),"  no buff");
                        break;
                    case 1:
                        mvprintw(9+4+(i*9),6+(22*j),"  +%d life",player.inventory[j+5*i].augmentation);
                        break;
                    case 2:
                        mvprintw(9+4+(i*9),6+(22*j),"  +%d strength",player.inventory[j+5*i].augmentation);
                        break;
                    case 3:
                        mvprintw(9+4+(i*9),6+(22*j),"  +%d armor",player.inventory[j+5*i].augmentation);
                        break;
                    case 4:
                        mvprintw(9+4+(i*9),6+(22*j),"  +%d weapon",player.inventory[j+5*i].augmentation);
                        break;
                    case 5:
                        mvprintw(9+4+(i*9),6+(22*j),"  +%d materials ",player.inventory[j+5*i].augmentation);
                        break;
                }
                    refresh();
            }
        }
    }
    attron(COLOR_PAIR(9));
    refresh();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void){
    initscr();
    noecho();
    halfdelay(10);
    //cbreak();
    //nodelay(stdscr,True);
    //timeout(delay);

    //setlocale(LC_CTYPE, "");
    keypad(stdscr, TRUE);
    //create size screen
    int screen_length=130; //130
    int screen_width=40;  //40
    if (screen_length<25 || screen_width<25){
        printf("error screen size");
        exit(1);
    }
    if(has_colors()==FALSE && can_change_color()==FALSE){
        printf("terminal doesn't support colors");
        exit(1);
    }
    WINDOW *background = 0, *dungeon = 0;

    FILE* file=NULL;
    file=fopen("save.txt", "r+");
    if(file == NULL){
        file=fopen("save.txt", "w+");
    }
    FILE* blade_file=NULL;
    blade_file=fopen("blade.txt", "r");
    if(blade_file == NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
    FILE* stuff_file=NULL;
    stuff_file=fopen("Armor.txt", "r");
    if(stuff_file == NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
    FILE* object_file=NULL;
    object_file=fopen("Object.txt", "r");
    if(object_file == NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
    //init loop to play
    int in_menu = 1;
    int end = 0;
    int in_game = 0;
    int in_pause = 0;
    int in_inventory = 0;
    //create color
    start_color();
    //init_color(COLOR_BlaCK, 700, 1000,1000);
    init_color(COLOR_RED, 700, 0, 0);
    init_color(COLOR_BLUE, 200, 200, 750);
    init_color(COLOR_GREEN, 200, 500, 200);
    init_color(COLOR_YELLOW, 750, 750, 50);
    init_color(COLOR_PINK, 1000, 375, 500);
    init_color(COLOR_BROWN, 300, 200, 0);
    init_color(COLOR_BEIGE,250, 200, 100);
    init_color(COLOR_BEIGE_LIGHT, 300, 200, 100);
    //background menu
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    //select menu
    init_pair(2,COLOR_WHITE,COLOR_RED);
    //background game and background item
    init_pair(3,COLOR_WHITE,COLOR_BEIGE);
    //life
    init_pair(4,COLOR_WHITE,COLOR_GREEN);
    //time
    init_pair(5,COLOR_WHITE,COLOR_YELLOW);
    //fond
    init_pair(6,COLOR_WHITE,COLOR_BLACK);
    //time out
    init_pair(7,COLOR_RED,COLOR_BEIGE);
    //inventory background
    init_pair(8, COLOR_WHITE, COLOR_BEIGE_LIGHT);
    //inventory select
    init_pair(9,COLOR_WHITE,COLOR_RED);
//change color
    //Room background
    init_pair(10, COLOR_WHITE, COLOR_BEIGE_LIGHT);
    //enemy
    init_pair(11,COLOR_WHITE,COLOR_RED);
    //object
    init_pair(12,COLOR_WHITE,COLOR_GREEN);
    //armor
    init_pair(13,COLOR_WHITE,COLOR_GREEN);
    //blade
    init_pair(14,COLOR_WHITE,COLOR_GREEN);
    //hit
    init_pair(15,COLOR_BLACK,COLOR_WHITE);
    //background terminal
    init_pair(16,COLOR_WHITE,COLOR_BLACK);

    //menu
    int menu_cursor=0;
    //create player
    Hero player;
    int inventory_cursor=0;
    //init name
    char name[4];
    int seed;
    //key player
    int key_exit=27;
    int key_enter=10;
    int key_inventory='0';
    int key_delete='*';
    int key_sup_text=263;
    int move_up=KEY_UP;
    int move_down=KEY_DOWN;
    int move_left=KEY_LEFT;
    int move_right=KEY_RIGHT;
    int key_fight='a';
    // ...
    //init Room
    int max_room= MAX_ROOM;
    int room_count= 0;
    int door_count=0;
    Room *tab_room;
    Door *tab_door;
    tab_door = malloc(sizeof(Door) * MAX_ROOM * 4);
    if (tab_door == NULL) {
        exit(1);
    }
    tab_room = malloc(max_room * sizeof(Room));
    if (tab_room == NULL) {
        exit(1);
    }
    //init timer
    time_t timer = 0;
    int time_pause = 0;
    int time_play = 0;
    time_t time_start_pause;
    int time_to_play = 1;
    
    while(in_menu){
        //display menu
        displayMenu(screen_length, screen_width, menu_cursor, background);
        
        int test1=getch();
        //choose menu button
        //press enter
        if(test1==key_enter){
            int complete_name = 0;
            int Exit = 0;

            //init name
            name[0] = 0;
            name[1] = 0;
            name[2] = 0;
            name[3] = '\0';

            int advancement = 0;
            int load_menu_cursor=0;
            //start the game
            switch(menu_cursor){
                case 0:
                    complete_name = 0;
                    Exit = 0;
                    advancement = 0;
                    
                    while(!complete_name && !Exit){
                        displayNameMenu(screen_length, screen_width, background, name);
                        test1 = getch();
                        if (test1==key_exit){
                            //key esc
                            Exit=1;
                        }
                        else if (test1==key_enter && advancement > 2){
                            complete_name=1;
                        }
                        else if (test1==key_sup_text && advancement > 0){
                            advancement--;
                            name[advancement]=0;
                        }
                        //recover first name letter
                        else if ((48<=test1 && test1<=59) || (97<=test1 && test1<=122) || (65<=test1 && test1<=90)){
                            name[advancement]=test1;
                            advancement++;
                        }
                    }
                    if (complete_name){
                        int count=0;
                        mvprintw(8,10,"Enter your seed");
                        refresh();
                        do{
                        scanf("%d",&seed);
                        displaySeedMenu(screen_length, screen_width, background, seed, count);
                        count++;
                        }while(seed>=1000000000 || seed<0);

                        srand(seed);

                        in_game = 1;
                        Exit = 0;
                        end = 0;
                        player = buildHero(blade_file, stuff_file);

                        room_count = 1;
                        door_count = 4;
                        createMainDoor(tab_door);
                        tab_room[0] = createMainRoom();
                        
                        timer = time(NULL);
                        time_pause = 0;
                        time_play = 0;
                    }
                    break;
                case 1:
                    complete_name = 0;
                    Exit = 0;
                    advancement = 0;
                    
                    while(!complete_name && !Exit){
                        displayNameLoadMenu(screen_length, screen_width, background, name, load_menu_cursor);
                        test1 = getch();
                        if (test1==key_exit){
                            //key esc
                            Exit=1;
                        }
                        else if (test1==key_enter && advancement >= 2){
                            complete_name=1;
                        }
                        else if (test1==key_sup_text){
                            advancement--;
                            name[advancement]=0;
                        }
                        //recover first name letter
                        else if ((48<=test1 && test1<=59) || (97<=test1 && test1<=122) || (65<=test1 && test1<=90)){
                            name[advancement]=test1;
                            advancement++;
                        }
                    }
                    if (complete_name){
                        //search game
                        int verify=EOF;
                        if(searchSave(name, file)){
                            int temp;
                            //Load information
                            //Load player
                            player.stuff.name=malloc(21*sizeof(char));
                            if(player.stuff.name==NULL){
                                printf("error calloc");
                                exit(3);
                            }
                            player.blade.name=calloc(21,sizeof(char));
                            if(player.blade.name==NULL){
                                printf("error calloc");
                                exit(3);
                            }
                            verify=fscanf(file, "%d %d %d %d %d %d %d %d %d %s %d %d %d %s %d %d ",
                                          &player.coordinates.x, &player.coordinates.y, &player.room, &player.life,
                                          &player.max_life, &player.level, &player.XP, &player.score, &player.strength,
                                          player.stuff.name, &player.stuff.id,&player.stuff.weight,&player.stuff.shield,
                                          player.blade.name, &player.blade.id, &temp);
                            if(verify == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            switch(temp){
                                case 1:
                                    player.blade.type= RANGED;
                                    break;
                                case 2:
                                    player.blade.type= CC;
                                    break;
                            }
                            verify=fscanf(file, "%d %d %d %d ", &player.blade.range, &player.blade.dmg,
                                          &player.blade.weight, &player.nbr_object_inventory);
                            if(verify == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            player.inventory=calloc(15,sizeof(Object));
                            if(player.inventory==NULL){
                                printf("error calloc");
                                exit(3);
                            }
                            for(int i=0;i<player.nbr_object_inventory;i++){
                                verify=fscanf(file, "%d", &player.inventory[i].id);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                player.inventory[i]= searchObject(player.inventory[i].id, object_file);
                            }
                            player.orientation = 0;
                            player.start_hit = 0;

                            //Load important var
                            verify=fscanf(file, "%d %d %d", &room_count, &door_count, &max_room);
                            if(verify == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            tab_door = malloc(sizeof(Door) * max_room * 4);
                            if (tab_door == NULL) {
                                exit(1);
                            }
                            tab_room = malloc(max_room * sizeof(Room));
                            if (tab_room == NULL) {
                                exit(1);
                            }
                            //Load Room
                            for(int i=0; i < room_count; i++){
                                verify=fscanf(file, "%d %d %d %d %d", &tab_room[i].x_min, &tab_room[i].x_max,
                                              &tab_room[i].y_min, &tab_room[i].y_max, &tab_room[i].nbr_enemy);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                //Load enemy in the Room
                                tab_room[i].tab_enemy=malloc(tab_room[i].nbr_enemy * sizeof(Enemy));
                                if(tab_room[i].tab_enemy == NULL){
                                    printf("error malloc");
                                    exit(3);
                                }
                                for(int j=0; j < tab_room[i].nbr_enemy; j++){
                                    verify=fscanf(file, "%d", &temp);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    switch(temp){
                                        case 1:
                                            tab_room[i].tab_enemy[j].name= GIGA_ROBOT;
                                            break;
                                        case 2:
                                            tab_room[i].tab_enemy[j].name= DRONE;
                                            break;
                                        case 3:
                                            tab_room[i].tab_enemy[j].name= ALIEN;
                                            break;
                                        case 4:
                                            tab_room[i].tab_enemy[j].name= ROBOT;
                                            break;
                                        case 5:
                                            tab_room[i].tab_enemy[j].name= BLOB;
                                            break;
                                        case 6:
                                            tab_room[i].tab_enemy[j].name= TURRET;
                                            break; 
                                    }
                                    verify=fscanf(file, "%d %d %d %d %d %d %d %d %d ",
                                                  &tab_room[i].tab_enemy[j].coordinates.x,
                                                  &tab_room[i].tab_enemy[j].coordinates.y,
                                                  &tab_room[i].tab_enemy[j].life, &tab_room[i].tab_enemy[j].armor,
                                                  &tab_room[i].tab_enemy[j].strength, &tab_room[i].tab_enemy[j].speed,
                                                  &tab_room[i].tab_enemy[j].range, &tab_room[i].tab_enemy[j].XP, &temp);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }

                                    switch(temp){
                                        case 1:
                                            tab_room[i].tab_enemy[j].type= ALL_IN;
                                            break;
                                        case 2:
                                            tab_room[i].tab_enemy[j].type= FLYING;
                                            break;
                                        case 3:
                                            tab_room[i].tab_enemy[j].type= RANGE;
                                            break;
                                    }
                                    tab_room[i].tab_enemy[j].orientation=0;
                                    tab_room[i].tab_enemy[j].cooldown=0;
                                }
                                verify=fscanf(file, "%d", &tab_room[i].nbr_object);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                //Load object in the Room
                                tab_room[i].tab_object=malloc(tab_room[i].nbr_object * sizeof(Object));
                                if(tab_room[i].tab_object == NULL){
                                    printf("error malloc");
                                    exit(3);
                                }
                                for(int j=0; j < tab_room[i].nbr_object; j++){
                                    verify=fscanf(file, "%d ", &tab_room[i].tab_object[j].id);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    tab_room[i].tab_object[j]=searchObject(tab_room[i].tab_object[j].id,object_file);

                                    verify=fscanf(file, "%d %d ", &tab_room[i].tab_object[j].coordinates.x,
                                                  &tab_room[i].tab_object[j].coordinates.y);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                }
                                verify=fscanf(file, "%d", &tab_room[i].nbr_armor);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                //Load armor in the Room
                                tab_room[i].tab_armor=malloc(tab_room[i].nbr_armor * sizeof(Armor));
                                if(tab_room[i].tab_armor == NULL){
                                    printf("error malloc");
                                    exit(3);
                                }
                                for(int j=0; j < tab_room[i].nbr_armor; j++){
                                    verify=fscanf(file, "%d ", &tab_room[i].tab_armor[j].id);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    tab_room[i].tab_armor[j]= searchStuff(tab_room[i].tab_armor[j].id, stuff_file);

                                    verify=fscanf(file, "%d %d ", &tab_room[i].tab_armor[j].coordinates.x, &tab_room[i].tab_armor[j].coordinates.y);
                                            if(verify == EOF){
                                                printf("error load charging");
                                                exit(3);
                                            }
                                }
                                verify=fscanf(file, "%d", &tab_room[i].nbr_blade);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                //Load blade in the Room
                                tab_room[i].tab_blade=malloc(tab_room[i].nbr_blade * sizeof(Weapon));
                                if(tab_room[i].tab_blade == NULL){
                                    printf("error malloc");
                                    exit(3);
                                }
                                for(int j=0; j < tab_room[i].nbr_blade; j++){
                                    verify=fscanf(file, "%d ", &tab_room[i].tab_blade[j].id);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    tab_room[i].tab_blade[j]= searchBlade(tab_room[i].tab_blade[j].id, blade_file);

                                    verify=fscanf(file, "%d %d ", &tab_room[i].tab_blade[j].coordinates.x,
                                                  &tab_room[i].tab_blade[j].coordinates.y);
                                    if(verify == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                }
                            }
                            //Load Door
                            for(int i=0; i < door_count; i++){
                                verify=fscanf(file, "%d %d %d %d %d", &tab_door[i].x, &tab_door[i].y,
                                              &tab_door[i].room_num1, &tab_door[i].room_num2, &tab_door[i].direction);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                            }
                            //Load seed
                            verify=fscanf(file, "%d", &seed);
                            if(verify == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            //Load time
                            verify=fscanf(file, "%d", &time_play);
                            if(verify == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            timer=time(NULL);
                            time_pause=0;
                            in_game=1;
                            end=0;
                        }
                    }
                    break;
                case 2:
                  //to be continued int the next episode ???
                    break;
                case 3:
                    in_menu=0;
                    break;
            }
        }
        //select button
        else if (test1==key_exit){
            //key esc
            in_menu=0;
        }
        //key up or key left
        else if (test1 == move_up || test1 == move_left){
            menu_cursor--;
        }
        //key down
        else if (test1 == move_down || test1 == move_right){
            menu_cursor++;
        }
        //keeps the menu cursor on a button
        menu_cursor=(menu_cursor+4)%4;
        while(in_game){
            if(!in_pause && !in_inventory){
                //display game
                displayGame(screen_length, screen_width, player, background, timer, time_pause, time_play,
                            time_to_play, &end);

                //display dungeon
                displayDungeon(screen_length, screen_width, player, door_count, tab_door, room_count, tab_room,dungeon);

                test1 = getch();

                //select button
                if (test1==key_exit){
                    //key echap
                    in_pause = 1;
                    time_start_pause=time(NULL);

                    //display pause menu
                    displayGame(screen_length, screen_width, player, background, timer, time_pause, time_play,
                                time_to_play, &end);

                    move(screen_width/2,screen_length/2);
                    printw("pause");
                    move(screen_width+10,screen_length+10);
                    refresh();
                    }
                //up key
                else if (test1 == move_up){
                    player.orientation = 0;
                    //move into Door
                    if(player.coordinates.y == tab_room[player.room].y_max){
                        for(int i=0; i < door_count; i++){
                            if(tab_door[i].x == player.coordinates.x && tab_door[i].y - 1 == player.coordinates.y){
                                player.coordinates.y+=2;
                                if(tab_door[i].room_num2 == -1){
                                    //generate Room
                                    tab_room[room_count]= generateRoom(&seed, &max_room,tab_room,&tab_door[i],
                                                                       &room_count,tab_door, &door_count);
                                    //generate mobs armor blade
                                    tab_room[room_count - 1].nbr_enemy = rand() % 3;
                                    tab_room[room_count - 1].nbr_object = rand() % 2;
                                    tab_room[room_count - 1].nbr_armor = rand() % 1;
                                    tab_room[room_count - 1].nbr_blade = rand() % 1;
                                    seed+=4;

                                    tab_room[room_count - 1].tab_enemy = malloc(sizeof(Enemy)
                                            * tab_room[room_count - 1].nbr_enemy);
                                    tab_room[room_count - 1].tab_object = malloc(sizeof(Object)
                                            * tab_room[room_count - 1].nbr_object);
                                    tab_room[room_count - 1].tab_blade = malloc(sizeof(Weapon)
                                            * tab_room[room_count - 1].nbr_blade);
                                    tab_room[room_count - 1].tab_armor = malloc(sizeof(Armor)
                                            * tab_room[room_count - 1].nbr_armor);

                                    enemySpawn(tab_room[room_count - 1].nbr_enemy,
                                               &tab_room[room_count - 1], &seed);
                                    stuffSpawn(&tab_room[room_count - 1], object_file,
                                               blade_file, stuff_file, &seed);
                                }
                                if(player.room == tab_door[i].room_num1){
                                    player.room=tab_door[i].room_num2;
                                }
                                else{
                                    player.room=tab_door[i].room_num1;
                                }
                            }
                        }
                    }
                    else{
                        player.coordinates.y++;
                    }
                }
                //down key
                else if (test1 == move_down){
                    player.orientation = 2;
                    //move into Door
                    if(player.coordinates.y == tab_room[player.room].y_min){
                        for(int i=0; i < door_count; i++){
                            if(tab_door[i].x == player.coordinates.x && tab_door[i].y + 1 == player.coordinates.y){
                                player.coordinates.y-=2;
                                if(tab_door[i].room_num2 == -1){
                                    //generate Room
                                    tab_room[room_count]= generateRoom(&seed, &max_room,tab_room,&tab_door[i],
                                                                       &room_count,tab_door, &door_count);
                                    
                                    //generate mobs armor blade
                                    tab_room[room_count - 1].nbr_enemy = rand() % 3;
                                    tab_room[room_count - 1].nbr_object = rand() % 2;
                                    tab_room[room_count - 1].nbr_armor = rand() % 1;
                                    tab_room[room_count - 1].nbr_blade = rand() % 1;
                                    seed+=4;

                                    tab_room[room_count - 1].tab_enemy = malloc(sizeof(Enemy)
                                            * tab_room[room_count - 1].nbr_enemy);
                                    tab_room[room_count - 1].tab_object = malloc(sizeof(Object)
                                            * tab_room[room_count - 1].nbr_object);
                                    tab_room[room_count - 1].tab_blade = malloc(sizeof(Weapon)
                                            * tab_room[room_count - 1].nbr_blade);
                                    tab_room[room_count - 1].tab_armor = malloc(sizeof(Armor)
                                            * tab_room[room_count - 1].nbr_armor);

                                    enemySpawn(tab_room[room_count - 1].nbr_enemy,
                                               &tab_room[room_count - 1], &seed);
                                    stuffSpawn(&tab_room[room_count - 1], object_file,
                                               blade_file,stuff_file, &seed);
                                }
                                if(player.room == tab_door[i].room_num1){
                                    player.room=tab_door[i].room_num2;
                                }
                                else{
                                    player.room=tab_door[i].room_num1;
                                }
                            }
                        }
                    }
                    else{
                        player.coordinates.y--;
                    }
                }
                //left key
                else if (test1 == move_left){
                    player.orientation=3;
                    //move into Door
                    if(player.coordinates.x == tab_room[player.room].x_min){
                        for(int i=0; i < door_count; i++){
                            if(tab_door[i].y == player.coordinates.y && tab_door[i].x + 1 == player.coordinates.x){
                                player.coordinates.x-=2;
                                if(tab_door[i].room_num2 == -1){
                                    //generate Room
                                    tab_room[room_count]= generateRoom(&seed, &max_room,tab_room,&tab_door[i],
                                                                       &room_count,tab_door, &door_count);
                                    
                                    //generate mobs armor
                                    tab_room[room_count - 1].nbr_enemy= rand() % 3;
                                    tab_room[room_count - 1].nbr_object= rand() % 2;
                                    tab_room[room_count - 1].nbr_armor= rand() % 1;
                                    tab_room[room_count - 1].nbr_blade= rand() % 1;
                                    seed+=4;

                                    tab_room[room_count - 1].tab_enemy = malloc(sizeof(Enemy)
                                            * tab_room[room_count - 1].nbr_enemy);
                                    tab_room[room_count - 1].tab_object = malloc(sizeof(Object)
                                            * tab_room[room_count - 1].nbr_object);
                                    tab_room[room_count - 1].tab_blade = malloc(sizeof(Weapon)
                                            * tab_room[room_count - 1].nbr_blade);
                                    tab_room[room_count - 1].tab_armor = malloc(sizeof(Armor)
                                            * tab_room[room_count - 1].nbr_armor);

                                    enemySpawn(tab_room[room_count - 1].nbr_enemy, &tab_room[room_count - 1], &seed);
                                    stuffSpawn(&tab_room[room_count - 1], object_file, blade_file, stuff_file, &seed);
                                }
                                if(player.room == tab_door[i].room_num1){
                                    player.room=tab_door[i].room_num2;
                                }
                                else{
                                    player.room=tab_door[i].room_num1;
                                }
                            }
                        }
                    }
                    else{
                        player.coordinates.x--;
                    }
                }
                //right key
                if (test1 == move_right){
                    player.orientation=1;
                    //move into Door
                    if(player.coordinates.x == tab_room[player.room].x_max){
                        for(int i=0; i < door_count; i++){
                            if(tab_door[i].y == player.coordinates.y && tab_door[i].x - 1 == player.coordinates.x){
                                player.coordinates.x+=2;
                                if(tab_door[i].room_num2 == -1){
                                    //generate Room
                                    tab_room[room_count]= generateRoom(&seed, &max_room,tab_room,&tab_door[i],
                                                                       &room_count, tab_door, &door_count);

                                    //generate mobs armor blade
                                    tab_room[room_count - 1].nbr_enemy=1; //rand()%3;
                                    tab_room[room_count - 1].nbr_object= rand() % 2;
                                    tab_room[room_count - 1].nbr_armor= rand() % 1;
                                    tab_room[room_count - 1].nbr_blade= rand() % 1;
                                    seed+=4;

                                    tab_room[room_count - 1].tab_enemy = malloc(sizeof(Enemy)
                                            * tab_room[room_count - 1].nbr_enemy);
                                    tab_room[room_count - 1].tab_object = malloc(sizeof(Object)
                                            * tab_room[room_count - 1].nbr_object);
                                    tab_room[room_count - 1].tab_blade = malloc(sizeof(Weapon)
                                            * tab_room[room_count - 1].nbr_blade);
                                    tab_room[room_count - 1].tab_armor = malloc(sizeof(Armor)
                                            * tab_room[room_count - 1].nbr_armor);

                                    enemySpawn(tab_room[room_count - 1].nbr_enemy, &tab_room[room_count - 1], &seed);
                                    stuffSpawn(&tab_room[room_count - 1], object_file, blade_file, stuff_file, &seed);
                                }
                                if(player.room == tab_door[i].room_num1){
                                    player.room=tab_door[i].room_num2;
                                }
                                else{
                                    player.room=tab_door[i].room_num1;
                                }
                            }
                        }
                    }
                    else{
                        player.coordinates.x++;
                    }
                }
                //press 0
                else if(test1==key_inventory){
                    //open inventory
                    in_inventory = 1;
                    inventory_cursor = 0;
                    }
                //press enter
                else if(test1==key_enter){
                    //collect thing
                    collectObject(&player, tab_room);
                    collectArmor(&player, tab_room, screen_length, screen_width, background, timer, time_pause,
                                 time_play, time_to_play, &end);
                    collectBlade(&player, tab_room, screen_length, screen_width, background, timer, time_pause,
                                 time_play, time_to_play, &end);
                }
                else if(test1==key_fight){
                    //attack
                    player.start_hit=time(NULL);
                    youHit(&player, tab_room);
                }
            }
            else if(in_pause){
                test1 = getch();
                if (test1==key_exit){
                    //key esc
                    in_game=0;
                    in_pause=0;
                    menu_cursor=0;
                    time_pause += time(NULL)-time_start_pause;
                    time_play += (time(NULL) - timer) - time_pause;

                    //save player
                    int verify2=EOF;
                    if(!searchSave(name, file)){
                        verify2=fprintf(file, "@%s", name);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(5);
                        }
                    }
                    verify2=fprintf(file, " ");
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(5);
                    }
                    verify2=fprintf(file, "%d %d %d %d %d %d %d %d %d %s %d %d %d %s %d ",
                                    player.coordinates.x, player.coordinates.y, player.room, player.life,
                                    player.max_life, player.level, player.XP, player.score, player.strength,
                                    player.stuff.name, player.stuff.id, player.stuff.weight, player.stuff.shield,
                                    player.blade.name, player.blade.id);
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(5);
                    }
                    switch (player.blade.type){
                        case RANGED:
                            verify2=fprintf(file, "1 ");
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            break;
                        case CC:
                            verify2=fprintf(file, "2 ");
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                            break;    
                    }
                    verify2=fprintf(file, "%d %d %d %d ", player.blade.range, player.blade.dmg, player.blade.weight,
                                    player.nbr_object_inventory);
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(3);
                    }
                    //save inventory (object)
                    for(int i=0;i<player.nbr_object_inventory;i++){
                        verify2=fprintf(file, "%d ", player.inventory[i].id);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                        }
                    }
                    //save important var
                    verify2=fprintf(file, "%d %d %d ", room_count, door_count, max_room);
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(3);
                        }
                    //save Room
                    for(int i=0; i < room_count; i++){
                        verify2=fprintf(file, "%d %d %d %d %d ", tab_room[i].x_min, tab_room[i].x_max,
                                        tab_room[i].y_min, tab_room[i].y_max, tab_room[i].nbr_enemy);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                        }
                        //save enemy in the Room
                        for(int j=0; j < tab_room[i].nbr_enemy; j++){
                            switch(tab_room[i].tab_enemy[j].name){
                                case GIGA_ROBOT:
                                    verify2=fprintf(file, "1 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case DRONE:
                                    verify2=fprintf(file, "2 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case ALIEN:
                                    verify2=fprintf(file, "3 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case ROBOT:
                                    verify2=fprintf(file, "4 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case BLOB:
                                    verify2=fprintf(file, "6 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case TURRET:
                                    verify2=fprintf(file, "7 ");
                                    if(verify2 == EOF){
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                            }
                            verify2=fprintf(file, "%d %d %d %d %d %d %d %d ", tab_room[i].tab_enemy[j].coordinates.x,
                                            tab_room[i].tab_enemy[j].coordinates.y, tab_room[i].tab_enemy[j].life,
                                            tab_room[i].tab_enemy[j].armor, tab_room[i].tab_enemy[j].strength,
                                            tab_room[i].tab_enemy[j].speed, tab_room[i].tab_enemy[j].range,
                                            tab_room[i].tab_enemy[j].XP);
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            switch(tab_room[i].tab_enemy[j].type) {
                                case ALL_IN:
                                    verify2 = fprintf(file, "1 ");
                                    if (verify2 == EOF) {
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case FLYING:
                                    verify2 = fprintf(file, "2 ");
                                    if (verify2 == EOF) {
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                                case RANGE:
                                    verify2 = fprintf(file, "3 ");
                                    if (verify2 == EOF) {
                                        printf("error load charging");
                                        exit(3);
                                    }
                                    break;
                            }
                        }
                        verify2=fprintf(file, "%d ", tab_room[i].nbr_object);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                        }
                        //save object
                        for(int j=0; j < tab_room[i].nbr_object; j++){
                            verify2=fprintf(file, "%d %d %d ", tab_room[i].tab_object[j].id,
                                            tab_room[i].tab_object[j].coordinates.x,
                                            tab_room[i].tab_object[j].coordinates.y);
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                        }
                        verify2=fprintf(file, "%d ", tab_room[i].nbr_armor);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                            }
                        //save armor
                        for(int j=0; j < tab_room[i].nbr_armor; j++){
                            verify2=fprintf(file, "%d %d %d ", tab_room[i].tab_armor[j].id,
                                            tab_room[i].tab_armor[j].coordinates.x,
                                            tab_room[i].tab_armor[j].coordinates.y);
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                        }
                        verify2=fprintf(file, "%d ", tab_room[i].nbr_blade);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                        }
                        //save blade
                        for(int j=0; j < tab_room[i].nbr_blade; j++){
                            verify2=fprintf(file, "%d %d %d ", tab_room[i].tab_blade[j].id,
                                            tab_room[i].tab_blade[j].coordinates.x,
                                            tab_room[i].tab_blade[j].coordinates.y);
                            if(verify2 == EOF){
                                printf("error load charging");
                                exit(3);
                            }
                        }
                    }
                    //save Door
                    for(int i=0; i < door_count; i++){
                        verify2=fprintf(file, "%d %d %d %d %d ", tab_door[i].x, tab_door[i].y, tab_door[i].room_num1,
                                        tab_door[i].room_num2, tab_door[i].direction);
                        if(verify2 == EOF){
                            printf("error load charging");
                            exit(3);
                        }
                    }
                    //save seed
                    verify2=fprintf(file, "%d ", seed);
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(5);
                    }
                    //save time
                    verify2=fprintf(file, "%d\n", time_play);
                    if(verify2 == EOF){
                        printf("error load charging");
                        exit(5);
                    }
                }
                else if(test1!=-1){
                    //continue
                    in_pause=0;
                    time_pause += time(NULL)-time_start_pause;
                }
            }
            else if(in_inventory){
                //display game
                displayGame(screen_length, screen_width, player, background, timer, time_pause, time_play,
                            time_to_play, &end);
                //display inventory menu
                displayInventoryMenu(screen_length, screen_width, player, dungeon, inventory_cursor);

                test1 = getch();
                if (test1==key_exit || test1==key_inventory){
                    //close inventory
                    in_inventory=0;
                }
                //key up
                else if (test1 == move_up && inventory_cursor - 5 >= 0){
                    inventory_cursor-=5;
                }
                //key down
                else if (test1 == move_down && inventory_cursor + 5 <= 14){ //inventory size-1
                    inventory_cursor+=5;
                }
                //key left
                else if (test1 == move_left && inventory_cursor - 1 >= 0){
                    inventory_cursor--;
                }
                //key right
                else if (test1 == move_right && inventory_cursor + 1 <= 14){//inventory size-1
                    inventory_cursor++;
                }
                //press *
                else if(test1==key_delete){
                    do{
                        //refresh the timer
                        //display game
                        displayGame(screen_length, screen_width, player, background, timer, time_pause, time_play,
                                    time_to_play, &end);
                        //display inventory menu
                        displayInventoryMenu(screen_length, screen_width, player, dungeon, inventory_cursor);
                        //verification
                        attron(COLOR_PAIR(8));
                        mvprintw(screen_width-4,4,"are you sure you want to delete this item %s?",
                                 player.inventory[inventory_cursor].name);
                        mvprintw(screen_width-3,4,"y/n");
                        refresh();
                        test1=getch();
                        //yes
                        if(test1==121){
                            player.inventory[inventory_cursor]=player.inventory[player.nbr_object_inventory];
                            player.inventory[player.nbr_object_inventory].id=0;
                            player.nbr_object_inventory--;
                        }
                    }while(test1!=121 && test1!=110);
                }
                //press enter
                else if(test1==key_enter){
                    //use item
                    useObject(&player, inventory_cursor);
                }
            }
            //enemy enters or hits player
            beHit(&player, tab_room);
            winLevel(&player);
            
            if(!in_pause && player.life<=0){
                death(&player);
            }
            if(end && player.score<100){
                clear();
                attron(COLOR_PAIR(16));
                printw("YOU LOSE, the monsters have damaged your space ship, you won't get far now.");
                refresh();
                do{
                test1=getch();
                }while(test1==-1);
                in_game=0;
            }
            else if(player.score>=100){
                clear();
                attron(COLOR_PAIR(16));
                printw("YOU WIN, you have enough materials to repair your space ships");
                refresh();
                do{
                test1=getch();
                }while(test1==-1);
                in_game=0;
            }
        }
    }
    free(player.inventory);
    delwin(background);
    endwin();
    return 0;
}