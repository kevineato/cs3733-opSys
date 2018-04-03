CC = gcc
CFLAGS = -O0 -ggdb3 -std=c99 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lm
OBJDIR = obj
OBJ1 = $(OBJDIR)/assign3part1.o
OBJ23 = $(OBJDIR)/pagetable.o $(OBJDIR)/phypages.o
OBJ2 = $(OBJDIR)/assign3part2.o
OBJ3 = $(OBJDIR)/assign3part3.o
OBJS = $(OBJ1) $(OBJ2) $(OBJ3)
TARGET1 = assign3part1
TARGET2 = assign3part2
TARGET3 = assign3

.PHONY: all clean

all: $(OBJS) $(TARGET1) $(TARGET2) $(TARGET3)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		mkdir $@

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET1): $(OBJ1)
		$(CC) $^ -o $@

$(TARGET2): $(OBJ2) $(OBJ23)
		$(CC) $^ -o $@

$(TARGET3): $(OBJ3) $(OBJ23)
		$(CC) $(LDFLAGS) $^ -o $@

clean:
		@rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(wildcard *.o) $(wildcard output*)
		@rm -rf $(OBJDIR)
