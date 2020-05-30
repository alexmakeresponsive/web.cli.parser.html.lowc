//
//  pathconstructor.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "path.h"
#include "date.h"

char* getPathOutRaw()
{
    static char dir[] = "/Volumes/User/work/software/system/c/code/home/web/parser/hh/out";
    return dir;
}

char* getPathOutPage(int numberPage)
{
    char* dirRaw  = getPathOutRaw();
    char* strDate = getDateCurrent();
    
    static char dir[256];
    char charPage[4];

    sprintf(charPage, "%d", numberPage);
    
    strcpy(dir, dirRaw);
    strcat(dir, "/");
    strcat(dir, strDate);
    strcat(dir, "/page");
    strcat(dir, charPage);
    strcat(dir, ".txt");
    
    return dir;
}

char* getPathOut()
{
    char* dirRaw  = getPathOutRaw();
    char* strDate = getDateCurrent();
    
    static char dir[256];
    
    strcpy(dir, dirRaw);
    strcat(dir, "/");
    strcat(dir, strDate);
    
    return dir;
}
