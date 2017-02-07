//
//  main.c
//  BB_Dictionary
//
//  Created by fairy-slipper on 4/21/16.
//  Copyright © 2016 fairy-slipper. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BB_Dictionary.h"

#define SIZE 32000

char *token = (char *)NULL;

int hash(char *key) {
    
    int idx = 0;
    
    for (int i=0; i<strlen(key); i++) {
        idx ^= (idx << 5) + (idx >> 2) + key[i];
        //idx +=key[i]*26;
    }
    return idx%SIZE;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    FILE *wordsfd = fopen(argv[1], "r");
    if (wordsfd == NULL) {
        printf("Error opening melody file!!\n");
        return 0;
    }
    
    Dictionary *myDict = create(SIZE);
    
    char buf[1000];
    while (fgets(buf,1000, wordsfd)!=NULL) {
        const char t[3] = " \n";
        token = strtok(buf, t);
        
        for(int i=0; token!=NULL; i++) {
            char *c = (char *)malloc(sizeof(char)*strlen(token));
            strcpy(c, token);
            //printf("%s", token);
            store(myDict, token, c, hash);
            token=strtok(NULL, t);
        }
    }
    
    printf("%s\n", lookup(myDict, "apple", hash));
    printf("%s\n", lookup(myDict, "because", hash));
    
//    char *a = (char *)malloc(sizeof(char)*10);
//    char *b = (char *)malloc(sizeof(char)*10);
//    char *c = (char *)malloc(sizeof(char)*10);
//    strcpy(a, "apple");
//    strcpy(b, "banana");
//    strcpy(c, "cherry");
//    
//    store(myDict, "ab", a, hash);
//    store(myDict, "ba", b, hash);
//    store(myDict, "abb", c, hash);
//    
//    printf("%s\n", lookup(myDict, "ab", hash));
//    printf("%s\n", lookup(myDict, "ba", hash));
//    printf("%s\n", lookup(myDict, "abb", hash));
//    
//    delete(myDict, "ab", hash);
//    printf("%s\n", lookup(myDict, "ab", hash));
//    printf("%s\n", lookup(myDict, "ba", hash));
//    printf("%s\n", lookup(myDict, "abb", hash));
    
    printf("Max collisions: %i\n", greatest_num_collisions(myDict));
    
    clear_dict(myDict);
    
    return 0;
}
