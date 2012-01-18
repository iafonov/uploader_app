#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <json/json.h>

#include <sys/stat.h>
#include "../log.h"
#include "util.h"
#include "uploads_list.h"

uploads_list* uploads_list_init(char *uploads_path) {
  uploads_list* result = malloc(sizeof(uploads_list));
  result->uploads_path = strdup(uploads_path);
  return result;
}

void uploads_list_free(uploads_list* l) {
  free(l->uploads_path);
  free(l);
}

static int file_size(char *folder_path, char *file_name) {
  struct stat st;
  char *path = join_path(folder_path, file_name);
  stat(path, &st);
  free(path);

  return st.st_size;
}

static void fill_json_file_entry(char *path, struct dirent *ep, void *data) {
  json_object* json_file_entry = (json_object*)data;
  char* url = join_path(path + strlen("../public/") , ep->d_name);
  int size = file_size(path, ep->d_name);

  json_object_object_add(json_file_entry, "name", json_object_new_string(ep->d_name));
  json_object_object_add(json_file_entry, "url", json_object_new_string(url));
  json_object_object_add(json_file_entry, "size", json_object_new_int(size));

  free(url);
}

static void fill_json_files_array(char *path, struct dirent *ep, void *data) {
  if (ep->d_type != DT_DIR) return;

  json_object* json_files_array = (json_object*)data;
  json_object* json_file_entry = json_object_new_object();

  char* folder_path = join_path(path, ep->d_name);

  traverse_directory(folder_path, fill_json_file_entry, json_file_entry);

  json_object_array_add(json_files_array, json_file_entry);

  free(folder_path);
}

const char* uploads_list_to_json(uploads_list *l) {
  json_object* json_result = json_object_new_object();
  json_object* json_files_array = json_object_new_array();

  traverse_directory(l->uploads_path, fill_json_files_array, json_files_array);

  json_object_object_add(json_result, "files", json_files_array);

  char *result = strdup(json_object_to_json_string(json_result));

  json_object_put(json_result);

  return json_object_to_json_string(json_result);
}