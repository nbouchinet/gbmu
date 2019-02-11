## Auto generated make tool, don't edit manually.
src/$(OBJECT_DIR)/%.o: src/%.cpp
	$(COMP) $@ $<
src/$(OBJECT_DIR)/Cartridge.o: src/Cartridge.cpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/AMemoryBankController.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/MemoryBankController2.hpp \
  src/MemoryBankController3.hpp src/RealTimeClock.hpp \
  src/MemoryBankController5.hpp
src/Cartridge.hpp:
src/MemoryBankController1.hpp:
src/AMemoryBankController.hpp:
src/Fwd.hpp:
src/IReadWrite.hpp:
src/MemoryBankController2.hpp:
src/MemoryBankController3.hpp:
src/RealTimeClock.hpp:
src/MemoryBankController5.hpp:
src/$(OBJECT_DIR)/Debugger.o: src/Debugger.cpp src/Debugger.hpp \
  src/Fwd.hpp src/cpu/Core.hpp utils/Operations_utils.hpp \
  src/IReadWrite.hpp
src/Debugger.hpp:
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/$(OBJECT_DIR)/Gameboy.o: src/Gameboy.cpp src/Gameboy.hpp \
  src/AMemoryBankController.hpp src/Fwd.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/IReadWrite.hpp src/Debugger.hpp \
  src/Cartridge.hpp src/MemoryBankController1.hpp src/MemoryBus.hpp \
  src/cpu/InterruptController.hpp src/cpu/Timer.hpp src/LCDRegisters.hpp
src/Gameboy.hpp:
src/MemoryBus.hpp:
src/cpu/InterruptController.hpp:
src/cpu/Timer.hpp:
src/LCDRegisters.hpp:
src/$(OBJECT_DIR)/main.o: src/main.cpp src/Gameboy.hpp \
  src/AMemoryBankController.hpp src/Fwd.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/IReadWrite.hpp src/Debugger.hpp
src/$(OBJECT_DIR)/MemoryBus.o: src/MemoryBus.cpp src/MemoryBus.hpp \
  src/Fwd.hpp src/IReadWrite.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/AMemoryBankController.hpp \
  src/cpu/Core.hpp utils/Operations_utils.hpp \
  src/cpu/InterruptController.hpp src/cpu/Timer.hpp src/LCDRegisters.hpp
src/$(OBJECT_DIR)/PPU.class.o: src/PPU.class.cpp src/PPU.class.h \
  src/ScreenOutput.class.h src/Fwd.hpp src/Gameboy.hpp \
  src/AMemoryBankController.hpp src/cpu/Core.hpp \
  utils/Operations_utils.hpp src/IReadWrite.hpp src/Debugger.hpp \
  src/MemoryBus.hpp
src/PPU.class.h:
src/ScreenOutput.class.h:
src/$(OBJECT_DIR)/ScreenOutput.class.o: src/ScreenOutput.class.cpp \
  src/ScreenOutput.class.h
