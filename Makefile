
CC=gcc -D __OS_$(shell uname)__

all: clean comp

clean:
	@rm -f server client *.o

comp: OS_Info OS_$(shell uname)

OS_Info:
	@echo $(shell uname)...

#------------------------------------
OS_Darwin: server.o client.o
	@$(CC) -o server server.o
	@$(CC) -o client client.o
	@rm -f *.o

OS_Linux: server.o client.o
	@$(CC) -o server server.o
	@$(CC) -o client client.o
	@rm -f *.o
#------------------------------------

server.o: server.cpp
	@$(CC) -c server.cpp -o server.o

client.o: client.cpp
	@$(CC) -c client.cpp -o client.o


# OUT = lib/alib.a
# CC = g++
# ODIR = obj
# SDIR = src
# INC = -Iinc

# _OBJS = a_chsrc.o a_csv.o a_enc.o a_env.o a_except.o \
#         a_date.o a_range.o a_opsys.o
# OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


# $(ODIR)/%.o: $(SDIR)/%.cpp 
#     $(CC) -c $(INC) -o $@ $< $(CFLAGS) 

# $(OUT): $(OBJS) 
#     ar rvs $(OUT) $^

# .PHONY: clean

# clean:
#     rm -f $(ODIR)/*.o $(OUT)
