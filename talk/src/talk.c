// talk.c - Echo a message
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
} flags; 

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./talk [flags] <message>");
  println(STDOUT, "Flags: ");
  println(STDOUT, "-h --help: Display this");
  println(STDOUT, "-v --version: Get version info");
  return;
}

// Search argv and return flags
flags findFlags() {
  flags flagData;
  return flagData;
}

// Entry function
void main(int argc, char **argv) {
  // Check usage
  if (argc < 2) {
    displayUsage();
    exit(1);
  }

  // Get argument and print
  println(STDOUT, argv[1]);

  exit(0);
}
