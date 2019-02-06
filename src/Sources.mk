## Auto generated make tool, don't edit manually.

OBJ_FILES_src := Cartridge.o \
                 Gameboy.o \
                 InterruptController.o \
                 main.o \
                 MemoryBus.o \
                 Timer.o

OBJECTS += $(patsubst %, src/$(OBJECT_DIR)/%, $(OBJ_FILES_src))