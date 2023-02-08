# Project Name
TARGET = wavae_daisy

# Sources
CPP_SOURCES = wavae_daisy.cpp

# Library Locations
LIBDAISY_DIR = ../libDaisy/
DAISYSP_DIR = ../DaisySP/

######################################
# Cube_AI
######################################
# source
CPP_SOURCES += network.cpp

C_SOURCES =  \
X-CUBE-AI/App/sine_model.c \
X-CUBE-AI/App/sine_model_data.c \
X-CUBE-AI/App/sine_model_data_params.c \

C_INCLUDES =  \
-IMiddlewares/ST/AI/Inc \
-IX-CUBE-AI/App \

# LDFLAGS
LIBS =  \
-l:NetworkRuntime730_CM7_GCC.a
LIBDIR =  \
-LMiddlewares/ST/AI/Lib
######################################

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
