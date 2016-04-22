//
//  BB_Dictionary.c
//  BB_Dictionary
//
//  Created by fairy-slipper on 4/21/16.
//  Copyright © 2016 fairy-slipper. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BB_Dictionary.h"

typedef struct node_struct NODE;

struct node_struct {
    char *key;
    void *value;
    NODE *next;
    NODE *prev;
};

struct dictionary_struct {
    NODE **items;
    int count;
};

int hash(char *key) {
    
    int idx = 0;
    
    for (int i=0; i<strlen(key); i++) {
        idx ^= (idx << 5) + (idx >> 2) + key[i];
    }
    return idx%32000;
}

Dictionary *create() {
    Dictionary *newDict = (Dictionary *)malloc(sizeof(Dictionary));
    newDict->items = malloc(32000*sizeof(NODE *));
    return newDict;
}

void store(Dictionary *dict, char *key, void *val) {
    
    int hval = hash(key);
    
    if (dict->items[hval] == NULL) {
        
        NODE *newN = (NODE *)malloc(sizeof(NODE));
        newN->key = key;
        newN->value = val;
        newN->next = NULL;
        newN->prev = NULL;
        dict->items[hval] = newN;
        
    } else {
        
        NODE *tmp = dict->items[hval];
        while (tmp != NULL) {
            if (!strcmp(tmp->key, key)) { //catch duplicate
                tmp->value = val;
                return;
            }
            tmp = tmp->next;
        }
        
        tmp = dict->items[hval];
        NODE *prevtmp = NULL;
        while (tmp->next != NULL) {
            prevtmp = tmp;
            tmp = tmp->next;
        }
        
        NODE *newN = (NODE *)malloc(sizeof(NODE));
        newN->key = key;
        newN->value = val;
        newN->next = NULL;
        newN->prev = prevtmp;
        tmp->next = newN;
    }
}

void delete(Dictionary *dict, char *key) {
    
    int hval = hash(key);
    
    NODE *item = dict->items[hval];
    NODE *previtem = NULL;
    while (item!=NULL) {
        if (!strcmp(item->key, key)) {
            if (previtem != NULL && item->next != NULL) {
                previtem->next = item->next;
                item->next->prev = previtem;
                free(item->value);
                free(item);
            }
            if (previtem != NULL && item->next == NULL) {
                free(item->value);
                free(item);
                previtem->next = NULL;
            }
            if (previtem == NULL && item->next != NULL) {
                NODE *tmp = item->next;
                free(item->value);
                free(item);
                dict->items[hval] = tmp;
            }
            if (previtem == NULL && item->next == NULL) {
                free(item->value);
                free(item);
                dict->items[hval] = NULL;
            }
            return;
        }
        previtem = item;
        item = item->next;
    }
}

void *lookup(Dictionary *dict, char *key) {
    
    int hval = hash(key);
    
    NODE *item = dict->items[hval];
    while (item!=NULL) {
        if (!strcmp(item->key, key)) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

void clean_node(NODE *n) {
    if (n->next != NULL) {
        clean_node(n->next);
    }
    if (n->value != NULL) {
        free(n->value);
    }
    if (n != NULL) {
        free(n);
    }
}

void clean(Dictionary *dict) {
    for (int i=0; i<32000; i++) {
        if (dict->items[i]!=NULL) {
            clean_node(dict->items[i]);
        }
    }
    //free(dict->items);
}