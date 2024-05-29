SRC = $(wildcard src/*.c) $(wildcard src/arm7tdmi/*.c)

gcc:
	windres config.rc -O coff -o config.res
	gcc -Iinclude -Llib $(SRC) config.res -lmingw32 -lSDL2main -lSDL2 -lopengl32 -mavx -O2 -flto -DMAINLOOP_GL -o "emuboy gx.exe"
	del config.res

emcc:
	emcc -Iinclude $(SRC) -O3 -flto=full \
	-sUSE_SDL=2 \
	-sINVOKE_RUN=0 \
	-sTOTAL_MEMORY=128MB \
	--embed-file data/vba_bios.bin \
	-o website/emulator.js

codegen-thumb:
	gcc codegen/src/thumb.c -o codegen_thumb.exe
	codegen_thumb.exe src/arm7tdmi/thumb.c
	del codegen_thumb.exe

debug-compile:
	gcc -pg -no-pie -Iinclude -Llib $(SRC) -lmingw32 -lSDL2main -lSDL2 -lopengl32 -DMAINLOOP_GL -o "emuboy gx.exe"
	
debug-graph:
	gprof "emuboy gx.exe" | gprof2dot -n0 -e0 | dot -Tsvg -o graph.svg

.PHONY: gcc emcc codegen-thumb debug-compile debug-graph