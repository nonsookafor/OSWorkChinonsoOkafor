// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

node_t *node_alloc() {
	node_t *node = (node_t*) malloc(sizeof(node_t));
	node->next=NULL;
	return node;
}


list_t *list_alloc() {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	list->head = NULL;
	return list;
}


void list_free(list_t *l) {
	free(l);
}


void node_free(node_t *n) {
	free(n);
}


void list_print(list_t *l) {
	node_t* curr = l->head;
  while (curr != NULL) {
    printf("%d\n", curr->value);
    curr = curr->next;
  }
}


int list_length(list_t *l) {
	int i = 0;
	if (l->head == NULL) {
		return 0;
	}
	else {
		node_t* curr = l->head;
		while (curr != NULL) {
			i = i + 1;
			curr = curr->next;
		}
		return i;
	}
	printf("Length is %d\n", i);
 }


void list_add_to_back(list_t *l, elem value) {
	if (l->head == NULL) {
		l->head = node_alloc();
		l->head->value = value;
		l->head->next = NULL;
	}
	else {
		node_t* curr = l->head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = node_alloc();
		curr->next->value = value;
		curr->next->next = NULL;
	}
}


void list_add_to_front(list_t *l, elem value) {
	if (l->head == NULL) {
		l->head = node_alloc();
		l->head->value = value;
		l->head->next = NULL;
	}
	else {
		node_t* newNode = node_alloc();
		newNode->value = value;
		newNode->next = l->head;
		l->head = newNode;
	}
}


void list_add_at_index(list_t *l, elem value, int index) {
	int i = 0;
	if (index == 0) {
		node_t* newNode = node_alloc();
		newNode->value = value;
		newNode->next = l->head;
		l->head = newNode;
	}
	else if (index == list_length(l)) {
		list_add_to_back(l, value);
	}
	else {
		if (list_length(l) > index) {
			node_t* curr = l->head;
			while (curr->next != NULL) {
				if (i + 1 == index) {
					node_t* newNode = node_alloc();
					newNode->value = value;
					newNode->next = curr->next;
					curr->next = newNode;
					break;
				}
				curr = curr->next;
				i = i + 1;
			}
		}
	}
}


elem list_remove_from_back(list_t *l) {
	if (list_length(l) != 0) {
		if (list_length(l) == 1) {
			int i = l->head->value;
			free(l);
			return i;
		}
		else {
			node_t* curr = l->head;
			while (curr->next != NULL) {
				if (curr->next->next == NULL) {
					int i = curr->next->value;
					curr->next = curr->next->next;
					return i;
				}
				curr = curr->next;
			}
		}
	}
	else {
		return -1;
	}
}


elem list_remove_from_front(list_t *l) { 
	if (list_length(l) != 0) {
		if (list_length(l) == 1) {
			int i = l->head->value;
			free(l);
			return i;
		}
		else {
			int i = l->head->value;
			l->head = l->head->next;
			return  i;
		}
	}
	else {
		return -1;
	}
}


elem list_remove_at_index(list_t *l, int index) {
	if (list_length(l) == 0) {
		return -1;
	}
	else {
		if (index == 0) {
			list_remove_from_front(l);
		}
		else if (index == list_length(l) - 1) {
			list_remove_from_back(l);
		}
		else {
			int i = 0; 
			if (list_length(l) > index) {
				node_t* curr = l->head;
				while (curr->next != NULL) {
					if (i + 1 == index) {
						int ans = curr->next->value;
						curr->next = curr->next->next;
						return ans;
					}
					curr = curr->next;
					i = i + 1;
				}
			}
			else {
				return -1;
			}
		}
	}
}


bool list_is_in(list_t *l, elem value) {
	node_t* curr = l->head;
	while (curr != NULL) {
		if (curr->value == value) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}


elem list_get_elem_at(list_t *l, int index) {
	if (list_length(l) == 0) {
		return -1;
	}
	else {
		if (index == 0) {
			return l->head->value;
		}
		else {
			int i = 0; 
			if (list_length(l) > index) {
				node_t* curr = l->head;
				while (curr->next != NULL) {
					if (i + 1 == index) {
						int ans = curr->next->value;
						return ans;
					}
					curr = curr->next;
					i = i + 1;
				}
			}
			else {
				return -1;
			}
		}
	}
}


int list_get_index_of(list_t *l, elem value) {
	if (list_length(l) == 0) {
		return -1;
	}
	else {
		if (value == l->head->value) {
			return 0;
		}
		else {
			int i = 0; 
			node_t* curr = l->head;
			bool x = false;
			while (curr->next != NULL) {
				if (curr->next->value == value) {
					int ans = i + 1;
					x = true;
					return ans;
				}
				curr = curr->next;
				i = i + 1;
			}
			return -1;
		}
	}
}

