## Auto generated make tool, don't edit manually.
src/cpu/$(OBJECT_DIR)/%.o: src/cpu/%.cpp
	$(COMP) $@ $<
src/cpu/$(OBJECT_DIR)/Core.o: src/cpu/Core.cpp src/cpu/Core.hpp \
  src/Fwd.hpp src/IReadWrite.hpp utils/Operations_utils.hpp \
  src/Gameboy.hpp src/AMemoryBankController.hpp src/Debugger.hpp \
  src/MemoryBus.hpp src/Cartridge.hpp src/MemoryBankController1.hpp \
  src/PPU.hpp src/ScreenOutput.hpp src/cpu/InterruptController.hpp
src/cpu/Core.hpp:
src/Fwd.hpp:
src/IReadWrite.hpp:
utils/Operations_utils.hpp:
src/Gameboy.hpp:
src/AMemoryBankController.hpp:
src/Debugger.hpp:
src/MemoryBus.hpp:
src/Cartridge.hpp:
src/MemoryBankController1.hpp:
src/PPU.hpp:
src/ScreenOutput.hpp:
src/cpu/InterruptController.hpp:
src/cpu/$(OBJECT_DIR)/CoreExecute.o: src/cpu/CoreExecute.cpp \
  src/cpu/Core.hpp src/Fwd.hpp src/IReadWrite.hpp \
  utils/Operations_utils.hpp src/cpu/instructions.inc
src/cpu/instructions.inc:
src/cpu/$(OBJECT_DIR)/InterruptController.o: \
  src/cpu/InterruptController.cpp src/cpu/InterruptController.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/Gameboy.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/AMemoryBankController.hpp \
  src/Debugger.hpp src/MemoryBus.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/PPU.hpp src/ScreenOutput.hpp
src/cpu/$(OBJECT_DIR)/Timer.o: src/cpu/Timer.cpp src/cpu/Timer.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/Gameboy.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/AMemoryBankController.hpp \
  src/Debugger.hpp src/MemoryBus.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/PPU.hpp src/ScreenOutput.hpp \
  src/cpu/InterruptController.hpp
src/cpu/Timer.hpp:
