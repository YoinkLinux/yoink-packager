//
// Created by gcpease on 11/28/2021.
//

#include <cstdio>
#include <curl/curl.h>
#include "yoinkinstaller.h"

int main() {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char *url = "https://web.peasenet.com/yoinklinux/acl-2.2.53.tar.gz";
    char outfilename[FILENAME_MAX] = "/tmp/acl-2.2.53.tar.gz";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}