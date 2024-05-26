#include "params.h"

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

void displayGame(int screen_length, int screen_width, Hero player, WINDOW* background, time_t timer, int time_pause, int time_play, int time_to_play, int* end){
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