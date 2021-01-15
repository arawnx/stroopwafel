CC = gcc
CFLAGS = -lncurses
SRCDIR = src
BINDIR = bin
_OBJS = main.o
OBJS = $(_OBJS:%=$(BINDIR)/%)

all: stroop

$(BINDIR):
	mkdir -p $@

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

stroop: $(BINDIR) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@
