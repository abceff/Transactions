FLAGS = g++ -g #-std=c++17 -Wall -Wextra -Werror
MAIN = ConsoleEngine/main.cpp
TESTS = Tests/tests.cpp
CONSOLE_ENGINE = ConsoleEngine/ConsoleEngine.cpp
HASH_TABLE = Databases/HashTable/HashTable.cpp
INVESTIGATION = InvestigationOfTimeCharacteristics/InvestigationOfTimeCharacteristics.cpp
HASH_TABLE_BINARY = hash_table.out
TESTS_BINARY = tests.out
INVESTIGATION_BINARY = investigation.out

all: hash_table_compile

hash_table: hash_table_compile

hash_table: hash_table_compile hash_table_run

hash_table_compile:
	$(FLAGS) -DHASHTABLE $(MAIN) $(CONSOLE_ENGINE) $(HASH_TABLE) -o $(HASH_TABLE_BINARY)

hash_table_run:
	./$(HASH_TABLE_BINARY)

test: test_compile test_run

test_compile:
	$(FLAGS) -lgtest $(TESTS) $(HASH_TABLE) $(CONSOLE_ENGINE) -o $(TESTS_BINARY)

test_run:
	./$(TESTS_BINARY)

investigation: investigation_compile investigation_run

investigation_compile:
	$(FLAGS) $(INVESTIGATION) $(HASH_TABLE) $(CONSOLE_ENGINE) -o $(INVESTIGATION_BINARY)

investigation_run:
	./$(INVESTIGATION_BINARY)

clean:
	rm -rf *.out*