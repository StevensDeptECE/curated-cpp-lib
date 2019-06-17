MAIN	:= ${CURDIR}

all:	openssl # bzip2 flif freetype


openssl:
	cd openssl-1.1.1c ; make ; ls *.a ; echo "cp *.a $(MAIN)/libs"

bzip2:
	cd bzip2-1.0.6; make ; cp *.a $(MAIN)/libs

flif:
	cd FLIF/src ; make libflif.a ; cp *.o $(MAIN)/objs/FLIF ; cp *.a $(MAIN)/libs

freetype:
	cd freetype-2.9 ; make ; cp objs/*.o $(MAIN)/objs/freetype ; cp objs/*.a $(MAIN)/libs
