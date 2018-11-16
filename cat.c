/**
 * @file	cat.c
 * @brief	Function for cat.
 * @date	03/11/2018
 *
 * cat -- print some string, Version 1.
 *
 * This file define[<34;63;9M[<34;108;28Ms cat common internal data structures, constants and
 * functions
 *
 * @see		TODO: documents
 *
 * Copyright 2018 by C S, Inc.,
 *
 * This software is the confidential and proprietary information
 * of C S, Inc. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with C S.
 */


#ifndef _CAT_C_
#define _CAT_C_

#include "cat.h"


#define CAT_STR  "||   date      ||  deposit   ||  withdraw  ||   balance  ||\n\
===========================================================\n\
||  8 jun 2018 || 000000.000 || 000000.000 || 000000.000 ||\n\
||  9 jun 2018 || 002500.000 || 000000.000 || 002500.000 ||\n\
|| 10 jun 2018 || 001000.000 || 000000.000 || 003500.000 ||\n\
|| 11 jun 2018 || 000000.000 || 000500.000 || 003000.000 ||\n"

/** @brief	Object - Private Accaunt block information.


struct cat_date {
  int day;
  char month[20];
  int year;
};

struct cat_list {
    struct cat_date tr;
    float balance;
    float deposit;
    float withdraw;
    int state;
    struct cat_list * _next;
};

typedef struct cat_list cat_list;
 */

/** @brief	FSM - finite-state machine.
 *
 * https://gist.github.com/pujansrt/1218502
 *
 * Here it is possible to autogenerate both unit
 * and function tests and the source code of state
 * transitions from one simple input language.
 *
 * The logic of console or graphical input can also be here.

typedef enum State {
    BEGIN,             //0
    DEPOSIT,             //1
    WITHDRAW,    //2
    END,           //3
    BALANCE           //4
} State;
 */

void cat_fsm(cat_list *lst, cat_list *temp, float value, int state)
{
    if (state == BEGIN) {
        temp->balance = value; // saving the data field of the node to be added
    }
    if (state == DEPOSIT) {
        temp->deposit = value; // saving the data field of the node to be added
        temp->balance = lst->balance + value;
    }
    if (state == WITHDRAW) {
        temp->withdraw = value; // saving the data field of the node to be added
        temp->balance = lst->balance - value;
    }
    if (state == BALANCE) {
        ;
    }
}
/** @brief	Move - the switching functions / equalization / branching.
 */

struct cat_list * init(float value, int state)
{
    struct cat_list *lst;
    // memory allocation at the root of the list
    lst = (struct cat_list*)malloc(sizeof(struct cat_list));
    lst->balance = value;
    lst->_next = lst; // pointer to the root node itself
    return(lst);
}

/** @brief	Parser - the function parser (parsing) / compilation.
 */

int listprint(char * cat_string, cat_list * lst, int state)
{
    int j = 0;
    struct cat_date tr;
    struct cat_list *p;
    p = lst;
    j += sprintf(cat_string+j, "||   date      ||  deposit   ||  withdraw  ||   balance  ||\n");
    j += sprintf(cat_string+j, "===========================================================\n");
    do {
        tr = p->tr;
        j += sprintf(cat_string+j,"|| %2d %s %4d ",tr.day, tr.month, tr.year);
        j += sprintf(cat_string+j,"|| %010.3f || %010.3f || %010.3f ||\n", p->deposit, p->withdraw, p->balance); // the output values of the node p
        p = p->_next; // move to the next node
    } while (p != lst); // the ending condition of the bypass
    return 0;
}

/** @brief	Memory - field of memory and the physical devices.
 */

struct cat_list * addelem(cat_list *lst, float value, int state)
{
    struct cat_list *temp, *p;
    temp = (struct cat_list*)malloc(sizeof(cat_list));
    p = lst->_next; // saving a pointer to the next item
    lst->_next = temp; // the previous node indicates the node to be created
    cat_fsm(lst, temp, value, state); // FSM logic
    temp->_next = p; // the node that is created points to the following element
    return(temp);
}
/** @brief	Time -  time intervals. The forks and the distribution of concurrent threads and Network.
 */

/** @brief	Bus - search function / insert data into the repository. Microservers and JSON-RPC/CORBA/RMI
 */
struct cat_list * cat_deposit( cat_list *lst, float value, float balance, int state)
{
    lst = addelem(lst, value, state);
    return(lst);
}

struct cat_list * cat_withdraw( cat_list *lst, float value, float balance, int state)
{
    lst = addelem(lst, value, state);
    return(lst);
}

/** @brief	User session - Graphical interface or CLI or just tests
 */


int main ()
{
    int res = 0;
    float balance = 0.0;
    struct cat_list *lst;
    struct cat_list *cur_lst;
    char cat_string[sizeof(CAT_STR)];

    lst = init(balance, BEGIN);
    struct cat_date tr = {8,"jun", 2018};
    lst->tr = tr;

    cur_lst = cat_deposit( lst, 2500.00, lst->balance, DEPOSIT);
    tr.day = 9;
    cur_lst->tr = tr;

    cur_lst = cat_deposit( cur_lst, 1000.00, cur_lst->balance, DEPOSIT);
    tr.day = 10;
    cur_lst->tr = tr;

    cur_lst = cat_withdraw( cur_lst, 500.00, cur_lst->balance, WITHDRAW);
    tr.day = 11;
    cur_lst->tr = tr;

    res = listprint(cat_string, lst, BALANCE);


    printf(cat_string);
    assert( !strncmp (cat_string, CAT_STR, sizeof(CAT_STR)));
    return 0;
}
#endif /* CAT_C_ */