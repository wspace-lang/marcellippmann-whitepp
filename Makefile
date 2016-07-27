#******************************************************************************
#* This file is part of White++.                                              *
#*                                                                            *
#* Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
#* Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
#*                                                                            *
#******************************************************************************

SRCDIR      = src
BINDIR      = bin
INCLUDEDIR  = include
BUILDDIR    = build

CXX         = g++

CXXFLAGS   += -O3 -Wall -std=gnu++14 -I $(INCLUDEDIR) -c
LDFLAGS    +=


TARGET      = $(BINDIR)/White++
FILES       = $(wildcard $(SRCDIR)/*.cpp)
OBJ         = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(FILES:.cpp=.o))


VERBOSE    ?=

ifeq ($(VERBOSE),)
  ECHO    = @
  OUTPUT  = > /dev/null 2> /dev/null
else
  ECHO    =
  OUTPUT  =
endif


default all: $(TARGET)

$(TARGET): $(OBJ)
	$(ECHO) mkdir -p $(BINDIR)
	@echo " * Linking …"
	$(ECHO) $(CXX) $(LDFLAGS) $^ -o $@ $(OUTPUT)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(ECHO) mkdir -p $(BUILDDIR)
	@echo " * Building $< …"
	$(ECHO) $(CXX) $(CXXFLAGS) -o $@ $< $(OUTPUT)

cl clean:
	@echo " * Cleaning up …"
	$(ECHO) rm -rf $(BINDIR) $(BUILDDIR)
