#include "../includes/mpm_list.h"
#include <stdio.h>
#include <stdlib.h>

void free_list(List *list, void (*free_ele)(void *)) {

  Node *node;
  void *_state;

  if (list == NULL || list->head == NULL)
    return;

  node = mpm_list_next(list, &_state);

free_element:
  if (node != NULL && node->element != NULL) {

    // if Not null
    if (is_null(free_ele) == 0)
      free_ele(node->element);

    free_node(node);
  }

  while ((node = mpm_list_next(NULL, &_state)) != NULL)
    goto free_element;

    free(list);
}
