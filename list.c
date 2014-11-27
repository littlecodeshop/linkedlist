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
#include <string.h>

//012
//345
//678
int possible_moves[][9] = {
    {2,1,3},      //0
    {3,0,2,4},    //1
    {2,1,5},      //2
    {3,0,4,6},    //3
    {4,1,3,5,7},  //4
    {3,2,4,8},    //5
    {2,3,7},      //6
    {3,6,4,8},    //7
    {2,5,7}       //8
}; 


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

int empty(list *l){
    return(l->head == NULL);
}

void add_element(list * l, void * el){
    
    //create the new Node
    node * n = (node*)malloc(sizeof(node));
    n->element = el;
    n->next = NULL;
    if(l->head == NULL){ //TODO : comment eviter ca ?
        l->head = n;
    } 
    l->tail = n;
}

void * remove_element(list * l, void * el){
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

char * format_list_of_strings(node * n)
{
    return n->element;
}


void list_dump(list * l,char * (*format)(struct _node *))
{
    node * ptr = l->head;
    while(ptr!=NULL){
        printf("%s\n",format(ptr));
        ptr=ptr->next;
    }
}

void * remove_first(list * l){
    node * ptr = l->head;
    return remove_element(l,ptr->element);
}

void * remove_last(list *l){
    node * ptr = l->tail;
    return remove_element(l,ptr->element);
}


void test_dump_multiple_lists(list *l,char *format){

    node * ptr = l->head;
    while(ptr){
        printf("Dumping List :\n");
        list * al = (list*)(ptr->element);
        list_dump(al,format_list_of_strings);
        ptr = ptr->next;
    }
}

void test_list(){

    list * l = list_init();
    list * l2 = list_init();
    list * l3 = list_init();
    list * l4 = list_init();

    
    add_element(l,"hello");
    add_element(l,"world");

    add_element(l2,"this");
    add_element(l2,"is");
    add_element(l2,"Richard");
    add_element(l2,"Ribier");

    add_element(l3,l);
    add_element(l3,l2);

    list_dump(l,format_list_of_strings);
    list_dump(l,format_list_of_strings);
    remove_element(l,"hello");
    list_dump(l,format_list_of_strings);

    list_dump(l2,format_list_of_strings);
    test_dump_multiple_lists(l3,"%s\n");

    char *test = remove_element(l2,"is");
    printf("I got this :%s\n",test);
    remove_element(l2,"tata");
    list_dump(l2,format_list_of_strings);
    //empty list
    remove_element(l4,"nothing");
    list_dump(l4,format_list_of_strings);

    test_dump_multiple_lists(l3,"%s\n");

    printf("test remove first\n");
    list_dump(l2,format_list_of_strings);
    remove_first(l2);
    list_dump(l2,format_list_of_strings);

    printf("test remove last\n");
    list_dump(l2,format_list_of_strings);
    remove_last(l2);
    list_dump(l2,format_list_of_strings);
    
}
/* ======== Slide Puzzle specifics ========*/
char * format_slide(node *n)
{
    
    char * tmp = (char*)malloc(24);
    char * position = (char*)n->element;
    int i,j,index=0;
    for(j=0;j<3;j++){
        tmp[index++]='|';
        for(i=0;i<3;i++){
            tmp[index++]=position[i+(j*3)];
            tmp[index++]='|';
        }
        tmp[index++] = '\n';
    }
    return tmp;
}

void slide_dump(char * position)
{
    int i,j;
    for(j=0;j<3;j++){
        printf("|");
        for(i=0;i<3;i++){
            printf("%c|",position[i+(j*3)]);
        }
        printf("\n");
    }

}

/**
 * Generates a list containing the list of successors
 * from the passed position
 */

list * slide_successors(char * position)
{

    list * l = list_init();

    //find the position of 0 
    int i,index = 0;
    while(position[index]!='0'){
        index++;
    }

    //index a la position 
    int cnt = possible_moves[index][0];
    for(i = 1;i<=cnt;i++){
        int spot = possible_moves[index][i];
        char * new_position = strdup(position);
        //je swappe la position vide avec le spot
        new_position[index] = new_position[spot];
        new_position[spot] = '0'; 
        add_element(l,new_position);
    }

    return l;
}

int main(int argc, char **argv){
    test_list();
    char * position = "012345678";
    list_dump(slide_successors(position),format_slide);
}

