CC = gcc
CFLAGS = -O0 -ggdb3 -std=c99 -pedantic -Wall -Werror -Wextra
OBJDIR = obj
OBJ0 = $(OBJDIR)/assign1-0.o
OBJ1 = $(OBJDIR)/assign1.o
OBJ = $(OBJDIR)/pslibrary.o
OBJS = $(OBJ0) $(OBJ1) $(OBJ)
TARGET0 = assign1-0
TARGET1 = assign1

.PHONY: all clean

all: $(OBJS) $(TARGET0) $(TARGET1)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		mkdir $@

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET0): $(OBJ) $(OBJ0)
		$(CC) $(LDFLAGS) $^ -o $@

$(TARGET1): $(OBJ) $(OBJ1)
		$(CC) $(LDFLAGS) $^ -o $@

clean:
		@rm -f $(TARGET0) $(TARGET1) $(wildcard *.o)
		@rm -rf $(OBJDIR)
