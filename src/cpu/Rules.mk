## Auto generated make tool, don't edit manually.
src/cpu/$(OBJECT_DIR)/%.o: src/cpu/%.cpp
	$(COMP) $@ $<
src/cpu/$(OBJECT_DIR)/Core.o: src/cpu/Core.cpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/cpu/../MemoryBus.hpp \
  src/cpu/../Cartridge.hpp src/cpu/../MemoryBankController1.hpp \
  src/cpu/../IMemoryBankController.hpp \
  src/cpu/../InterruptController.hpp src/cpu/instructions.inc
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/cpu/../MemoryBus.hpp:
src/cpu/../Cartridge.hpp:
src/cpu/../MemoryBankController1.hpp:
src/cpu/../IMemoryBankController.hpp:
src/cpu/../InterruptController.hpp:
src/cpu/instructions.inc:
