.PHONY : clean run dummy

CC=gcc
CFLAGS=-std=c99

CAMERASCRIPT=cam_stdout.py
DUMMYSCRIPT=dummy_stdout.py
GPIOSCRIPT=gpio_out

all: $(GPIOSCRIPT)

$(GPIOSCRIPT): $(GPIOSCRIPT).c
	$(CC) $(CFLAGS) $< -o $@

run: $(GPIOSCRIPT)
	./$(CAMERASCRIPT) | sudo ./$(GPIOSCRIPT)

dummy: $(GPIOSCRIPT)
	./$(DUMMYSCRIPT) | sudo ./$(GPIOSCRIPT)

clean:
	rm -f *.o $(GPIOSCRIPT)

