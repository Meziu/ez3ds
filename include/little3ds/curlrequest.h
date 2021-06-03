#include <stdio.h>
#include <curl/curl.h>
#include <3ds.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000

extern u32 *SOC_buffer;

void initCurlR();
char* curlRequest(const char* url);
