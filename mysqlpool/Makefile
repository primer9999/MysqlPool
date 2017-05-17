MYSQLPOOL_INCLUDE=./include

INCLUDE=-I$(MYSQLPOOL_INCLUDE)

BINARY=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
FLAG=-g -Wall -std=c++11 $$(mysql_config --cflags --libs)
TARGET=MysqlPool
all:$(TARGET)

$(TARGET):$(BINARY)
	g++ $(FLAG) $^ -o $@

%.o:%.cpp
	g++ $(FLAG) $< -o $@ -c $(INCLUDE)

clean:
	rm -rf *.o



