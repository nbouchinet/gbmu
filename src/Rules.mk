## Auto generated make tool, don't edit manually.
src/$(OBJECT_DIR)/%.o: src/%.cpp
	$(COMP) $@ $<
src/$(OBJECT_DIR)/Cartridge.o: src/Cartridge.cpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/IMemoryBankController.hpp
src/Cartridge.hpp:
src/MemoryBankController1.hpp:
src/IMemoryBankController.hpp:
src/$(OBJECT_DIR)/Gameboy.o: src/Gameboy.cpp src/Gameboy.hpp \
  src/MemoryBus.hpp src/Cartridge.hpp src/MemoryBankController1.hpp \
  src/IMemoryBankController.hpp src/InterruptController.hpp \
  src/cpu/Core.hpp utils/Operations_utils.hpp src/Timer.hpp
src/Gameboy.hpp:
src/MemoryBus.hpp:
src/InterruptController.hpp:
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/Timer.hpp:
src/$(OBJECT_DIR)/InterruptController.o: src/InterruptController.cpp \
  src/InterruptController.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/cpu/../MemoryBus.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/IMemoryBankController.hpp
src/cpu/../MemoryBus.hpp:
src/$(OBJECT_DIR)/main.o: src/main.cpp src/Gameboy.hpp
src/$(OBJECT_DIR)/MemoryBus.o: src/MemoryBus.cpp src/MemoryBus.hpp \
  src/Cartridge.hpp src/MemoryBankController1.hpp \
  src/IMemoryBankController.hpp src/InterruptController.hpp
src/$(OBJECT_DIR)/Timer.o: src/Timer.cpp src/Timer.hpp \
  src/InterruptController.hpp
