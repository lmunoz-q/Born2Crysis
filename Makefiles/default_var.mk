UNAME := $(shell uname)
MAKEFILES_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
TEST_ARG +=
OBJ_DIR := .obj
DEP_DIR := .dep
TEST_SRCS := ./test.c
LD := gcc
PRE_TEST :=
BLACK_LIST_SRCS += cmake-build-debug/

ifeq ($(UNAME), Darwin)

PACKAGE_MANAGER_DIR = $(HOME)/.brew
PACKAGE_MANAGER = $(HOME)/.brew/bin/brew
PACKAGE_MANAGER_BIN = $(HOME)/.brew/bin
PACKAGE_MANAGER_LIB = $(HOME)/.brew/lib
PACKAGE_MANAGER_INC = $(HOME)/.brew/include

CMAKE = $(PACKAGE_MANAGER_BIN)/cmake

$(PACKAGE_MANAGER):
	git clone --depth=1 https://github.com/Homebrew/brew $(PACKAGE_MANAGER_DIR) && echo 'export PATH=$(PACKAGE_MANAGER_BIN):$(PATH)' >> $(HOME)/.zshrc && source $(HOME)/.zshrc && brew update

$(CMAKE):
	$(PACKAGE_MANAGER) install cmake

else

$(warning "non darwin system aren't supported for now")

endif

INC_DIR += inc $(PACKAGE_MANAGER_INC)
