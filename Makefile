CC = gcc -std=c11
C_LIBS = -lm -lcheck -lpthread
CFLAGS =-Wall -Wextra -Werror -D _GNU_SOURCE
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
LOL = /Applications/Qt/6.2.4/macos/bin/qmake6

#ifeq ($(shell uname -s),Linux)
#	TEST_FLAGS += -lrt -lsubunit
#else ifeq ($(shell uname -s),Darwin)
#	C_LIBS += $(shell pkg-config --libs check)
#	CFLAGS += $(shell pkg-config --cflags check)
#endif

all: s21_smartcalc.a

install:
	mkdir build
	make && cd build && $(LOL) ../s21_calc && make
	open build/s21_calc.app

uninstall:
	rm -rf build

dvi:
	open ./html/index.html

dist:
	mkdir s21_smartcalc_archive
	cp Makefile $(SOURCES) Tests/* s21_calc/* *.h s21_smartcalc_archive/
	tar cvzf s21_smartcalc_archive.tgz s21_smartcalc_archive/

test: s21_smartcalc.a
	$(CC) $(CFLAGS) Tests/s21_smartcalc_test.c s21_smartcalc.a $(C_LIBS) -o test
	./test
	rm -rf *.o

s21_smartcalc.a: $(OBJECTS)
	ar rcs s21_smartcalc.a $(OBJECTS)
	ranlib s21_smartcalc.a
	rm -rf *.o

gcov_flag:
	$(eval CFLAGS += --coverage)

gcov_report: clean gcov_flag test
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf *.gcno *.gcda *.gcov

style:
	clang-format -n $(SOURCES) Tests/*.c --style=google

clean:
	rm -rf *.a *.o Tests/*.o test *.a *.gcno *.gcda *.gcov *.info *.tgz
	-rm -rf s21_smartcalc_archive

rebuild: clean all
