
CC       := gcc
CXX      := g++

OBJDIR              := obj
OSCODE              := $(shell lsb_release -sc)
BINDIR              := bin-$(OSCODE)

INCDIR              :=
INCDIR              += main/inc
INCDIR              += module1/inc
INCDIR              += module2/inc
INCDIR              += module3/inc

SRCDIR              := main/src
SRC1DIR             := module1/src
SRC2DIR             := module2/src
SRC3DIR             := module3/src

SRC_SRCS            := $(wildcard $(SRCDIR)/*.cpp)
SRC1_SRCS           := $(wildcard $(SRC1DIR)/*.cpp)
SRC2_SRCS           := $(wildcard $(SRC2DIR)/*.cpp)
SRC3_SRCS           := $(wildcard $(SRC3DIR)/*.c)

SRC_OBJS            := $(SRC_SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
SRC1_OBJS           := $(SRC1_SRCS:$(SRC1DIR)/%.cpp=$(OBJDIR)/%.o)
SRC2_OBJS           := $(SRC2_SRCS:$(SRC2DIR)/%.cpp=$(OBJDIR)/%.o)
SRC3_OBJS           := $(SRC3_SRCS:$(SRC3DIR)/%.c=$(OBJDIR)/%.o)

MAIN_APP            := $(BINDIR)/Main
MAIN_SRCS           := $(SRCDIR)/program.cpp
MAIN_SRCS           += $(SRC1DIR)/mod1c1.cpp
MAIN_SRCS           += $(SRC1DIR)/mod1c2.cpp
MAIN_SRCS           += $(SRC2DIR)/mod2c1.cpp
MAIN_SRCS           += $(SRC2DIR)/mod2c2.cpp
MAIN_SRCS           += $(SRC3DIR)/mod3c1.c
MAIN_SRCS           += $(SRC3DIR)/mod3c2.c

MAIN_OBJS           := $(MAIN_SRCS)
MAIN_OBJS           := $(patsubst $(SRC1DIR)/%,$(OBJDIR)/%,$(MAIN_OBJS:.cpp=.o))
MAIN_OBJS           := $(patsubst $(SRC2DIR)/%,$(OBJDIR)/%,$(MAIN_OBJS:.cpp=.o))
MAIN_OBJS           := $(patsubst $(SRC3DIR)/%,$(OBJDIR)/%,$(MAIN_OBJS:.c=.o))

MAIN_OBJS           := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(MAIN_OBJS:.cpp=.o))

CFLAGS              :=
CFLAGS              += $(INCDIR:%=-I%)
CFLAGS              += -Wextra
CFLAGS              += -Wcast-align
CFLAGS              += -Wconversion
CFLAGS              += -Werror
CFLAGS              += -Wmaybe-uninitialized
CFLAGS              += -m64
CFLAGS              += -fprofile-arcs
CFLAGS              += -ftest-coverage
CFLAGS              += -g
CFLAGS              += -O0
CFLAGS              += -Wall

CXXFLAGS			:= $(CFLAGS)
CXXFLAGS            += -std=c++11

LDFLAGS 			:=
LDFLAGS				+= -lstdc++
LDFLAGS				+= -lm
LDFLAGS				+= -lpthread
LDFLAGS             += -lquadmath
LDFLAGS             += -lgcov --coverage

.PHONY: directories

all: directories $(MAIN_APP)

$(MAIN_APP): $(MAIN_OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

$(SRC_OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC1_OBJS): $(OBJDIR)/%.o : $(SRC1DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC2_OBJS): $(OBJDIR)/%.o : $(SRC2DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRC3_OBJS): $(OBJDIR)/%.o : $(SRC3DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(BINDIR) $(OBJDIR)

clean:
	rm -fr $(MAIN_APP) $(OBJDIR)

