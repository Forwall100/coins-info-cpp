#include "Tables.hpp"

class CoinPage {
private:
  Coin coin;

public:
  CoinPage(string id) { coin = Coin(id); }
  CoinPage() : coin(Coin("bitcoin")){};

  void printCoinPage() {
    system("clear");

    cout << termcolor::white << "#" << coin.getRank() << " "
         << termcolor::bright_cyan << coin.getName() << termcolor::bright_green
         << "[" << coin.getSymbol() << "]" << endl;

    cout << termcolor::bright_cyan << "Price: " << termcolor::bright_green
         << "[" << coin.getPrice() << "]" << endl;

    cout << termcolor::bright_cyan << "Market Cap: " << termcolor::bright_green
         << "[" << coin.getMarketCap() << "]" << endl;

    if (coin.getDayChange() > 0) {
      cout << termcolor::bright_cyan
           << "Change 24h%: " << termcolor::bright_green << "["
           << coin.getDayChange() << "]" << endl;
    } else {
      cout << termcolor::bright_cyan << "Change 24h%: " << termcolor::bright_red
           << "[" << coin.getDayChange() << "]" << endl;
    }

    if (coin.getWeekChange() > 0) {
      cout << termcolor::bright_cyan
           << "Change 7d%: " << termcolor::bright_green << "["
           << coin.getWeekChange() << "]" << endl;
    } else {
      cout << termcolor::bright_cyan << "Change 7d%: " << termcolor::bright_red
           << "[" << coin.getWeekChange() << "]" << endl;
    }

    cout << termcolor::bright_cyan << "Description: " << termcolor::white
         << coin.getDesc() << endl;
  }
};