/*
 * MIT License
 *
 * Copyright (c) 2021 Adam Salhi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <git/pull.h>
#include <git/push.h>
#include <new.h>

int main(int argc, char *argv[]) {
  char current_dir[100];
  const char *version = "ProMan v0.0.1";
  int temp = 0;

  if (argc == 1) {
    printf("ProMan v0.0.1\nMissing command-line args\n");
  } else if (argc == 2) {
    if (strcmp(argv[1], "init") == 0 &&
        getcwd(current_dir, sizeof(current_dir)) != NULL) {
      printf("+ Initializing new project in directory %s\n", current_dir);
    } else if (strcmp(argv[1], "new") == 0) {
      printf("Error: Command 'new' requires extra parameters.\n");
    } else if (strcmp(argv[1], "del") == 0) {
      printf("Error: Command 'del' requires extra parameters.\n");
    } else if (strcmp(argv[1], "push") == 0) {
      printf("Error: Command 'push' requires extra parameters.\n");
    } else if (strcmp(argv[1], "version") == 0) {
      printf("%s\n", version);
    } else {
      printf("Error: Unknown argument\n");
    }
  } else if (argc == 3) {
    if (strcmp(argv[1], "new") == 0 &&
        getcwd(current_dir, sizeof(current_dir)) != NULL) {
      printf("+ Creating new directory '%s' in %s\n", argv[2], current_dir);
      temp = new (argv[2], current_dir);
      if (temp) {
        printf("+ Done!\n");
      } else {
        printf("+ Error: Could not create project: '%s'\n", argv[2]);
      }
    } else if (strcmp(argv[1], "push") == 0 &&
               getcwd(current_dir, sizeof(current_dir)) != NULL) {
      printf("+ Pushing changes in directory '%s'\n", current_dir);
      temp = push(argv[2], current_dir);
      if (temp) {
        printf("+ Done!\n");
      } else {
        printf("+ Error: Could not push changes in directory: '%s'\n",
               current_dir);
      }
    } else if (strcmp(argv[1], "del") == 0 &&
               getcwd(current_dir, sizeof(current_dir)) != NULL) {
      printf("+ Deleting project '%s'\n", argv[2]);
    }
  }

  return 0;
}
