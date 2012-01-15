#ifndef _uploads_list_h
#define _uploads_list_h

typedef struct uploads_list uploads_list;

struct uploads_list {
	char *uploads_path;
};

uploads_list* uploads_list_init(char *uploads_path);
void uploads_list_free(uploads_list* l);

const char* uploads_list_to_json(uploads_list *l);

#endif
