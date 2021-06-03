#include "little3ds/curlrequest.h"

u32 *SOC_buffer;

struct string
{
    char *ptr;
    size_t len;
};

void init_string(struct string *s)
{
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t write_to_string(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);

    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

void initCurlR()
{
    SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);
    socInit(SOC_buffer, SOC_BUFFERSIZE);
}

char* curlRequest(const char* url)
{
    CURL *curl;
    int result;

    curl = curl_easy_init();

    struct string retrieved_data;
    init_string(&retrieved_data);
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &retrieved_data);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);


    if (result == 0)
    {
        return retrieved_data.ptr;
    }
    else
    {
      return "err";
    }
}
