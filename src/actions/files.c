#include <stdint.h>
#include <json/json.h>

#include "files.h"
#include "../data_access/uploads_list.h"

void action_list_files(http_request* request, http_response *response) {
  uploads_list* list = uploads_list_init(request->configuration->uploads_root);
  char *serialized_json = uploads_list_to_json(list);

  render_json(response, serialized_json);

  free(serialized_json);
  uploads_list_free(list);
}
