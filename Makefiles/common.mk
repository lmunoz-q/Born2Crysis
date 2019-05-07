.DEFAULT_GOAL := all

CFLAGS += -Wall -Wextra -Werror $($(UNAME)_CFLAGS) $(foreach V, $(INC_DIR), -I$(V))

LDFLAGS += $($(UNAME)_LDFLAGS)
LDLIBS += $($(UNAME)_LDLIBS)
SRCS += $($(UNAME)_SRCS)
TEST_SRCS += $($(UNAME)_TEST_SRCS)

ifneq ($($(UNAME)_CC), )
CC := $($(UNAME)_CC)
endif

ifneq ($($(UNAME)_LD), )
LD := $($(UNAME)_LD)
endif

ifneq ($($(UNAME)_AR), )
AR := $($(UNAME)_AR)
endif

ifeq ($(SRCS), )
#$(info no SRCS set, including .srcs)
include .srcs
endif

OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(patsubst %.c, $(DEP_DIR)/%.d, $(SRCS))

ifneq ($(DEBUG), )
FORWARD += DEBUG=1
PRE_TEST += #valgrind
CFLAGS += -g
endif

ifneq ($(SANITIZE), )
FORWARD += SANITIZE=1
CFLAGS += -g -fsanitize=address
LDFLAGS += -fsanitize=address
endif

ifneq ($(RECURSIVE), )
FORWARD += RECURSIVE=1
endif

#if neither DEBUG nor SANITIZE is set
ifneq ($(DEBUG), )
ifneq ($(SANITIZE), )
CFLAGS += -O3
endif
endif

.PRECIOUS: $(OBJ_DIR)/. $(OBJ_DIR)%/.

all: $(NAME) FORCE

$(OBJ_DIR)/.:
	@echo Preparing $(OBJ_DIR) to hold object files
	@mkdir -p $@

$(OBJ_DIR)%/.:
	@echo Preparing subdir $(patsubst %/., %, $@) to hold object files
	@mkdir -p $@

$(DEP_DIR)/.:
	@echo Preparing $(DEP_DIR) to hold dependency files
	@mkdir -p $@

$(DEP_DIR)%/.:
	@echo Preparing subdir $(patsubst %/., %, $@) to hold dependency files
	@mkdir -p $@

re: FORCE
	$(MAKE) $(FORWARD) fclean
	$(MAKE) $(FORWARD) all

#%.h:

.PHONY: FORCE all re clean fclean

FORCE:
