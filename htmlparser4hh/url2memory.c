//
//  url2memory.c
//  htmlparser4hh
//
//  Created by Alexandr on 29.05.2020.
//  Copyright © 2020 Alexandr. All rights reserved.
//

/* <DESC>
 * Shows how the write callback function can be used to download data into a
 * chunk of memory instead of storing it in a file.
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "url2memory.h"

struct MemoryStruct {
  char *memory;
  size_t size;
} mem1;

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void getBody(unsigned long htmlRawSize, char htmlRaw[])
{
    long i = 0;
    long j = 0;
    
    int iCount = 0;
    
    char *htmlBody;
    
    char htmlStringForFind1[64];
    char htmlStringForFind2[64];
    
    char htmlStringForFind1Value[] = "<div";
    char htmlStringForFind2Value[] = "</div>";
    
    char htmlTagFind[]     = "head";
    int  htmlTagFindSymbolFind = 0;
    
    char *htmlStringForFindPtr1;
    char *htmlStringForFindPtr2;
    
    long positionStringForFind1 = 0;
    long positionStringForFind2 = 0;
    
    
    htmlBody = (char *) malloc(htmlRawSize);
    
    strcpy(htmlStringForFind1, htmlStringForFind1Value);
    strcpy(htmlStringForFind2, htmlStringForFind2Value);
    
    
    //get sub string
         i = 0;
         j = 0;
    for (i = 0; i < strlen(htmlRaw); i++)
    {
        for (j = 0; htmlTagFind[j] != '\0'; j++)
        {
            if(htmlRaw[i] != htmlTagFind[j])
            {
                continue;
            }
            
//            printf("%c \n", htmlRaw[i]);
        }
    }
    
    
    
//    system("clear");
    printf("%lu bytes retrieved\n", htmlRawSize);
//    printf("htmlBody: %s \n", htmlBody);
//    printf("iCount: %i \n", iCount);
//    printf("htmlRaw last symbol: %c \n", htmlRaw[2]);
    
    free(htmlBody);
}

int url2MemoryExec(void)
{
  CURL *curl_handle;
  CURLcode res;

  struct MemoryStruct chunk;

  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://localhost/");

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */

//    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
//    printf("chunk: %s", chunk.memory);
      
      getBody(chunk.size, chunk.memory);
  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

  return 0;
}
