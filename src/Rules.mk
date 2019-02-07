## Auto generated make tool, don't edit manually.
src/$(OBJECT_DIR)/%.o: src/%.cpp
	$(COMP) $@ $<
src/$(OBJECT_DIR)/Cartridge.o: src/Cartridge.cpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/IMemoryBankController.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/MemoryBankController2.hpp \
  src/MemoryBankController3.hpp src/RealTimeClock.hpp \
  src/MemoryBankController5.hpp
src/Cartridge.hpp:
src/MemoryBankController1.hpp:
src/IMemoryBankController.hpp:
src/Fwd.hpp:
src/IReadWrite.hpp:
src/MemoryBankController2.hpp:
src/MemoryBankController3.hpp:
src/RealTimeClock.hpp:
src/MemoryBankController5.hpp:
src/$(OBJECT_DIR)/Gameboy.o: src/Gameboy.cpp src/Gameboy.hpp src/Fwd.hpp \
  src/Cartridge.hpp src/MemoryBankController1.hpp \
  src/IMemoryBankController.hpp src/IReadWrite.hpp src/MemoryBus.hpp \
  src/cpu/Core.hpp utils/Operations_utils.hpp \
  src/cpu/InterruptController.hpp src/cpu/Timer.hpp
src/Gameboy.hpp:
src/MemoryBus.hpp:
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/cpu/InterruptController.hpp:
src/cpu/Timer.hpp:
src/$(OBJECT_DIR)/main.o: src/main.cpp src/Gameboy.hpp src/Fwd.hpp
src/$(OBJECT_DIR)/MemoryBus.o: src/MemoryBus.cpp src/MemoryBus.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/IMemoryBankController.hpp \
  src/Gameboy.hpp src/cpu/Timer.hpp src/cpu/InterruptController.hpp
