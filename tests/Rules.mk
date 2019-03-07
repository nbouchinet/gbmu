TEST_CC			:= clang++
TEST_CFLAGS		:=
TEST_LFLAGS		:= -lgtest -pthread 
ifeq ($(shell uname -s), Darwin)
	TEST_CFLAGS		+= -I ~/.brew/include
	TEST_LFLAGS		+= -L ~/.brew/lib
endif
COMPLINK		:= $(CC) $(TEST_CFLAGS) $(TEST_LFLAGS) -o

CURR_DIR		:= tests
## Put all the tests here
TEST_FILES		:= 	sample.cpp \
				Operations_utils.cpp \
				Core.cpp \
				Gameboy.cpp \
				MemoryBankController1.cpp \
				MemoryBankController2.cpp \
				MemoryBankController3.cpp \
				Timer.cpp \
				Interrupt.cpp \
				Sound.cpp \
				RealTimeClock.cpp

TEST_OBJECTS	:= $(addprefix $(CURR_DIR)/$(OBJECT_DIR)/, $(TEST_FILES:.cpp=.o))
RUN_TEST_RULES	:= $(addprefix test_, $(TEST_FILES:.cpp=))

TEST_FILES	:= $(addprefix $(CURR_DIR)/, $(TEST_FILES))
TEST_TARGETS	:= $(TEST_FILES:.cpp=)
TEST_OBJ_DIR	:= $(CURR_DIR)/$(OBJECT_DIR)

OBJ_DIRS 	+= $(TEST_OBJ_DIR)

.PRECIOUS: $(TEST_TARGETS) $(TEST_OBJECTS)
.PHONY: test_all
test_all: $(RUN_TEST_RULES)

.PHONY: clear_tests
clear_tests:
	rm -rf $(TEST_OBJ_DIR)
	rm -f $(TEST_TARGETS)

test_%: all $(TEST_OBJ_DIR) $(CURR_DIR)/%
ifeq ($(shell uname -s), Darwin)
	$(eval FAIL := $(shell script -q $*.out $(CURR_DIR)/$* > /dev/null; echo $$?))
else
	$(eval FAIL := $(shell script -qec $(CURR_DIR)/$* $*.out > /dev/null; echo $$?))
endif
	@if [ $(FAIL) -gt 0 ]; \
		then \
		$(ECHO) "["$(RED)KO$(RESET)"] -" $*; \
		cat $*.out; \
		else \
		$(ECHO)  "["$(GREEN)OK$(RESET)"] -" $*; \
		fi
	@rm $*.out

$(CURR_DIR)/%: $(CURR_DIR)/$(OBJECT_DIR)/%.o $(NAME)
	$(TEST_CC) -o $@ $< $(subst src/obj/main.o,,$(OBJECTS)) $(TEST_LFLAGS)

$(CURR_DIR)/$(OBJECT_DIR)/%.o: $(CURR_DIR)/%.cpp
	$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c -o $@ $<

$(TEST_OBJ_DIR):
	mkdir $@
