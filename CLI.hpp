#include "CoinPage.hpp"
#include <termios.h>
#include <unistd.h>

class CLI {
private:
  string input;
  int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
  }

public:
  void printHints() {
    cout << termcolor::cyan << "j" << termcolor::bright_green
         << ": Next Page      " << termcolor::cyan << "k"
         << termcolor::bright_green << ": Previous Page      "
         << termcolor::cyan << "/" << termcolor::bright_green << ": Enter ID"
         << endl;
  }
  void mainloop() {
    int page = 0;
    system("clear");
    TableTopMarketCap table(page);
    table.printTable();
    printHints();
    for (;;) {
      switch (getch()) {
      case 'j': {
        page++;
        system("clear");
        TableTopMarketCap table(page);
        table.printTable();
        printHints();
        break;
      }
      case 'k': {
        if (page == 0) {
          break;
        }
        page--;
        system("clear");
        TableTopMarketCap table(page);
        table.printTable();
        printHints();
        break;
      }
      case '/': {
        cout << termcolor::bright_green << "[Enter id] ➔  ";
        cin >> input;
        try {
          CoinPage coinPage(input);
          coinPage.printCoinPage();
        } catch (const exception &e) {
          system("clear");
          TableTopMarketCap table(page);
          table.printTable();
          printHints();
          break;
        }
        break;
      }
      }
    }
  }
};