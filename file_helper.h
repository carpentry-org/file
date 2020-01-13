/*
  the following code is based on https://rosettacode.org/wiki/Walk_a_directory/Recursively#C,
  modified by Nat Quayle Nelson (natquaylenelson@gmail.com) and Veit Heller
  (veit@veitheller.de) to work nicely with Carp.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <err.h>

enum {
  WALK_OK = 0,
  WALK_NAMETOOLONG,
  WALK_CANTOPEN,
  WALK_CANTSTAT,
  WALK_BADIO
};
 
#define WS_NONE    0
#define WS_RECURSIVE  (1 << 0)
#define WS_FOLLOWLINK  (1 << 1)  /* follow symlinks */
#define WS_DOTFILES  (1 << 2)  /* per unix convention, .file is hidden */
#define WS_MATCHDIRS  (1 << 3)  /* if pattern is used on dir names too */

int walk_recur(String dname, void (*operation)(String), int spec) {
  struct dirent *dent;
  DIR *dir;
  struct stat st;
  char fn[FILENAME_MAX];
  int res = WALK_OK;
  int len = strlen(dname);

  if (len >= FILENAME_MAX - 1) return WALK_NAMETOOLONG;

  strcpy(fn, dname);
  fn[len++] = '/';
 
  if (!(dir = opendir(dname))) return WALK_CANTOPEN;
 
  errno = 0;
  while ((dent = readdir(dir))) {
    if (!(spec & WS_DOTFILES) && dent->d_name[0] == '.')
      continue;
    if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
      continue;
 
    strncpy(fn + len, dent->d_name, FILENAME_MAX - len);
    if (lstat(fn, &st) == -1) {
      res = WALK_CANTSTAT;
      continue;
    }
 
    /* don't follow symlink unless told so */
    if (S_ISLNK(st.st_mode) && !(spec & WS_FOLLOWLINK)) continue;
 
    /* will be false for symlinked dirs */
    if (S_ISDIR(st.st_mode)) {
      /* recursively follow dirs */
      if ((spec & WS_RECURSIVE)) walk_recur(fn, operation, spec);
 
      if (!(spec & WS_MATCHDIRS)) continue;
    }

    char* for_carp = malloc(FILENAME_MAX);
    strcpy(for_carp, fn);
    (*operation)(for_carp);
  }
 
  if (dir) closedir(dir);
  return res ? res : errno ? WALK_BADIO : WALK_OK;
}

int walk_dir(String* dname, void (*operation)(String), int spec) {
  return walk_recur(*dname, operation, spec);
}
