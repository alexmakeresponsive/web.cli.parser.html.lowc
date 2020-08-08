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

#define BREAK 0
#define RESUME 1
#define CONTINUE 2

int iterationStatePrint = RESUME;

char textList[1000][128];
char textListFilterBuffer[128];

int itemsCopyCount  = 0;


int parseCompanyName()
{
    
    char* page0filename = getPathOutPage(0);
    
    char htmlRaw[600000];
    long htmlRawIndex = 0;
    
    int  htmlRawIndexCurrent  = 0;     // for read from file
    int  htmlRawCharCount = 0;
    
    
    
    printf("\n");
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
    long stringBeforeTextLength = strlen(stringBeforeText);
    long stringBeforeTextIndex = 0;
    
    long stringBeforeTextIndexCompare = 0;
    long stringBeforeTextCompareLevel = 0;
    
    int  modePointer = MODE_POINTER_READ;
    int  modeCompare = MODE_COMPARE_STOP;
    
    long textListIndex1 = 0;
    long textListIndex2 = 0;
    
    long htmlRawLength = strlen(htmlRaw);
    
    
    while (htmlRawIndex < htmlRawLength)
    {
        while (stringBeforeTextIndex < stringBeforeTextLength)
        {
            if (modePointer == MODE_POINTER_COPY)
            {
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
        
        if (stringBeforeTextCompareLevel == stringBeforeTextLength)
        {
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

                textListIndex2 = 0;
                textListIndex1++;
            
                itemsCopyCount++;
        }
        
                stringBeforeTextIndex = 0;
                htmlRawIndex++;
    }
    
    printf("last htmlRawIndex: %lu \n", htmlRawIndex);
    printf("compamies count: %d \n", itemsCopyCount);
          
            printf("\n");
            printf("\033[0;32m");
    

        textListIndex1 = 0;
        textListIndex2 = 0;
    
    int textListFilterBufferIndex = 0;
    int itemsCopyCountCurrent = 0;
    
    while (textListIndex1 < itemsCopyCount)
    {
        // clean buffer
        while (textListFilterBufferIndex < 128)
        {
            textListFilterBuffer[textListFilterBufferIndex] = '\0';
            textListFilterBufferIndex++;
        }
            textListFilterBufferIndex = 0;
            textListIndex2 = 0;
        // clean buffer
        
        // copy company to buffer
        while (textListIndex2 < 128)
        {
            textListFilterBuffer[textListFilterBufferIndex] = textList[textListIndex1][textListIndex2];
            
            textListFilterBufferIndex++;
            textListIndex2++;
        }
            textListFilterBufferIndex = 0;
            textListIndex2 = 0;
        // copy company to buffer
        
        
        // filter company
            iterationStatePrint = RESUME;
        
            findCompanyByName(textListIndex1);
        
        if (iterationStatePrint == CONTINUE)
        {
            printf("\033[0;31m");
            printf("%-4s%lu. ", "", textListIndex1 + 1);
            printf("%s", textListFilterBuffer);
            printf("\n");
            printf("\033[0;32m");
                        
            textListIndex2 = 0;
            textListIndex1++;

            continue;
        }
        // filter company

        
            printf("%-4s%lu. ", "", textListIndex1 + 1);

        while (textListIndex2 < 128)
        {
            printf("%c", textList[textListIndex1][textListIndex2]);

            textListIndex2++;
        }
            printf("\n");
        
            
            textListIndex2 = 0;
            textListIndex1++;
    }
    
            printf("\033[0m");
            printf("\n");

    
    printf("companies count removed: %d \n", itemsCopyCount - itemsCopyCountCurrent);
    printf("companies count after filter: %d \n", itemsCopyCountCurrent);
    
            printf("\n");
    
    
    // filter results
    
    // How filter results?
    // add loop before loop( while (textListIndex2 < 128) ) for check it
    // Copy chars of company to buffer
    // Compare chars for next company with char in buffer
    // if all chars match then break loop( while (textListIndex1 < itemsCopyCount) )
    
    
    // filter results
    
    return 0;
}

int findCompanyByName(long indexCurrent)
{
    long textListIndex1 = 0;
    long textListIndex2 = 0;
    
    int textListFilterBufferIndex = 0;
    
    char textListFilterBufferCurrent[128];
    int  textListFilterBufferCurrentIndex = 0;
    
    
    while (textListIndex1 < itemsCopyCount)
    {
        if(textListIndex1 <= indexCurrent)
        {
            textListFilterBufferCurrentIndex = 0;
            textListFilterBufferIndex = 0;
            textListIndex2 = 0;
        
            textListIndex1++;
            
            
            
            continue;
        }
        
        // clean buffer
        while (textListFilterBufferCurrentIndex < 128)
        {
            textListFilterBufferCurrent[textListFilterBufferCurrentIndex] = '\0';
            textListFilterBufferCurrentIndex++;
        }
            textListFilterBufferCurrentIndex = 0;
        // clean buffer
        
        
        
        while (textListIndex2 < 128)
        {
            textListFilterBufferCurrent[textListFilterBufferCurrentIndex] = textList[textListIndex1][textListIndex2];
            
            textListFilterBufferCurrentIndex++;
            textListFilterBufferIndex++;
            textListIndex2++;
        }
        
        if(indexCurrent == 8)
        {
//            printf("textListFilterBufferCurrent: %s \n", textListFilterBufferCurrent);
//            printf("compare %d \n", strncmp(textListFilterBuffer, textListFilterBufferCurrent, 10));
        }
            
        if (strncmp(textListFilterBuffer, textListFilterBufferCurrent, 10) == 0)
        {
//            printf("textListFilterBuffer: %s \n", textListFilterBuffer);
//            printf("textListFilterBufferCurrent: %s \n", textListFilterBufferCurrent);
            
            
            
            iterationStatePrint = CONTINUE;
            break;
        }
        
            textListFilterBufferCurrentIndex = 0;
            textListFilterBufferIndex = 0;
            textListIndex2 = 0;
        
            textListIndex1++;
    }
    
    
    
    return 0;
}
