# DE10 Nano IP address
IP=10.0.0.2

# define the C compiler to use
CC=arm-linux-gnueabihf-gcc
STRIP=arm-linux-gnueabihf-strip -s

# define any compile-time flags
CFLAGS = -Wall -g -Dsoc_cv_av -O2

# define any directories containing header files other than /usr/include
#
INCLUDES = -I./include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS =

# define the C source files
SRCS = $(wildcard src/*.c)

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(addprefix obj/, $(notdir $(patsubst %.c,%.o,$(wildcard src/*))))

# define the executable file 
MAIN = motor

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: clean

all: $(OBJS) $(MAIN)
	@echo  Done.

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
	$(STRIP) $(MAIN)
# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f $(OBJS) $(MAIN)

upload:
	scp $(MAIN) root@$(IP):~/robot/$(MAIN)
