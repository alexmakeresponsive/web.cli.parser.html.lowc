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
    int  html0RawIndexCurrent  = 0;     // for read from file
    int  html0RawIndex2Current = 0;     // for parse html0Raw
    int  html0RawCharCount = 0;
    
    char htmlChunkFind[] = "data-qa=\"vacancy-serp__vacancy-employer\">";
    int  htmlChunkFindIndexCurrent = 0;
    int  htmlChunkFindIndexCompare = 0;
    char text[128];
    char textList[500][128];
    
    // file size
    struct stat st;
           off_t size;
    
    stat(page0filename, &st);

    size = st.st_size;
    printf("\n");
    printf("file size: %i bytes \n", size);
    // file size
    
    // file line count
    int   c;
    char  ch;
    FILE* file;
    int   lineCount = 0;
    
        file = fopen(page0filename, "r");
    if (file) {
        while ((ch = getc(file)) != EOF)
        {
            if(ch == '\n')
            {
                lineCount++;
            }
        
                html0Raw[html0RawIndexCurrent] = ch;
                html0RawIndexCurrent++;
                html0RawCharCount++;
        }
        fclose(file);
    }

    printf("file line count: %d lines \n", lineCount);
    printf("file chars count: %d chars \n", html0RawCharCount);
    printf("html0Raw [] sizeof: %d \n", sizeof(html0Raw));
    printf("htmlChunkFind [] sizeof: %d \n", sizeof(htmlChunkFind));
    // file line count
    

    
    // How find company name?
    // Read every symbol from html0Raw
    // compare symbol in html0Raw and htmlChunkFind
    // if symbol found then htmlChunkFindIndexCompare++
    // if htmlChunkFindIndexCompare == sizeof(htmlChunkFind) then text[] = html0Raw[html0RawIndex2Current]
    // if symbol == '<' then copy text to textList and htmlChunkFindIndexCompare = 0;
    // if symbol == '>' then htmlChunkFindIndexCompare = 0;
    
    

}
