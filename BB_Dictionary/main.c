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

int main(int argc, const char * argv[]) {
    // insert code here...
    Dictionary *myDict = create();
    
    char *a = (char *)malloc(sizeof(char)*6);
    strcpy(a, "apple");
    
    char *b = (char *)malloc(sizeof(char)*7);
    strcpy(b, "banana");
    
    char *c = (char *)malloc(sizeof(char)*7);
    strcpy(c, "cherry");
    
    store(myDict, "ab", a);
    store(myDict, "ab", b);
    store(myDict, "ba", c);
    
    printf("%s\n", lookup(myDict, "ab"));
    
    delete(myDict, "ab");
    
    store(myDict, "ab", a);
    
    printf("%s\n", lookup(myDict, "ab"));
    
    if (lookup(myDict, "ab")==NULL) {
        printf("success!\n");
    }
    
    clean(myDict);
    
    return 0;
}
