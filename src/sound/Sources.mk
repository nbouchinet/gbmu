## Auto generated make tool, don't edit manually.

OBJ_FILES_src/sound := APU.o \
                       ModulationUnits.o \
                       PortAudioInterface.o \
                       SoundChannel.o \
                       SquareChannel.o

OBJECTS += $(patsubst %, src/sound/$(OBJECT_DIR)/%, $(OBJ_FILES_src/sound))