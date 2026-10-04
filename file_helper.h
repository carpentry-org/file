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

int File_follow_stat(char** f) {
  struct stat st;

  if (stat(*f, &st) == -1) {
    return -1;
  }

  return st.st_mode;
}

uint64_t File_dir_dev(DIR* d) {
  struct stat st;

  if (fstat(dirfd(d), &st) == -1) {
    return 0;
  }

  return (uint64_t)st.st_dev;
}

uint64_t File_dir_ino(DIR* d) {
  struct stat st;

  if (fstat(dirfd(d), &st) == -1) {
    return 0;
  }

  return (uint64_t)st.st_ino;
}
