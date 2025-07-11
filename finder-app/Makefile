# Makefile for building writer.c

# Default compiler and flags
CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Werror -g

# Source and target
TARGET := writer
SRC := writer.c
OBJS := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET) *.elf *.map