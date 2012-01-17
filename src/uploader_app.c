#include "uploader_app.h"

#include "actions/upload.h"
#include "actions/status.h"
#include "actions/files.h"

void action_index(http_request* request, http_response *response) {
  render_file(response, "index.html");
}

void configure() {
  mount("/", action_index);

  mount("/files/new/(:upload_id)", action_upload)->before_filter = before_upload_filter;
  mount("/files/status/(:upload_id)", action_status);
  mount("/files.json", action_list_files);
}

int main(int argc, char *argv[]) {
  return cosmonaut_start(argc, argv, configure);
}
