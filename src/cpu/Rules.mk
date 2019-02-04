## Auto generated make tool, don't edit manually.
src/cpu/$(OBJECT_DIR)/%.o: src/cpu/%.cpp
	$(COMP) $@ $<
src/cpu/$(OBJECT_DIR)/Core.o: src/cpu/Core.cpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/cpu/instructions.inc
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/cpu/instructions.inc:
