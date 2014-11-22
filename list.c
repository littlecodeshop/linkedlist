
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

void dump_element(list l,char *format){

    node * ptr = l.head;
    while(ptr){
        printf(format,(ptr)->element);
        ptr = ptr->next;
    }
}

void dump_lists(list l,char *format){

    node * ptr = l.head;
    while(ptr){
        printf("LIST :\n");
        list * al = (list*)(ptr->element);
        dump_element(*al,format);
        ptr = ptr->next;
    }
}
int main(int argc, char **argv){
    list * l = list_init();
    list * l2 = list_init();
    list * l3 = list_init();

    addElement(l,"hello");
    addElement(l,"world");
    addElement(l2,"this");
    addElement(l2,"is");
    addElement(l2,"Richard");
    addElement(l3,l);
    addElement(l3,l2);
    dump_element(*l,"%s\n");
    dump_element(*l2,"%s\n");
    dump_lists(*l3,"%s\n");

}

