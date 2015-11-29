TESTMODULES := test_strings test_stringlist test_stringpair test_kvlist
STRINGS_DEP := strings/strings.h strings/strings.c
STRINGS_SRC := strings/strings.c
TESTING_DEP := testing/testing.h testing/testing.c
TESTING_SRC := testing/testing.c
DATAS_DEP	:= datastruct/stringlist.h datastruct/stringlist.c
DATAS_DEP   += datastruct/stringpair.h datastruct/stringpair.c
DATAS_DEP   += datastruct/kvlist.h datastruct/kvlist.c
DATAS_SRC	:= datastruct/stringlist.c
DATAS_SRC   += datastruct/stringpair.c
DATAS_SRC   += datastruct/kvlist.c
CC			:= cc
BINDIR		:= bin
TESTDIR		:= tests
TEST_CFLAGS := -std=c99 -pedantic -Wall -I./


tests: $(TESTMODULES)

test_strings: $(TESTDIR)/test_strings.c $(STRINGS_DEP) $(TESTING_DEP)
	$(CC) -o $(BINDIR)/test_strings $(TESTDIR)/test_strings.c \
		$(STRINGS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_stringlist: $(TESTDIR)/test_stringlist.c $(DATAS_DEP) $(TESTING_DEP)
	$(CC) -o $(BINDIR)/test_stringlist $(TESTDIR)/test_stringlist.c \
		$(DATAS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_stringpair: $(TESTDIR)/test_stringpair.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_stringpair $(TESTDIR)/test_stringpair.c \
		$(DATAS_SRC) $(STRINGS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_kvlist: $(TESTDIR)/test_kvlist.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_kvlist $(TESTDIR)/test_kvlist.c \
		$(DATAS_SRC) $(STRINGS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)
