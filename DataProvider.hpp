#include "./lib/json.hpp"
#include "./lib/termcolor.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <string.h>
using json = nlohmann::json;

using namespace std;

class DataProvider {
private:
  json response;
  static size_t getResponsetoString(void *contents, size_t size, size_t nmemb,
                                    void *userp) {
    ((string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
  }

  json getJson(string url) {
    system("clear");
    cout << termcolor::green << "Loading..." << endl;
    CURL *curl;
    CURLcode responseCURL;
    string str_response;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResponsetoString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);
    responseCURL = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    system("clear");
    return json::parse(str_response);
  }

public:
  DataProvider(string url) { response = getJson(url); }

  DataProvider() {}

  json getCoinData(string id) {
    response = getJson("https://api.coingecko.com/api/v3/coins/" + id);
    return response;
  }

  json getTopCoins() {
    response =
        getJson("https://api.coingecko.com/api/v3/coins/"
                "markets?vs_currency=usd&order=market_cap_desc&per_page=100&"
                "page=1&sparkline=false&price_change_percentage=24h%2C7d");
    return response;
  }

  json getResponse() { return response; }
};