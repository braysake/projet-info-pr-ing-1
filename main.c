#include "params.h"

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
                            //load object inventory
                            for(int i=0;i<player.nbr_object_inventory;i++){
                                verify=fscanf(file, "%d", &player.inventory[i].id);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
                                player.inventory[i]= searchObject(player.inventory[i].id, object_file);
                                
                                verify=fscanf(file, "%d", &player.inventory[i].stack);
                                if(verify == EOF){
                                    printf("error load charging");
                                    exit(3);
                                }
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
                        verify2=fprintf(file, "%d %d ", player.inventory[i].id, player.inventory[i].stack);
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
                            verify2=fprintf(file, "%d %d %d", tab_room[i].tab_object[j].id,
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