MAIN	:= ${CURDIR}
LIBDIR	:= $(MAIN)/libs
OBJS	:= $(MAIN)/objs


all:	openssl  bzip2 flif freetype libogg.a libvorbis.a


openssl:
	cd openssl-1.1.1c ; make ; ls *.a ; cp *.a $(LIBDIR)

bzip2:
	cd bzip2-1.0.6; make ; cp *.a $(LIBDIR)/libs

flif:
	cd FLIF/src ; make libflif.a ; \
	cp *.o $(OBJS)/FLIF ; cp *.a $(LIBDIR)/libs
freetype:
	cd freetype-2.9 ; make ; \
	cp objs/*.o $(OBJS)/freetype ; cp objs/*.a $(LIBDIR)/libs

libogg.a:
	cd libogg-1.3.3 ; make ; cp src/.libs/libogg.a $(LIBDIR)/libs

libvorbis.a:
	cd libvorbis-1.3.6 ; make ; cp lib/.libs/libvorbis.a $(LIBDIR)/libs

