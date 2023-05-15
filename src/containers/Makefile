CC=g++
FLAGS=-Wall -Wextra -Werror -g --std=c++17
GCOV=-coverage
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lgtest -lpthread
endif

TEST_DIR=../test/

.PHONY: all clean test gcov_report

all: test clean

test: test_array #test_stack test_map test_tree test_vector test_list test_queue

test_map:
	$(CC) $(FLAGS) -I. map.h $(TEST_DIR)test_map.cc  -fsanitize=address -g $(TEST_FLAGS) -o test_map
	./test_map

test_tree:
	$(CC) $(FLAGS) -I. rb_tree.h $(TEST_DIR)test_tree.cc  -fsanitize=address -g $(TEST_FLAGS) -o test_rb_tree
	./test_rb_tree

test_list:
	$(CC) $(FLAGS) -I. list.h $(TEST_DIR)test_list.cc  $(TEST_FLAGS) -o test_list
	./test_list

test_set:
	$(CC) $(FLAGS) -I. set.h rb_tree.h $(TEST_DIR)test_set.cc $(TEST_FLAGS) -o test_set
	./test_set

test_stack:
	$(CC) $(FLAGS) -I. stack.h rb_tree.h $(TEST_DIR)test_stack.cc $(TEST_FLAGS) -o test_stack
	./test_stack

test_array:
	$(CC) $(FLAGS) -I../containers_plus ../containers_plus/array.h $(TEST_DIR)test_array.cc $(TEST_FLAGS) -o test_array
	./test_array

test_queue:
	$(CC) $(FLAGS) -I. queue.h $(TEST_DIR)test_queue.cc  $(TEST_FLAGS) -o test_queue
	./test_queue

test_vector:
	$(CC) $(FLAGS) -I. vector.h $(TEST_DIR)test_vector.cc  $(TEST_FLAGS) -o test_vector
	./test_vector

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

check:
	bash ../style.sh
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.h \
																		../tests/test_list.cc \
																		../tests/test_set.cc \
																		../tests/test_vector.cc

valgrind: test_list test_set test_vector
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test_list ./s21_test_set ./s21_test_vector
else
	leaks --atExit -- test_list ./s21_test_set ./s21_test_vector
endif


clean:
	rm -rf objects *.gcno *.gcda *.o *.info report test_queue test_vector test_set test_list \
	test_tree test_map test_stack test_array
