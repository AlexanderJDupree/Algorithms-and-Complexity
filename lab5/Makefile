# File: makefile
# Description: Basic makefile for automated builds
# Author: Alexander DuPree

ifndef config
  config=release
endif

CC := gcc
CFLAGS := -Wall #-Werror

ifeq ($(config), release)
CFLAGS += -O3
endif

ifeq ($(config), debug)
CFLAGS += -g
endif

SRC := dupree_a_lab5.c
TARGET := lab5

TARGET: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

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
