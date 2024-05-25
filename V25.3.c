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
  int roomNum1;
  int roomNum2;
  int direction;
} door;

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
}room;

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
} hero;

int min(int a,int b){
    if(a<=b){
        return a;
        }
    return b;
    }

int absolute_value(int a){
    if(a<0){
        return -a;
        }
    return a;
    }

Weapon search_blade(int ID,FILE* file){
    int verify,test,temp;
    Weapon blade;
	rewind(file);
    char c=getc(file);
	while(c != EOF){
		if(c=='@'){
            verify=fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
                }
            if(ID==test){
                blade.id=ID;

                blade.name=calloc(21,sizeof(char));
                if(blade.name==NULL){
                    printf("error calloc");
                    exit(3);
                    }
                verify=fscanf(file, "%s", blade.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &temp);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                switch(temp){
                    case 1:
                        blade.type= RANGED;
                        break;
                    case 2:
                        blade.type= CC;
                        break;
                }

                verify=fscanf(file, "%d", &blade.range);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &blade.dmg);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &blade.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                return blade;
                }   
		    }
        c=getc(file);
        }
    printf("formatting error blade.txt");
    exit(12);
    }

Armor search_stuff(int ID,FILE* file){
    int verify,test;
    char* verify_name=NULL;
    Armor stuff;
	rewind(file);
    char c=getc(file);
	while(c != EOF){
		if(c=='@'){
            verify=fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
                }
            if(ID==test){
                stuff.id=ID;

                stuff.name=calloc(21,sizeof(char));
                if(stuff.name==NULL){
                    printf("error calloc");
                    exit(3);
                    }
                verify=fscanf(file, "%s", stuff.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }

                verify=fscanf(file, "%d", &stuff.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &stuff.shield);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                return stuff;
                }   
		    }
        c=getc(file);
        }
    printf("formatting error stuff.txt");
    exit(12);
    }

Object search_object(int ID,FILE* file){
    int verify,test;
    Object think;
	rewind(file);
    char c=getc(file);

	while(c != EOF){
		if(c=='@'){
            verify=fscanf(file, "%d", &test);
            if(verify == EOF){
                printf("error load charging");
                exit(3);
                }

            if(ID==test){
                think.id=ID;

                think.name=calloc(21,sizeof(char));
                if(think.name==NULL){
                    printf("error calloc");
                    exit(3);
                    }
                verify=fscanf(file, "%s", think.name);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &think.weight);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &think.single_use);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &think.max_stack);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }

                verify=fscanf(file, "%d", &think.augmentation);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                verify=fscanf(file, "%d", &think.what_augmentation);
                if(verify == EOF){
                    printf("error load charging");
                    exit(3);
                    }
                return think;
                }  
		    }
        c=getc(file);
        }
    printf("formatting error Object.txt");
    exit(12);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function hero
hero build_hero(FILE* blade_file, FILE* fichier_stuff){
    hero player;
    player.coordinates.x=0;
    player.coordinates.y=0;
    player.room=0;
    player.orientation=0;
    player.life=100;
    player.start_hit=0;
    player.max_life=100;
    player.level=0;
    player.XP=0;
    player.score=0;
    player.strength=1;
    player.nbr_object_inventory=0;
    player.inventory=calloc(15,sizeof(Object));
    if(player.inventory==NULL){
        printf("error calloc inventory");
        exit(2);
        }
    player.blade=search_blade(0, blade_file);
    player.stuff=search_stuff(0,fichier_stuff);

    return player;
    }
    
void display_game(int screen_length,int screen_width,hero player,WINDOW* background, time_t timer,int time_pause,int time_jouer,int time_to_play,int* end);  

void use_object(hero* player,int position_stuff){
    //effect
    switch (player->inventory[position_stuff].what_augmentation){
        case 1:
            //life
            player->life+=player->inventory[position_stuff].augmentation;
            if(player->life>player->max_life){
                player->life=player->max_life;
                }
            break;
        case 2:
            //strength
            player->strength+=player->inventory[position_stuff].augmentation;
            break;
        case 3:
            //armor
            player->stuff.shield+=player->inventory[position_stuff].augmentation;
            break;
        case 4:
            //armor
            player->blade.dmg+=player->inventory[position_stuff].augmentation;
            break;
        case 5:
            //score
            player->score+=player->inventory[position_stuff].augmentation;
            break;
        }

    if (player->inventory[position_stuff].single_use){
        player->inventory[position_stuff].stack--;
        }
    if(player->inventory[position_stuff].stack==0){
        //delete stuff
        player->inventory[position_stuff]=player->inventory[player->nbr_object_inventory-1];
        player->inventory[player->nbr_object_inventory-1].id=0;
        player->nbr_object_inventory--;
        }
    }

int collect_object(hero* player,room* a){
    room* tab=a+player->room;
    
    for(int i=0;i<tab->nbr_object;i++){
        if(player->coordinates.x==tab->tab_object[i].coordinates.x && player->coordinates.y==tab->tab_object[i].coordinates.y){
            for(int j=0;j<15;j++){
                if(player->inventory[j].id==tab->tab_object[i].id && player->inventory[j].stack<player->inventory[j].max_stack){
                    player->inventory[j].stack++;

                    tab->tab_object[i]=tab->tab_object[tab->nbr_object];
                    tab->tab_object[tab->nbr_object].id=0;
                    tab->nbr_object--;
                    return 1;
                    }
                if(player->inventory[j].id==0){
                    player->inventory[j]=tab->tab_object[i];

                    player->inventory[j].stack=1;
                    player->nbr_object_inventory++;

                    tab->tab_object[i]=tab->tab_object[tab->nbr_object];
                    tab->tab_object[tab->nbr_object].id=0;
                    tab->nbr_object--;
                    return 1;
                    }
                }
            }
        }
    }

void collect_armor(hero* player,room* a,int screen_length, int screen_width,WINDOW* background,time_t timer,int time_pause,int time_jouer,int time_to_play,int* end){
    room* tab=a+player->room;
    
    for(int i=0;i<tab->nbr_armor;i++){
        if(player->coordinates.x==tab->tab_armor[i].coordinates.x && player->coordinates.y==tab->tab_armor[i].coordinates.y){
            int test1=getch();
            do{
                //refresh the timer
                //display game
                display_game(screen_length,screen_width,*player,background,timer,time_pause,time_jouer,time_to_play,end);

                //verfication
                attron(COLOR_PAIR(8));
                mvprintw(7,4,"are you sure you want to change your stuff?");
                mvprintw(8,4,"y/n");

                //name objet use
                mvprintw(9,6,"name: %s           ",player->stuff.name);
                mvprintw(11,6,"shield: %d        ",player->stuff.shield);
                mvprintw(13,6,"weight: %d        ",player->stuff.weight);
                
                //name objet
                mvprintw(9,20,"name:%s",tab->tab_armor[i].name);
                mvprintw(11,20,"shield: %d",tab->tab_armor[i].shield);
                mvprintw(13,20,"weight: %d",tab->tab_armor[i].weight);
                refresh();

                test1=getch();
                //yes
                if(test1==121){
                    player->stuff=tab->tab_armor[i];
                    tab->tab_armor[i]=tab->tab_armor[tab->nbr_armor-1];
                    tab->nbr_armor--;
                    }
                //no
                else if(test1==110){
                    tab->tab_armor[i]=tab->tab_armor[tab->nbr_armor-1];
                    tab->nbr_armor--;
                    }
            }while(test1!=121 && test1!=110);
            attron(COLOR_PAIR(3));
            }
        }
    }

void collect_blade(hero* player,room* a,int screen_length,int screen_width,WINDOW* background,time_t timer,int time_pause,int time_jouer,int time_to_play,int* end){
    room* tab=a+player->room;
    
    for(int i=0;i<tab->nbr_blade;i++){
        if(player->coordinates.x==tab->tab_blade[i].coordinates.x && player->coordinates.y==tab->tab_blade[i].coordinates.y){
            int test1=getch();
            do{
                //refresh the timer
                //display game
                display_game(screen_length,screen_width,*player,background,timer,time_pause,time_jouer,time_to_play,end);

                //verfication
                attron(COLOR_PAIR(8));
                mvprintw(7,4,"are you sure you want to change your blade?");
                mvprintw(8,4,"y/n");
                refresh();

                //name objet use
                mvprintw(9,6,"name: %s         ",player->blade.name);
                mvprintw(11,6,"range: %d       ",player->blade.range);
                mvprintw(13,6,"damage: %d      ",player->blade.dmg);
                mvprintw(15,6,"weight: %d      ",player->blade.weight);
                
                //name objet
                mvprintw(9,20,"name: %s",tab->tab_blade[i].name);
                mvprintw(11,20,"range: %d",tab->tab_blade[i].range);
                mvprintw(13,20,"damage: %d",tab->tab_blade[i].dmg);
                mvprintw(15,20,"weight: %d",tab->tab_blade[i].weight);

                test1=getch();
                //yes
                if(test1==121){
                    player->blade=tab->tab_blade[i];
                    tab->tab_blade[i]=tab->tab_blade[tab->nbr_blade-1];
                    tab->nbr_blade--;
                    }
                //no
                else if(test1==110){
                    tab->tab_blade[i]=tab->tab_blade[tab->nbr_blade-1];
                    tab->nbr_blade--;
                    }
            }while(test1!=121 && test1!=110);
            attron(COLOR_PAIR(3));
            }
        }
    }
 
void display_hit(hero player,int screen_length,int screen_width){
    attron(COLOR_PAIR(15));

    if(player.start_hit-time(NULL)>0 && player.start_hit-time(NULL)<=1){
        for(int i=0;i<=player.blade.range;i++){
            switch(player.orientation){
                case 0:
                    mvprintw(6+(screen_width-8)/2-i,3+(screen_length-6)/2,"a");
                    break;

                case 1:
                    mvprintw(6+(screen_width-8)/2, 3+(screen_length-6)/2+i,"a");
                    break;

                case 2:
                    mvprintw(6+(screen_width-8)/2+i, 3+(screen_length-6)/2,"a");
                    break;

                case 3:
                    mvprintw(6+(screen_width-8)/2, 3+(screen_length-6)/2-i,"a");
                    break;
                }
            }
        refresh();
        }
    }

void you_hit(hero* player,room* a){
    room* tab=a+player->room;

    switch (player->blade.type){
        case CC:
            for(int i=0;i<tab->nbr_enemy;i++){
                //search is as enemy in the front of the player
                switch(player->orientation){
                    //up
                    case 0:
                        if(player->coordinates.y < tab->tab_enemy[i].coordinates.y && player->coordinates.y+player->blade.range > tab->tab_enemy[i].coordinates.y && player->coordinates.x==tab->tab_enemy[i].coordinates.x){
                            tab->tab_enemy[i].life-=player->strength+player->blade.dmg;
                            }
                        break;
                    //right
                    case 1:
                        if(player->coordinates.x < tab->tab_enemy[i].coordinates.x && player->coordinates.x+player->blade.range > tab->tab_enemy[i].coordinates.x && player->coordinates.y==tab->tab_enemy[i].coordinates.y){
                            tab->tab_enemy[i].life-=player->strength+player->blade.dmg;
                            }
                        break;
                    //down
                    case 2:
                        if(player->coordinates.y > tab->tab_enemy[i].coordinates.y && player->coordinates.y+player->blade.range < tab->tab_enemy[i].coordinates.y && player->coordinates.x==tab->tab_enemy[i].coordinates.x){
                            tab->tab_enemy[i].life-=player->strength+player->blade.dmg;
                            }
                        break;
                    //left
                    case 3:
                        if(player->coordinates.x > tab->tab_enemy[i].coordinates.x && player->coordinates.x+player->blade.range < tab->tab_enemy[i].coordinates.x && player->coordinates.y==tab->tab_enemy[i].coordinates.y){
                            tab->tab_enemy[i].life-=player->strength+player->blade.dmg;
                            }
                        break;
                    }

                //Enemy dead
                if(tab->tab_enemy[i].life==0){
                    //win xp
                    player->XP+=tab->tab_enemy[i].XP;
                    player->score+=2;
                    //sup Enemy
                    tab->tab_enemy[i]=tab->tab_enemy[tab->nbr_enemy];
                    tab->nbr_enemy--;
                    }
                }
            break;
        
        case RANGED:
            if(tab->nbr_enemy>0){
                tab->tab_enemy[0].life-=player->strength+player->blade.dmg;
                }
            //Enemy dead
            if(tab->tab_enemy[0].life==0){
                //win xp
                player->XP+=tab->tab_enemy[0].XP;
                player->score+=2;
                //sup Enemy
                tab->tab_enemy[0]=tab->tab_enemy[tab->nbr_enemy];
                tab->nbr_enemy--;
                }
            break;
        }
    }

void be_hit(hero* player,room* a){
    room* tab=a+player->room;

    for(int i=0;i<tab->nbr_enemy;i++){
        if(player->coordinates.y==tab->tab_enemy[i].coordinates.y && (player->coordinates.x-tab->tab_enemy[i].coordinates.x <= tab->tab_enemy[i].range || player->coordinates.x-tab->tab_enemy[i].coordinates.x <= -tab->tab_enemy[i].range)){
            int total_damage=tab->tab_enemy[i].strength-player->stuff.shield;
            if(total_damage>0){
                player->life-=total_damage;
                }
            }
        else if(player->coordinates.x==tab->tab_enemy[i].coordinates.x && (player->coordinates.y-tab->tab_enemy[i].coordinates.y <= tab->tab_enemy[i].range || player->coordinates.y-tab->tab_enemy[i].coordinates.y <= -tab->tab_enemy[i].range)){
            int total_damage=tab->tab_enemy[i].strength-player->stuff.shield;
            if(total_damage>0){
                player->life-=total_damage;
                }
            }
        }
    }

void win_level(hero* player){
    while(player->XP >= 1000){
        player->XP -= 1000;
        player->level++;
        
        //buff for XP
         player->strength++;
         player->max_life+=2;
         player->life+=2;       
        }
    }
    
void death(hero* player){
    player->coordinates.x=0;
    player->coordinates.y=0;
    player->room=0;
    player->life=100;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//room fonction
int
searchneardoor (door * tabdoor, door testdoor, int doorcount)
{
	for (int i = 0; i < doorcount; i++)
		{
			switch (testdoor.direction)
				{
				case 0:
					if (tabdoor[i].x >= (testdoor.x) - 6
							&& tabdoor[i].x <= (testdoor.x) + 6
							&& tabdoor[i].y >= (testdoor.y) + 1
							&& tabdoor[i].y <= (testdoor.y) + 9)
						{
							return 1;
						}
					break;
				case 1:
					if (tabdoor[i].y >= (testdoor.y) - 6
							&& tabdoor[i].y <= (testdoor.y) + 6
							&& tabdoor[i].x >= (testdoor.x) + 1
							&& tabdoor[i].x <= (testdoor.x) + 9)
						{
							return 1;
						}
					break;
				case 2:
					if (tabdoor[i].x >= (testdoor.x) - 6
							&& tabdoor[i].x <= (testdoor.x) + 6
							&& tabdoor[i].y <= (testdoor.y) - 1
							&& tabdoor[i].y >= (testdoor.y) - 9)
						{
							return 1;
						}
					break;
				case 3:
					if (tabdoor[i].y >= (testdoor.y) - 6
							&& tabdoor[i].y <= (testdoor.y) + 6
							&& tabdoor[i].x <= (testdoor.x) - 1
							&& tabdoor[i].x >= (testdoor.x) - 9)
						{
							return 1;
						}
					break;
				}
		}
	return 0;
}



int
searchreallyneardoor (door possibledoor, door testdoor)
{
	switch (testdoor.direction)
		{
		case 0:
			if (possibledoor.x >= (testdoor.x) - 5
					&& possibledoor.x <= (testdoor.x) + 5
					&& possibledoor.y >= (testdoor.y) + 1
					&& possibledoor.y <= (testdoor.y) + 7
					&& possibledoor.direction != testdoor.direction)
				{
					if (possibledoor.roomNum1 != testdoor.roomNum1
							&& possibledoor.roomNum2 != testdoor.roomNum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 1:
			if (possibledoor.y >= (testdoor.y) - 5
					&& possibledoor.y <= (testdoor.y) + 5
					&& possibledoor.x >= (testdoor.x) + 1
					&& possibledoor.x <= (testdoor.x) + 7)
				{
					if (possibledoor.roomNum1 != testdoor.roomNum1
							&& possibledoor.roomNum2 != testdoor.roomNum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 2:
			if (possibledoor.x >= (testdoor.x) - 5
					&& possibledoor.x <= (testdoor.x) + 5
					&& possibledoor.y <= (testdoor.y) - 1
					&& possibledoor.y >= (testdoor.y) - 7)
				{
					if (possibledoor.roomNum1 != testdoor.roomNum1
							&& possibledoor.roomNum2 != testdoor.roomNum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		case 3:
			if (possibledoor.y >= (testdoor.y) - 5
					&& possibledoor.y <= (testdoor.y) + 5
					&& possibledoor.x <= (testdoor.x) - 1
					&& possibledoor.x >= (testdoor.x) - 7)
				{
					if (possibledoor.roomNum1 != testdoor.roomNum1
							&& possibledoor.roomNum2 != testdoor.roomNum1
							&& possibledoor.direction != testdoor.direction)
						{
							return 1;
						}
				}
			break;
		}
	return 0;
}

int
confirmoverlap (room * roomsizetab, room newroom, int roomcount)
{
	for (int i = 0; i < roomcount; i++)
		{
			if ((((newroom.y_min >= roomsizetab[i].y_min - 1
						 && newroom.y_min <= roomsizetab[i].y_max + 1)
						|| (newroom.y_max >= roomsizetab[i].y_min - 1
								&& newroom.y_max <= roomsizetab[i].y_max + 1))
					 &&
					 ((newroom.x_min >= roomsizetab[i].x_min - 1
						 && newroom.x_min <= roomsizetab[i].x_max + 1)
						|| (newroom.x_max >= roomsizetab[i].x_min - 1
								&& newroom.x_max <= roomsizetab[i].x_max + 1)))
					||
					(((roomsizetab[i].y_min >= newroom.y_min - 1
						 && roomsizetab[i].y_min <= newroom.y_max + 1)
						|| (roomsizetab[i].y_max >= newroom.y_min - 1
								&& roomsizetab[i].y_max <= newroom.y_max + 1))
					 &&
					 ((roomsizetab[i].x_min >= newroom.x_min - 1
						 && roomsizetab[i].x_min <= newroom.x_max + 1)
						|| (roomsizetab[i].x_max >= newroom.x_min - 1
								&& roomsizetab[i].x_max <= newroom.x_max + 1))))
				{
					return 0;							//overlap
				}
		}
	return 1;											//no overlap
}

int
confirmdoorloc (door * tabdoor, door testdoor, int doorcount,
								room * roomsizetab, int roomcount)
{
	for (int i = 0; i < doorcount; i++)
		{
			if (testdoor.x <= tabdoor[i].x + 4
					&& testdoor.x >= tabdoor[i].x - 4
					&& testdoor.y <= tabdoor[i].y + 4
					&& testdoor.y >= tabdoor[i].y - 4
					&& tabdoor[i].direction != testdoor.direction)
				{
					for (int j = 0; j < roomcount; j++)
						{
							switch (testdoor.direction)
								{
								case 0:
									if (((testdoor.y + 1 >= roomsizetab[j].y_min
												&& testdoor.y + 1 <= roomsizetab[j].y_max)
											 || (testdoor.y + 5 >= roomsizetab[j].y_min
													 && testdoor.y + 5 <= roomsizetab[j].y_max))
											&&
											((testdoor.x - 3 >= roomsizetab[j].x_min
												&& testdoor.x - 3 <= roomsizetab[j].x_max)
											 || (testdoor.x + 3 >= roomsizetab[j].x_min
													 && testdoor.x + 3 <= roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 1:
									if (((testdoor.y - 3 >= roomsizetab[j].y_min
												&& testdoor.y - 3 <= roomsizetab[j].y_max)
											 || (testdoor.y + 3 >= roomsizetab[j].y_min
													 && testdoor.y + 3 <= roomsizetab[j].y_max))
											&&
											((testdoor.x + 1 >= roomsizetab[j].x_min
												&& testdoor.x + 1 <= roomsizetab[j].x_max)
											 || (testdoor.x + 5 >= roomsizetab[j].x_min
													 && testdoor.x + 5 <= roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 2:
									if (((testdoor.y - 1 >= roomsizetab[j].y_min
												&& testdoor.y - 1 <= roomsizetab[j].y_max)
											 || (testdoor.y - 5 >= roomsizetab[j].y_min
													 && testdoor.y - 5 <= roomsizetab[j].y_max))
											&&
											((testdoor.x - 3 >= roomsizetab[j].x_min
												&& testdoor.x - 3 <= roomsizetab[j].x_max)
											 || (testdoor.x + 3 >= roomsizetab[j].x_min
													 && testdoor.x + 3 <= roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								case 3:
									if (((testdoor.y - 3 >= roomsizetab[j].y_min
												&& testdoor.y - 3 <= roomsizetab[j].y_max)
											 || (testdoor.y + 3 >= roomsizetab[j].y_min
													 && testdoor.y + 3 <= roomsizetab[j].y_max))
											&&
											((testdoor.x - 1 >= roomsizetab[j].x_min
												&& testdoor.x - 1 <= roomsizetab[j].x_max)
											 || (testdoor.x - 5 >= roomsizetab[j].x_min
													 && testdoor.x - 5 <= roomsizetab[j].x_max)))
										{
											return 0;
										}
									break;
								}
						}										//not allowed
				}
		}
	return 1;											//allowed
}

int
confirmdoororientation (room * roomsizetab, room newroom, int roomcount,
												door prevdoor)
{
	for (int j = 0; j < 4; j++)
		{
			if (newroom.room_door[j] == 1 && (prevdoor.direction + 2) % 4 != j)
				{
					for (int i = 0; i < roomcount; i++)
						{
							switch (j)
								{
								case 0:
									if ((newroom.y_max + 5 >= roomsizetab[i].y_min
											 && newroom.y_max + 5 <= roomsizetab[i].y_max)
											&&
											((newroom.x_min >= roomsizetab[i].x_min
												&& newroom.x_min <= roomsizetab[i].x_max)
											 || (newroom.x_max >= roomsizetab[i].x_min
													 && newroom.x_max <= roomsizetab[i].x_max)))
										{
											return 0;
										}
									break;
								case 1:
									if (((newroom.y_min >= roomsizetab[i].y_min
												&& newroom.y_min <= roomsizetab[i].y_max)
											 || (newroom.y_max >= roomsizetab[i].y_min
													 && newroom.y_max <= roomsizetab[i].y_max))
											&& (newroom.x_max + 5 >= roomsizetab[i].x_min
													&& newroom.x_max + 5 <= roomsizetab[i].x_max))
										{
											return 0;
										}
									break;
								case 2:
									if ((newroom.y_min - 5 >= roomsizetab[i].y_min
											 && newroom.y_min - 5 <= roomsizetab[i].y_max)
											&&
											((newroom.x_min >= roomsizetab[i].x_min
												&& newroom.x_min <= roomsizetab[i].x_max)
											 || (newroom.x_max >= roomsizetab[i].x_min
													 && newroom.x_max <= roomsizetab[i].x_max)))
										{
											return 0;
										}
									break;
								case 3:
									if (((newroom.y_min >= roomsizetab[i].y_min
												&& newroom.y_min <= roomsizetab[i].y_max)
											 || (newroom.y_max >= roomsizetab[i].y_min
													 && newroom.y_max <= roomsizetab[i].y_max))
											&&
											(newroom.x_min - 5 >= roomsizetab[i].x_min
											 && newroom.x_min - 5 <= roomsizetab[i].x_max))
										{
											return 0;
										}
									break;
								}

						}
				}
		}
	return 1;

}

int
adaptnextsizeroomfuse (room * newroom, int roomcount,
											 door * tabdoor, door testdoor, int doorcount)
{
	int countdoor;
	for (int i = 0; i < doorcount; i++)
		{
			if (tabdoor[i].direction != testdoor.direction
					&& searchreallyneardoor (tabdoor[i], testdoor) > 0)
				{
					switch (testdoor.direction)
						{
						case 0:
							switch (tabdoor[i].direction)
								{
								case 1:
									newroom->x_min = tabdoor[i].x + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->y_max = tabdoor[i].y - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->x_max = tabdoor[i].x - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 1:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->y_min = tabdoor[i].y + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->y_max = tabdoor[i].y - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->x_max = tabdoor[i].x - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 2:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->y_min = tabdoor[i].y + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newroom->x_min = tabdoor[i].x + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 3:
									newroom->x_max = tabdoor[i].x - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						case 3:
							switch (tabdoor[i].direction)
								{
								case 0:
									newroom->y_min = tabdoor[i].y + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 1:
									newroom->x_min = tabdoor[i].x + 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								case 2:
									newroom->y_max = tabdoor[i].y - 1;
									tabdoor[i].roomNum2 = roomcount;
									countdoor++;
									newroom->room_door[((tabdoor[i].direction) + 2) % 4] = 1;
									break;
								}
							break;
						}
				}
		}
	return countdoor;
}


room
generateroom (int seed, int *maxroom, room * tabroom,
							door * prevdoor, int *roomcount, door * tabdoor, int *doorcount)
{
	room newroom;
	int randtamp, directionindex, randtamp2, doornum = *doorcount;
	prevdoor->roomNum2 = *roomcount;
	newroom.num_door = 1;

	for (int i = 0; i < 4; i++)
		{
			newroom.room_door[i] = -1;
		}
	newroom.room_door[(prevdoor->direction + 2) % 4] = 1;
	for (int i = 0; i < *doorcount; i++)
		{
			if (searchreallyneardoor (tabdoor[i], *prevdoor) > 0)
				{
					newroom.num_door++;
				}
		}
	if (newroom.num_door > 1)
		{
			newroom.x_max = 0;
			newroom.x_min = 0;
			newroom.y_max = 0;
			newroom.y_min = 0;
			adaptnextsizeroomfuse (&newroom, *roomcount, tabdoor,
														 *prevdoor, *doorcount);
			do
				{
					switch (prevdoor->direction)
						{
						case 0:
							newroom.y_min = prevdoor->y + 1;
							if (newroom.x_min == 0)
								{
									newroom.x_min = prevdoor->x - 5 + (rand () % 3);
								}
							if (newroom.x_max == 0)
								{
									newroom.x_max = prevdoor->x + 5 - (rand () % 3);
								}
							if (newroom.y_max == 0)
								{
									newroom.y_max = newroom.y_min + 4 + (rand () % 5);
								}
							break;
						case 1:
							newroom.x_min = prevdoor->x + 1;
							if (newroom.x_max == 0)
								{
									newroom.x_max = newroom.x_min + 4 + (rand () % 5);
								}
							if (newroom.y_min == 0)
								{
									newroom.y_min = prevdoor->y - 5 + (rand () % 3);
								}
							if (newroom.y_max == 0)
								{
									newroom.y_max = prevdoor->y + 5 - (rand () % 3);
								}
							break;
						case 2:
							newroom.y_max = prevdoor->y - 1;
							if (newroom.x_min == 0)
								{
									newroom.x_min = prevdoor->x - 5 + (rand () % 3);
								}
							if (newroom.x_max == 0)
								{
									newroom.x_max = prevdoor->x + 5 - (rand () % 3);
								}
							if (newroom.y_min == 0)
								{
									newroom.y_min = newroom.y_max - 4 - (rand () % 5);
								}
							break;
						case 3:
							newroom.x_max = prevdoor->x - 1;
							if (newroom.x_min == 0)
								{
									newroom.x_min = newroom.x_max - 4 - (rand () % 5);
								}
							if (newroom.y_min == 0)
								{
									newroom.y_min = prevdoor->y - 5 + (rand () % 3);
								}
							if (newroom.y_max == 0)
								{
									newroom.y_max = prevdoor->y + 5 - (rand () % 3);
								}
							break;
						}

				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
		}														//connecting rooms
	else if (searchneardoor (tabdoor, *prevdoor, *doorcount) > 0)
		{
			directionindex = 0;
			do
				{
					switch (prevdoor->direction)
						{
						case 0:
							newroom.x_min = prevdoor->x - 3 + (rand () % 2);
							newroom.x_max = newroom.x_min + 3 + (rand () % 4);
							newroom.y_min = prevdoor->y + 1;
							newroom.y_max = newroom.y_min + 3 + (rand () % 4);
							break;
						case 1:
							newroom.x_min = prevdoor->x + 1;
							newroom.x_max = newroom.x_min + 3 + (rand () % 4);
							newroom.y_min = prevdoor->y - 3 + (rand () % 2);
							newroom.y_max = newroom.y_min + 3 + (rand () % 4);
							break;
						case 2:
							newroom.x_min = prevdoor->x - 3 + (rand () % 2);
							newroom.x_max = newroom.x_min + 3 + (rand () % 4);
							newroom.y_max = prevdoor->y - 1;
							newroom.y_min = newroom.y_max - 3 - (rand () % 4);
							break;
						case 3:
							newroom.x_max = prevdoor->x - 1;
							newroom.x_min = newroom.x_max - 3 - (rand () % 4);
							newroom.y_min = prevdoor->y - 3 + (rand () % 2);
							newroom.y_max = newroom.y_min + 3 + (rand () % 4);
							break;
						}
				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
			do
				{
					newroom.num_door = rand () % 3 + 1;
					for (int i = 0; i < 4; i++)
						{
							newroom.room_door[i] = -1;
						}
					newroom.room_door[(prevdoor->direction + 2) % 4] = 1;
					while (newroom.num_door > MAX_ROOM - *roomcount)
						{
							newroom.num_door--;
							switch (newroom.num_door)
								{
								case 2:
									randtamp = rand () % 4;
									if (randtamp == (prevdoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newroom.room_door[randtamp] = 1;
									break;
								case 3:
									randtamp = rand () % 4;
									if (randtamp == (prevdoor->direction + 2) % 4)
										{
											randtamp = (randtamp + 1) % 4;
										}
									newroom.room_door[randtamp] = 1;
									randtamp2 = rand () % 4;
									do
										{
											randtamp2 = (randtamp2 + 1) % 4;
										}
									while (randtamp2 !=
												 (prevdoor->direction + 2) % 4
												 && randtamp2 != randtamp);
									newroom.room_door[randtamp2] = 1;
									break;
								}
						}
				}
			while (confirmdoororientation (tabroom, newroom, *roomcount, *prevdoor)
						 == 0);
			for (int i = *doorcount; i < doornum + newroom.num_door - 1; i++)
				{
					tabdoor[i].roomNum1 = *roomcount;
					tabdoor[i].roomNum2 = -1;
					while (newroom.room_door[directionindex] != 1
								 || directionindex == ((prevdoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}
					tabdoor[i].direction = directionindex;
					do
						{
							for (int i = 0; i < 4; i++)
								{
									newroom.room_door[i] = -1;
								}
							switch (tabdoor[i].direction)
								{
								case 0:
									tabdoor[i].x =
                                            newroom.x_min + 1 +
                                            (rand () % (newroom.x_max - newroom.x_min - 1));
									tabdoor[i].y = newroom.y_max + 1;
									break;
								case 1:
									tabdoor[i].x = newroom.x_max + 1;
									tabdoor[i].y =
                                            newroom.y_min + 1 +
                                            (rand () % (newroom.y_max - newroom.y_min - 1));
									break;
								case 2:
									tabdoor[i].x =
                                            newroom.x_min + 1 +
                                            (rand () % (newroom.x_max - newroom.x_min - 1));
									tabdoor[i].y = newroom.y_min - 1;
									break;
								case 3:
									tabdoor[i].x = newroom.x_min - 1;
									tabdoor[i].y =
                                            newroom.y_min + 1 +
                                            (rand () % (newroom.y_max - newroom.y_min - 1));
									break;
								}
						}
					while (confirmdoorloc
								 (tabdoor, tabdoor[i], *doorcount, tabroom, *roomcount) == 0);
					directionindex++;
					(*doorcount)++;
				}
		}														//near rooms
	else
		{
			directionindex = 0;
			switch (prevdoor->direction)
				{
				case 0:
					newroom.x_min = prevdoor->x - 4 + (rand () % 3);
					newroom.x_max = newroom.x_min + 4 + (rand () % 5);
					newroom.y_min = prevdoor->y + 1;
					newroom.y_max = newroom.y_min + 4 + (rand () % 5);
					break;
				case 1:
					newroom.x_min = prevdoor->x + 1;
					newroom.x_max = newroom.x_min + 4 + (rand () % 5);
					newroom.y_min = prevdoor->y - 4 + (rand () % 3);
					newroom.y_max = newroom.y_min + 4 + (rand () % 5);
					break;
				case 2:
					newroom.x_min = prevdoor->x - 4 + (rand () % 3);
					newroom.x_max = newroom.x_min + 4 + (rand () % 5);
					newroom.y_max = prevdoor->y - 1;
					newroom.y_min = newroom.y_max - 4 - (rand () % 5);
					break;
				case 3:
					newroom.x_max = prevdoor->x - 1;
					newroom.x_min = newroom.x_max - 4 - (rand () % 5);
					newroom.y_min = prevdoor->y - 4 + (rand () % 3);
					newroom.y_max = newroom.y_min + 4 + (rand () % 5);
					break;
				}
			while (confirmoverlap (tabroom, newroom, *roomcount) == 0);
			do
				{
					for (int i = 0; i < 4; i++)
						{
							newroom.room_door[i] = -1;
						}
					newroom.room_door[(prevdoor->direction + 2) % 4] = 1;
					newroom.num_door = rand () % 3 + 2;
					while (newroom.num_door > MAX_ROOM - *roomcount)
						{
							newroom.num_door--;
						}
					switch (newroom.num_door)
						{
						case 2:
							randtamp = rand () % 4;
							if (randtamp == (prevdoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newroom.room_door[randtamp] = 1;
							break;
						case 3:
							randtamp = rand () % 4;
							if (randtamp == (prevdoor->direction + 2) % 4)
								{
									randtamp = (randtamp + 1) % 4;
								}
							newroom.room_door[randtamp] = 1;
							randtamp2 = rand () % 4;
							do
								{
									randtamp2 = (randtamp2 + 1) % 4;
								}
							while (randtamp2 ==
										 (prevdoor->direction + 2) % 4 || randtamp2 == randtamp);
							newroom.room_door[randtamp2] = 1;
							break;
						case 4:
							for (int i = 0; i < 4; i++)
								{
									newroom.room_door[i] = 1;
								}
						}
				}
			while (confirmdoororientation (tabroom, newroom, *roomcount, *prevdoor)
						 == 0);
			for (int i = *doorcount; i < doornum + newroom.num_door - 1; i++)
				{
					tabdoor[i].roomNum1 = *roomcount;
					tabdoor[i].roomNum2 = -1;
					while (newroom.room_door[directionindex] != 1
								 || directionindex == ((prevdoor->direction) + 2) % 4)
						{
							directionindex = (directionindex + 1) % 4;
						}
					tabdoor[i].direction = directionindex;
					do
						{
							switch (tabdoor[i].direction)
								{
								case 0:
									tabdoor[i].x =
                                            newroom.x_min + 1 +
                                            (rand () % (newroom.x_max - newroom.x_min - 1));
									tabdoor[i].y = newroom.y_max + 1;
									break;
								case 1:
									tabdoor[i].x = newroom.x_max + 1;
									tabdoor[i].y =
                                            newroom.y_min + 1 +
                                            (rand () % (newroom.y_max - newroom.y_min - 1));
									break;
								case 2:
									tabdoor[i].x =
                                            newroom.x_min + 1 +
                                            (rand () % (newroom.x_max - newroom.x_min - 1));
									tabdoor[i].y = newroom.y_min - 1;
									break;
								case 3:
									tabdoor[i].x = newroom.x_min - 1;
									tabdoor[i].y =
                                            newroom.y_min + 1 +
                                            (rand () % (newroom.y_max - newroom.y_min - 1));
									break;
								}
						}
					while (confirmdoorloc
								 (tabdoor, tabdoor[i], *doorcount, tabroom, *roomcount) == 0);
					(*doorcount)++;
					directionindex++;
				}
		}

	(*roomcount)++;
	return newroom;
}

room
createmainroom ()
{
	room froom;
	for (int j = 0; j < 4; j++)
		{
			froom.room_door[j] = 1;
		}
	froom.num_door = 4;
	froom.x_min = 1 * -4;
	froom.x_max = 1 * 5;
	froom.y_min = 1 * -4;
	froom.y_max = 1 * 5;

	return froom;
}

void
createmaindoor (door * tabdoor)
{
	tabdoor[0].x = 0;
	tabdoor[0].y = 6;
	tabdoor[0].roomNum1 = 0;
	tabdoor[0].roomNum2 = -1;
	tabdoor[0].direction = 0;
	tabdoor[1].x = 6;
	tabdoor[1].y = 0;
	tabdoor[1].roomNum1 = 0;
	tabdoor[1].roomNum2 = -1;
	tabdoor[1].direction = 1;
	tabdoor[2].x = 0;
	tabdoor[2].y = -5;
	tabdoor[2].roomNum1 = 0;
	tabdoor[2].roomNum2 = -1;
	tabdoor[2].direction = 2;
	tabdoor[3].x = -5;
	tabdoor[3].y = 0;
	tabdoor[3].roomNum1 = 0;
	tabdoor[3].roomNum2 = -1;
	tabdoor[3].direction = 3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//enemy fonction
double calculateDistance(Position pos1, Position pos2) {
    int dx = pos2.x - pos1.x;
    int dy = pos2.y - pos1.y;
    return sqrt(dx*dx + dy*dy);
}

int checkRange(Enemy* a, hero* player){
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
            return a;
        case DRONE:
            a.type = FLYING;
            a.life = 1;
            a.armor = 1;
            a.strength = 5;
            a.speed = 30;
            a.range = 8;
            return a;
        case ALIEN:
            a.type = ALL_IN;
            a.life = 80;
            a.armor = 10;
            a.strength = 15;
            a.speed = 20;
            a.range = 2;
            return a;
        case ROBOT:
            a.type = ALL_IN;
            a.life = 10;
            a.armor = 5;
            a.strength = 25;
            a.speed = 15;
            a.range = 2;
            return a;
        case TURRET:
            a.type = RANGE;
            a.life = 30;
            a.armor = 5;
            a.strength = 10;
            a.speed = 0;
            a.range = 8;
            return a;
        case BLOB:
            a.type = ALL_IN;
            a.life = 20;
            a.armor = 1;
            a.strength = 10;
            a.speed = 10;
            a.range = 1;
            return a;
        default:
            exit(404);
    }
}

void mobOrientation(Enemy* a, hero* player){
    if (player->coordinates.x > a->coordinates.x && player->coordinates.y > a->coordinates.y){
        if(a->coordinates.x - player->coordinates.x > a->coordinates.y - player->coordinates.y){
            a->orientation = 1;
        } else{
            a->orientation = 0;
        }
    }
    else if (player->coordinates.x > a->coordinates.x && player->coordinates.y < a->coordinates.y){
        if(a->coordinates.x - player->coordinates.x > a->coordinates.y - player->coordinates.y){
            a->orientation = 1;
        } else{
            a->orientation = 2;
        }
    }
    else if (player->coordinates.x < a->coordinates.x && player->coordinates.y < a->coordinates.y){
        if(a->coordinates.x - player->coordinates.x > a->coordinates.y - player->coordinates.y){
            a->orientation = 2;
        } else{
            a->orientation = 3;
        }
    }
    else {
        if(a->coordinates.x - player->coordinates.x > a->coordinates.y - player->coordinates.y){
            a->orientation = 3;
        } else{
            a->orientation = 0;
        }
    }
}

void moveMob(Enemy* a, hero* player, room* b){
    int x = 0;
    int y = 0;
    printf("hero Position : %d %d\n", player->coordinates.x, player->coordinates.y);
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

void enemySpawn(int number, room* b, int* seed){
    int x;
    b->tab_enemy = malloc(sizeof(Enemy)*number);
    if (b->tab_enemy == NULL){
        exit(1);
    }
    for (int i=0;i<number;i++){
        Enemy a;

        x = rand()%6+1;
        //*seed++;
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
        //*seed+=2;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//think fonction
void stuffSpawn(room* a, FILE* Object, FILE* Blade, FILE* Armor, int* seed){
    a->tab_object = malloc(sizeof(Object)*a->nbr_object);
    a->tab_blade = malloc(sizeof(Weapon)*a->nbr_blade);
    a->tab_armor = malloc(sizeof(Armor)*a->nbr_armor);

    for (int i=0; i<a->nbr_object ; i++){
        a->tab_object[i] = search_object(rand()%14,Object);
        a->tab_object[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_object[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
    }

    for (int i=0; i<a->nbr_blade ; i++){
        a->tab_blade[i] = search_blade(rand()%7,Blade);
        a->tab_blade[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_blade[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
    }

    for (int i=0; i<a->nbr_armor ; i++){
        a->tab_armor[i] = search_stuff(rand()%6,Armor);
        a->tab_armor[i].coordinates.x = rand() % (a->x_max - a->x_min) + a->x_min;
        a->tab_armor[i].coordinates.y = rand() % (a->y_max - a->y_min) + a->y_min;
    }
    //*seed+=3;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//display fonction
void display_menu(int screen_length,int screen_width,int menu_cursor,WINDOW* background){
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

void display_name_menu(int screen_length,int screen_width,WINDOW* background,char* name){
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

int search_save(char* name,FILE* fichier){
	rewind(fichier);
    char c=getc(fichier);
	while(c != EOF){
		if(c=='@'){
            int name_pareil=1;
            for(int i=0;i<3;i++){
                c=getc(fichier);
                if(c != name[i]){
                    i=3;
                    name_pareil=0;
                    }
                }
            if(name_pareil){
                return 1;
                }
            }
		c=getc(fichier);
		}
    return 0;
    }

void display_seed_menu(int screen_length,int screen_width,WINDOW* background,int seed,int count){
    mvprintw(10+2*count,10,"%d",seed);
    refresh();
    }

void display_name_load_menu(int screen_length,int screen_width,WINDOW* background,char* name,int load_menu_cursor){
    display_name_menu(screen_length,screen_width,background,name);

    //browse the different backups and display their names
    /*
    
    */
    }

void display_game(int screen_length,int screen_width,hero player,WINDOW* background, time_t timer,int time_pause,int time_jouer,int time_to_play,int* end){
    clear();
    refresh();
    background=newwin(screen_width,screen_length,0,0);
    wbkgd(background,COLOR_PAIR(3));  
    wrefresh(background);

    time_t time_now=time(NULL);
    int time_total=time_now-timer-time_pause+time_jouer;

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
    mvprintw(1,screen_length-66,"materiel: %04d     level: %03d     XP: %04d     inventory: %02d/15",player.score, player.level,player.XP, player.nbr_object_inventory);
    mvprintw(3,screen_length-66,"Weapon: %s  %d damage  %d range",player.blade.name, player.blade.dmg, player.blade.range);
    mvprintw(5,screen_length-66,"Stuff: %s  %d armor",player.stuff.name, player.stuff.shield);
    move(screen_width+10,screen_length+10);
    refresh();
    }

void display_donjon(int screen_length,int screen_width,hero player,int doorcount,door* tabdoor,int roomcount,room* tabroom, WINDOW* donjon){
    //refresh();
    donjon=newwin(screen_width-8,screen_length-6,6,3);
    wbkgd(donjon,COLOR_PAIR(6));
    wrefresh(donjon);

    int local_x;
    int local_y;

    //display room
    for(int i=0;i<roomcount;i++){
        //display room background
        for(int j=0;j<=absolute_value(tabroom[i].y_max - tabroom[i].y_min); j++){
            for(int k=0;k<=absolute_value(tabroom[i].x_max - tabroom[i].x_min); k++){
                local_x= player.coordinates.x - tabroom[i].x_max + k;
                local_y=-(player.coordinates.y - tabroom[i].y_max + j);
                if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
                    attron(COLOR_PAIR(10));
                    mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x," ");
                    refresh();
                    }
                }
            }

        //display enemy
        for(int l=0;l<tabroom[i].nbr_enemy;l++){
            local_x=player.coordinates.x-tabroom[i].tab_enemy[l].coordinates.x;
            local_y=-(player.coordinates.y-tabroom[i].tab_enemy[l].coordinates.y);
            if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
                attron(COLOR_PAIR(11));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"E");
                refresh();
                }
            }

        //display objetc
        for(int l=0;l<tabroom[i].nbr_object;l++){
            local_x=player.coordinates.x-tabroom[i].tab_object[l].coordinates.x;
            local_y=-(player.coordinates.y-tabroom[i].tab_object[l].coordinates.y);
            if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
                attron(COLOR_PAIR(12));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"O");
                refresh();
                }
            }
        //display armor
        for(int l=0;l<tabroom[i].nbr_armor;l++){
            local_x=player.coordinates.x-tabroom[i].tab_armor[l].coordinates.x;
            local_y=-(player.coordinates.y-tabroom[i].tab_armor[l].coordinates.y);
            if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
                attron(COLOR_PAIR(13));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"A");
                }
            }
        //display blade
        for(int l=0;l<tabroom[i].nbr_blade;l++){
            local_x=player.coordinates.x-tabroom[i].tab_blade[l].coordinates.x;
            local_y=-(player.coordinates.y-tabroom[i].tab_blade[l].coordinates.y);
            if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
                attron(COLOR_PAIR(14));
                mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"W");
                refresh();
                }
            }
      }
    //display door
    for(int i=0;i<doorcount;i++){
      int local_x=player.coordinates.x-tabdoor[i].x;
      int local_y=-(player.coordinates.y-tabdoor[i].y);
      if(absolute_value(local_x) <= (screen_length-6)/2 && absolute_value(local_y) <= (screen_width-8)/2){
        attron(COLOR_PAIR(6));
        mvprintw(6+(screen_width-8)/2-local_y,3+(screen_length-6)/2-local_x,"P");
        refresh();
        }
      }

    display_hit(player,screen_length,screen_width);

    //display hero
    attron(COLOR_PAIR(10));
    mvprintw(6+(screen_width-8)/2,3+(screen_length-6)/2,"&");
    refresh();
    }

void display_inventory_menu(int screen_length,int screen_width,hero player,WINDOW* donjon,int inventory_cursor){
    //window start in 6 3
    donjon=newwin(screen_width-8,screen_length-6,6,3);
    wbkgd(donjon,COLOR_PAIR(8));
    wrefresh(donjon);

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
                //x=start_window+2+nbr_object_raw*lenght_object
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
                //name objet
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
    WINDOW *background,*donjon;

    
    FILE* fichier=NULL;
    fichier=fopen("save.txt","r+");
    if(fichier==NULL){
	    fichier=fopen("save.txt","w+");
    }
    FILE* fichier_blade=NULL;
    fichier_blade=fopen("blade.txt","r");
    if(fichier_blade==NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
    FILE* fichier_stuff=NULL;
    fichier_stuff=fopen("Armor.txt","r");
    if(fichier_stuff==NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
    FILE* fichier_object=NULL;
    fichier_object=fopen("Object.txt","r");
    if(fichier_object==NULL){
        printf("error txt doesn't exist");
        exit(1);
    }
 
    //init loop to play
    int in_menu=1;
    int end=0;
    int in_game=0;
    int in_pause=0;
    int in_inventory=0;

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
    //background game and baground item
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
    //room background
    init_pair(10, COLOR_WHITE, COLOR_BEIGE_LIGHT);
    //ennemy
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
    hero player;
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
    int moove_up=KEY_UP;
    int moove_down=KEY_DOWN;
    int moove_left=KEY_LEFT;
    int moove_right=KEY_RIGHT;
    int key_fight='a';
    // ...
    
    //init room
    int maxroom= MAX_ROOM;
    int roomcount= 0;
    int doorcount=0;
    room *tabroom;
    door *tabdoor;
    tabdoor = malloc(sizeof(door) * MAX_ROOM * 4);
    if (tabdoor == NULL) {
        exit(1);
        }
    tabroom = malloc(maxroom * sizeof(room));
    if (tabroom == NULL) {
        exit(1);
        }
    
    //init timer
    time_t timer=0;
    int time_pause=0;
    int time_jouer=0;
    time_t time_start_pause;
    int time_to_play=1;
    
    while(in_menu){
        //display menu
        display_menu(screen_length,screen_width,menu_cursor,background);
        
        int test1=getch();
        //choose menu button
        //press enter
        if(test1==key_enter){
            int name_complet=0;
            int Exit=0;

            //init name
            name[0]=0;
            name[1]=0;
            name[2]=0;
            name[3]='\0';

            int avancement=0;
            int load_menu_cursor=0;
            //start the game
            switch(menu_cursor){
                case 0:
                    name_complet=0;
                    Exit=0;
                    avancement=0;
                    
                    while(!name_complet && !Exit){
                        display_name_menu(screen_length,screen_width,background,name);
                        
                        test1=getch();
                        if (test1==key_exit){
                            //key echap
                            Exit=1;
                            }
                        else if (test1==key_enter && avancement>2){
                            name_complet=1;
                            }
                        else if (test1==key_sup_text && avancement>0){
                            avancement--;
                            name[avancement]=0;
                            }
                        //recover first name letter
                        else if ((48<=test1 && test1<=59) || (97<=test1 && test1<=122) || (65<=test1 && test1<=90)){
                            name[avancement]=test1;
                            avancement++;
                            }
                        }

                    if (name_complet){
                        int count=0;
                        mvprintw(8,10,"Enter your seed");
                        refresh();
                        do{
                        scanf("%d",&seed);
                        display_seed_menu(screen_length,screen_width,background,seed,count);
                        count++;
                        }while(seed>=10000000000 || seed<0);

                        srand(seed);

                        in_game=1;
                        Exit=0;
                        end=0;
                        player=build_hero(fichier_blade,fichier_stuff);

                        roomcount=1;
                        doorcount=4;
                        createmaindoor(tabdoor);
                        tabroom[0] = createmainroom();
                        
                        timer=time(NULL);
                        time_pause=0;
                        time_jouer=0;
                        }
                    break;
                case 1:
                    name_complet=0;
                    Exit=0;
                    avancement=0;
                    
                    while(!name_complet && !Exit){
                        display_name_load_menu(screen_length,screen_width,background,name,load_menu_cursor);
                        
                        test1=getch();
                        if (test1==key_exit){
                            //key echap
                            Exit=1;
                            }
                        else if (test1==key_enter && avancement>=2){
                            name_complet=1;
                            }
                        else if (test1==key_sup_text){
                            avancement--;
                            name[avancement]=0;
                            }
                        //recover first name letter
                        else if ((48<=test1 && test1<=59) || (97<=test1 && test1<=122) || (65<=test1 && test1<=90)){
                            name[avancement]=test1;
                            avancement++;
                            }
                        }
                        
                    if (name_complet){
                        //search game
                        int verif=EOF;
                        if(search_save(name,fichier)){
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
                            verif=fscanf(fichier,"%d %d %d %d %d %d %d %d %d %s %d %d %d %s %d %d ",&player.coordinates.x, &player.coordinates.y, &player.room, &player.life, &player.max_life, &player.level, &player.XP, &player.score, &player.strength, player.stuff.name, &player.stuff.id, &player.stuff.weight, &player.stuff.shield, player.blade.name, &player.blade.id, &temp);
                            if(verif==EOF){
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

                            verif=fscanf(fichier,"%d %d %d %d ",&player.blade.range, &player.blade.dmg, &player.blade.weight, &player.nbr_object_inventory);
                            if(verif==EOF){
                                printf("error load charging");
                                exit(3);
                                }

                            player.inventory=calloc(15,sizeof(Object));
                            if(player.inventory==NULL){
                                printf("error calloc");
                                exit(3);
                                }
                            for(int i=0;i<player.nbr_object_inventory;i++){
                                verif=fscanf(fichier,"%d",&player.inventory[i].id);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }
                                player.inventory[i]=search_object(player.inventory[i].id,fichier_object);
                                }
                            player.orientation=0;
                            player.start_hit=0;

                            //Load important var
                            verif=fscanf(fichier,"%d %d %d",&roomcount, &doorcount, &maxroom);
                            if(verif==EOF){
                                printf("error load charging");
                                exit(3);
                                }

                            tabdoor = malloc(sizeof(door) * maxroom * 4);
                            if (tabdoor == NULL) {
                                exit(1);
                                }

                            tabroom = malloc(maxroom * sizeof(room));
                            if (tabroom == NULL) {
                                exit(1);
                                }

                            //Load room
                            for(int i=0;i<roomcount;i++){
                                verif=fscanf(fichier, "%d %d %d %d %d", &tabroom[i].x_min, &tabroom[i].x_max, &tabroom[i].y_min, &tabroom[i].y_max, &tabroom[i].nbr_enemy);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }

                                //Load enemy in the room
                                tabroom[i].tab_enemy=malloc(tabroom[i].nbr_enemy * sizeof(Enemy));
                                if( tabroom[i].tab_enemy==NULL){
                                    printf("error malloc");
                                    exit(3);
                                    }
                                for(int j=0;j<tabroom[i].nbr_enemy;j++){
                                    verif=fscanf(fichier,"%d",&temp);
                                    if(verif==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    switch(temp){
                                        case 1:
                                            tabroom[i].tab_enemy[j].name= GIGA_ROBOT;
                                            break;
                                        case 2:
                                            tabroom[i].tab_enemy[j].name= DRONE;
                                            break;
                                        case 3:
                                            tabroom[i].tab_enemy[j].name= ALIEN;
                                            break;
                                        case 4:
                                            tabroom[i].tab_enemy[j].name= ROBOT;
                                            break;
                                        case 5:
                                            tabroom[i].tab_enemy[j].name= BLOB;
                                            break;
                                        case 6:
                                            tabroom[i].tab_enemy[j].name= TURRET;
                                            break; 
                                        }

                                    verif=fscanf(fichier,"%d %d %d %d %d %d %d %d %d ",&tabroom[i].tab_enemy[j].coordinates.x, &tabroom[i].tab_enemy[j].coordinates.y, &tabroom[i].tab_enemy[j].life, &tabroom[i].tab_enemy[j].armor, &tabroom[i].tab_enemy[j].strength, &tabroom[i].tab_enemy[j].speed, &tabroom[i].tab_enemy[j].range, &tabroom[i].tab_enemy[j].XP, &temp);
                                    if(verif==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }

                                    switch(temp){
                                        case 1:
                                            tabroom[i].tab_enemy[j].type= ALL_IN;
                                            break;
                                        case 2:
                                            tabroom[i].tab_enemy[j].type= FLYING;
                                            break;
                                        case 3:
                                            tabroom[i].tab_enemy[j].type= RANGE;
                                            break;
                                        }
                                    tabroom[i].tab_enemy[j].orientation=0;
                                    tabroom[i].tab_enemy[j].cooldown=0;
                                    }

                                verif=fscanf(fichier,"%d",&tabroom[i].nbr_object);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }

                                //Load object in the room
                                tabroom[i].tab_object=malloc(tabroom[i].nbr_object * sizeof(Object));
                                if( tabroom[i].tab_object==NULL){
                                    printf("error malloc");
                                    exit(3);
                                    }
                                for(int j=0;j<tabroom[i].nbr_object;j++){
                                    verif=fscanf(fichier,"%d ",&tabroom[i].tab_object[j].id);
                                    if(verif==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    tabroom[i].tab_object[j]=search_object(tabroom[i].tab_object[j].id,fichier_object);
                                    }

                                verif=fscanf(fichier,"%d",&tabroom[i].nbr_armor);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }
                                //Load armor in the room
                                tabroom[i].tab_armor=malloc(tabroom[i].nbr_armor * sizeof(Armor));
                                if( tabroom[i].tab_armor==NULL){
                                    printf("error malloc");
                                    exit(3);
                                    }
                                for(int j=0;j<tabroom[i].nbr_armor;j++){
                                    verif=fscanf(fichier,"%d",&tabroom[i].tab_armor[j].id);
                                    if(verif==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    tabroom[i].tab_armor[j]=search_stuff(tabroom[i].tab_armor[j].id,fichier_stuff);
                                    }

                                verif=fscanf(fichier,"%d",&tabroom[i].nbr_blade);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }      
                                //Load blade in the room
                                tabroom[i].tab_blade=malloc(tabroom[i].nbr_blade * sizeof(Weapon));
                                if( tabroom[i].tab_blade==NULL){
                                    printf("error malloc");
                                    exit(3);
                                    }
                                for(int j=0;j<tabroom[i].nbr_blade;j++){
                                    verif=fscanf(fichier,"%d",&tabroom[i].tab_blade[j].id);
                                    if(verif==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    tabroom[i].tab_blade[j]=search_blade(tabroom[i].tab_blade[j].id,fichier_blade);
                                    }
                                }
                            //Load door
                            for(int i=0;i<doorcount;i++){
                                verif=fscanf(fichier, "%d %d %d %d %d", &tabdoor[i].x, &tabdoor[i].y, &tabdoor[i].roomNum1, &tabdoor[i].roomNum2, &tabdoor[i].direction);
                                if(verif==EOF){
                                    printf("error load charging");
                                    exit(3);
                                    }
                                }
                            //Load time
                            verif=fscanf(fichier,"%d",&time_jouer);
                            if(verif==EOF){
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
                  //to be continued int the next episode
                    break;
                case 3:
                    in_menu=0;
                    break;
                }
            }
        //select button
        else if (test1==key_exit){
            //key echap
            in_menu=0;
            }
        //key up or key left
        else if (test1==moove_up || test1==moove_left){
            menu_cursor--;
            }
        //key down
        else if (test1==moove_down || test1==moove_right){
            menu_cursor++;
            }
        //keeps the menu cursor on a button
        menu_cursor=(menu_cursor+4)%4;
        
        while(in_game){
            if(!in_pause && !in_inventory){
                //display game
                display_game(screen_length,screen_width,player,background,timer,time_pause,time_jouer,time_to_play,&end);

                //display donjon
                display_donjon(screen_length,screen_width,player,doorcount,tabdoor,roomcount,tabroom,donjon);

                test1=getch();

                //select button
                if (test1==key_exit){
                    //key echap
                    in_pause=1;
                    time_start_pause=time(NULL);

                    //display pause menu
                    display_game(screen_length,screen_width,player,background,timer,time_pause,time_jouer,time_to_play,&end);

                    move(screen_width/2,screen_length/2);
                    printw("pause");
                    move(screen_width+10,screen_length+10);
                    refresh();
                    }
                //key up
                else if (test1==moove_up){
                    player.orientation=0;
                    //moove into door
                    if(player.coordinates.y==tabroom[player.room].y_max){
                        for(int i=0;i<doorcount;i++){
                            if(tabdoor[i].x==player.coordinates.x && tabdoor[i].y-1==player.coordinates.y){
                                player.coordinates.y+=2;
                                if(tabdoor[i].roomNum2 == -1){
                                    //générer room
                                    tabroom[roomcount]=generateroom(seed,&maxroom,tabroom,&tabdoor[i],&roomcount,tabdoor,&doorcount);
                                    
                                    //générer mobs armor blade   
                                    tabroom[roomcount-1].nbr_enemy=rand()%5;
                                    tabroom[roomcount-1].nbr_object=rand()%2;
                                    tabroom[roomcount-1].nbr_armor=rand()%1;
                                    tabroom[roomcount-1].nbr_blade=rand()%1;
                                    seed+=4;

                                    enemySpawn(tabroom[roomcount-1].nbr_enemy, &tabroom[roomcount-1], &seed);
                                    stuffSpawn(&tabroom[roomcount-1], fichier_object, fichier_blade, fichier_stuff, &seed);
                                    }
                                if(player.room==tabdoor[i].roomNum1){
                                    player.room=tabdoor[i].roomNum2;
                                    }
                                else{
                                    player.room=tabdoor[i].roomNum1;
                                    }
                                }
                            }
                        }
                    else{
                        player.coordinates.y++;
                        }
                    }
                //key down
                else if (test1==moove_down){
                    player.orientation=2;
                    //moove into door
                    if(player.coordinates.y==tabroom[player.room].y_min){
                        for(int i=0;i<doorcount;i++){
                            if(tabdoor[i].x==player.coordinates.x && tabdoor[i].y+1==player.coordinates.y){
                                player.coordinates.y-=2;
                                if(tabdoor[i].roomNum2 == -1){
                                    //générer room
                                    tabroom[roomcount]=generateroom(seed,&maxroom,tabroom,&tabdoor[i],&roomcount,tabdoor,&doorcount);
                                    
                                    //générer mobs armor blade    
                                    tabroom[roomcount-1].nbr_enemy=rand()%5;
                                    tabroom[roomcount-1].nbr_object=rand()%2;
                                    tabroom[roomcount-1].nbr_armor=rand()%1;
                                    tabroom[roomcount-1].nbr_blade=rand()%1;
                                    seed+=4;

                                    enemySpawn(tabroom[roomcount-1].nbr_enemy, &tabroom[roomcount-1], &seed);
                                    stuffSpawn(&tabroom[roomcount-1], fichier_object, fichier_blade, fichier_stuff, &seed);
                                    }
                                if(player.room==tabdoor[i].roomNum1){
                                    player.room=tabdoor[i].roomNum2;
                                    }
                                else{
                                    player.room=tabdoor[i].roomNum1;
                                    }
                                }
                            }
                        }
                    else{
                        player.coordinates.y--;
                        }
                    }
                //key left
                else if (test1==moove_left){
                    player.orientation=3;
                    //moove into door
                    if(player.coordinates.x==tabroom[player.room].x_min){
                        for(int i=0;i<doorcount;i++){
                            if(tabdoor[i].y==player.coordinates.y && tabdoor[i].x+1==player.coordinates.x){
                                player.coordinates.x-=2;
                                if(tabdoor[i].roomNum2 == -1){
                                    //générer room
                                    tabroom[roomcount]=generateroom(seed,&maxroom,tabroom,&tabdoor[i],&roomcount,tabdoor,&doorcount);
                                    
                                    //générer mobs armor 
                                    tabroom[roomcount-1].nbr_enemy=rand()%5;
                                    tabroom[roomcount-1].nbr_object=rand()%2;
                                    tabroom[roomcount-1].nbr_armor=rand()%1;
                                    tabroom[roomcount-1].nbr_blade=rand()%1;

                                    seed+=4;

                                    enemySpawn(tabroom[roomcount-1].nbr_enemy, &tabroom[roomcount-1], &seed);
                                    stuffSpawn(&tabroom[roomcount-1], fichier_object, fichier_blade, fichier_stuff, &seed);
                                    }
                                if(player.room==tabdoor[i].roomNum1){
                                    player.room=tabdoor[i].roomNum2;
                                    }
                                else{
                                    player.room=tabdoor[i].roomNum1;
                                    }
                                }
                            }
                        }
                    else{
                        player.coordinates.x--;
                        }
                    }
                //key right
                if (test1==moove_right){
                    player.orientation=1;
                    //moove into door
                    if(player.coordinates.x==tabroom[player.room].x_max){
                        for(int i=0;i<doorcount;i++){
                            if(tabdoor[i].y==player.coordinates.y && tabdoor[i].x-1==player.coordinates.x){
                                player.coordinates.x+=2;
                                if(tabdoor[i].roomNum2 == -1){
                                    //générer room
                                    tabroom[roomcount]=generateroom(seed,&maxroom,tabroom,&tabdoor[i],&roomcount,tabdoor,&doorcount);

                                    //générer mobs armor blade
                                    /*
                                    tabroom[roomcount-1].nbr_enemy=rand()%5;
                                    tabroom[roomcount-1].nbr_object=rand()%2;
                                    tabroom[roomcount-1].nbr_armor=rand()%1;
                                    tabroom[roomcount-1].nbr_blade=rand()%1;
                                    */
                                    tabroom[roomcount-1].nbr_enemy=0;
                                    tabroom[roomcount-1].nbr_object=1;
                                    tabroom[roomcount-1].nbr_armor=1;
                                    tabroom[roomcount-1].nbr_blade=1;


                                    seed+=4;

                                    enemySpawn(tabroom[roomcount-1].nbr_enemy, &tabroom[roomcount-1], &seed);
                                    stuffSpawn(&tabroom[roomcount-1], fichier_object, fichier_blade, fichier_stuff,&seed);
                                    }
                                if(player.room==tabdoor[i].roomNum1){
                                    player.room=tabdoor[i].roomNum2;
                                    }
                                else{
                                    player.room=tabdoor[i].roomNum1;
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
                    in_inventory=1;
                    inventory_cursor=0;
                    }
        
                //press enter
                else if(test1==key_enter){
                    //collect thing
                    collect_object(&player,tabroom);
                    collect_armor(&player,tabroom,screen_length,screen_width,background,timer,time_pause,time_jouer,time_to_play,&end);
                    collect_blade(&player,tabroom,screen_length,screen_width,background,timer,time_pause,time_jouer,time_to_play,&end);
                    }
                    
                else if(test1==key_fight){
                    //attack
                    player.start_hit=time(NULL);
                    you_hit(&player,tabroom);
                    }

                }
            else if(in_pause){
                test1=getch();
                if (test1==key_exit){
                    //key echap
                    in_game=0;
                    in_pause=0;
                    menu_cursor=0;
                    time_pause+=time(NULL)-time_start_pause;
                    time_jouer+=(time(NULL)-timer)-time_pause;

                    //save
                    //save player
                    int verif2=EOF;
                    if(!search_save(name,fichier)){
                        verif2=fprintf(fichier,"@%s",name);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(5);
                            }  
                        }
                    verif2=fprintf(fichier," ");
                    if(verif2==EOF){
                        printf("error load charging");
                        exit(5);
                        }

                    verif2=fprintf(fichier,"%d %d %d %d %d %d %d %d %d %s %d %d %d %s %d ", player.coordinates.x, player.coordinates.y, player.room, player.life, player.max_life, player.level, player.XP, player.score, player.strength, player.stuff.name, player.stuff.id, player.stuff.weight, player.stuff.shield, player.blade.name, player.blade.id);
                    if(verif2==EOF){
                        printf("error load charging");
                        exit(5);
                        }   

                    switch (player.blade.type){
                        case RANGED:
                            verif2=fprintf(fichier,"1 ");
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            break;
                        case CC:
                            verif2=fprintf(fichier,"2 ");
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            break;    
                        }
                    verif2=fprintf(fichier,"%d %d %d %d ",player.blade.range, player.blade.dmg, player.blade.weight, player.nbr_object_inventory);
                    if(verif2==EOF){
                        printf("error load charging");
                        exit(3);
                        }

                    //save inventory (object)
                    for(int i=0;i<player.nbr_object_inventory;i++){
                        verif2=fprintf(fichier,"%d ",player.inventory[i].id);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }
                        }

                    //save important var
                    verif2=fprintf(fichier,"%d %d %d ", roomcount, doorcount, maxroom);
                    if(verif2==EOF){
                        printf("error load charging");
                        exit(3);
                        }

                    //save room
                    for(int i=0;i<roomcount;i++){
                        verif2=fprintf(fichier, "%d %d %d %d %d ", tabroom[i].x_min, tabroom[i].x_max, tabroom[i].y_min, tabroom[i].y_max, tabroom[i].nbr_enemy);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }

                        //save enemy in the room
                        for(int j=0;j<tabroom[i].nbr_enemy;j++){
                            switch(tabroom[i].tab_enemy[j].name){
                                case GIGA_ROBOT:
                                    verif2=fprintf(fichier,"1 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case DRONE:
                                    verif2=fprintf(fichier,"2 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case ALIEN:
                                    verif2=fprintf(fichier,"3 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case ROBOT:
                                    verif2=fprintf(fichier,"4 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case BLOB:
                                    verif2=fprintf(fichier,"6 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case TURRET:
                                    verif2=fprintf(fichier,"7 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                }

                            verif2=fprintf(fichier,"%d %d %d %d %d %d %d %d ",tabroom[i].tab_enemy[j].coordinates.x, tabroom[i].tab_enemy[j].coordinates.y, tabroom[i].tab_enemy[j].life, tabroom[i].tab_enemy[j].armor, tabroom[i].tab_enemy[j].strength, tabroom[i].tab_enemy[j].speed, tabroom[i].tab_enemy[j].range, tabroom[i].tab_enemy[j].XP);
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }

                            switch(tabroom[i].tab_enemy[j].type){
                                case ALL_IN:
                                    verif2=fprintf(fichier,"1 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case FLYING:
                                    verif2=fprintf(fichier,"2 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                case RANGE:
                                    verif2=fprintf(fichier,"3 ");
                                    if(verif2==EOF){
                                        printf("error load charging");
                                        exit(3);
                                        }
                                    break;
                                }
                            }

                        verif2=fprintf(fichier,"%d ",tabroom[i].nbr_object);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }
                        //save object
                        for(int j=0;j<tabroom[i].nbr_object;j++){
                            verif2=fprintf(fichier,"%d ",tabroom[i].tab_object[j].id);
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            }

                        verif2=fprintf(fichier,"%d ",tabroom[i].nbr_armor);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }
                        //save armor
                        for(int j=0;j<tabroom[i].nbr_armor;j++){
                            verif2=fprintf(fichier,"%d ",tabroom[i].tab_armor[j].id);
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            }

                        verif2=fprintf(fichier,"%d ",tabroom[i].nbr_blade);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }
                        //save blade
                        for(int j=0;j<tabroom[i].nbr_blade;j++){
                            verif2=fprintf(fichier,"%d ",tabroom[i].tab_blade[j].id);
                            if(verif2==EOF){
                                printf("error load charging");
                                exit(3);
                                }
                            }
                        }
                    //save door
                    for(int i=0;i<doorcount;i++){
                        verif2=fprintf(fichier, "%d %d %d %d %d ", tabdoor[i].x, tabdoor[i].y, tabdoor[i].roomNum1, tabdoor[i].roomNum2, tabdoor[i].direction);
                        if(verif2==EOF){
                            printf("error load charging");
                            exit(3);
                            }
                      }
                    //save time
                    verif2=fprintf(fichier,"%d\n",time_jouer);
                    if(verif2==EOF){
                        printf("error load charging");
                        exit(5);
                        }
                    }
                else if(test1!=-1){
                    //continue
                    in_pause=0;
                    time_pause+=time(NULL)-time_start_pause;
                    }
                }

            else if(in_inventory){
                //display game
                display_game(screen_length,screen_width,player,background,timer,time_pause,time_jouer,time_to_play,&end);
                //display inventory menu
                display_inventory_menu(screen_length,screen_width,player,donjon,inventory_cursor);

                test1=getch();
                if (test1==key_exit || test1==key_inventory){
                    //close inventory
                    in_inventory=0;
                    }
                //key up
                else if (test1==moove_up && inventory_cursor-5>=0){
                    inventory_cursor-=5;
                    }
                //key down
                else if (test1==moove_down && inventory_cursor+5<=14){ //inventory size-1
                    inventory_cursor+=5;
                    }
                //key left
                else if (test1==moove_left && inventory_cursor-1>=0){
                    inventory_cursor--;
                    }
                //key right
                else if (test1==moove_right && inventory_cursor+1<=14){//inventory size-1
                    inventory_cursor++;
                    }
                //press *
                else if(test1==key_delete){
                    do{
                        //refresh the timer
                        //display game
                        display_game(screen_length,screen_width,player,background,timer,time_pause,time_jouer,time_to_play,&end);
                        //display inventory menu
                        display_inventory_menu(screen_length,screen_width,player,donjon,inventory_cursor);
                        //verfication
                        attron(COLOR_PAIR(8));
                        mvprintw(screen_width-4,4,"are you sure you want to delete this item %s?",player.inventory[inventory_cursor].name);
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
                    use_object(&player,inventory_cursor);
                    }
                }
/* 
            for(int i=0;i<tabroom[player.room].nbr_enemy;i++){
                //mobOrientation(&tabroom[player.room].tab_enemy[i], &player);
                //moveMob(Enemy* a, hero* player, room* b)
                }
*/
            //ennemy enters or hits player
            be_hit(&player,tabroom);
            
            win_level(&player);
            
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
