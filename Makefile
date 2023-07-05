.PHONY: all clean_g rebuild

CC=gcc -Wall -Wextra -Werror

FUNC_FILES_O=*.o
CHECKFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIBNAME=s21_math.a
GLFLAGS=--coverage
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: s21_math.a

s21_math.a: build_object_files_1 build_library clean_g

test: build_object_files build_library build_test start_tests gcov_report

style: 
	clang-format -style=google -n *.c *.h

build_object_files:
		$(CC) $(GCOVFLAGS) $(GLFLAGS) -c s21_math.c

build_object_files_1:
		$(CC) -c s21_math.c

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

build_test: 
		$(CC) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) test_func.c -L. s21_math.a  -o test_func

start_tests:
		./test_func

gcov_report: build_object_files build_library build_test start_tests
	lcov -o tests.info -c -d .  
	genhtml -o report tests.info
	open report/index.html
	make clean_g


clean:
	rm -rf *.o *.gcno *.gcov *.gcda *.a *.info test_func report

clean_g:
	rm -rf *.o *.gcno *.gcov *.gcda *.info *_test

rebuild:
	make clean_g
	make
