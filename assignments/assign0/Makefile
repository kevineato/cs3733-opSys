CC = gcc
CFLAGS = -I. -O0 -ggdb3 -std=c99 -pedantic -Wall -Werror -Wextra
OBJDIR = obj
OBJ1 = $(OBJDIR)/driver1.o
OBJ2 = $(OBJDIR)/driver2.o
OBJ = $(OBJDIR)/myio.o
OBJS = $(OBJ1) $(OBJ2) $(OBJ)
TARGET1 = driver1
TARGET2 = driver2

.PHONY: all clean

all: $(OBJS) $(TARGET1) $(TARGET2)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		mkdir $@

$(OBJDIR)/%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(TARGET1): $(OBJ) $(OBJ1)
		$(CC) $(LDFLAGS) $^ -o $@

$(TARGET2): $(OBJ) $(OBJ2)
		$(CC) $(LDFLAGS) $^ -o $@

clean:
		@rm -f $(TARGET1) $(TARGET2) $(wildcard *.o)
		@rm -rf $(OBJDIR)
