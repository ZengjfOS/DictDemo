#include "single_linked.h"

#define NR(x) ((sizeof(x))/sizeof(x[0]))
#define MAP_LENGTH      26
#define ITEM_SIZE       128

/**
 * test struct
 */
typedef struct ITEM_DICT{
    char en[ITEM_SIZE];
    char ch[ITEM_SIZE];
}item_dict;

/**
 * callback function
 */
void print(void* data);
int compare(void* data, single_linked* linked_data);


int main(int argc, char** argv){

    single_linked* map[MAP_LENGTH][MAP_LENGTH] = {0};
    int i = 0;
    int j = 0;
    for(i = 0; i < NR(map); i++){
        for(j = 0; j < NR(map); j++){
            map[i][j] = create_single_linked(NULL, 0);
        }
    }

    item_dict item ={0};
    FILE* dict_db = fopen("./ciku.dict", "r+");
    char* temp = NULL;
    int map_y = 0;
    int map_x = 0;

    while(temp = fgets(item.en, ITEM_SIZE, dict_db)){

        if((*temp >= 'a') && (*temp <= 'z')){
            map_y = *temp - 'a';
        }else if((*temp >= 'A') && (*temp <= 'Z')){
            map_y = *temp - 'A';
        }
        if((*temp >= 'a') && (*temp <= 'z')){
            map_x = *temp - 'a';
        }else if((*temp >= 'A') && (*temp <= 'Z')){
            map_x = *temp - 'A';
        }

        temp = fgets(item.ch, ITEM_SIZE, dict_db);
        top_add_single_linked(&item, sizeof(item_dict), map[map_y][map_x]);
    }
    /**
     * at first time I had forget to close the dict_db file
     * and the software valgrind help me to catch this
     */
    fclose(dict_db);

    char en[ITEM_SIZE] = {0};
    while(1){
        printf("please input the word you wanna to search:\n");
        temp = fgets(en, ITEM_SIZE, stdin);
        if(strncmp(en, ".quit", strlen(".quit")) == 0){
            break;
        }
        
        if((*temp >= 'a') && (*temp <= 'z')){
            map_y = *temp - 'a';
        }else if((*temp >= 'A') && (*temp <= 'Z')){
            map_y = *temp - 'A';
        }
        if((*temp >= 'a') && (*temp <= 'z')){
            map_x = *temp - 'a';
        }else if((*temp >= 'A') && (*temp <= 'Z')){
            map_x = *temp - 'A';
        }

        search_print_single_linked(en, map[map_y][map_x], compare, print);
    }

    for(i = 0; i < NR(map); i++){
        for(j = 0; j < NR(map); j++){
            free_single_linked(map[i][j]);
            map[i][j] = NULL;
        }
    }
}

void print(void* data){
    item_dict* item = ((single_linked*)data)->datap;
    printf("en: %s", item->en);
    printf("ch: %s", item->ch);
}
int compare(void* data, single_linked* linked_data){
    item_dict* item = (item_dict*)(linked_data->datap);
    char* en = (char*)data;
    return (strcasecmp(en, item->en) == 0);
    
}
