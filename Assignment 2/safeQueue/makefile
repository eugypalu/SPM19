OBJECTS = main.cpp
CFLAGS = -pthread -std=c++17
CC = g++
PROGRAM_NAME = main.o
TEST = TestQueue.cpp
TESTNAME = TestQueue.o

$(PROGRAM_NAME):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJECTS)

clean: 
	rm -f $(PROGRAM_NAME)
	rm -f $(TESTNAME)
	@echo "Clean done"

test:
	$(CC) $(CFLAGS) -o $(TESTNAME) $(TEST)