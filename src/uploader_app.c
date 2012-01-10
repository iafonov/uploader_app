#include "/usr/local/include/cosmonaut/cosmonaut.h"

void action_index(http_request* request, http_response *response) {
  render_file(response, "index.html");
}

void action_upload(http_request* request, http_response *response) {
  render_text(response, "uploaded");
}

void action_list_files(http_request* request, http_response *response) {
  render_json(response, "{\"files\": [            \
    {                                            \
      \"name\": \"file.png\",                    \
      \"url\": \"/RANDOM/file.png\",           \
      \"description\": \"This is cool file\"     \
    },                                           \
    {                                            \
      \"name\": \"another_file.png\",            \
      \"url\": \"/RANDOM/another_file.png\",   \
      \"description\": \"Another cool file\"     \
    }                                            \
  ]}");
}

void configure() {
  route("/", action_index);
  route("/upload", action_upload);
  route("/files.json", action_list_files);
}

int main(int argc, char *argv[]) {
  cosmonaut_start(argc, argv, configure);
}
