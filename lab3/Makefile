# File: makefile
# Description: Basic makefile for automated builds
# Author: Alexander DuPree

ifndef config
  config=release
endif

CC := gcc
CFLAGS := -Wall -Werror

ifeq ($(config), release)
CFLAGS += -O3
endif

ifeq ($(config), debug)
CFLAGS += -g
endif

LAB3A_SRC := dupree_a_lab3a.c
LAB3B_SRC := dupree_a_lab3b.c
PROJECTS := Lab3a Lab3b

all: $(PROJECTS)

Lab3a: $(LAB3A_SRC)
	$(CC) $(CFLAGS) -o lab_3a $(LAB3A_SRC)

Lab3b: $(LAB3B_SRC)
	$(CC) $(CFLAGS) -o lab_3b $(LAB3B_SRC)

.PHONEY: clean help run

run:
	./$(TARGET)

clean:
	@rm $(TARGET)

help:
	@echo "Usage: make [config=name]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "Use 'make run' to execute application"
