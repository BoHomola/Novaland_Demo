////////////////////////////////////////////////////////////////////////////////
// File:        HttpRequest.h
// Author:      Bohumil Homola
// Date:        10/21/2023
// Description:
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

#include "NovalandCommon.h"
#include "curl/curl.h"

namespace Novaland::Http
{
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

inline std::string MakeHttpRequest(const std::string &url)
{
    CURL *curl = nullptr;
    CURLcode res = CURLE_OK;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            Logger::Error("curl_easy_perform() failed: {}", curl_easy_strerror(res));
            return "";
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}
} // namespace Novaland::Http
