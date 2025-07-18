CFLAGS=-g

######################################################################
# FILES:
#
#	Be very careful if you change the order of the files listed
# here.  if1632.o must linked first to guarrantee that it sits at a low
# enough address.  I intend to change this requirement someday, but
# for now live with it.
#
DLL_LENGTH=256

BUILDOBJS=dll_kernel.o dll_user.o dll_gdi.o dll_unixlib.o \
	  dll_kernel_tab.o dll_user_tab.o dll_gdi_tab.o dll_unixlib_tab.o

MUST_BE_LINKED_FIRST=if1632.o $(BUILDOBJS)

OBJS=$(MUST_BE_LINKED_FIRST) \
	dump.o heap.o ldt.o kernel.o relay.o selector.o user.o wine.o

TARGET=wine
LIBS=-lldt

all: $(TARGET) libldt.a

clean:
	rm -f *.o *~ *.s dll_*

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

build: build.c
	cc -g -o build build.c

libldt.a: ldtlib.c
	$(CC) -O6 -c ldtlib.c
	ar rcs libldt.a ldtlib.o

dll_kernel.S dll_kernel_tab.c: build kernel.spec
	build kernel.spec

dll_user.S dll_user_tab.c: build user.spec
	build user.spec

dll_gdi.S dll_gdi_tab.c: build gdi.spec
	build gdi.spec

dll_unixlib.S dll_unixlib_tab.c: build unixlib.spec
	build unixlib.spec
