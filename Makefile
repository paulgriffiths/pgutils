TESTMODULES := test_strings test_stringlist test_stringpair test_kvlist
TESTMODULES += test_stackint test_stackdouble test_queueint test_std_wrappers
TESTMODULES += test_dictstring
STRINGS_DEP := strings/strings.h strings/strings.c
STRINGS_SRC := strings/strings.c
TESTING_DEP := testing/testing.h testing/testing.c
TESTING_SRC := testing/testing.c
DATAS_DEP	:= datastruct/stringlist.h datastruct/stringlist.c
DATAS_DEP   += datastruct/stringpair.h datastruct/stringpair.c
DATAS_DEP   += datastruct/kvlist.h datastruct/kvlist.c
DATAS_DEP   += datastruct/stackint.h datastruct/stackint.c
DATAS_DEP   += datastruct/stackdouble.h datastruct/stackdouble.c
DATAS_DEP   += datastruct/queueint.h datastruct/queueint.c
DATAS_DEP   += datastruct/dictstring.h datastruct/dictstring.c
DATAS_SRC	:= datastruct/stringlist.c
DATAS_SRC   += datastruct/stringpair.c
DATAS_SRC   += datastruct/kvlist.c
DATAS_SRC   += datastruct/stackint.c
DATAS_SRC   += datastruct/stackdouble.c
DATAS_SRC   += datastruct/queueint.c
DATAS_SRC   += datastruct/dictstring.c
WRAPS_DEP	:= wrappers/std_wrappers.c wrappers/std_wrappers.h
WRAPS_DEP	+= wrappers/unix_wrappers.c wrappers/unix_wrappers.h
WRAPS_SRC	+= wrappers/std_wrappers.c wrappers/unix_wrappers.c
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

test_stackint: $(TESTDIR)/test_stackint.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_stackint $(TESTDIR)/test_stackint.c \
		$(DATAS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_stackdouble: $(TESTDIR)/test_stackdouble.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_stackdouble $(TESTDIR)/test_stackdouble.c \
		$(DATAS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_queueint: $(TESTDIR)/test_queueint.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_queueint $(TESTDIR)/test_queueint.c \
		$(DATAS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_std_wrappers: $(TESTDIR)/test_std_wrappers.c $(WRAPS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_std_wrappers $(TESTDIR)/test_std_wrappers.c \
		$(WRAPS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

test_dictstring: $(TESTDIR)/test_dictstring.c $(DATAS_DEP) $(TESTING_DEP) \
	$(STRINGS_DEP)
	$(CC) -o $(BINDIR)/test_dictstring $(TESTDIR)/test_dictstring.c \
		$(DATAS_SRC) $(TESTING_SRC) $(TEST_CFLAGS)

