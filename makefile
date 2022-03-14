EXECUTABLE=http
ARGS=

all: clean
	@gcc main.c -o $(EXECUTABLE)

start: all
	@valgrind --leak-check=full ./http $(ARGS)

clean:
	@rm -f ./$(EXECUTABLE)
