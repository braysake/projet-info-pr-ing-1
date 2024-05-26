#include "params.h"

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