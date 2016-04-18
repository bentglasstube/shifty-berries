SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard content/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))

CC=clang++
CFLAGS=-g --std=c++14
CFLAGS+=-Wall -Wextra -Werror -pedantic
LDFLAGS=-static-libstdc++ -static-libgcc

LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer

EXECUTABLE=$(BUILDDIR)/shifty-berries

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(BUILDDIR)/src
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR)

video: ld35.mkv

ld35.mkv: ld35.glc ld35.wav
	glc-play $< -o - -y 1 |ffmpeg -i - -i ld35.wav -acodec flac -vcodec libx264 -y $@

ld35.wav: ld35.glc
	glc-play $< -a 1 -o $@

ld35.glc: $(EXECUTABLE)
	glc-capture -so $@ $(EXECUTABLE)

shifty-berries.tgz: $(EXECUTABLE)
	mkdir shifty-berries
	cp $(EXECUTABLE) README.md shifty-berries
	cp -R content shifty-berries/content
	tar zcf $@ shifty-berries
	rm -rf shifty-berries

.PHONY: all clean run video
