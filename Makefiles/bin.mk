ifeq ($(MAKEFILES_DIR), )
MAKEFILES_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
endif

include $(MAKEFILES_DIR)/common.mk

.srcs:
	printf "SRCS = " > .srcs
	find . -type f | grep "\.c$$" $(foreach V, $(BLACK_LIST_SRCS), | grep -v "$(V)") | cut -f2- -d/ | grep -v " " | sed "s/^/       /" | sed "s/$$/ \\\\/" | sed "1s/^       //" | sed "$$ s/..$$//" >> .srcs

$(NAME): $(CLIB) $(OBJS) | $(LDLIBS)
	@echo Compiling binary $@
	@$(LD) $(OBJS) $(CLIB) $| $(LDFLAGS) -o $@

CMake:
	echo "cmake_minimum_required(VERSION 3.13)\nproject($(NAME))\nset(CMAKE_CXX_STANDARD 14)\ninclude_directories($(INC_DIR))" > CMakeLists.txt
	$(foreach V, $(CLIB), echo "add_subdirectory($(dir $(V)))" >> CMakeLists.txt;)
	echo "add_executable($(NAME) $(SRCS))" >> CMakeLists.txt

test: $(NAME) FORCE
	$(PRE_TEST) ./$(NAME) $(TEST_ARG)

clean: FORCE
	@echo Removing $(OBJ_DIR)
	@$(RM) -rf $(OBJ_DIR)
ifneq ($(RECURSIVE), )
ifneq ($(CLIB), )
	@echo Recursive:
	@$(foreach V, $(dir $(CLIB)), $(MAKE) $(FORWARD) -C $(V) --no-print-directory -j clean;)
endif
endif

fclean: FORCE
	@echo Removing $(NAME) and $(OBJ_DIR)
	@$(RM) -rf $(OBJ_DIR) $(NAME)
ifneq ($(RECURSIVE), )
ifneq ($(CLIB), )
	@echo Recursive:
	@$(foreach V, $(dir $(CLIB)), $(MAKE) $(FORWARD) -C $(V) --no-print-directory -j fclean;)
endif
endif

include $(MAKEFILES_DIR)/common_second_pass.mk
