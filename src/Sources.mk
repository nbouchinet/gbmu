## Auto generated make tool, don't edit manually.

OBJ_FILES_src := Cartridge.o \
                 Debugger.o \
                 Gameboy.o \
                 main.o \
                 MemoryBus.o \
                 PPU.class.o \
                 ScreenOutput.class.o

OBJECTS += $(patsubst %, src/$(OBJECT_DIR)/%, $(OBJ_FILES_src))