ifeq ($(shell uname -s), Darwin)
ECHO        := echo
else
ECHO        := echo -e
endif

## Colors
#
BLUE        := "\033[34m"
GREEN        := "\033[32m"
RED        := "\033[31m"
RESET        := "\033[0m"
PNAME        := $(BLUE)$(NAME)$(RESET)
#

OBJECT_DIR 		:= obj
OBJECTS			:= ../src/obj/Bios.o \
	../src/obj/Cartridge.o \
	../src/obj/Core.o \
	../src/obj/CoreExecute.o \
	../src/obj/Debugger.o \
	../src/obj/Gameboy.o \
	../src/obj/InputController.o \
	../src/obj/InterruptController.o \
	../src/obj/MemoryBus.o \
	../src/obj/PPU.o \
	../src/obj/ScreenOutput.o \
	../src/obj/Timer.o

TEST_CC			:= clang++
TEST_CFLAGS		:= -std=c++14 -Wall -Wextra -Werror -I ../
TEST_LFLAGS		:= -lgtest -pthread
ifeq ($(shell uname -s), Darwin)
	TEST_CFLAGS		+= -I ~/.brew/include
	TEST_LFLAGS		+= -L ~/.brew/lib
endif
COMPLINK		:= $(CC) $(TEST_CFLAGS) $(TEST_LFLAGS) -o

## Put all the tests here
TEST_FILES		:= 	sample.cpp \
				Operations_utils.cpp \
				Core.cpp \
				Gameboy.cpp \
				MemoryBankController1.cpp \
				MemoryBankController2.cpp \
				MemoryBankController3.cpp \
				RealTimeClock.cpp \
				Timer.cpp \
				Interrupt.cpp

TEST_OBJECTS	:= $(addprefix $(OBJECT_DIR)/, $(TEST_FILES:.cpp=.o))
RUN_TEST_RULES	:= $(addprefix test_, $(TEST_FILES:.cpp=))

TEST_TARGETS	:= $(TEST_FILES:.cpp=)
TEST_OBJ_DIR	:= obj

OBJ_DIRS 	+= $(TEST_OBJ_DIR)

.PRECIOUS: $(TEST_TARGETS) $(TEST_OBJECTS)
.PHONY: all
all: $(RUN_TEST_RULES)

.PHONY: clear_tests
clean:
	rm -rf $(TEST_OBJ_DIR)
	rm -f $(TEST_TARGETS)

test_%: $(TEST_OBJ_DIR) %
ifeq ($(shell uname -s), Darwin)
	$(eval FAIL := $(shell script -q $*.out ./$* > /dev/null; echo $$?))
else
	$(eval FAIL := $(shell script -qec ./$* $*.out > /dev/null; echo $$?))
endif
	@if [ $(FAIL) -gt 0 ]; \
		then \
		$(ECHO) "["$(RED)KO$(RESET)"] -" $*; \
		cat $*.out; \
		else \
		$(ECHO)  "["$(GREEN)OK$(RESET)"] -" $*; \
		fi
	@rm $*.out

%: $(OBJECT_DIR)/%.o
	$(TEST_CC) -o $@ $< $(subst ../src/obj/main.o,,$(OBJECTS)) $(TEST_LFLAGS)

$(OBJECT_DIR)/%.o: %.cpp
	$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c -o $@ $<

$(TEST_OBJ_DIR):
	mkdir $@
