#
# **************************************************************
# *                Simple C++ Makefile Template                *
# *                                                            *
# * Author: Arash Partow (2003)                                *
# * URL: http://www.partow.net/programming/makefile/index.html *
# *                                                            *
# * Copyright notice:                                          *
# * Free use of this C++ Makefile template is permitted under  *
# * the guidelines and in accordance with the the MIT License  *
# * http://www.opensource.org/licenses/MIT                     *
# *                                                            *
# **************************************************************
#

CXX      := g++
# CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -O2 -std=c++11 -Wall -Wextra -Wcast-align -Wconversion -Werror -Wmaybe-uninitialized -m64 $(INCLUDE)
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lpthread -lquadmath
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := main
INCLUDE  := -I ./include/module1/ \
            -I ./include/module2/ \
            -I ./include/ \

SRC1  	= ./src/module1
SRC2  	= ./src/module2
SRCMAIN = ./src

SRC      :=                      \
   $(wildcard $(SRC1)/*.cpp) \
   $(wildcard $(SRC2)/*.cpp) \
   $(wildcard $(SRCMAIN)/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
