BUILD_DIR = build

all: test

test:
	mkdir -p $(BUILD_DIR)
	cmake . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR) tests
	./build/tests

clang:
	clang-format -n test/*.cc containers/* containers_plus/*

valgrind:
	valgrind --leak-check=full ./build/tests

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all test clang valgrind clean
