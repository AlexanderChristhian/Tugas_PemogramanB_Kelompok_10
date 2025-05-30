CC=gcc
CFLAGS=-Wall -lm
SRC_DIR=src
BIN_DIR=bin

# Detect OS
ifeq ($(OS),Windows_NT)
	EXE=.exe
	RM=del /Q
	MKDIR=mkdir
else
	EXE=
	RM=rm -f
	MKDIR=mkdir -p
endif

# Target executables
TARGETS=main$(EXE) dataset_generator$(EXE) break_even_analysis$(EXE)

all: $(TARGETS)

main$(EXE): $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -o $(SRC_DIR)/$@ $< -lm
dataset_generator$(EXE): $(SRC_DIR)/dataset_generator.c
	$(CC) $(CFLAGS) -o $(SRC_DIR)/$@ $< -lm
break_even_analysis$(EXE): $(SRC_DIR)/break_even_analysis.c
	$(CC) $(CFLAGS) -o $(SRC_DIR)/$@ $< -lm
clean:
	$(RM) $(SRC_DIR)/*$(EXE) $(SRC_DIR)/*.txt $(SRC_DIR)/*.gnu
.PHONY: all clean
