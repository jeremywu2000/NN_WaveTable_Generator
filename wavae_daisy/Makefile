# Project Name
TARGET = wavae_daisy

# Sources
CPP_SOURCES = wavae_daisy.cpp

# Library Locations
LIBDAISY_DIR = ../libDaisy/

######################################
# Cube_AI
######################################
CUBE_DIR = ../wavae_cube/

# source
CPP_SOURCES += network.cpp

# TODO replace with vae model
C_SOURCES =  \
$(CUBE_DIR)/X-CUBE-AI/App/vae.c \
$(CUBE_DIR)/X-CUBE-AI/App/vae_data.c \
$(CUBE_DIR)/X-CUBE-AI/App/vae_data_params.c \

C_INCLUDES =  \
-I$(CUBE_DIR)/Middlewares/ST/AI/Inc \
-I$(CUBE_DIR)/X-CUBE-AI/App \

# LDFLAGS
LIBS =  \
-l:NetworkRuntime730_CM7_GCC.a
LIBDIR =  \
-L$(CUBE_DIR)/Middlewares/ST/AI/Lib
######################################

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
