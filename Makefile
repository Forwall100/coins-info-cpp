OBJS	= main.o
SOURCE	= main.cpp
HEADER	= CLI.hpp Coin.hpp CoinPage.hpp DataProvider.hpp Interfaces.hpp Tables.hpp
OUT	= app
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lcurl

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)