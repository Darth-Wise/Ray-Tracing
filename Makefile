CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99
TARGET = main

all: $(TARGET)

$(TARGET): main.c color.h vec3.h
	$(CC) $(CFLAGS) main.c -o $(TARGET) -lm

clean:
	rm -f $(TARGET) image.ppm