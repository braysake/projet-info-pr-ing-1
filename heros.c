#include "params.h"

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