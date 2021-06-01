
#include <string.h>
#include <stdint.h>
#include  "../includes/mpm_list.h"

uint8_t find_string(Node *node ,void *str){
	
	if((node->element==NULL)||(str==NULL)) return -1;
	else{
		if(strcmp((char *)node->element, (char *)str)==0){
			return 1;
		}else return -1;
	}
}

