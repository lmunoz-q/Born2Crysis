#note: some of the variables listed below have default values set in Makefile.gen

#name of the author of the executable/library (used by the creation of the auteur file)
AUTHOR := hmartzol

#name of compiled file (if the 'a' extension is used, the makefile will use the library compilation mode)
NAME :=

#args passed to executable if executed from "make test"
EXEARGS :=

#path to folder containing source files, project header, resulting objects and rules respectively
#note: they can all be ".", but try to have a diferent path (ex: src, inc, .obj and .dep)
#note: SRCDIR, OBJDIR and DEPDIR must only contain one path, INCDIRS can have multiple paths
SRCDIR := src
INCDIRS := inc
OBJDIR := .obj
DEPDIR := .dep

#if the $(NAME) is a library, path to a file containing a main to test the library, ignored otherwise
MAIN := main.c

#name of files to compile without the extension (the path is relative to $(SRCDIR)) {if not set, make will include the file .items}
ITEMS :=

#Compilation flags (used for all cals of the compiler)
CFLAGS := -Wall -Wextra -Werror -O2 -g #-Wno-deprecated -Wno-deprecated-declarations -O3
#path to external includes directories
PINC := #../libft/inc ../libftx2/inc ../minilibx_X11 ../libftocl/inc ../libftjson/inc
#path to libs to compile
CLIB := #../libft ../libftx2 ../minilibx_X11 ../libftocl ../libftjson
#exact path of lib files to add in source
LIB := #../libftx2/libftx2.a ../libftocl/libftocl.a ../libftjson/libftjson.a ../libft/libft.a ../minilibx_X11/libmlx.a
#args passed to CC/ar on final link
LARGS := #-lOpenCL -ICL -lXext -lX11

#CFLAGS, PINC, CLIB, LIB and LARGS variable exist in two other version: Lvar and Mvar, respectively to be used on linux an mac
#example LLIB will be LIB only on linux, and MLIB will only be used on mac

#you can also change variables in Makefile.gen, changes will be global (on all makefiles including Makefile.gen)

#append the Makefile.gen (change path if necessary)
include ../Makefiles/Makefile.gen
