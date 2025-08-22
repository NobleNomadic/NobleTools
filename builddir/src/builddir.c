/*
 * NobleTools - Command line tools made with NobleLib
 *
 * Copyright (C) 2025 NobleNomadic
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
*/
// builddir.c - Create new directory
#include "../../lib/noblelib.h"

// Store what flags are enabled during a run of the program
typedef struct {
  short versionFlag;
  short helpFlag;
} flags;

// Print help message
void displayUsage() {
  println(STDOUT, "Usage: ./builddir [flags] <directory name>");
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help     Display this help message");
  println(STDOUT, "  -v --version  Display version info");
}

// Display version info
void displayVersion() {
  println(STDOUT, "builddir v1.0.0");
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
      *pathIndex = i; // First non-flag argument is the directoy name
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
    println(STDERR, "Error: No directory name provided.");
    displayUsage();
    exit(1);
  }

  // Make the drectory with the provided path
  mkdir(argv[pathIndex], 0777);

  exit(0);
}
