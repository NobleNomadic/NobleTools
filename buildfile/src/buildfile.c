// buildfile.c - Create a new file
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
} flags;

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./buildfile [flags] <message>");
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help     Display this help message");
  println(STDOUT, "  -v --version  Display version info");
}

// Display version info
void displayVersion() {
  println(STDOUT, "buildfile v1.0.0");
}

// String compare wrapper using noblelib
int strEq(const char *a, const char *b) {
  return stringCompare(a, b) == 0;
}

// Search argv and return flags
flags findFlags(int argc, char **argv, int *pathIndex) {
  flags flagData = {0, 0}; // Initialize all flags to 0
  *pathIndex = -1;

  for (int i = 1; i < argc; i++) {
    if (strEq(argv[i], "-h") || strEq(argv[i], "--help")) {
      flagData.helpFlag = 1;
    } else if (strEq(argv[i], "-v") || strEq(argv[i], "--version")) {
      flagData.versionFlag = 1;
    } else {
      *pathIndex = i; // First non-flag argument is the filename 
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

  int pathIndex = -1;
  flags flagData = findFlags(argc, argv, &pathIndex);

  // Check if help flag was set
  if (flagData.helpFlag) {
    displayUsage();
    exit(0);
  }

  // Check if version flag was set
  if (flagData.versionFlag) {
    displayVersion();
    exit(0);
  }

  if (pathIndex == -1) {
    println(STDERR, "Error: No filename provided.");
    displayUsage();
    exit(1);
  }

  // Open a file with the filename provided
  int newFileFD = open(argv[pathIndex], O_WRONLY | O_CREAT | O_EXCL, 0644); 
  close(newFileFD);

  exit(0);
}
