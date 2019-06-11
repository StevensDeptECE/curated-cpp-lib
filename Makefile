MAIN	:= ${CURDIR}

all:
	cd openssl-1.1.1c ; make ; cp *.a $(MAIN)/libs
	cd bzip2-1.0.6; make ; cp *.a $(MAIN)/libs
	echo ${CURDIR}
	cd FLIF/src ; make libflif.a ; cp *.o $(MAIN)/objs/FLIF ; cp *.a $(MAIN)/libs
	cd freetype-2.9 ; make ; cp objs/*.o $(MAIN)/objs/freetype ; cp objs/*.a $(MAIN)/libs
