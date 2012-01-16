#ifndef _util_h
#define _util_h

typedef void (*on_entry_cb)(char *path, struct dirent *ep, void* data);
void traverse_directory(char *path, on_entry_cb entry_cb, void *data);

char *str_concat(char *str1, char *str2);
char *join_path(char *str1, char *str2);

#endif
