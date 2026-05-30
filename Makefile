CC := gcc
CCARGS := -lncurses -o pong

# Size-oriented flags
CCARGS := $(CCARGS) -m32 -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-exceptions -Os -fno-stack-protector -fno-math-errno -fmerge-all-constants -Wl,-z,norelro -Wl,--hash-style=gnu -Wl,--build-id=none
STRIPARGS := -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag
UPXARGS := --ultra-brute --no-lzma

all: pong

pong: pong.c
	$(CC) pong.c $(CCARGS)

	strip $(STRIPARGS) pong
	upx $(UPXARGS) pong

	@echo
	@echo "Size (in bytes):"
	@du -b pong

clean:
	-rm pong
