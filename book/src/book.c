// book.c - Print file contents
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
} flags;

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./book [flags] <filename>");
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help     Display this help message");
  println(STDOUT, "  -v --version  Display version info");
}

// Display version info
void displayVersion() {
  println(STDOUT, "book v1.0.0");
}

// String compare wrapper using noblelib
int strEq(const char *a, const char *b) {
  return stringCompare(a, b) == 0;
}

// Search argv and return flags
flags findFlags(int argc, char **argv, int *fileIndex) {
  flags flagData = {0, 0}; // Initialize all flags to 0
  *fileIndex = -1;

  for (int i = 1; i < argc; i++) {
    if (strEq(argv[i], "-h") || strEq(argv[i], "--help")) {
      flagData.helpFlag = 1;
    } else if (strEq(argv[i], "-v") || strEq(argv[i], "--version")) {
      flagData.versionFlag = 1;
    } else {
      *fileIndex = i; // First non-flag argument is the message
      break;
    }
  }

  return flagData;
}

// Entry point
void main(int argc, char **argv) {
    if (argc < 2) {
        displayUsage();
        exit(1);
    }

    int fileIndex = -1;
    flags flagData = findFlags(argc, argv, &fileIndex);

    if (flagData.helpFlag) {
        displayUsage();
        exit(0);
    }

    if (flagData.versionFlag) {
        displayVersion();
        exit(0);
    }

    if (fileIndex == -1) {
        println(STDERR, "Error: No filename provided.");
        displayUsage();
        exit(1);
    }

    // Open the file
    long fd = open(argv[fileIndex], 0, 0);
    if (fd < 0) {
        println(STDERR, "Error: Unable to open file.");
        exit(1);
    }

    // Read and print file contents
    char buffer[16384];
    long n;
    while ((n = fgets(buffer, sizeof(buffer), fd)) > 0) {
        print(STDOUT, buffer);
    }

    close(fd);
    exit(0);
}
