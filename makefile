CC = cc
AR = ar
RANLIB = ranlib

SRCDIR = ./
INCDIR = ./
BINDIR = ./

CFLAGS = -g -Wall -std=c11

RM = /bin/rm -f

OBJ = $(BINDIR)/libbcd.o

LIB = $(BINDIR)/libbcd.a

SOURCES = $(SRCDIR)/bcd.c

all: $(SOURCES)
	$(CC) -c -o$(OBJ)  -I$(INCDIR) $(SOURCES)  $(CFLAGS)
	$(AR) rc $(LIB) $(OBJ)
	$(RANLIB) $(LIB)
	-$(RM) $(BINDIR)/*.o

clean:
	-$(RM) $(BINDIR)/$(LIB)
