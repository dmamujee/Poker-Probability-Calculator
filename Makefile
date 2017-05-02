## Poker-Probability-Calculator makefile
# David Mamujee

CC = g++
CXXFLAGS = -Wall -g -MMD -DDEBUG1 #-DDEBUG

OBJS = card.o game.o
DEPENDS = $(OBJS:.o=.d)

EXEC = poker_prob_calc

# Builds the main.cc file as the program
$(EXEC) : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) main.cc -o $(EXEC) $(X11FLAGS)

#get all *.d depends files
-include ${DEPENDS}

.PHONY: clean
clean:
	\rm *.o $(EXEC)
