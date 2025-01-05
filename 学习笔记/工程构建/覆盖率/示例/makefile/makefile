CC = gcc
CFLAGS = -fprofile-arcs -ftest-coverage -g
LDFLAGS = -fprofile-arcs -ftest-coverage

SRC = main.c math_utils.c
OBJ = $(SRC:.c=.o)
TARGET = app

.PHONY: all clean coverage

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) *.gcno *.gcda *.info

coverage: all
	./$(TARGET)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage-report