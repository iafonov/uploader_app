#ifndef _upload_h
#define _upload_h

#include "../uploader_app.h"

void set_upload_progress_hook(http_request* request);
void action_upload(http_request* request, http_response *response);

#endif
