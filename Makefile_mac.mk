
# Template project MacOS Makefile

SRC_DIRS := .

# Use only CXX to compile all files

# Use find to gather all .cpp and .c files in SRC_DIRS
cpp_src := $(shell find $(SRC_DIRS) -name '*.cpp')

# Setup compilation options
CXXFLAGS = -Werror=unused-function -Wall -Wextra -Wpedantic -std=c++11 -DSYNC_PLAYER

# Extra compilation options
# #############################

# For Debugging
CXXFLAGS += -ggdb

CXXFLAGS += -DUFBX_REAL_IS_FLOAT

# For optimization
# CXXFLAGS += -O3

# ROCKET module

# Add rocket files
# on MacOS this confuses the linker by making each file
# in rocket/ to appear twice
#cpp_src += $(wildcard rocket/*.cpp)
ROCKET_INCLUDE = -Irocket/
CXXFLAGS += $(ROCKET_INCLUDE)
# The rocket code of library is compiled in SYNC_PLAYER mode
# CXX_FLAGS += -DSYNC_PLAYER

# ############################################
# MacOS specific settings

# Set Compiler
CXX = clang++
EXE_SUFFIX = .out
# Homebrew include directory
# This is for MacPorts. Alter to fit your system.
CXXFLAGS += -I/opt/local/include

# Create a list of libraries that need to be linked
LDFLAGS = -lmgdl -lpng -lsndfile -lopenal -Wno-unused-function

# MacOS need to tell to use OpenGL and GLUT instead of -lglut
LDFLAGS += -framework OpenGL -framework GLUT 

# Add MacPorts library path
LDFLAGS += -L/opt/local/lib

# Add mgdl library search directory and include
MGDL_DIR=$(HOME)/libmgdl
LDFLAGS += -L$(MGDL_DIR)
MGDL_INCLUDE = -I$(MGDL_DIR)


# Executable is the same name as current directory +
# platform specific postfix
TARGET	:=	$(notdir $(CURDIR))_mac.out

# ########################
# Common settings and targets

# Add them all to Compilation options
CXXFLAGS += $(MGDL_INCLUDE)

# Create a list of object files that make needs to
# process
OFILES	:= $(cpp_src:.cpp=.mo)

.PHONY: all

# When all OFILES have been processed, link them together
all : $(OFILES)
	$(CXX) $(OFILES) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

# Remove obj directory, all object files and the target
clean:
	@echo clean ...
	@rm -fr $(OFILES) $(TARGET)

# For any .cpp file, create a object file with the same
# name.
%.mo : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
