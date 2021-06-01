#include<stdlib.h>
#include <stdio.h>
#include "../includes/mpm_list.h"
#include<stdint.h>
#include <string.h>

int main(int argc,char **argv){

	if(argc!=2){

		fprintf(stderr,"%s num_ele\n",argv[0]);
		return 1;
	}

	int num  =atoi(argv[1]);

	List list;
	void *_state;

	Node *node;
	Node *temp;

	mpm_list_add(&list,"Hello");

	for(int i = 0 ;i<num;i++){
		mpm_list_add(&list,"How");

		mpm_list_add(&list,"are");

		mpm_list_add(&list,"you?");
	}

while((temp = mpm_list_find(&list,"How",find_string))){
	fprintf(stderr ,"\n=>%s\n",(char *)temp->element);
	mpm_list_delete(&list,(Node *)temp);
}
	//------------------------------------
	node = mpm_list_next(&list,&_state);

	IS_NULL(node);

print:
	fprintf(stderr,"%s\n",(char *)node->element);


	while((node=mpm_list_next(NULL,&_state))){
		goto print;
	}

	//data is note alloocated in heap so note need to give clean_element function 
	free_list(&list,NULL);

	return 0;
}
