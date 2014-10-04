# pgutils makefile
# ================
# Copyright 2014 Paul Griffiths
# Email: paul@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Programs
SED := sed
MV  := mv -f
RM  := rm -f

# Objects, sources and libraries variables
library := libpgutils.a
sources := $(wildcard *.c)
objects  = $(subst .c,.o,$(sources))
depends  = $(subst .c,.d,$(sources))

mkfile_path := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
include_dir := $(mkfile_path)/include

# Compiler flags
CFLAGS           = -std=c99 -pedantic -Wall -Wextra -I$(include_dir)
C_DEBUG_FLAGS   := -ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS := -O3 -DNDEBUG

# Clean files and globs
CLNGLOB  = $(objects) $(libraries) $(depends) $(library)
CLNGLOB += *~ *.o *.gcov *.out *.gcda *.gcno

# Default target
default: debug

# Included modules
include src/module.mk
#include src/strings/module.mk

# Build targets section
# =====================

# debug - builds objects with debugging info
.PHONY: debug
debug: CFLAGS += $(C_DEBUG_FLAGS)
debug: all

# release - builds with optimizations and without debugging info
.PHONY: release
release: CFLAGS += $(C_RELEASE_FLAGS)
release: all

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@$(RM) $(CLNGLOB) 2>/dev/null

# docs - makes Doxygen documentation:
.PHONY: docs
docs:
	@doxygen
	-@cd latex; make; cd ..
	@if [ ! -d docs ]; then \
		mkdir docs; fi
	@echo "Copying reference manual to docs..."
	@cp latex/refman.pdf docs 
	@echo "Done."

# tags - makes tags file
.PHONY: tags
tags:
	@ctags *.c *.g


# Executable targets section
# ==========================

# Main executable
.PHONY: all
all: $(library)

$(library): $(objects)
	@echo "Building library..."
	$(AR) rcs $@ $^

# Dependencies
ifneq "$(MAKECMDGOALS)" "clean"
  -include $(depends)
endif

# Build for dependencies
%.d: %.c
	@echo "Building dependencies for $<..."
	@$(CC) $(CFLAGS) -M $< | \
		$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1: ,' > $@.tmp
	@$(MV) $@.tmp $@

