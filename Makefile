COMPILE = g++
FLAGS =

OBJS = 

all: ./src/main.cpp $(OBJS)
		$(COMPILE) $(FLAGS) -g ./src/main.cpp $(OBJS) -o ./bin/feature-selection

clean:
		rm -rf ./bin/
