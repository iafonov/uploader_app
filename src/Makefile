OBJ = uploader_app.o             \
			data_access/util.o         \
			data_access/uploads_list.o \
			actions/upload.o           \
			actions/status.o           \
			actions/files.o            \

OPTIMIZATION?=-O0
CFLAGS?=$(OPTIMIZATION) -Wall $(ARCH) $(PROF)
LDFLAGS?=-lcosmonaut -ljson -lhiredis

uploader_app: ${OBJ}

all: uploader_app

start:
	./uploader_app --config ../config/uploader_app.conf

clean:
	rm -f uploader_app
	rm -f *.o