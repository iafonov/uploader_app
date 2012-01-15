OBJ = util.o         \
			uploader_app.o \
			uploads_list.o \

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