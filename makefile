CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror
GTEST = -lgtest

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LFLAGS = -lpthread
	OPEN = -xdg-open
else
	OPEN = -open
endif

TREE = self_balancing_binary_search_tree
APP = transactions

all : test build

build : $(APP)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(APP) : main.o main_window.o dialog_database.o dialog_research.o controller.o hash_table.a $(TREE).a
	$(CC) $^ -o $@ $(LFLAGS)

hash_table.a : hash_table.o
	ar rcs $@ $<
	ranlib $@

$(TREE).a : $(TREE).o
	ar rcs $@ $<
	ranlib $@

test : tests

tests : tests.o hash_table.a $(TREE).a
	$(CC) $(CFLAGS) $^ $(GTEST) $(LFLAGS) -o $@.out
	./$@.out

cppcheck :
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression --suppress=unreadVariable --suppress=knownConditionTrueFalse *.cpp *.hpp *.h *.inl

gcov : gcov_report

gcov_report : clean
	$(MAKE) CFLAGS="$(CFLAGS) --coverage" LFLAGS="$(LFLAGS) --coverage" tests
	lcov -t tests.out -o test.info -c -d . --no-external
	genhtml -o report test.info
	$(OPEN) report/index.html

clean : clean_report
	$(RM) *.a *.o *.out $(APP)

clean_report :
	$(RM) -rf *.gcda *.gcno *.info *.gch report

rebuild : clean all
