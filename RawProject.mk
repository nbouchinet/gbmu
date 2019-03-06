## Standard things
#
.SUFFIXES:
CC 		:= clang++
CFLAGS		:= -I. -Wall -Wextra -Werror -g -std='c++14' -pthread
RM		:= rm -f
OBJECT_DIR	:= obj
COMP		:= $(CC) $(CFLAGS) -c -o
ifeq ($(shell uname -s), Darwin)
ECHO		:= echo
else
ECHO		:= echo -e
endif
#

## Sources directories
#
TEST_DIRS	:= tests
SRC_DIRS	:= src src/cpu utils
#

## Colors
#
BLUE		:= "\033[34m"
GREEN		:= "\033[32m"
RED		:= "\033[31m"
RESET		:= "\033[0m"
PNAME		:= $(BLUE)$(NAME)$(RESET)
#

## Including sources files
#
include $(patsubst %, %/Sources.mk, $(SRC_DIRS))
#

OBJ_DIRS	:= $(patsubst %, %/obj, $(SRC_DIRS))

.PHONY: all
all: $(OBJ_DIRS) $(OBJECTS) $(IMPL_OBJS)

## Including compilation rules
#
include $(patsubst %, %/Rules.mk, $(SRC_DIRS))
#

%/$(OBJECT_DIR):
	mkdir $@

## Including tests
#
-include $(patsubst %, %/Rules.mk, $(TEST_DIRS))
#

.PHONY: clean
clean:
	@$(RM) -r $(OBJ_DIRS)
	@$(ECHO) "Objects directories removed"

.PHONY: fclean
fclean: clean
	@$(RM) $(TEST_TARGETS)
	@$(ECHO) $(NAME) "deleted"

.PHONY: re
re: fclean all

.PHONY: makedeps
makedeps:
	python3 ./tools/gen_make_sources.py --source='.cpp' $(SRC_DIRS)
