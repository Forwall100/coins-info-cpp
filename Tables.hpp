#include "Coin.hpp"
#include "Interfaces.hpp"

class TableRecord : Coin, ITableAdd {
public:
  TableRecord(Coin coin) {
    symbol = coin.getSymbol();
    coinID = coin.getId();
    name = coin.getName();
    desc = coin.getDesc();
    price = coin.getPrice();
    market_cap = coin.getMarketCap();
    rank = coin.getRank();
    day_change = coin.getDayChange();
    week_change = coin.getWeekChange();
  };

  void add2table(TextTable *t) {
    t->add(to_string(rank));
    t->add(name);
    t->add(to_string(price));
    t->add(to_string(day_change));
    t->add(to_string(week_change));
    t->add(symbol);
    t->add(coinID);
    t->endOfRow();
  }
};

class Table {
protected:
  vector<TableRecord> coins;
  TextTable t;

public:
  Table(){};
  Table(vector<string> columns) {
    for (auto i : columns) {
      t.add(i);
    }
    t.endOfRow();
  };

  Table(vector<TableRecord> coins) {
    for (auto coin : coins) {
      coin.add2table(&t);
    }
  };

  vector<TableRecord> getCoins() { return coins; }

  TextTable getTable() { return t; }

  void add(TableRecord coin) {
    coins.push_back(coin);
    coin.add2table(&t);
  }

  void printTable() { cout << termcolor::bright_cyan << t << endl; }
};

class TableTopMarketCap : Table {
private:
  int page;

public:
  TableTopMarketCap() {
    t.add("Rank");
    t.add("Coin");
    t.add("Price");
    t.add("Change 24h%");
    t.add("Change 7d%");
    t.add("Ticker");
    t.add("ID");
    t.endOfRow();
  }
  TableTopMarketCap(int _page) {
    page = _page;
    t.add("Rank");
    t.add("Coin");
    t.add("Price");
    t.add("Change 24h%");
    t.add("Change 7d%");
    t.add("Ticker");
    t.add("ID");
    t.endOfRow();
    DataProvider dataProvider;
    json resp = dataProvider.getTopCoins();
    for (auto i : resp) {
      TableRecord coin = TableRecord(
          Coin(i["symbol"], i["id"], i["name"], "", i["current_price"],
               i["market_cap"], i["market_cap_rank"],
               i["price_change_percentage_24h_in_currency"],
               i["price_change_percentage_7d_in_currency"]));
      coins.push_back(coin);
    }
    for (int i = page * 10; i < page * 10 + 10; i++) {
      coins[i].add2table(&t);
    }
  }
};