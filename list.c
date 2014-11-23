/*
 * =====================================================================================
 *
 *       Filename: list 
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  Dim 23 nov 09:13:26 2014
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:  Richard Ribier (Coder), 
 *        Company:  LittleCodeShop
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    void * element;
    struct _node * next;
} node;

typedef struct {
    node * head; //pointeur sur premier element
    node * tail; //pointeur sur dernier element
} list;


list* list_init(){
    list * l = (list*)malloc(sizeof(list));
    l->head=l->tail=NULL;
    return l;
}

void addElement(list * l, void * el){
    
    //create the new Node
    node * n = (node*)malloc(sizeof(node));
    n->element = el;
    n->next = NULL;
    if(l->head == NULL){ //TODO : comment eviter ca ?
        l->head = n;
        l->tail = n;
    } 
    l->tail->next = n;
    l->tail = n;
}

void * removeElement(list * l, void * el){
    node ** head_ptr;
    head_ptr = &(l->head); 
    while(*(head_ptr)!=NULL){
        if((*head_ptr)->element == el){
        *head_ptr = (*head_ptr)->next;
        return el;
        }
        head_ptr = &((*head_ptr)->next);
    }

    return NULL;
}


void * remove_first(list * l){
    node * ptr = l->head;
    return removeElement(l,ptr->element);
}

void * remove_last(list *l){
    node * ptr = l->tail;
    return removeElement(l,ptr->element);
}

void dump_list(list *l,char *format){

    node * ptr = l->head;
    while(ptr){
        printf(format,(ptr)->element);
        ptr = ptr->next;
    }
}

void dump_lists(list *l,char *format){

    node * ptr = l->head;
    while(ptr){
        printf("Dumping List :\n");
        list * al = (list*)(ptr->element);
        dump_list(al,format);
        ptr = ptr->next;
    }
}

void test_list(){

    list * l = list_init();
    list * l2 = list_init();
    list * l3 = list_init();
    list * l4 = list_init();

    
    addElement(l,"hello");
    addElement(l,"world");

    addElement(l2,"this");
    addElement(l2,"is");
    addElement(l2,"Richard");
    addElement(l2,"Ribier");

    addElement(l3,l);
    addElement(l3,l2);

    dump_list(l,"LIST l : %s\n");
    removeElement(l,"hello");
    dump_list(l,"LIST l : %s\n");

    dump_list(l2,"%s\n");
    dump_lists(l3,"%s\n");

    char *test = removeElement(l2,"is");
    printf("I got this :%s\n",test);
    removeElement(l2,"tata");
    dump_list(l2,"%s\n");
    //empty list
    removeElement(l4,"nothing");
    dump_list(l4,"%s\n");

    dump_lists(l3,"%s\n");

    printf("test remove first\n");
    dump_list(l2,"%s\n");
    remove_first(l2);
    dump_list(l2,"%s\n");

    printf("test remove last\n");
    dump_list(l2,"%s\n");
    remove_last(l2);
    dump_list(l2,"%s\n");
    
}

int main(int argc, char **argv){
    test_list();
}

