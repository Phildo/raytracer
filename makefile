CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)
HRC    =$(wildcard $(SRCDIR)/*.h);
SRC    =$(wildcard $(SRCDIR)/*.cpp);
OUT    =a.out
IMG    =test.ppm

a.out: $(SRC) $(HRC)
	gcc $(SRC) -o a.out

run: $(OUT)
	./$(OUT)

$(IMG): $(OUT)
	./$(OUT) > $(IMG)

img: $(IMG)
	

tags: $(SRC) $(HRC)
	ctags $(SRC)

