include include.mk

TARGET=main
CFLAGS=-g
INCLUDEDIR=-I $(GTEST)/include
LINKDIR=-L$(GTEST)
LIB=-lgtest

OBJS=main.o trie.o
SRCS=main.cc trie.cc

all: $(TARGET)
.PHONY: all

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) $(SRCS) -c $^

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LINKDIR) $(LIB)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
