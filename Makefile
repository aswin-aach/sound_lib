TESTFILES = $(wildcard tests/*.c)
TESTOUTFILES = $(subst tests, out, $(TESTFILES:.c=.out))

LDFLAGS = -Lout -lsound -lm

all:	autoformat out/libsound.a

tests:	$(TESTOUTFILES)

out/%.out: out/libsound.a tests/%.c
	cc -o $@ -I. -Wall $(word 2,$^) $(LDFLAGS)

out/libsound.a:	out/soundlib.o
	ar rcvs out/libsound.a out/soundlib.o

out/soundlib.o:	out soundlib.c
	cc -o out/soundlib.o -Wall -pedantic-errors -c soundlib.c

autoformat:
	-astyle -n --style=kr --align-pointer=name --recursive ./*.c,*.h

out:
	mkdir -p out

clean:
	rm -rf out

.PHONY: all clean tests autoformat
