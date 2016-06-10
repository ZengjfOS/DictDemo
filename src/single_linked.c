#include "single_linked.h"
/**
 * create a single linked as header
 */
single_linked* create_single_linked(void *data, int size){
    single_linked* header = malloc(sizeof(single_linked));
    ERR(1, NULL == header, goto err; "create single linked header fail.\n");
    header->next = NULL;
    header->datap = NULL;
    header->size = 0;
    
    if(check_data_size(data,size)){
        void* new_data = malloc(size);
        ERR(1, NULL == new_data, goto new_data_err; "create single linked header with data fail.\n");
        memcpy(new_data, data, size);
        header->size = size;
        header->datap = new_data;
    }
    return header;
new_data_err:
    free(header);
err:
    return NULL;
}

int check_data_size(void* data, int size){
    return ((data != NULL) && (size > 0));
}

int top_add_single_linked(void* data, int size, single_linked* header){
    ERR(1, NULL == header, return -1, "the header was NULL in top add single linked\n");
    single_linked* new_node = NULL;

    if(check_data_size(data, size)){
        single_linked* new_node = malloc(sizeof(single_linked));
        ERR(1, NULL == new_node, goto err; "top add malloc node fail.\n");
        new_node->next = NULL;
        new_node->datap = NULL;
        new_node->size = 0;

        void* new_data = malloc(size);
        ERR(1, NULL == new_data, goto err1; "top add malloc data fail.\n");
        memcpy(new_data, data, size);
        new_node->size = size;
        new_node->datap = new_data;

        new_node->next = header->next;
        /**
         * I had pazzled at this point with (header->next = new_node->next)
         */
        header->next = new_node;
        
    }   
    return 0;
err1:
    free(new_node);
err:
    return -1;
}

/**
 * add data to single linked at tail
 */
int tail_add_single_linked(void* data, int size, single_linked* header){
    ERR(1, NULL == header, return -1, "the header was NULL in tail add single linked\n");
    single_linked* new_node = NULL;

    if(check_data_size(data, size)){
        single_linked* new_node = malloc(sizeof(single_linked));
        ERR(1, NULL == new_node, goto err; "top add malloc node fail.\n");
        new_node->next = NULL;
        new_node->datap = NULL;
        new_node->size = 0;

        void* new_data = malloc(size);
        ERR(1, NULL == new_data, goto err1; "top add malloc data fail.\n");
        memcpy(new_data, data, size);
        new_node->size = size;
        new_node->datap = new_data;

        //new_node->next = header->next;
        while(header->next)
            header = header->next;
        /**
         * I had pazzled at this point with (header->next = new_node->next)
         */
        header->next = new_node;
    }   
    return 0;
err1:
    free(new_node);
err:
    return -1;
}

/**
 * delete data in single linked 
 */
int delete_single_linked(void* data, single_linked* header, single_linked_compare compare){
    ERR(1, ((NULL == data) || (NULL == header) || (NULL == compare)), return; "you shouldn't giving NULL for delete single linkde\n");

    single_linked* tmp = header->next;
    single_linked* pre = header;
    while(tmp){
        /**
         * you should giving a return value to decision delete this or not
         */
        if(compare(data, tmp->datap)){
            pre->next = tmp->next;
            tmp->next = NULL;
            free(tmp->datap);
            free(tmp);
            tmp = pre->next;
        }else{
            pre = tmp;
            tmp = tmp->next;
        }
    }
    return 0;
}

/**
 * print all data in single linked
 */
void print_single_linked(single_linked* header, single_linked_print print){
    ERR(1, ((NULL == header) || (NULL == print)), return, "you shouldn't giving NULL for print single linkde\n");
    single_linked* tmp = header->next;
    while(tmp){
        print(tmp);
        tmp = tmp->next;
    }
}

/**
 * free all data in single linked
 */
void free_single_linked(single_linked* header){
    ERR(1, NULL == header, return; "free a header with NULL\n");

    single_linked* tmp = header->next;
    single_linked* pre = header->next;
    while(tmp){
        pre = tmp;
        tmp = tmp->next;
        free(pre->datap);
        free(pre);
    }

    if(header->datap != NULL){
        free(header->datap);
        header->datap = NULL;
    }
    header->next = NULL;
    free(header);
    header == NULL;
}

void empty_single_linked(single_linked* header){
    ERR(1, NULL == header, return, "empty header was NULL\n");

    single_linked* tmp = header->next;
    single_linked* pre = header->next;
    while(tmp){
        pre = tmp;
        tmp = tmp->next;
        free(pre->datap);
        free(pre);
    }

    if(header->datap != NULL){
        free(header->datap);
        header->datap = NULL;
    }
    header->next = NULL;
    header->size = 0;
}
int search_print_single_linked(void* data, single_linked* header, single_linked_compare compare, single_linked_print print){
    ERR(1, ((NULL == data) || (NULL == header) || (NULL == compare) || (NULL == print)), return -1 , "you shouldn't giving NULL for delete single linkde\n");

    single_linked* tmp = header->next;
    while(tmp){
        /**
         * you should giving a return value to decision delete this or not
         */
        if(compare(data, tmp)){
            print(tmp);
            break;
        }
        tmp = tmp->next;
    }
    return 0;
}
void reverse_single_linked(single_linked* header){
    ERR(1, NULL == header, return, "reverse single linked fail.\n");
    single_linked* pre = header->next;
    single_linked* cur = header->next;
    header->next = NULL;

    while(cur){
        pre = cur;
        cur = cur->next;
        pre->next = header->next;
        header->next = pre;
    }
}
