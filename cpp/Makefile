.PHONY : all clean rebuild

CC := arm-linux-g++
TARGET := app.out
TYPE := cpp

MODULE := eth ser
		  

MODULE := $(addprefix moudle/, $(MODULE))

DIR_INC := $(addsuffix /inc, $(MODULE)) 
DIR_SRC := . $(addsuffix /src, $(MODULE))
DIR_BUILD := build

MKDIR := mkdir
RM := rm -rf

CURRENT := $(realpath .)

SRCS := $(wildcard $(addsuffix /*.$(TYPE), $(DIR_SRC)))

OBJS := $(SRCS:.$(TYPE)=.o)
OBJS := $(notdir $(OBJS))
OBJS := $(addprefix $(DIR_BUILD)/, $(OBJS)) 


DEPS := $(OBJS:.o=.dep)

vpath %.h $(DIR_INC)
vpath %.$(TYPE) $(DIR_SRC)

GFLAGS := -I $(DIR_INC)

ifneq ("$(MAKECMDGOALS)","clean")
include  $(DEPS)
endif



all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ -Xlinker "-(" $^ -Xlinker "-)"

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