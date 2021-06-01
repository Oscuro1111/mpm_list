#include "../includes/mpm_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>


uint8_t is_null(void *exp){
  if(exp==NULL) return 1;
  else return 0;
}


void free_node(Node *node){

  if(is_null(node)){
    return;
  }

  free(node);
}

Node *allocate_node(){

  Node *node = (Node *)malloc(sizeof(Node));

  if(node==NULL){
    fprintf(stderr,"Unabel to alolocate memory for the node %s\n",strerror(errno));
    return NULL;
  }

  return node;
}

uint8_t add_ele(Node *node ,void *ele){

  if(is_null(ele)||is_null(node)) return 1;

  node->element =ele;
  return 0;
}

int mpm_list_add(List * list ,void *ele){

  Node *node;
  Node *temp;

  IS_NULL(list);
  IS_NULL(ele);

  if(is_null(list->head)){

    node = allocate_node();

    IS_NULL(node);

    if (add_ele(node, ele) == 0) {
      list->head = node;
      node->next = NULL;
      node->prev = node;

      list->tail = node;
      list->length++;
      return 0;
    }else{
      //free memory in case any unexpected  issue.
      free_node(node);
      return -1;
    }
  }

  //add element to tail of the list
  temp = list->tail;

  node = allocate_node();

  IS_NULL(node);

  if(add_ele(node, ele)==0){

    node->next = NULL;     // ..[tail] -><-[node]->NULL
    node->prev =temp;
    temp->next = node;

    list->tail = node;
    list->length++;
  }else {
    //release resources if unexpected issue  happened
    free_node(node);
    return -1;
  }

  return 0;
}

int mpm_list_delete(List * list,void *ele){

  IS_NULL(list);
  IS_NULL(list->head);
  IS_NULL(ele);

  Node *temp;
  Node *temp2;
  Node *temp3;

  temp = list->head;

  while((temp!=NULL)&&(temp!=(Node *)ele)){
    temp = temp->next;
  }

  if(temp!=NULL){
    temp2 = temp->next;
    temp3  =temp->prev;
    if(temp2!=NULL){
      temp3->next = temp2;
      temp2->prev = temp3;
    }else{
      temp3->next =NULL;
      list->tail = temp3;
    }

    list->length--;
    free_node(temp);
  }

  return 0;
}

Node *mpm_list_next(List *list,void **__save_ptr){

  Node *node=NULL;

  if(list!=NULL&&is_null(list->head)){
    return NULL;
  }
  if(list!=NULL){
   node = list->head;
    *__save_ptr = node->next;
  }else if(__save_ptr!=NULL&&*__save_ptr!=NULL){
    node = (Node *)*__save_ptr;
    *__save_ptr = node->next;
  }
  return node;
}

Node *mpm_list_find(List * list , void *ele ,uint8_t  (*find_cond)(Node *,void *)){

  Node *node=NULL;

  void *_state;

  if (list != NULL && is_null(list->head)) {
    return NULL;
  }

  node = mpm_list_next(list,&_state);

  if(is_null(node)){
    return NULL;
  }

 __find:
  if (find_cond(node,ele)==1) {
     return node;
   }

while ((node = mpm_list_next(NULL, &_state)) != NULL)
     goto __find;

   return NULL;
}
