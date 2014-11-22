
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int element;
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

void addElement(list * l, int el){
    
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

void dump(list l){

    node * ptr = l.head;
    while(ptr){
        printf("=>%d\n",(ptr)->element);
        ptr = ptr->next;
    }
}

int main(int argc, char **argv){
    list * l = list_init();
    addElement(l,1);
    addElement(l,2);
    addElement(l,3);
    addElement(l,4);
    addElement(l,5);
    dump(*l);
}

