# Target library
lib := libuthread.a
objs := queue.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD
CFLAGS += -g

# Debug flag
ifneq ($(V),1)
Q = @
endif

all: $(lib)


# Make libuthread.a
$(lib): $(objs)
	@echo "AR    $@"
	$(Q)ar rcs $@ $^
# # Make libuthread.a
# $(lib): $(objs)
# 	@echo "CC	$@"
# 	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

# Include dependencies
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

# Application objects to compile
objs := $(patsubst %.x,%.o,$(programs))

# Generic rule for compiling objects
%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

# Cleaning rule
clean: 
	@echo "CLEAN"
	$(Q)rm -rf $(lib) $(objs) $(deps)
## TODO: Phase 1
