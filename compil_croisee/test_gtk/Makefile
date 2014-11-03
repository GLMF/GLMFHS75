ARM_PREFIX=/home/yann/raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
#ARM_PREFIX=arm-linux-gnueabi-
CC = $(ARM_PREFIX)gcc
SRC += gtktest.c
TARGET = gtktest
 
LIBRARY += gtk-3 
LIBRARY += gdk-3 
LIBRARY += atk-1.0 
LIBRARY += gio-2.0 
LIBRARY += pangocairo-1.0 
LIBRARY += gdk_pixbuf-2.0 
LIBRARY += cairo-gobject 
LIBRARY += pango-1.0 
LIBRARY += cairo 
LIBRARY += gobject-2.0 
LIBRARY += glib-2.0 
LIBRARY += rt
LIBRARY += pcre
 
LIBRARYDIR += $(HOME)/raspberry/lib/arm-linux-gnueabihf
LIBRARYDIR += $(HOME)/raspberry/usr/lib/arm-linux-gnueabihf
LIBRARYDIR += $(HOME)/raspberry/lib
LIBRARYDIR += $(HOME)/raspberry/usr/lib
 
XLINK_LIBDIR += $(HOME)/raspberry/lib/arm-linux-gnueabihf
XLINK_LIBDIR += $(HOME)/raspberry/usr/lib/arm-linux-gnueabihf

 
INCLUDEDIR += $(HOME)/raspberry/usr/include/gtk-3.0 
INCLUDEDIR += $(HOME)/raspberry/usr/include/pango-1.0 
INCLUDEDIR += $(HOME)/raspberry/usr/include/gio-unix-2.0/ 
INCLUDEDIR += $(HOME)/raspberry/usr/include/atk-1.0 
INCLUDEDIR += $(HOME)/raspberry/usr/include/cairo
INCLUDEDIR += $(HOME)/raspberry/usr/include/gdk-pixbuf-2.0 
INCLUDEDIR += $(HOME)/raspberry/usr/include/freetype2
INCLUDEDIR += $(HOME)/raspberry/usr/include/glib-2.0 
INCLUDEDIR += $(HOME)/raspberry/usr/lib/arm-linux-gnueabihf/glib-2.0/include
INCLUDEDIR += $(HOME)/raspberry/usr/include/pixman-1
INCLUDEDIR += $(HOME)/raspberry/usr/include/libpng12
 
OPT = -O0
DEBUG = -g
WARN= -Wall 
PTHREAD= -pthread
 
INCDIR  = $(patsubst %,-I%,$(INCLUDEDIR))
LIBDIR  = $(patsubst %,-L%,$(LIBRARYDIR))
LIB    = $(patsubst %,-l%,$(LIBRARY))
XLINKDIR = $(patsubst %,-Xlinker -rpath-link=%,$(XLINK_LIBDIR))
 
all:
	$(CC) $(OPT) $(DEBUG) $(WARN) $(LIBDIR) $(PTHREAD) $(INCDIR) $(XLINKDIR) $(LIB) $(SRC) -o $(TARGET)
 
clean:
	rm -rf $(TARGET)
