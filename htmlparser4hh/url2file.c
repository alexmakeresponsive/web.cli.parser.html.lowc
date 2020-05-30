//
//  url2file.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

/* <DESC>
* Download a given URL into a local file named page.out.
* </DESC>
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

#include "url2file.h"
#include "constructor/path.h"
#include "constructor/url.h"


int url2FileExecInner(char url[], int pageCurrent);


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int url2FileExec(char urlRaw[], char pageStartChar[], char pageEndChar[])
{
    int i;
    int pageStart = atoi(pageStartChar) - 1;
    int pageEnd   = atoi(pageEndChar) - 1;

    
    for (i=pageStart; i<=pageEnd; i++)
    {
        url2FileExecInner(urlRaw, i);
    }

    return 0;
}


int url2FileExecInner(char urlRaw[], int pageCurrent)
{
    CURL* curl_handle;
    
    FILE* pagefile;
    
    char* pagefilename = getPathOutPage(pageCurrent);
    char* url = getUrlPage(urlRaw, pageCurrent);
    


    printf("pagefilename: %s \n", pagefilename);
//    printf("url: %s \n", url);
    
//    return 0;
    
    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
       pagefile = fopen(pagefilename, "wb");
    if(pagefile)
    {
        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

        /* get it! */
        curl_easy_perform(curl_handle);

        /* close the header file */
        fclose(pagefile);
        
        printf("page %d downloaded \n", pageCurrent);
    } else {
        printf("error open \n");
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    curl_global_cleanup();
    
    return 0;
}

