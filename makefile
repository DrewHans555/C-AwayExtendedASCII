.PHONY: clean
.PHONY: test
.PHONY: usage

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

PROGRAM_OUT_NAME = "cawayextendedascii"

PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/
PATHS = src/
PATHT = test/
PATHU = unity/src/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

SRC = $(wildcard $(PATHS)*.c)
SRCT = $(wildcard $(PATHT)*.c)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -DTEST

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
endif

$(PATHB)$(PROGRAM_OUT_NAME).$(TARGET_EXTENSION): $(SRC)
	$(LINK) -o $@ $^

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Test%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o
	$(LINK) -o $@ $^

$(PATHB)%.$(TARGET_EXTENSION): $(PATHO)%.o #custom
	$(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

usage:
	@echo 
	@echo "Usage:"
	@echo "	make"
	@echo "	---> will compile all code in /src into $(PATHB)$(PROGRAM_OUT_NAME).$(TARGET_EXTENSION)"
	@echo
	@echo "	make test"
	@echo "	---> will compile all testable modules with unity, run all tests, and then print test results"
	@echo
	@echo "	make usage"
	@echo "	---> will print this usage"
	@echo
	@echo "	make clean"
	@echo "	---> will remove all .o, .$(TARGET_EXTENSION), and .txt files in /build"
	@echo
