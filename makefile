CURDIR=$(shell pwd)
SRCDIR=$(CURDIR)
HRC=$(wildcard $(SRCDIR)/*.h)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OUT=a.out
IMG=test.ppm
CC=g++

$(OUT): $(HRC) $(SRC)
	$(CC) $(SRC) -o a.out

run: $(OUT)
	./$(OUT)

$(IMG): $(OUT)
	./$(OUT) > $(IMG)

img: $(IMG)
	

tags: $(HRC) $(SRC)
	ctags $(SRC)

