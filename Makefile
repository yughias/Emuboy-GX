SRC = $(wildcard src/*.c) $(wildcard src/arm7tdmi/*.c)

gcc:
	gcc -Iinclude -Llib $(SRC) -lmingw32 -lSDL2main -lSDL2 -lopengl32 -O2 -flto -DMAINLOOP_GL

emcc:
	emcc -Iinclude $(SRC) -O3 -flto=full \
	-sUSE_SDL=2 \
	-s TOTAL_MEMORY=1024MB \
	--embed-file gba_bios.bin \
	--embed-file rom.gba \
	-o index.html