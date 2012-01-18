OBJ = uploader_app.o             \
			data_access/util.o         \
			data_access/uploads_list.o \
			data_access/redis.o        \
			actions/upload.o           \
			actions/status.o           \
			actions/files.o            \

OPTIMIZATION?=-O0
CFLAGS?=$(OPTIMIZATION) -g -Wall $(ARCH) $(PROF)
LDFLAGS?=-lcosmonaut -ljson -lhiredis

uploader_app: ${OBJ}

all: uploader_app

start:
	./uploader_app --config ../config/uploader_app.conf

valgrind:
	export LD_LIBRARY_PATH="/usr/local/lib" && valgrind --tool=memcheck --dsymutil=yes --leak-check=full --show-reachable=yes ./uploader_app --config ../config/uploader_app.conf

clean:
	rm -f uploader_app
	rm -f *.o