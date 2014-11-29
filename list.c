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
#include <assert.h>

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
} list;


list* list_init(){
    list * l = (list*)malloc(sizeof(list));
    l->head=NULL;
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
        return;
    } 

    node * ptr = l->head;
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next = n;
}

list* list_copy(const list * l){
    list * copy = list_init();
    node * ptr = l->head;
    while(ptr!=NULL){
        add_element(copy,ptr->element);
        ptr = ptr->next;
    }
    return copy;
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

void * remove_last(list * l){
    node * ptr = l->head;
    if(ptr==NULL)
        return NULL;
    while(ptr->next!=NULL)
    {
        ptr = ptr->next;
    }
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

   //TEST last element
   list *l = list_init();
   add_element(l,"hello");
   add_element(l,"world");
   list_dump(l,format_list_of_strings);
   char * t1 = remove_last(l);
   list_dump(l,format_list_of_strings);
   char * t2 = remove_last(l);
   list_dump(l,format_list_of_strings);
   assert(t1=="world");
   assert(t2=="hello");
    
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



void generic_search(char * start, char * goal, list*(*successors)(char*)){
    list *closed_set = list_init();
    list *open_list = list_init();
    list *path = list_init();

    //au debut la liste des possible paths ne contient que le path avec start
    add_element(path,start);
    add_element(open_list,path);

    while(1){
        if(empty(open_list)) //si il n'y a plus rien a tester alors stop !
            break;

        list * candidate_path = remove_last(open_list);
        printf("JE VAIS TESTER :\n");
        list_dump(candidate_path,format_slide);
        char * position = remove_last(candidate_path);
        //rajouter une liste pour chaque successors !
        list * next_to_try = successors(position);
        list_dump(next_to_try,format_slide);

        //rajouter le dernier dedans :)
        add_element(candidate_path,position);

        //loop over successors and create a new list and add
        char * succ = NULL;
        while((succ=remove_last(next_to_try))){
            list * new_path = list_copy(candidate_path);
            add_element(new_path,succ);
            printf("NEW PATH TO TRY\n");
            list_dump(new_path,format_slide);
        };
    }
}

int main(int argc, char **argv){
    test_list();
    char * position = "012345678";
    generic_search("102345678","012345678",slide_successors);
}

