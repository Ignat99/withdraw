/**
 * @file	cat.h
 * @brief	Internal constants and data structures for cat.
 * @date	03/11/2018
 *
 * cat -- print some string, Version 1.
 *
 * This file defines cat common internal data structures, constants and
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


#ifndef _CAT_H_
#define _CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>


#define MY_STR = "acc, debit, credit, balance"

/** @brief	Object - Private Accaunt block information.
 */

struct cat_date {
  int day;
  char month[20];
  int year;
};

struct cat_list {
    /** The cat block */
    struct cat_date tr;
    float balance;
    float deposit;
    float withdraw;
    int state;
    struct cat_list * _next;
};

typedef struct cat_list cat_list;

/** @brief	FSM - finite-state machine.
 * https://gist.github.com/pujansrt/1218502
 *
 * Here it is possible to autogenerate both 
 * unit and function tests and the source 
 * code of state transitions from one simple 
 * input language.
 */
typedef enum State {
    BEGIN,             //0
    DEPOSIT,             //1
    WITHDRAW,    //2
    END,           //3
    BALANCE           //4
} State;

void cat_fsm (cat_list *lst, cat_list *temp, float value, int state);

/** @brief	Move - the switching functions / equalization / branching.
 */

struct cat_list * init(float value, int state);

/** @brief	Parser - the function parser (parsing) / compilation.
 */

int listprint(char * cat_string, cat_list * lst, int state);

/** @brief	Memory - field of memory and the physical devices.
 */

struct cat_list * addelem(cat_list *lst, float value, int state);

/** @brief	Time -  time intervals. The forks and the distribution of concurrent threads and Network.
 */

/** @brief	Bus - search function / insert data into the repository. Microservers and JSON-RPC/CORBA/RMI
 */

struct cat_list * cat_withdraw( cat_list *lst, float value, float balance, int state);
struct cat_list * cat_deposit( cat_list * lst, float value, float balance, int state);

#endif /* CAT_H_ */