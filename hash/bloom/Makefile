include include.mk

TARGET=main
CFLAGS=-g
INCLUDEDIR=-I $(GTEST)/include
LINKDIR=-L$(GTEST)
LIB=-lgtest -lpthread

OBJS=main.o bloomfilter.o bitmap.o
SRCS=main.cc bloomfilter.cc bitmap.cc

all: $(TARGET)
.PHONY: all

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDEDIR) $(SRCS) -c $^

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LINKDIR) $(LIB)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
