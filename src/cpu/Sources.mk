## Auto generated make tool, don't edit manually.

OBJ_FILES_src/cpu := Core.o \
                     InterruptController.o \
                     Timer.o

OBJECTS += $(patsubst %, src/cpu/$(OBJECT_DIR)/%, $(OBJ_FILES_src/cpu))