## Auto generated make tool, don't edit manually.

OBJ_FILES_src := Cartridge.o \
                 Debugger.o \
                 Gameboy.o \
                 MemoryBus.o \
                 PPU.o \
                 ScreenOutput.o

OBJECTS += $(patsubst %, src/$(OBJECT_DIR)/%, $(OBJ_FILES_src))