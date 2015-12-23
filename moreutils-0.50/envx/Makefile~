CC=gcc
PREFIX=/usr/local
LIBDIR=$(PREFIX)/lib
INCLUDEDIR=/usr/local/include

all: pwdx envx

pwdx: pwdx.c liblab.so
	#$(CC) -o pwdx pwdx.c -llab -L $(LIBDIR)
	$(CC) -o pwdx pwdx.c liblab.so
	strip pwdx

envx: envx.c liblab.so
	#$(CC) -o envx envx.c -llab -L $(LIBDIR)
	$(CC) -o envx envx.c liblab.so
	strip envx


#.c.o: 
#	$(CC) -fPIC -c -o $@ $<

#liblab.so: pwdxlib.o envxlib.o
liblab.so: lab2.o
	#$(CC) -shared -o liblab.so pwdxlib.o envxlib.o
	$(CC) -shared -o liblab.so lab2.o
	strip liblab.so

lab2.o: lib/lab2.c
	$(CC) -fPIC -c -o $@ lib/lab2.c

amiroot:
	@[ `id -u` -eq 0 ] || { echo "You mast be ROOT, make sudu <target> install-lib"; exit 1; }

install-lib: liblab.so amiroot 
	mkdir -p $(LIBDIR) $(INCLUDEDIR)
	install liblab.so $(LIBDIR) 
	ldconfig
	
uninstall-lib: amiroot
	rm -f $(LIBDIR)/liblab.so
	
clean:
	rm -f *.so *.o
