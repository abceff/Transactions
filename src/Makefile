FLAGS = g++ -g -std=c++17
MAIN = ConsoleEngine/main.cpp
TESTS = Tests/GoogleTests.cpp
CONSOLE_ENGINE = ConsoleEngine/ConsoleEngine.cpp
UTILS = Utils/Utils.cpp
ABSTRACT_DATABASE = Databases/AbstractDatabase/AbstractDatabase.cpp
HASH_TABLE = Databases/HashTable/HashTable.cpp
SELF_BALANCING_BINARY_SEARCH_TREE = Databases/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.cpp
INVESTIGATION = InvestigationOfTimeCharacteristics/InvestigationOfTimeCharacteristics.cpp
CONSOLE_INTERFACE_BINARY = console_interface.out
TESTS_BINARY = tests.out
INVESTIGATION_BINARY = investigation.out

ifeq ($(filter arm64, $(shell uname -m)), arm64)
    GTEST = -I/usr/local/include -stdlib=libc++ /usr/local/lib/libgtest.a
else
    GTEST = -lgtest
endif

all: test

hash_table.a:
	g++ -c $(UTILS) $(ABSTRACT_DATABASE) $(HASH_TABLE)
	ar rcs hash_table.a Utils.o AbstractDatabase.o HashTable.o
	rm -rf Utils.o AbstractDatabase.o HashTable.o

self_balancing_binary_search_tree.a:
	g++ -c $(UTILS) $(ABSTRACT_DATABASE) $(SELF_BALANCING_BINARY_SEARCH_TREE)
	ar rcs self_balancing_binary_search_tree.a Utils.o AbstractDatabase.o SelfBalancingBinarySearchTree.o
	rm -rf Utils.o AbstractDatabase.o SelfBalancingBinarySearchTree.o

console_interface: console_interface_compile console_interface_run

console_interface_compile:
	$(FLAGS) $(MAIN) $(UTILS) $(CONSOLE_ENGINE) $(ABSTRACT_DATABASE) $(HASH_TABLE) $(SELF_BALANCING_BINARY_SEARCH_TREE) -o $(CONSOLE_INTERFACE_BINARY)

console_interface_run:
	./$(CONSOLE_INTERFACE_BINARY)

test: test_compile test_run

test_compile:
	$(FLAGS) $(GTEST) $(TESTS) $(UTILS) $(ABSTRACT_DATABASE) $(HASH_TABLE) $(SELF_BALANCING_BINARY_SEARCH_TREE) $(CONSOLE_ENGINE) -o $(TESTS_BINARY)

test_run:
	./$(TESTS_BINARY)

investigation: investigation_compile investigation_run

investigation_compile:
	$(FLAGS) $(INVESTIGATION) $(UTILS) $(ABSTRACT_DATABASE) $(HASH_TABLE) $(SELF_BALANCING_BINARY_SEARCH_TREE) $(CONSOLE_ENGINE) -o $(INVESTIGATION_BINARY)

investigation_run:
	./$(INVESTIGATION_BINARY)

leaks_check:
	CK_FORKS=no leaks -atExit -- ./$(TESTS_BINARY)

clean:
	rm -rf *.out* *.o *.a