# Configuration
CC := clang++
CPP_FILES := $(wildcard *.cpp)
LD_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CC_FLAGS := --std=c++14 -pthread -O3 -lX11
OUTNAME = app

# Make difference between x86 and arm
ifeq ($(shell uname -m), armv7l)
CC := $(CC)-6 -d
endif

# Clean at each compilation
.PHONY: clean

all: clean app

# Commands
clean:
	rm -f *.gch $(OUTNAME)

app:
	#$(CC) $(CPP_FILES) -o $(OUTNAME) $(LD_FLAGS) $(CC_FLAGS)
	swipl-ld -o $(OUTNAME) -ld clang++  $(CPP_FILES) $(LD_FLAGS) $(CC_FLAGS) rules.pl
