CC=gcc -m64 -D _OS_Windows_
SDIR = source
ODIR = build
LIBDIR = .
BFile = ./bin/jinx.exe

_EXOBJS = 
EXOBJS = $(patsubst %,$(LIBDIR)/%,$(_EXOBJS))

_OBJS = main.obj
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.obj: $(SDIR)/%.c 
	@$(CC) -c $(INC) -o $@ $< $(CFLAGS) 
	
#------------------------------------
build : $(OBJS)
	@$(CC) -o $(BFile) $(OBJS) $(EXOBJS)

test :
	@$(BFile)

clean : $(OBJS)
	@rm -f $(BFile) $(OBJS)