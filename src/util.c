#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>

#include "util.h"

void traverse_directory(char *path, on_entry_cb entry_cb, void *data) {
  DIR *dir;
  struct dirent *dir_entry;
  dir = opendir(path);

  if (dir != NULL) {
    while((dir_entry = readdir(dir))) {
      if (dir_entry->d_name[0] != '.') { entry_cb(path, dir_entry, data); }
    }

    closedir(dir);
  } else {
    perror("Couldn't open the directory");
  }
}

char *join_path(char *str1, char *str2) {
  char* result = malloc(strlen(str1) + strlen("/") + strlen(str2));
  sprintf(result, "%s/%s", str1, str2);
  return result;
}

char *str_concat(char *str1, char *str2) {
  if (str1 == NULL) {
    return strdup(str2);
  }

  if (str2 == NULL) {
    return strdup(str1);
  }

  int len1 = strlen(str1), len2 = strlen(str2);
  char *result = malloc(strlen(str1) + strlen(str2) + 1);

  memcpy(result, str1, len1);
  memcpy(result + len1, str2, len2 + 1);

  return result;
}
