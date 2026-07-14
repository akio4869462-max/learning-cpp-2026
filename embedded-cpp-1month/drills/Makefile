# 使い方:
#   make drill01 && ./drill01     1本だけビルドして実行
#   make all                      全部ビルド
#   make run                      全部ビルドして順に実行(FAILがあると途中で止まる)
#   make drill03 ASAN=1           サニタイザ付きビルド(メモリ検査)
#   make clean

CFLAGS   := -Wall -Wextra -Wconversion -g -std=c11
CXXFLAGS := -Wall -Wextra -Wconversion -g -std=c++17

ifdef ASAN
  CFLAGS   += -fsanitize=address,undefined
  CXXFLAGS += -fsanitize=address,undefined
endif

C_DRILLS   := drill01_bits drill02_pointers drill03_memory drill04_struct
CXX_DRILLS := drill05_class drill06_polymorphism drill07_stl \
              drill08_ringbuf drill09_fsm drill10_crc_debounce

SHORT_C    := drill01 drill02 drill03 drill04
SHORT_CXX  := drill05 drill06 drill07 drill08 drill09 drill10

all: $(C_DRILLS) $(CXX_DRILLS)

# 短い名前(make drill01)でもフルネームでもビルドできるように
drill01: drill01_bits
drill02: drill02_pointers
drill03: drill03_memory
drill04: drill04_struct
drill05: drill05_class
drill06: drill06_polymorphism
drill07: drill07_stl
drill08: drill08_ringbuf
drill09: drill09_fsm
drill10: drill10_crc_debounce
	@true

$(C_DRILLS): %: %.c
	$(CC) $(CFLAGS) -o $@ $<
	@ln -sf $@ $(word 1,$(subst _, ,$@))

$(CXX_DRILLS): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
	@ln -sf $@ $(word 1,$(subst _, ,$@))

run: all
	@set -e; for d in $(C_DRILLS) $(CXX_DRILLS); do \
		echo "==== $$d ===="; ./$$d; echo; \
	done

clean:
	rm -f $(C_DRILLS) $(CXX_DRILLS) $(SHORT_C) $(SHORT_CXX)

.PHONY: all run clean $(SHORT_C) $(SHORT_CXX)
