## Auto generated make tool, don't edit manually.
src/$(OBJECT_DIR)/%.o: src/%.cpp
	$(COMP) $@ $<
src/$(OBJECT_DIR)/Core.o: src/Core.cpp src/Core.hpp \
  src/Operations_utils.hpp src/instructions.inc
src/Core.hpp:
src/Operations_utils.hpp:
src/instructions.inc:
src/$(OBJECT_DIR)/main.o: src/main.cpp
