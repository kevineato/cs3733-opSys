CC = gcc
CFLAGS = -O0 -ggdb3 -std=c99 -pedantic -Wall -Werror -Wextra
OBJDIR = obj
OBJ1 = $(OBJDIR)/assign2.o
OBJ = $(OBJDIR)/pslibrary.o
OBJS = $(OBJ0) $(OBJ1) $(OBJ)
TARGET1 = assign2

.PHONY: all clean

all: $(OBJS) $(TARGET1)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		mkdir $@

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET1): $(OBJ) $(OBJ1)
		$(CC) $(LDFLAGS) $^ -o $@

clean:
		@rm -f $(TARGET0) $(TARGET1) $(wildcard *.o)
		@rm -rf $(OBJDIR)
