
CC=gcc -D _OS_$(OS)_
SDIR = source
ODIR = build
INC = -Iinc

all: clean comp

clean:
	rm -f $(ODIR)/*.*

comp: PRE_$(OS) OS_$(OS)
#------------------------------------
_EXOBJS = libws2_32.a
EXOBJS = $(patsubst %,$(LIBDIR)/%,$(_EXOBJS))

_OBJS = client.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 
#------------------------------------
PRE_Darwin:
PRE_Linux:
PRE_Windows_NT:
LIBDIR = C:/MinGW/lib
#------------------------------------
OS_Darwin: $(OBJS)
	$(CC) -o $(ODIR)/client $(OBJS)
OS_Linux: $(OBJS)
	$(CC) -o $(ODIR)/client $(OBJS)
OS_Windows_NT: $(OBJS)
	$(CC) -o $(ODIR)/client.exe $(OBJS) $(EXOBJS)
#------------------------------------