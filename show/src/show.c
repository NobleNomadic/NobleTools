// show.c - Display contents of a directory
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
} flags;

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./show"); 
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help     Display this help message");
  println(STDOUT, "  -v --version  Display version info");
}

// Display version info
void displayVersion() {
  println(STDOUT, "show v1.0.0");
}

// String compare wrapper using noblelib
int strEq(const char *a, const char *b) {
  return stringCompare(a, b) == 0;
}

// Search argv and return flags
flags findFlags(int argc, char **argv) {
  flags flagData = {0, 0}; // Initialize all flags to 0

  for (int i = 1; i < argc; i++) {
    if (strEq(argv[i], "-h") || strEq(argv[i], "--help")) {
      flagData.helpFlag = 1;
    } else if (strEq(argv[i], "-v") || strEq(argv[i], "--version")) {
      flagData.versionFlag = 1;
    } 
  }

  return flagData;
}

// Entry point
void main(int argc, char **argv) {
  flags flagData = findFlags(argc, argv);

  // Handle help and version flags
  if (flagData.helpFlag) {
    displayUsage();
    exit(0);
  }

  if (flagData.versionFlag) {
    displayVersion();
    exit(0);
  }

  // Buffer to store directory entries
  char buffer[4096];

  // Open current directory
  long dirFd = open(".", 0, 0);
  if (dirFd < 0) {
    println(STDERR, "Failed to open directory.");
    exit(1);
  }

  // Read directory entries
  long bytesRead = getdents(dirFd, (linuxDirent *)buffer, sizeof(buffer));
  if (bytesRead < 0) {
    println(STDERR, "Failed to read directory entries.");
    close(dirFd);
    exit(1);
  }

  long pos = 0;
  while (pos < bytesRead) {
    linuxDirent *d = (linuxDirent *)(buffer + pos);
    println(STDOUT, d->d_name);  // Print the name of the entry
    pos += d->d_reclen;          // Move to the next entry
  }

  close(dirFd);
  exit(0);
}

