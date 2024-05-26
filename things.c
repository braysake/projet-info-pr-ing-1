#include "params.h"

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