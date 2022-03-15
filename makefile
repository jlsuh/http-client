EXECUTABLE=http
ARGS=

all: clean
	@gcc main.c -o $(EXECUTABLE)

start: all
	@valgrind --tool=none ./$(EXECUTABLE) $(ARGS)

clean:
	@rm -f ./$(EXECUTABLE)
