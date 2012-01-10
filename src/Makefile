all: uploader_app

start:
	./uploader_app --config ../config/uploader_app.conf

uploader_app: uploader_app.o
	$(CC) -o $@ $(CCOPT) $(DEBUG) $(LDFLAGS) -lcosmonaut $<

clean:
	rm -f uploader_app
	rm -f *.o