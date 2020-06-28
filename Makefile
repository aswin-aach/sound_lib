TESTFILES = $(wildcard tests/*.c)
TESTOUTFILES = $(subst tests, out, $(TESTFILES:.c=.out))

LDFLAGS = -Lout -lsound -lm

all:	libsound.a

tests:	$(TESTOUTFILES)

out/%.out: libsound.a tests/%.c
	cc -o $@ -I. $(word 2,$^) $(LDFLAGS)

libsound.a:	soundlib.o
	ar rcvs out/libsound.a out/soundlib.o

soundlib.o:	out soundlib.c
	cc -o out/soundlib.o -Wall -pedantic -c soundlib.c

out:
	mkdir -p out

clean:
	rm -rf out

.PHONY: all clean tests
