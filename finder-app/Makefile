.RECIPEPREFIX := >

CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -Werror -g

TARGET := writer
SRCS := writer.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
>$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
>$(CC) $(CFLAGS) -c $< -o $@

clean:
>rm -f $(TARGET) *.o

.PHONY: all clean
