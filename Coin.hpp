#include "DataProvider.hpp"
#include <iostream>
#include <string.h>

using namespace std;

class Coin {
protected:
  string symbol;
  string coinID;
  string name;
  string desc;
  float price;
  long long int market_cap;
  int rank;
  float day_change;
  float week_change;

public:
  Coin() : coinID{"bitcoin"} {}
  Coin(string id) {
    DataProvider dataProvider;
    json resp = dataProvider.getCoinData(id);
    coinID = resp["id"];
    symbol = resp["symbol"];
    name = resp["name"];
    desc = resp["description"]["en"];
    price = resp["market_data"]["current_price"]["usd"];
    day_change = resp["market_data"]["price_change_percentage_24h"];
    week_change = resp["market_data"]["price_change_percentage_7d"];
    market_cap = resp["market_data"]["market_cap"]["usd"];
    rank = resp["market_cap_rank"];
  }
  Coin(string _symbol, string _coinID, string _name, string _desc, float _price,
       int _market_cap, int _rank, float _day_change, float _week_change) {
    symbol = _symbol;
    coinID = _coinID;
    name = _name;
    desc = _desc;
    price = _price;
    market_cap = _market_cap;
    rank = _rank;
    day_change = _day_change;
    week_change = _week_change;
  }

  string getSymbol() { return symbol; }
  string getName() { return name; }
  string getDesc() { return desc; }
  string getId() { return coinID; }
  float getPrice() { return price; }
  float getDayChange() { return day_change; }
  float getWeekChange() { return week_change; }
  int getRank() { return rank; }
  long long int getMarketCap() { return market_cap; }

  ~Coin() {
    symbol = "";
    coinID = "";
    name = "";
    desc = "";
    price = 0.0;
    market_cap = 0;
    day_change = 0.0;
    week_change = 0.0;
  };
};