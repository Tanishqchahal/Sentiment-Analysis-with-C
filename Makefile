CC = gcc
CFLAGS = -Wall -Wextra 
EXECUTABLE = mySA
SRC = sa.c
OBJSRC = functions.c
OBJ = functions.o
HLP = functions.h

$(EXECUTABLE): $(SRC) $(OBJ)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC) $(OBJ)
$(OBJ): $(OBJSRC) $(HLP)
	$(CC) -c $(OBJSRC) $(CFLAGS) -o $(OBJ) 
clean:
	rm -f mySA functions.o