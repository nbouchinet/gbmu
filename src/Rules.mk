## Auto generated make tool, don't edit manually.
src/$(OBJECT_DIR)/%.o: src/%.cpp
	$(COMP) $@ $<
src/$(OBJECT_DIR)/Cartridge.o: src/Cartridge.cpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/AMemoryBankController.hpp \
  src/Fwd.hpp src/sound/Fwd.hpp src/IReadWrite.hpp \
  src/MemoryBankController2.hpp src/MemoryBankController3.hpp \
  src/RealTimeClock.hpp src/MemoryBankController5.hpp
src/Cartridge.hpp:
src/MemoryBankController1.hpp:
src/AMemoryBankController.hpp:
src/Fwd.hpp:
src/sound/Fwd.hpp:
src/IReadWrite.hpp:
src/MemoryBankController2.hpp:
src/MemoryBankController3.hpp:
src/RealTimeClock.hpp:
src/MemoryBankController5.hpp:
src/$(OBJECT_DIR)/Debugger.o: src/Debugger.cpp src/Debugger.hpp \
  src/cpu/Core.hpp src/Fwd.hpp src/sound/Fwd.hpp src/IReadWrite.hpp \
  utils/Operations_utils.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/AMemoryBankController.hpp \
  src/MemoryBus.hpp src/Gameboy.hpp src/PPU.hpp src/ScreenOutput.hpp \
  src/sound/APU.hpp src/sound/AudioInterface.hpp \
  src/sound/VolumeTable.hpp src/sound/portaudio/PortAudioInterface.hpp \
  src/cpu/InterruptController.hpp
src/Debugger.hpp:
src/cpu/Core.hpp:
utils/Operations_utils.hpp:
src/MemoryBus.hpp:
src/Gameboy.hpp:
src/PPU.hpp:
src/ScreenOutput.hpp:
src/sound/APU.hpp:
src/sound/AudioInterface.hpp:
src/sound/VolumeTable.hpp:
src/sound/portaudio/PortAudioInterface.hpp:
src/cpu/InterruptController.hpp:
src/$(OBJECT_DIR)/Gameboy.o: src/Gameboy.cpp src/Gameboy.hpp \
  src/cpu/Core.hpp src/Fwd.hpp src/sound/Fwd.hpp src/IReadWrite.hpp \
  utils/Operations_utils.hpp src/AMemoryBankController.hpp \
  src/Debugger.hpp src/Cartridge.hpp src/MemoryBankController1.hpp \
  src/MemoryBus.hpp src/PPU.hpp src/ScreenOutput.hpp src/sound/APU.hpp \
  src/sound/AudioInterface.hpp src/sound/VolumeTable.hpp \
  src/sound/portaudio/PortAudioInterface.hpp src/Bios.hpp \
  src/LCDRegisters.hpp src/UnitWorkingRAM.hpp \
  src/cpu/InputController.hpp src/cpu/InterruptController.hpp \
  src/cpu/Timer.hpp
src/Bios.hpp:
src/LCDRegisters.hpp:
src/UnitWorkingRAM.hpp:
src/cpu/InputController.hpp:
src/cpu/Timer.hpp:
src/$(OBJECT_DIR)/MemoryBus.o: src/MemoryBus.cpp src/MemoryBus.hpp \
  src/Fwd.hpp src/sound/Fwd.hpp src/IReadWrite.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/AMemoryBankController.hpp \
  src/Gameboy.hpp src/cpu/Core.hpp utils/Operations_utils.hpp \
  src/Debugger.hpp src/PPU.hpp src/ScreenOutput.hpp src/sound/APU.hpp \
  src/sound/AudioInterface.hpp src/sound/VolumeTable.hpp \
  src/sound/portaudio/PortAudioInterface.hpp src/LCDRegisters.hpp \
  src/UnitWorkingRAM.hpp src/cpu/InputController.hpp \
  src/cpu/InterruptController.hpp src/cpu/Timer.hpp src/Bios.hpp
src/$(OBJECT_DIR)/PPU.o: src/PPU.cpp src/PPU.hpp src/ScreenOutput.hpp \
  src/Fwd.hpp src/sound/Fwd.hpp src/IReadWrite.hpp src/Gameboy.hpp \
  src/cpu/Core.hpp utils/Operations_utils.hpp \
  src/AMemoryBankController.hpp src/Debugger.hpp src/Cartridge.hpp \
  src/MemoryBankController1.hpp src/MemoryBus.hpp src/sound/APU.hpp \
  src/sound/AudioInterface.hpp src/sound/VolumeTable.hpp \
  src/sound/portaudio/PortAudioInterface.hpp \
  src/cpu/InterruptController.hpp
src/$(OBJECT_DIR)/ScreenOutput.o: src/ScreenOutput.cpp \
  src/ScreenOutput.hpp
