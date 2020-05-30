//
//  parser.c
//  htmlparser4hh
//
//  Created by Alexandr on 30.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#include "parser.h"
#include "constructor/path.h"

#define CHUNK 1024


void parseCompanyName()
{
    FILE* fp;
    
    char* dirDataPath = getPathOut();
    char* page0filename = getPathOutPage(0);
    
    char html0Raw[600000];
    
    
    // file size
    struct stat st;
    off_t size;
    stat(page0filename, &st);

    size = st.st_size;
    printf("\n");
    printf("file size: %i \n", size);
    // file size
    
    // file line count
    int   c;
    char  ch;
    FILE* file;
    int lineCount = 0;
    
        file = fopen(page0filename, "r");
    if (file) {
        while ((ch = getc(file)) != EOF)
            if(ch == '\n')
            {
                lineCount++;
            }
        fclose(file);
    }

    printf("file line count: %d \n", lineCount);
    // file line count
}
