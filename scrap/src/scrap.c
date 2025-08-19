// scrap.c - Delete a file by unlinking from filesystem
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
  short recursiveFlag;
} flags;

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./talk [flags] <path>");
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help      Display this help message");
  println(STDOUT, "  -v --version   Display version info");
  println(STDOUT, "  -r --recursive Delete directory recursively");
}

// Display version info
void displayVersion() {
  println(STDOUT, "talk v1.0.0");
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
    } else if (strEq(argv[i], "-r") || strEq(argv[i], "--recursive")) {
      flagData.recursiveFlag = 1;
    } else {
      *pathIndex = i; // First non-flag argument is the path
      break;
    }
  }

  return flagData;
}

// Delete a directories contents recursively and then unlink the directory
void deleteRecursive(const char *path) {
  long fd = open(path, O_RDONLY | O_DIRECTORY, 0);

  if (fd < 0) {
    // Not a directory, attempt to unlink as file
    deletefd(path);
    return;
  }

  char buffer[1024];
  linuxDirent *d;
  long nread;

  while ((nread = getdents(fd, (linuxDirent *)buffer, sizeof(buffer))) > 0) {
    long bpos = 0;

    while (bpos < nread) {
      d = (linuxDirent *)(buffer + bpos);
      char *name = d->d_name;

      // Skip "." and ".."
      if ((stringCompare(name, ".") == 0) || (stringCompare(name, "..") == 0)) {
        bpos += d->d_reclen;
        continue;
      }

      // Build full path using noblelib strlen
      char fullPath[512];
      long i = 0, j = 0;
      long pathLen = strlen(path);
      long nameLen = strlen(name);

      // Copy path to fullPath
      while (i < pathLen) {
        fullPath[i] = path[i];
        i++;
      }

      // Add '/' if path does not end with it
      if (i > 0 && path[i - 1] != '/') {
        fullPath[i++] = '/';
      }

      // Append name
      while (j < nameLen) {
        fullPath[i++] = name[j++];
      }

      fullPath[i] = '\0';  // Null-terminate

      // Recursive call
      deleteRecursive(fullPath);

      bpos += d->d_reclen;
    }
  }

  close(fd);

  // Remove the empty directory
  deletefd(path);
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
    println(STDERR, "Error: No path provided.");
    displayUsage();
    exit(1);
  }

  // Check if recursive flag was set
  if (flagData.recursiveFlag) {
    deleteRecursive(argv[pathIndex]);
    exit(0);
  }

  // Unlink the provided path
  deletefd(argv[pathIndex]);

  exit(0);
}
