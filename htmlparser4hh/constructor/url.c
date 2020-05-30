//
//  url.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <string.h>

#include "url.h"

char* getUrlPage(char urlRaw[], int numberPage)
{
    static char url[512];
    char charPage[4];

    sprintf(charPage, "%d", numberPage);
    
    strcpy(url, urlRaw);
    strcat(url, "&page=");
    strcat(url, charPage);
    
    return url;
}
