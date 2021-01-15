CC = gcc
CFLAGS = -lncurses
SRCDIR = src
BINDIR = bin
_OBJS = main.o
OBJS = $(_OBJS:%=$(BINDIR)/%)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

stroop: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@
