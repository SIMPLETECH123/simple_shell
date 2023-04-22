#ifndef
#define

#include <stdlib.h>

/**
 * struct list_s - Func sing linked list
 * @key: ptr to void * type p to the key
 * @value:ptr to  void * type p to the
 * value
 * @next: ptr to struct list_s next node
 *
 **/

typedef struct list_s
{
  void *key;
  void *value;
  struct list_s *next;
}

list_t *add_node(list_t **head, void *key, void *value);
list_t *reverse_list(list_t **head);
void free_list(list_t **head, int flag);
int delete_node_at_index(list_t **head, unsigned int index);

#endif
