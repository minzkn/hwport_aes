###
### Copyright (C) HWPORT.COM
### All rights reserved.
### Author: JAEHYUK CHO <mailto:minzkn@minzkn.com>
###

CROSS_COMPILE                ?=#

CC                           :=$(CROSS_COMPILE)gcc#
LD                           :=$(CROSS_COMPILE)ld#
STRIP                        :=$(CROSS_COMPILE)strip#
RM                           :=rm -f#
AR                           :=$(CROSS_COMPILE)ar#

CFLAGS                       :=#
CFLAGS                       +=-Os#
CFLAGS                       +=-pipe#
CFLAGS                       +=-fPIC#
CFLAGS                       +=-fomit-frame-pointer#
CFLAGS                       +=-ansi#
CFLAGS                       +=-Wall -W#
CFLAGS                       +=-Wshadow#
CFLAGS                       +=-Wcast-qual#
CFLAGS                       +=-Wcast-align#
CFLAGS                       +=-Wpointer-arith#
CFLAGS                       +=-Wbad-function-cast#
CFLAGS                       +=-Wstrict-prototypes#
CFLAGS                       +=-Wmissing-prototypes#
CFLAGS                       +=-Wmissing-declarations#
CFLAGS                       +=-Wnested-externs#
CFLAGS                       +=-Winline#
CFLAGS                       +=-Wwrite-strings#
CFLAGS                       +=-Wchar-subscripts#
CFLAGS                       +=-Wformat#
CFLAGS                       +=-Wformat-security#
CFLAGS                       +=-Wimplicit#
CFLAGS                       +=-Wmain#
CFLAGS                       +=-Wmissing-braces#
CFLAGS                       +=-Wnested-externs#
CFLAGS                       +=-Wparentheses#
CFLAGS                       +=-Wredundant-decls#
CFLAGS                       +=-Wreturn-type#
CFLAGS                       +=-Wsequence-point#
CFLAGS                       +=-Wsign-compare#
CFLAGS                       +=-Wswitch#
CFLAGS                       +=-Wuninitialized#
CFLAGS                       +=-Wunknown-pragmas#
CFLAGS                       +=-Wcomment#
CFLAGS                       +=-Wundef#
CFLAGS                       +=-Wunused#
CFLAGS                       +=-Wunreachable-code#
CFLAGS                       +=-Wconversion#
CFLAGS                       +=-Wpadded#

LDFLAGS                      :=-s#

ARFLAGS                      :=rcs#

TARGET                       :=hwport_aes libhwport_aes.so libhwport_aes.so.0 libhwport_aes.so.0.0.0 libhwport_aes.a libhwport_aes.lo#

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) *.o $(TARGET)

hwport_aes: main.o libhwport_aes.a
	$(CC) $(LDFLAGS) -o $(@) $(^)
	$(STRIP) --remove-section=.comment --remove-section=.note $(@)

libhwport_aes.so libhwport_aes.so.0: libhwport_aes.so.0.0.0
	ln -sf $(<) $(@)

libhwport_aes.so.0.0.0: libhwport_aes.lo
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$(notdir $(@)) -o $(@) $(^)
	$(STRIP) --remove-section=.comment --remove-section=.note $(@)

libhwport_aes.a: aes.o
	$(AR) $(ARFLAGS) $(@) $(^) 

libhwport_aes.lo: aes.o
	$(LD) $(LDFLAGS) -r -o $(@) $(^)

%.o: %.c makefile
	$(CC) $(CFLAGS) -c -o $(@) $(<)

# End of makefile
