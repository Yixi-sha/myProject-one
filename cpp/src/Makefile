.PHONY : all clean rebuild

CC := arm-linux-g++
TARGET := app.out
TYPE := cpp


DIR_INC := inc
DIR_SRC := src
DIR_BUILD := build

MKDIR := mkdir
RM := rm -rf


CURRENT := $(realpath .)

SRCS := $(wildcard $(DIR_SRC)/*.$(TYPE))

OBJS := $(SRCS:.$(TYPE)=.o)
OBJS := $(patsubst $(DIR_SRC)/%, $(DIR_BUILD)/%, $(OBJS))

DEPS := $(SRCS:.$(TYPE)=.dep)
DEPS := $(patsubst $(DIR_SRC)/%, $(DIR_BUILD)/%, $(DEPS))

vpath %.h $(DIR_INC)
vpath %.$(TYPE) $(DIR_SRC)

GFLAGS := -I $(DIR_INC)

ifneq ("$(MAKECMDGOALS)","clean")
include  $(DEPS)
endif



all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^

test :
	@echo "$(DEPS)"

$(DIR_BUILD)/%.o : %.$(TYPE)
	$(CC) $(GFLAGS) -o $(filter %.o, $@) -c $(filter %.$(TYPE), $^)

ifeq ("$(wildcard $(DIR_BUILD))","")
$(DIR_BUILD)/%.dep : $(DIR_BUILD) %.$(TYPE)
else 
$(DIR_BUILD)/%.dep : %.$(TYPE)
endif
	@echo "Creat dep"
	@set -e ; \
	$(CC) $(GFLAGS) -MM -E $(filter %.$(TYPE), $^) | sed 's, \(.*\)\.o[ :],objs/\1.o $@ : ,g' > $@

$(DIR_BUILD) :
	$(MKDIR) $@

clean :
	$(RM) $(DIR_BUILD) *.out -rf

rebuild : clean all