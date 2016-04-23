//
//  BB_Dictionary.h
//  BB_Dictionary
//
//  Created by fairy-slipper on 4/21/16.
//  Copyright © 2016 fairy-slipper. All rights reserved.
//

#ifndef BB_Dictionary_h
#define BB_Dictionary_h

#include <stdio.h>

typedef struct dictionary_struct Dictionary;

Dictionary *create();

void store(Dictionary *dict, char *key, void *val, int (*hashPtr)(char *));

void *lookup(Dictionary *dict, char *key, int (*hashPtr)(char *));

void delete(Dictionary *dict, char *key, int (*hashPtr)(char *));

int greatest_num_collisions(Dictionary *dict);

void clear_dict(Dictionary *dict);

#endif /* BB_Dictionary_h */
