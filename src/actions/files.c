#include <json/json.h>

#include "files.h"
#include "../uploads_list.h"

void action_list_files(http_request* request, http_response *response) {
  uploads_list* list = uploads_list_init(request->configuration->uploads_root);

  render_json(response, uploads_list_to_json(list));

  uploads_list_free(list);
}
