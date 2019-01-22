TEST_CC			:= clang++
TEST_CFLAGS		:=
TEST_LFLAGS		:= -lgtest
ifeq ($(shell uname -s), Darwin)
TEST_CFLAGS		+= -I ~/.brew/include
TEST_LFLAGS		+= -L ~/.brew/lib
endif
COMPLINK		:= $(CC) $(TEST_CFLAGS) $(TEST_LFLAGS) -o

CURR_DIR		:= tests
## Put all the tests here
TEST_FILES		:= sample.cpp
#

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
	$(eval FAIL := $(shell script $*.out $(CURR_DIR)/$* > /dev/null; echo $$?))
	@if [ $(FAIL) -gt 0 ]; \
	then \
		$(ECHO) "["$(RED)KO$(RESET)"] -" $*; \
		cat tmp; \
	else \
		$(ECHO)  "["$(GREEN)OK$(RESET)"] -" $*; \
	fi
	@rm $*.out

$(CURR_DIR)/%: $(CURR_DIR)/$(OBJECT_DIR)/%.o $(NAME)
	$(TEST_CC) $(TEST_LFLAGS) -o $@ $<

$(CURR_DIR)/$(OBJECT_DIR)/%.o: $(CURR_DIR)/%.cpp
	$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c -o $@ $<

$(TEST_OBJ_DIR):
	mkdir $@
