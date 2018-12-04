//#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "kernel/rosa_def.h"

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#define taskHandle node

typedef struct
{
	tcb * head;
	tcb * tail;
} linked_list;

int16_t insert_at_head( linked_list *, tcb *);
int16_t insert_by_priority( linked_list *, tcb *);
int16_t insert_by_back_online_time(linked_list *, tcb*);
int16_t insert_after( tcb *, tcb *);
int16_t remove_tcb( tcb *);

void print_list(linked_list *);

#endif