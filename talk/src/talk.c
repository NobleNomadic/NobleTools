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
  println(STDOUT, "Flags:");
  println(STDOUT, "  -h --help     Display this help message");
  println(STDOUT, "  -v --version  Display version info");
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
flags findFlags(int argc, char **argv, int *messageIndex) {
  flags flagData = {0, 0}; // Initialize all flags to 0
  *messageIndex = -1;

  for (int i = 1; i < argc; i++) {
    if (strEq(argv[i], "-h") || strEq(argv[i], "--help")) {
      flagData.helpFlag = 1;
    } else if (strEq(argv[i], "-v") || strEq(argv[i], "--version")) {
      flagData.versionFlag = 1;
    } else {
      *messageIndex = i; // First non-flag argument is the message
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

  int messageIndex = -1;
  flags flagData = findFlags(argc, argv, &messageIndex);

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

  if (messageIndex == -1) {
    println(STDERR, "Error: No message provided.");
    displayUsage();
    exit(1);
  }

  println(STDOUT, argv[messageIndex]);
  exit(0);
}
