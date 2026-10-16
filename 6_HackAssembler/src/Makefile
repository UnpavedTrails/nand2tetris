CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

TARGET = HackAssembler
OBJS = main.o cleaning_utils.o symbols.o instruct.o c_support.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c cleaning_utils.h symbols.h instruct.h
	$(CC) $(CFLAGS) -c main.c

cleaning_utils.o: cleaning_utils.c cleaning_utils.h
	$(CC) $(CFLAGS) -c cleaning_utils.c

symbols.o: symbols.c symbols.h
	$(CC) $(CFLAGS) -c symbols.c

instruct.o: instruct.o instruct.h c_support.h
	$(CC) $(CFLAGS) -c instruct.c

c_support.o: c_support.o c_support.h
	$(CC) $(CFLAGS) -c c_support.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean