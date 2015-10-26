.PHONY : clean run

CC=gcc
CFLAGS=-std=c11

CAMERASCRIPT=cam_stdout.py
GPIOSCRIPT=gpio_out

all: $(GPIOSCRIPT)

$(GPIOSCRIPT): $(GPIOSCRIPT).c
	$(CC) $(CFLAGS) $< -o $@

run: $(GPIOSCRIPT)
	./$(CAMERASCRIPT) | sudo ./$(GPIOSCRIPT)

clean:
	rm -f *.o $(GPIOSCRIPT)

