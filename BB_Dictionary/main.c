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

int hash(char *key) {
    
    int idx = 0;
    
    for (int i=0; i<strlen(key); i++) {
        idx ^= (idx << 5) + (idx >> 2) + key[i];
    }
    return idx%32000;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Dictionary *myDict = create();
    
    char *a = (char *)malloc(sizeof(char)*6);
    strcpy(a, "apple");
    
    char *b = (char *)malloc(sizeof(char)*7);
    strcpy(b, "banana");
    
    char *c = (char *)malloc(sizeof(char)*7);
    strcpy(c, "cherry");
    
    store(myDict, "ab", a, hash);
    store(myDict, "ab", b, hash);
    store(myDict, "ba", c, hash);
    
    printf("%s\n", lookup(myDict, "ab", hash));
    
    delete(myDict, "ab", hash);
    
    store(myDict, "ab", a, hash);
    
    printf("%s\n", lookup(myDict, "ab", hash));
    
    if (lookup(myDict, "ab", hash)==NULL) {
        printf("success!\n");
    }
    
    clean(myDict);
    
    return 0;
}
