//
//  datetimeconstructor.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <time.h>
#include <stdio.h>

#include "date.h"

char* getDateCurrent()
{
    time_t timer;
    
    struct tm *localTime;
    
    static char strDate[24];

    timer     = time(NULL);
    localTime = localtime(&timer);
    
    strftime(strDate, 24, "%Y-%m-%d", localTime);
    
    return strDate;
}
