all: libs/libogg.a libs/libvorbis.a


libs/libogg.a:
	cd libogg-1.3.3 ; make ; cp src/.libs/libogg.a ../libs

libs/libvorbis.a:
	cd libvorbis-1.3.6 ; make ; cp lib/.libs/libvorbis.a ../libs
