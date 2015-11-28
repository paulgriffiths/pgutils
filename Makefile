TESTMODULES := test_strings
STRINGS_DEP := strings/strings.h strings/strings.c
STRINGS_SRC := strings/strings.c
TESTING_DEP := testing/testing.h testing/testing.c
TESTING_SRC := testing/testing.c
CC			:= cc
BINDIR		:= bin
TESTDIR		:= tests
TEST_CFLAGS := -std=c99 -pedantic -Wall -I./


tests: $(TESTMODULES)

test_strings: $(TESTDIR)/test_strings.c $(STRINGS_DEP) $(TESTING_DEP)
	$(CC) -o $(BINDIR)/test_strings $(TESTDIR)/test_strings.c \
		$(STRINGS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)
