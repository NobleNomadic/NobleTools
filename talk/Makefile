# Compiler / Assembler
CC      = gcc
CFLAGS  = -nostdlib -nostartfiles -nodefaultlibs -fno-stack-protector -w -ffreestanding
LDFLAGS = -static
ASM     = nasm
ASFLAGS = -f elf64

# Paths
TARGET    = build/talk
C_SOURCES = src/talk.c ../lib/noblelib.c
ASM_SOURCE= ../lib/start.asm
ASM_OBJECT= build/start.o

# Default target
all: $(TARGET)

# Link everything
$(TARGET): $(C_SOURCES) $(ASM_OBJECT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	strip $(TARGET) 

# Assemble start.asm
$(ASM_OBJECT): $(ASM_SOURCE)
	$(ASM) $(ASFLAGS) $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with symbols
debug: CFLAGS += -g
debug: clean all

# Clean build artifacts
clean:
	rm -f $(TARGET) $(ASM_OBJECT)

