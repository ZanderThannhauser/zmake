
CPPFLAGS += -D _GNU_SOURCE
CPPFLAGS += -I .

CFLAGS += -Wall -Werror -Wfatal-errors
CFLAGS += -Wno-unused-result

LDLIBS += -lm
LDLIBS += -lgmp
LDLIBS += -lgdbm

buildtype ?= release

ifeq ($(buildtype), release)
CPPFLAGS += -D RELEASE

CFLAGS += -O2
CFLAGS += -flto

LDFLAGS += -flto=auto
LDFLAGS += -static

else ifeq ($(buildtype), test)
CPPFLAGS += -D TESTING

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else ifeq ($(buildtype), debug)
CPPFLAGS += -D DEBUGGING -D ZEBU_DEBUG

CFLAGS += -g
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-label

else
$(error "invalid buildtype!");
endif

on_error ?= do_nothing
ifeq ($(on_error), do_nothing)
ON_ERROR =
else ifeq ($(on_error), open_editor)
ON_ERROR += || ($$EDITOR $<; false)
else
$(error "invalid on_error option!");
endif

buildprefix = bin/$(buildtype)-build
depprefix   = dep/$(buildtype)-build

default: $(buildprefix)/zmake

ARGS += --verbose
#ARGS += --dry-run
#ARGS += --print-dependency-tree
#ARGS += --simulate-clean

ARGS += --jobs 1
#ARGS += --jobs 2
#ARGS += --jobs 10

ARGS += -C examples/sandbox

#ARGS += -C examples/abcdefg
#ARGS += -C examples/abcdefg a b
#ARGS += -C examples/abcdefg c

#ARGS += -C examples/sleep
#ARGS += -C examples/sleep 1

#ARGS += -f ./examples/zmake/makefile

run: $(buildprefix)/zmake
	$< $(ARGS)

valrun: $(buildprefix)/zmake
	valgrind $< $(ARGS)

valrun-stop: $(buildprefix)/zmake
	valgrind --gen-suppressions=yes -- $< ${ARGS}

valrun-leak: $(buildprefix)/zmake
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -- $< ${ARGS}

tracerun: $(buildprefix)/zmake
	strace $< $(ARGS)

PREFIX ?= ~/bin

install: $(buildprefix)/zmake
	@ mkdir -vp $(PREFIX)
	@ cp -vau $(buildprefix)/zmake $(PREFIX)/zmake

.PRECIOUS: %/

%/:
	@ mkdir -p $@

srclist.mk:
	@ echo "searching for source files..."
	@ find -name '*.c' -! -path '*/-*' | sort -V | sed 's/^/srcs += /' > $@

ifneq "$(MAKECMDGOALS)" "clean"
include srclist.mk
endif

objs := $(patsubst %.c,$(buildprefix)/%.o,$(srcs))
objs := $(patsubst %.S,$(buildprefix)/%.o,$(objs))

deps := $(patsubst %.c,$(depprefix)/%.d,$(srcs))
deps := $(patsubst %.S,$(depprefix)/%.d,$(deps))

$(buildprefix)/zmake: $(objs)
	@ echo "linking $@"
	@ $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

parse/zebu.c parse/zebu.h dep/parse/zebu.d: parse/zebu.zb | dep/parse/
	zebu -v -m --template=fileio -i $< -o parse/zebu -MF dep/parse/zebu.d

$(buildprefix)/%.o $(depprefix)/%.d: %.c | $(buildprefix)/%/ $(depprefix)/%/
	@ echo "compiling $<"
	@ $(CC) -c $(CPPFLAGS) $(CFLAGS) $< -MMD -o $(buildprefix)/$*.o -MF $(depprefix)/$*.d $(ON_ERROR)

clean:
	for l in $$(cat .gitignore); do rm -rvf $$l; done

ifneq "$(MAKECMDGOALS)" "clean"
include $(deps)
endif
















