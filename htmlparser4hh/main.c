//
//  main.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>

#include "url2memory.h"
#include "url2file.h"

#include "parser.h"


int main(int argc, const char * argv[]) {
    
    if(argc < 3) {
      printf("Usage: %s <URL> <pageStart> <pageEnd>\n", argv[0]);
      return 1;
    }

//    if (!checkData())
//    {
//        url2FileExec(argv[1], argv[2], argv[3]);
//
//        return 0;
//    }
    
    parseCompanyName();
    
    return 0;
}
