/*
  the following code is based on https://rosettacode.org/wiki/Walk_a_directory/Recursively#C,
  modified by Nat Quayle Nelson (natquaylenelson@gmail.com) and Veit Heller
  (veit@veitheller.de) to work nicely with Carp.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

typedef struct dirent DirEntry;

char* Dir_d_name(struct dirent* dent) {
  return dent->d_name;
}

int File_stat(char** f) {
  struct stat st;

  if (lstat(*f, &st) == -1) {
    return -1;
  }

  return st.st_mode;
}
