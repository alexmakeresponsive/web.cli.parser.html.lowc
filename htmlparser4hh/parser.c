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

#define MODE_POINTER_READ 0
#define MODE_POINTER_COPY 1

#define MODE_COMPARE_STOP 0
#define MODE_COMPARE_RESUME 1

int parseCompanyName()
{
    
    char* page0filename = getPathOutPage(0);
    
    char htmlRaw[600000];
    long htmlRawIndex = 0;
    
    int  htmlRawIndexCurrent  = 0;     // for read from file
    int  htmlRawCharCount = 0;
    
    
    
    
    printf("Parse company name \n");
    
    
    
    
    // file line count
    char  ch;
    FILE* file;
    int   lineCount = 0;
    
    
    
        file = fopen(page0filename, "r");
    if (file)
    {
        while ((ch = getc(file)) != EOF)
        {
            if(ch == '\n')
            {
                lineCount++;
            }
        
                htmlRaw[htmlRawIndexCurrent] = ch;
                htmlRawIndexCurrent++;
                htmlRawCharCount++;
        }
        fclose(file);
    }

    printf("file line count: %d lines \n", lineCount);
    printf("file сhar сount: %d chars \n", htmlRawCharCount);
    // file line count
    

    

    
    // How find company name?
    // Read every symbol from html0Raw
    // compare symbol in html0Raw and htmlChunkFind
    // if symbol found then htmlChunkFindIndexCompare++
    // if htmlChunkFindIndexCompare == sizeof(htmlChunkFind) then text[] = html0Raw[html0RawIndex2Current]
    // if symbol == '<' then copy text to textList and htmlChunkFindIndexCompare = 0;
    // if symbol == '>' then htmlChunkFindIndexCompare = 0;
    
//    printf("htmlRaw []: %s \n", (htmlRaw));
//    return 0;
    
    
    
    
    char stringBeforeText[] = "data-qa=\"vacancy-serp__vacancy-employer\">";
    long stringBeforeTextIndex = 0;
    
    char stringBeforeTextCompare[256];
    
    
    long stringBeforeTextIndexCompare = 0;
    long stringBeforeTextCompareLevel = 0;
    
    int  modePointer = MODE_POINTER_READ;
    int  modeCompare = MODE_COMPARE_STOP;
    
    char textList[1000][128];
    
    long textListIndex1 = 0;
    long textListIndex2 = 0;
    
    int itemsCopyCount  = 0;
    int itemsCopyCountCurrent = 0;
    
//    printf("stringBeforeText length: %lu \n", strlen(stringBeforeText));
//    return 0;
    
    while (htmlRawIndex < strlen(htmlRaw))
    {
        while (stringBeforeTextIndex < strlen(stringBeforeText))
        {
            if (modePointer == MODE_POINTER_COPY)
            {
//                modeCompare = MODE_COMPARE_STOP;
//
//                stringBeforeTextCompareLevel = 0;
//                stringBeforeTextIndexCompare = 0;
                
                break;
            }
            
            if (modeCompare == MODE_COMPARE_RESUME)
            {
                stringBeforeTextIndex = stringBeforeTextIndexCompare;
            }
            
            if (htmlRaw[htmlRawIndex] == stringBeforeText[stringBeforeTextIndex])
            {
                modeCompare = MODE_COMPARE_RESUME;
                
                stringBeforeTextCompareLevel++;
                stringBeforeTextIndexCompare++;
                
                stringBeforeTextIndex = stringBeforeTextIndexCompare;
                
                break;
            }

                modeCompare = MODE_COMPARE_STOP;
            
                stringBeforeTextCompareLevel = 0;
                stringBeforeTextIndexCompare = 0;

                stringBeforeTextIndex++;
        }
        
        if (stringBeforeTextCompareLevel == strlen(stringBeforeText))
        {
//                    printf("MODE_POINTER_COPY enable for index: %lu \n", htmlRawIndex);
                
//                for (int i=0; i<=40; i++) {
//                    printf("%c", htmlRaw[htmlRawIndex + i]);
//                }
//                    printf("\n");
            
                modePointer = MODE_POINTER_COPY;
        }
        
        if (modePointer == MODE_POINTER_COPY && htmlRaw[htmlRawIndex] != '>' && htmlRaw[htmlRawIndex] != '<')
        {
                textList[textListIndex1][textListIndex2] = htmlRaw[htmlRawIndex];
                textListIndex2++;
        }
        
        if (modePointer == MODE_POINTER_COPY && htmlRaw[htmlRawIndex] == '<')
        {
                modePointer = MODE_POINTER_READ;
                modeCompare = MODE_COMPARE_STOP;
                
                stringBeforeTextCompareLevel = 0;
                stringBeforeTextIndexCompare = 0;
                
                textList[textListIndex1][textListIndex2 + 1] = '$';

                textListIndex2 = 0;
                textListIndex1++;
            
                itemsCopyCount++;
        }
        
                stringBeforeTextIndex = 0;
                htmlRawIndex++;
    }
    
    printf("last htmlRawIndex: %lu \n", htmlRawIndex);
    printf("compamies count: %d \n", itemsCopyCount);
          
           textListIndex1 = 0;
           textListIndex2 = 0;
    
    while (textListIndex1 < itemsCopyCount)
    {
        if (itemsCopyCountCurrent == itemsCopyCount)
        {
            break;
        }
        
            printf("%lu. ", textListIndex1 + 1);
        
        while (textListIndex2 < 256)
        {
            if (textList[textListIndex1][textListIndex2] == '$')
            {
                itemsCopyCountCurrent++;
                break;
            }
            printf("%c", textList[textListIndex1][textListIndex2]);
            
            textListIndex2++;
        }
        
            printf("\n");
        
            textListIndex2 = 0;
            textListIndex1++;
    }
    
    return 0;
}
