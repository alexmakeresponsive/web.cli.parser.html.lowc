//
//  checkdata.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


#include "data.h"
#include "../constructor/path.h"

int checkData(void)
{
    DIR* dirData;

    char* dirDataPath = getPathOut();

        dirData = opendir(dirDataPath);
    if (dirData)
    {
        closedir(dirData);
        
        printf("Data alredy exist. \n");
        return 1;
    }
    else
    {
        char* dirPath = getPathOut();
    
        printf("Create Data dir %s \n", dirPath);
        mkdir(dirPath, 0755);
        return 0;
    }
}
